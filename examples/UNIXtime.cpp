//This example shows how to set the UNIX time on the RTC, and how to read it.

#include <rv3028.h>
RV3028 rtc1;

//The below variable controls what the UNIX time will be set to
uint32_t UNIX = 1234567890;

int UNIXtime(){

printf("\nRead/Write UNIX Time - RTC Example");
    rtc1.begin();
  while (rtc1.begin() == false) {
    printf("\nSomething went wrong, check wiring");
    wait_us(1000*1000);
  }
  printf("\nRTC online!");

if (rtc1.setUNIX(UNIX) == false) {
          printf("\nSomething went wrong setting the time");
        }
while(1) {

  //PRINT TIME
  if (rtc1.updateTime() == false) //Updates the time variables from RTC
  {
    printf("\nrtc failed to update");
  } else {
    char* currentTime = rtc1.stringTimeStamp();
    int i = 0;
        printf("\nCurrent time is: ");
        while (currentTime[i] != '\0')
        {
            printf("%c", currentTime[i]);
            i++;
        }
    printf("\nUNIX Time: %u",rtc1.getUNIX());
  }
  wait_us(1000*1000);
}
}