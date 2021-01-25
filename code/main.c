 /**
 * @file
 * @brief       Stuff
 *
 * @author      Michael Mylius, Karl Klemann, Johannes Nodop
 *
 * @}
 */

#include <string.h>
#include <stdint.h>
#include <ctype.h>

#include "embUnit.h"
#include "embUnit/embUnit.h"
#include "fmt.h"
#include "cbor.h"
#include "phydat.h"
#include "saul_reg.h"
#include "net/loramac.h"     /* core loramac definitions */
#include "semtech_loramac.h" /* package API */
#include "thread.h"
#include "xtimer.h"
#include "bmx280.h"
#include "time.h"
#include "msg.h"

#include "net/gcoap.h"
//#include "kernel_types.h"
#include "shell.h"

#include "gps_data.h"
#include "periph/uart.h"
#include "cbor_util.h"
#include "led.h"
#include "periph/spi.h"

#define BUFSIZE 128
#define MSG_LENGTH 31
#define MAIN_QUEUE_SIZE (4)

bool DEBUG_GPS = false;


static msg_t _main_msg_queue[MAIN_QUEUE_SIZE];

int debug_toggle(int argc, char **argv);
extern int gcoap_cli_cmd(int argc, char **argv);
extern void gcoap_cli_init(void);

static const shell_command_t shell_commands[] = {
    { "coap", "CoAP example", gcoap_cli_cmd },
    { "debug", "Toggle debug prints", debug_toggle },
    { NULL, NULL, NULL }
};

struct gps_data gps_data = {0};

bool join_procedure_succeeded = false;
int spidev = SPI_DEV(0);


//#define RECV_MSG_QUEUE                   (4U)
//static msg_t _recv_queue[RECV_MSG_QUEUE];
//static char _recv_stack[THREAD_STACKSIZE_DEFAULT];
static char _send_stack[THREAD_STACKSIZE_DEFAULT];

// Downlink-Simulator EVERYTHING: 866474656D7064707265736367707364646174656474696D656368756D
// Downlink-Simulator TEMP & HUM: 826474656D706368756D   


semtech_loramac_t loramac;  /* The loramac stack device descriptor */
/* define the required keys for OTAA, e.g over-the-air activation (the
   null arrays need to be updated with valid LoRa values) */
static const uint8_t deveui[LORAMAC_DEVEUI_LEN] = { 0x00, 0xC4, 0x96, 0xFE, 0x9F, 0x57, 0x28, 0x26 };
static const uint8_t appeui[LORAMAC_APPEUI_LEN] = { 0x70, 0xB3, 0xD5, 0x7E, 0xD0, 0x03, 0x7B, 0xCE };
static const uint8_t appkey[LORAMAC_APPKEY_LEN] = { 0x5B, 0xF7, 0xA8, 0x26, 0x77, 0x3B, 0xE8, 0x15, 0x65, 0x55, 0x04, 0x06, 0xD8, 0xB3, 0xB6, 0xDD };

void sendMessage(char* message) {
    if (semtech_loramac_send(&loramac,
                             (uint8_t *)message, strlen(message)) != SEMTECH_LORAMAC_TX_DONE) {
        printf("Cannot send message '%s'\n", message);
    } else  {
        printf("Message '%s' was send!\n", message);
    }
}

