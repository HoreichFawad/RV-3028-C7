#ifndef ALARM_H
#define ALARM_H

#include <rv3028.h>
#include "mbed.h"

// Define the event flags for the alarm and print events
#define ALARM_FLAG 0x01
#define PRINT_TIME_FLAG 0x02

class Alarm {
public:
    // Constructor
    Alarm(PinName pin);

    // Set the RTC time
    bool setTime(int sec, int min, int hour, int day, int date, int month, int year);

    // Set and enable the alarm interrupt
    void setAlarm(int alm_minute, int alm_hour, int alm_day, bool is_weekday, uint8_t alm_mode);

    // Clear the alarm interrupt flag
    void clearAlarmFlag();

    // Print the current RTC time
    void printCurrentTime();

private:
    InterruptIn interruptPin; // Pin for the alarm interrupt

    // ISR for alarm interrupt
    void alarm_isr();
};

#endif // ALARM_H
