#include <rv3028.h>

RV3028 rtc;

int TrickleCharging() {

  printf("\nTrickle Charging - RTC Example");
  if (rtc.begin() == false) {
    printf("\nSomething went wrong, check wiring");
    while (1);
  }
  else
    printf("\nRTC online!");
  //Trickle Charger
  printf("\nConfig EEPROM 0x37 before: %d",rtc.readConfigEEPROM_RAMmirror(0x37));

//   rtc.enableTrickleCharge(TCR_3K);   //series resistor 3kOhm
  rtc.enableTrickleCharge(TCR_5K); //series resistor 5kOhm
  //rtc.enableTrickleCharge(TCR_9K); //series resistor 9kOhm
  //rtc.enableTrickleCharge(TCR_15K); //series resistor 15kOhm
  //rtc.disableTrickleCharge(); //Trickle Charger disabled

  printf("\nConfig EEPROM 0x37 after:%d \n",rtc.readConfigEEPROM_RAMmirror(0x37));

  //For more information see https://www.microcrystal.com/fileadmin/Media/Products/RTC/App.Manual/RV-3028-C7_App-Manual.pdf#page=48
}