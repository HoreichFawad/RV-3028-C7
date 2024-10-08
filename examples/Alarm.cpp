//This example shows how to set alarm interrupts at RV-3028-C7 Real Time Clock.

#include <rv3028.h>
RV3028 rtc;

InterruptIn button(PA_5);
// The below variables control what the date will be set to
int sec = 45;
int minute = 59;
int hour = 19;
int day = 5;
int date = 2;
int month = 8;
int year = 2019;

// The below variables control what the alarm will be set to
int alm_minute = 0;
int alm_hour = 20;
int alm_date_or_weekday = 2;
bool alm_isweekday = false;
uint8_t alm_mode = 0;
/*********************************
  Set the alarm mode in the following way:
  0: When minutes, hours and weekday/date match (once per weekday/date)
  1: When hours and weekday/date match (once per weekday/date)
  2: When minutes and weekday/date match (once per hour per weekday/date)
  3: When weekday/date match (once per weekday/date)
  4: When hours and minutes match (once per day)
  5: When hours match (once per day)
  6: When minutes match (once per hour)
  7: All disabled – Default value
  If you want to set a weekday alarm (alm_isweekday = true), set 'alm_date_or_weekday' from 0 (Sunday) to 6 (Saturday)
********************************/
void alarm(){
    
}


int setAlarm()
{
    
    printf("\nRead/Write Time - RTC Example");
    rtc.begin();
    if (rtc.begin() == false)
    {
        printf("\nSomething went wrong, check wiring");
        while (1);
    }
    else
        printf("\nRTC online!");
    wait_us(1000 * 1000);

    if (rtc.setTime(sec, minute, hour, day, date, month, year) == false)
    {
        printf("\nSomething went wrong setting the time");
    }
    // Enable alarm interrupt
    rtc.enableAlarmInterrupt(alm_minute, alm_hour, alm_date_or_weekday, alm_isweekday, alm_mode);
    // rtc.disableAlarmInterrupt();  //Only disables the interrupt (not the alarm flag)
    button.fall(&alarm);
    while (1)
    {

        // PRINT TIME
        if (rtc.updateTime() == false) // Updates the time variables from RTC
        {
            printf("\nRTC failed to update");
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
    bool bitStatus=rtc.readAlarmInterruptFlag();
    // Read Alarm Flag
    if (bitStatus)
    {
        printf("\nALARM!!!!");
        wait_us(1000 * 1000);
        rtc.clearAlarmInterruptFlag();
    }
}
}