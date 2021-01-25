#ifndef GPS_DATA_H
#define GPS_DATA_H

#include "inttypes.h"
#include "float.h"
#include "thread.h"

extern bool DEBUG_GPS;

struct date {
    uint8_t d;
    uint8_t m;
    uint16_t y;
};

struct time {
    uint8_t hour;
    uint8_t min;
    uint8_t sec;
    uint32_t mic;
};

struct gps {
    float lng;
    float lat;
    float vel;
};

struct gps_data {
    struct gps gps;
    struct time time;
    struct date date;
    uint8_t n_satellites;
};

struct gps_data getGPSData(void);
void initGPSData(kernel_pid_t lora_tid);

#endif