static void *_periodic_send(void *arg){

    //msg_init_queue(_recv_queue, RECV_MSG_QUEUE);
    (void)arg;
    
    saul_reg_t *devTemp = saul_reg, *devHum = saul_reg, *devPres = saul_reg; 
    uint8_t buf[BUFSIZE] = {0};
    phydat_t res;
    CborEncoder encoder, mapEncoder;

    devTemp = saul_reg_find_type(SAUL_SENSE_TEMP);
    devHum = saul_reg_find_type(SAUL_SENSE_HUM);
    devPres = saul_reg_find_type(SAUL_SENSE_PRESS);

    //Checks sensors
    printf("Sensors present: Temp: %d, Hum: %d, Pres: %d\n", devTemp != NULL, devHum != NULL, devPres != NULL);

    while (1) {      
        cbor_encoder_init(&encoder, buf, sizeof(buf), 0);
        cbor_encoder_create_map(&encoder, &mapEncoder, CborIndefiniteLength);

        // Temperature
        saul_reg_read(devTemp, &res);
        addFloatToMap("temp", ((float) res.val[0]) / 100.0, &mapEncoder);
        //cbor_encoder_close_container_checked(&encoder, &mapEncoder);

        // Air Pressure
        addUInt64ToMap("pres", (uint64_t)bmx280_read_pressure((bmx280_t*)(devHum->dev)), &mapEncoder);
        //cbor_encoder_close_container_checked(&encoder, &mapEncoder);

        // Humidity
        saul_reg_read(devHum, &res);
        addFloatToMap("hum", ((float) res.val[0]) / 100.0, &mapEncoder);
        //cbor_encoder_close_container_checked(&encoder, &mapEncoder);
    
        gps_data = getGPSData();
        addFloatToMap("long", gps_data.gps.lng, &mapEncoder);
        addFloatToMap("lat", gps_data.gps.lat, &mapEncoder);
        addFloatToMap("vel", gps_data.gps.vel, &mapEncoder);
        
        addUInt64ToMap("d", gps_data.date.d, &mapEncoder);
        addUInt64ToMap("m", gps_data.date.m, &mapEncoder);
        addUInt64ToMap("y", gps_data.date.y, &mapEncoder);

        addUInt64ToMap("hour", gps_data.time.hour, &mapEncoder);
        addUInt64ToMap("min", gps_data.time.min, &mapEncoder);
        addUInt64ToMap("sec", gps_data.time.sec, &mapEncoder);
        addUInt64ToMap("mic", gps_data.time.mic, &mapEncoder);
        
        cbor_encoder_close_container_checked(&encoder, &mapEncoder);

        //uint8_t ret = semtech_loramac_send(&loramac, buf, MSG_LENGTH);
        if(semtech_loramac_send(&loramac, buf, cbor_encoder_get_buffer_size(&encoder, buf)) == SEMTECH_LORAMAC_TX_DONE){
            setLEDColor(0, BLUE);
            xtimer_msleep(500);
            setLEDColor(0, GREEN);
        }       
       // printHexFromBuffer(buf, &encoder);
        xtimer_sleep(10);
    }
    return NULL;
}

int debug_toggle(int argc, char **argv)
{
    if (strcmp(argv[1], "gps") == 0) {
        printf("Debug toggle: gps => ");
        if (DEBUG_GPS) {
            printf("false");
            DEBUG_GPS = false;
        } else {
            printf("true");
            DEBUG_GPS = true;
        }
        printf("\n");
    } else {
        printf("Debug toggle: debug target does not exist\n");
    }

    return 0;
}

int main(void)
{
    gpio_init(GPIO_PIN(0,2), GPIO_OUT);
    gpio_init(GPIO_PIN(0,4), GPIO_OUT);

    initLEDs(GPIO_PIN(0,23), GPIO_PIN(0,18));
    setLEDColor(0, YELLOW);

    setLEDColor(0, BLUE);
    setLEDColor(1, BLUE);
    setLEDColor(2, BLUE);
    setLEDColor(3, BLUE);
    setLEDColor(4, BLUE);
    setLEDColor(5, BLUE);

    // INIT GPS
    kernel_pid_t lora_tid = thread_create(_send_stack, sizeof(_send_stack), THREAD_PRIORITY_MAIN - 1, 0, _periodic_send, NULL, "Send Thread");
    //thread_create(_send_stack, sizeof(_send_stack), THREAD_PRIORITY_MAIN - 1, 0, _periodic_send, NULL, "Send Thread");
    initGPSData(lora_tid);

    /* for the thread running the shell */
    msg_init_queue(_main_msg_queue, MAIN_QUEUE_SIZE);
    gcoap_cli_init();
    char line_buf[SHELL_DEFAULT_BUFSIZE];

    /* 1. initialize the LoRaMAC MAC layer */
    semtech_loramac_init(&loramac);
    /* 2. set the keys identifying the device */
    semtech_loramac_set_deveui(&loramac, deveui);
    semtech_loramac_set_appeui(&loramac, appeui);
    semtech_loramac_set_appkey(&loramac, appkey);
    /* 3. join the network */
    if (semtech_loramac_join(&loramac, LORAMAC_JOIN_OTAA) != SEMTECH_LORAMAC_JOIN_SUCCEEDED) {
        puts("LoRa join procedure failed");
        setLEDColor(0, RED);
        //return 1;
    } else {
        puts("LoRa join procedure succeeded");
        join_procedure_succeeded = true;
        setLEDColor(0, GREEN);
    }
    /* 3.5 Join succeded, create thread */
    
    shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);
    return 0;
}
