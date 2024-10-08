#include <rv3028.h>

RV3028 rtc;

// The below variables control what the date will be set to
int sec = 50;
int minute = 43;
int hour = 16;
int day = 4;
int date = 7;
int month = 10;
int year = 2024;

int runrv3028()
{
    rtc.begin();
    while (rtc.begin() == false)
    {
        printf("Something went wrong, check wiring");
        wait_us(100 * 1000);
    }
    printf("RTC online!");
    wait_us(100 * 1000);
    if (rtc.setTime(sec, minute, hour, day, date, month, year) == false)
    {
        printf("Something went wrong setting the time\n");
    }
    // rtc.set12Hour();
    while (1)
    {

        // PRINT TIME
        if (rtc.updateTime() == false) // Updates the time variables from RTC
        {
            printf("RTC failed to update\n");
        }
        else
        {
            char *currentTime = rtc.stringTimeStamp();
            int i = 0;
            printf("\nCurrent time is: ");
            while (currentTime[i] != '\0')
            {
                printf("%c", currentTime[i]);
                i++;
            }
            wait_us(1000 * 1000);
        }
    }
}