//built in library for managing I2C wiring 
#include <Wire.h>
//keypad library
#include <Keypad.h>
//LCD library
#include <LiquidCrystal_I2C.h>
//time module
#include <RTClib.h>
RTC_DS3231 rtc;

// constants for the rows and columns 
const byte ROWS= 4;
const byte COLS = 3;
// Array to represent the keys on the keypad
char hexaKeys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

// the pins connected to the arduino
byte rowPins[ROWS] = {9,8,7,6};
byte colsPins[COLS] = {5,4,3};

// creating an instance of keypad 
Keypad customkey = Keypad(makeKeymap(hexaKeys),rowPins,colsPins,ROWS,COLS);
//creating an instance of LCD
LiquidCrystal_I2C lcd(0x27,16,2);
//RFID Authorized UID (to add it to a database of authorized UIDs)
//String authorizedRFID = "12345";
//a list of authorized id (temporary database)
//String authorizedID[] = {"23495","12345","14102"};
//a list of pin code 
//String correctPins[] = {"1234","5678","9876"};
//an authorization bool for verification
//bool isAuthorized = false;
String enteredPin = "";
struct Worker {
  String RFID;
  String Pin;
  String name;
  String Scheduled_start;
  String Scheduled_end;
  String checkin;
  String checkout;
  bool isLate;
  bool leftEarly;
};

Worker workers[]= {
  {"12345","1234","Alice","08:00","18:00","","",false,false},
  {"67890","6789","Bob","08:00","18:00","","",false,false},
  {"34567","9182","Charlie","08:00","18:00","","",false,false}
};
// count for the worker loop 
const int workerCount = sizeof(workers)/sizeof(Worker);
// get time function in "HH:MM" format
String getTime() {
    DateTime now = rtc.now();
    char buffer[6];
    sprintf(buffer, "%02d:%02d", now.hour(), now.minute());
    return String(buffer);
}

//function for checking the pin code 
bool isGrantedfunc(String pin){
for (int i=0;i<workerCount;i++){
  if(workers[i].Pin == pin){
  
     return true;
  }
   else {
    return false;
  }}}
// Compare times (returns -1, 0, 1 for earlier, equal, later)
int compareTime(String time1, String time2) {
    int hour1 = time1.substring(0, 2).toInt();
    int min1 = time1.substring(3, 5).toInt();
    int hour2 = time2.substring(0, 2).toInt();
    int min2 = time2.substring(3, 5).toInt();
    if (hour1 < hour2 || (hour1 == hour2 && min1 < min2)) return -1;
    if (hour1 == hour2 && min1 == min2) return 0;
    return 1;
}

// function to handle all the workers 
void handleWorker(String scannedRFID){
for (int i=0;i<workerCount;i++){
  if(workers[i].RFID == scannedRFID){
    lcd.clear();
    lcd.print("Hello, " + workers[i].name + " enter your Pin code");
    char customKey = customkey.getKey();
  if(customKey){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(customKey);
    if (customKey){
    enteredPin+=customKey;
    lcd.setCursor(0,1);
    lcd.print(enteredPin);
    }
    if (enteredPin.length()==4){
   if(isGrantedfunc(enteredPin)){

    String currentTime = getTime();
    if(workers[i].checkin == ""){
      workers[i].checkin = currentTime;

      if (compareTime(currentTime,workers[i].Scheduled_start)>0){
        workers[i].isLate = true;
        lcd.clear();
        lcd.print("Late Check-in >:(");
      }
      else{
        lcd.clear();
        lcd.print("On Time :)");
      }
    }
    else{
      workers[i].checkout = currentTime;
      if (compareTime(currentTime, workers[i].Scheduled_end) < 0) {
                    workers[i].leftEarly = true;
                    lcd.clear();
                    lcd.print("Left Early!");
                } else {
                    lcd.clear();
                    lcd.print("Goodbye!");
                }
            }
    }
    else{
      lcd.clear();
      lcd.print("Access Denied");
    }
    enteredPin="";
  }
  else{
    lcd.clear();
    lcd.print("uncorrect Pin Code");  
    }
    enteredPin="";
    }
    else {
  lcd.clear();
  lcd.print("Unauthorized");
  
  }
  delay(2000);
  return;
}
lcd.clear();
    lcd.print("Unauthorized");
    delay(2000);
}
}


// bool isAuthorizedfunc(Worker worker){
// for (String id : authorizedID){
//   if(worker.RFID == id){
//     return true;
//   }
//   else {
//   return false;
// }}}
// function for Pin code 
// bool isGrantedfunc(Worker worker){
// for (String id : correctPins){
//   if (worker.Pin == id){
//     return true;
//   }
//   else {
//     return false;
//   }}}
// empty entered Pin
//String enteredPin = "";

void setup(){
  lcd.init();
  lcd.backlight();
  

  if (!rtc.begin()) {
        lcd.print("RTC not found!");
        while (1);
    }
    if (rtc.lostPower()) {
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }

    lcd.clear();
    lcd.print("Ready");
}

void loop(){
  //char customKey = customkey.getKey();
  //if(customKey){
    //lcd.clear();
    //lcd.setCursor(0,0);
    //lcd.print(customKey);
  //}

//scanned RFID (to change it with a actual scanned UID)
//String scannedRFID = "12345";

  // if (isAuthorizedfunc(scannedRFID)){
  //   lcd.clear();
  //   lcd.print("Enter PIN : ");
  //   char customKey = customkey.getKey();

  //   if (customKey){
  //     enteredPin+=customKey;
  //     lcd.setCursor(0,1);
  //     lcd.print(enteredPin);
  //   }
  //   // check if the Pin's length is 4
  //   if (enteredPin.length()==4){
  //     if(isGrantedfunc(enteredPin)){
  //       lcd.clear();
  //       lcd.print("Access Granted");
  //     }
  //     else {
  //       lcd.clear();
  //       lcd.print("Access Denied");
  //     }
  //     delay(2000);
  //     enteredPin=""; // initialize the pin to empty string 
  //   }
  // }
  // else {
  //   lcd.clear();
  //   lcd.print("Unauthorized");
  //   delay(2000);
  // }
  String scannedRFID = "12345";
  handleWorker(scannedRFID);
  delay(10000);
}

