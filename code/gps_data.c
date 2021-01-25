#include "gps_data.h"

#include <stdio.h>
#include <string.h>

#include "minmea.h"
#include "thread.h"
#include "periph/uart.h"
#include "string.h"
#include "stdint.h"
#include "config.h"
#include "led.h"

#define BAUDRATE (9600U)
#define DEV UART_DEV(1)

enum types{rmc, gga, gsa, gll, gst, gsv, vtg, zda};
static char strTypes[8][4] = {"RMC", "GGA", "GSA", "GLL", "GST", "GSV", "VTG", "ZDA"};
static kernel_pid_t rcv_tid;
static void rx_cb(void *uart, uint8_t c);

struct gps_data getGPSData(void) {
    msg_t msg;
    char buff[100] = {0};
    char sentences[4][100] = {0}; // {{rmc}, {gll}, {vtg}, {gsv}}
    int i = 0;
    bool lock[5] = {true, true, true, true, true}; // {rmc, gll, vtg, gsv, gsa}

    while (lock[0] || lock[1] || lock[2] || lock[3]) {
        msg_receive(&msg);
        
        if ((((char)msg.content.value) == '$')) {
            if (strstr(buff, strTypes[rmc])) {
                buff[i] = '\0';
                if (DEBUG_GPS) printf("NMEA: %s", buff);
                memcpy(sentences[0], buff, 100);
                lock[0] = false;
            }
            else if (strstr(buff, strTypes[gll])) {
                buff[i] = '\0';
                if (DEBUG_GPS) printf("NMEA: %s", buff);
                memcpy(sentences[1], buff, 100);
                lock[1] = false;
            }
            else if (strstr(buff, strTypes[vtg])) {
                buff[i] = '\0';
                if (DEBUG_GPS) printf("NMEA: %s", buff);
                memcpy(sentences[2], buff, 100);
                lock[2] = false;
            }
            else if (strstr(buff, strTypes[gsv])) {
                buff[i] = '\0';
                if (DEBUG_GPS) printf("NMEA: %s", buff);
                memcpy(sentences[3], buff, 100);
                lock[3] = false;
            }
            else if (strstr(buff, strTypes[gsa])) {
                buff[i] = '\0';
                if (DEBUG_GPS) printf("NMEA: %s", buff);
                lock[4] = false;
            }
            memset(buff, 0, 100);
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

    struct minmea_sentence_gsv sgsv;
    minmea_parse_gsv(&sgsv, sentences[3]);
    data.n_satellites = (uint8_t) sgsv.total_sats;
    if(data.n_satellites >= 5){
        setLEDColor(1, GREEN, 255);
    } else if(data.n_satellites > 0) {
        setLEDColor(1, ORANGE, 255);
    } else {
        setLEDColor(1, RED, 255);
    }

    /* printf("NMEA: %s \n", sentences[0]);
    printf("NMEA: %s \n", sentences[1]);
    printf("NMEA: %s \n", sentences[2]); */
    if (DEBUG_GPS) {
        printf("Date: day: %d, month: %d, year: %d\n", 
        data.date.d, data.date.m, data.date.y);
        printf("Time: hour: %d, min: %d, sec: %d, mircosec: %d\n", 
        data.time.hour, data.time.min, data.time.sec, data.time.mic);
        printf("GPS: long: %f, lat: %f, speed %f\n", 
        data.gps.lng, data.gps.lat, data.gps.vel);
        printf("\n\n");
    }

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