//  This example shows how to set the Backup Switchover Mode of RTC RV-3028-C7. 

#include <rv3028.h>

RV3028 rtc;

int BackupSwitchOverModes() {

  printf("\nBackup Switchover Mode - RTC Example");

  if (rtc.begin() == false) {
    printf("\nSomething went wrong, check wiring");
    while (1);
  }
  else
    printf("\nRTC online!");
  
  
  //Backup Switchover Mode
  printf("\nConfig EEPROM 0x37 before: %d",rtc.readConfigEEPROM_RAMmirror(0x37));

  rtc.setBackupSwitchoverMode(0);   //Switchover disabled
//   rtc.setBackupSwitchoverMode(1); //Direct Switching Mode
//   rtc.setBackupSwitchoverMode(2); //Standby Mode
//   rtc.setBackupSwitchoverMode(3); //Level Switching Mode (default)
    
  printf("\nConfig EEPROM 0x37 after: %d\n",rtc.readConfigEEPROM_RAMmirror(0x37));
  
  //For more information see https://www.microcrystal.com/fileadmin/Media/Products/RTC/App.Manual/RV-3028-C7_App-Manual.pdf#page=45
}