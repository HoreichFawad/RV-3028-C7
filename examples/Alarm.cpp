#include "Alarm.h"

// Global objects
RV3028 rtc;
Ticker ticker;
EventFlags eventFlags;

// Constructor to initialize the interrupt pin and attach the ISR
Alarm::Alarm(PinName pin) : interruptPin(pin) {
    interruptPin.mode(PullUp);  // Set PullUp mode for the pin
    interruptPin.fall(callback(this, &Alarm::alarm_isr));  // Attach interrupt service routine
}

// Method to set the RTC time
bool Alarm::setTime(int sec, int min, int hour, int day, int date, int month, int year) {
    return rtc.setTime(sec, min, hour, day, date, month, year);
}

// Method to set and enable the alarm interrupt
void Alarm::setAlarm(int alm_minute, int alm_hour, int alm_day, bool is_weekday, uint8_t alm_mode) {
    rtc.enableAlarmInterrupt(alm_minute, alm_hour, alm_day, is_weekday, alm_mode);
}

// Method to clear the alarm interrupt flag
void Alarm::clearAlarmFlag() {
    rtc.clearAlarmInterruptFlag();
}

// Method to print the current time from the RTC
void Alarm::printCurrentTime() {
    if (!rtc.updateTime()) {
        printf("\nRTC failed to update");
    } else {
        char *currentTime = rtc.stringTimeStamp();
        printf("\nCurrent time is: %s", currentTime);
    }
}

// ISR for alarm interrupt that sets the alarm flag
void Alarm::alarm_isr() {
    eventFlags.set(ALARM_FLAG);
}


void trigger_print_time() {
    eventFlags.set(PRINT_TIME_FLAG);
}

// Function to encapsulate the main alarm logic
void runAlarmDemo() {
    printf("\nRTC Alarm Example\n");

    // Create an Alarm object with PA_5 as the interrupt pin
    Alarm alarm(PA_5);

    // Initialize RTC and set time
    rtc.begin();
    if (!rtc.begin()) {
        printf("\nSomething went wrong, check wiring");
        while (1);
    } else {
        printf("\nRTC online!");
    }

    wait_us(1000 * 1000);

    // Set RTC time
    if (!alarm.setTime(45, 59, 19, 5, 2, 8, 2019)) {
        printf("\nSomething went wrong setting the time");
    }

    // Set and enable the alarm (example: alarm for 20:00 on the 2nd day of the month)
    alarm.setAlarm(0, 20, 2, false, 0); // (minute, hour, day, is_weekday, mode)

    // Attach ticker to signal the main thread for printing time every second
    ticker.attach(&trigger_print_time, 1s);

    while (1) {
        // Wait for either alarm or print time event
        uint32_t flags = eventFlags.wait_any(ALARM_FLAG | PRINT_TIME_FLAG);

        // Print the current time when the flag is set
        if (flags & PRINT_TIME_FLAG) {
            alarm.printCurrentTime();
        }

        // Handle alarm event
        if (flags & ALARM_FLAG) {
            printf("\nALARM TRIGGERED!!!\n");
            alarm.clearAlarmFlag(); // Clear the alarm interrupt flag
        }
    }
}