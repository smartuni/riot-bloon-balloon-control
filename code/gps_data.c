#include "gps_data.h"

#include <stdio.h>
#include <string.h>

#include "minmea.h"
#include "thread.h"
#include "periph/uart.h"
#include "string.h"
#include "stdint.h"

#define BAUDRATE (9600U)
#define DEV UART_DEV(1)

enum types{rmc, gga, gsa, gll, gst, gsv, vtg, zda};
static char strTypes[8][4] = {"RMC", "GGA", "GSA", "GLL", "GST", "GSV", "VTG", "ZDA"};
static kernel_pid_t rcv_tid;
static void rx_cb(void *uart, uint8_t c);

struct gps_data getGPSData(void) {
    msg_t msg;
    char buff[100] = {0};
    char sentences[3][100]; // {{rmc}, {gll}, {vtg}}
    int i = 0;
    bool lock[3] = {false}; // {rmc, gll, vtg}

    while (!lock[0] && !lock[1] && !lock[2]) {
        msg_receive(&msg);
        if ((((char)msg.content.value) == '$')) {
            if (strstr(buff, strTypes[rmc])) {
                buff[i] = '\0';
                memcpy(sentences[0], buff, 100);
                lock[0] = true;
            }
            else if (strstr(buff, strTypes[gll])) {
                buff[i] = '\0';
                memcpy(sentences[1], buff, 100);
                lock[1] = true;
            }
            else if (strstr(buff, strTypes[vtg])) {
                buff[i] = '\0';
                memcpy(sentences[2], buff, 100);
                lock[2] = true;
            }
            i = 0;
        }
        buff[i] = (char)msg.content.value;
        i++;
    }

    struct gps_data data = {0};

    struct minmea_sentence_rmc srmc;
    minmea_parse_rmc(&srmc, sentences[0]); // rmc sentence
    data.date.d = (uint8_t)srmc.date.day;
    data.date.m = (uint8_t)srmc.date.month;
    data.date.y = (uint16_t)srmc.date.year;
    data.time.hour= (uint8_t)srmc.time.hours;
    data.time.min= (uint8_t)srmc.time.minutes;
    data.time.sec= (uint8_t)srmc.time.seconds;
    data.time.mic= (uint32_t)srmc.time.microseconds;

    struct minmea_sentence_gll sgll;
    minmea_parse_gll(&sgll, sentences[1]); // gll sentence
    data.gps.lng = minmea_tocoord(&sgll.longitude);
    data.gps.lat = minmea_tocoord(&sgll.latitude);

    struct minmea_sentence_vtg svtg;
    minmea_parse_vtg(&svtg, sentences[2]); // vtg sentence
    data.gps.vel = minmea_tofloat(&svtg.speed_kph);

    printf("-------Date-------\n");
    printf("day: %d, month: %d, year%d\n\n", 
        data.date.d, data.date.m, data.date.y);
    printf("-------Time-------\n");
    printf("hour: %d, min: %d, sec: %d, mircosec: %ld\n\n", 
        data.time.hour, data.time.min, data.time.sec, data.time.mic);
    printf("-------GPS-------\n");
    printf("long: %f, lat: %f, speed %f\n\n", 
        data.gps.lng, data.gps.lat, data.gps.vel);

    return data;
}

void initGPSData(kernel_pid_t lora_tid) {
    rcv_tid = lora_tid;
    uart_init(DEV, BAUDRATE, rx_cb, (void*)DEV);

    //const uint8_t command[] = "$PMTK225,9*22";
    /* const uint8_t command[] = "$PMTK161,0*28";
    uart_write(DEV, command, sizeof(command));

    msg_t msg;
    char buff[100] = {0};
    for (int i = 0; i < 100; i++) {
        msg_receive(&msg);
        if ((((char)msg.content.value) == '$')) {
            buff[i] = '\0';
            if (strstr(buff, "PMTK")) {
                printf("Command success: %s\n", buff);
                break;
            }
            i = 0;
        }
        buff[i] = (char)msg.content.value;
    } */
}

static void rx_cb(void *uart, uint8_t c)
{
    //A character was received on an UART interface and triggered
    //   this callback through an interruption, we forward it via a message
    //   to the main thread.
    msg_t msg;
    msg.type = (int)uart;
    msg.content.value = (uint32_t)c;
    msg_send(&msg, rcv_tid);
}