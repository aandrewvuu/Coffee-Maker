#include <AverageThermocouple.h>
#include <MAX6675_Thermocouple.h>
#include <SmoothThermocouple.h>
#include <Thermocouple.h>
#include <LiquidCrystal.h>
#include <HX711_ADC.h>
#include <EEPROM.h>


// ThermoCouple
int thermo_so_pin  = 10;
int thermo_cs_pin  = 9;
int thermo_sck_pin = 8;

int relay_pin = 7; 

int HX711_dout = 6, HX711_sck = 7;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2; 

const int calVal_eepromAdress = 0;
unsigned long t = 0;

float val = 0;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
MAX6675_Thermocouple thermocouple(thermo_sck_pin, thermo_cs_pin, thermo_so_pin);
HX711_ADC LoadCell(HX711_dout, HX711_sck);
  
void setup() {
  Serial.begin(9600);

  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
  pinMode(relay_pin, OUTPUT);

  Serial.println();
  Serial.println("Starting...");

  LoadCell.begin();
  float calibrationValue; // calibration value (see example file "Calibration.ino")
  //calibrationValue = 696.0; // uncomment this if you want to set the calibration value in the sketch
#if defined(ESP8266)|| defined(ESP32)
  //EEPROM.begin(512); // uncomment this if you use ESP8266/ESP32 and want to fetch the calibration value from eeprom
#endif
  EEPROM.get(calVal_eepromAdress, calibrationValue); // uncomment this if you want to fetch the calibration value from eeprom

  unsigned long stabilizingtime = 2000; // preciscion right after power-up can be improved by adding a few seconds of stabilizing time
  boolean _tare = true; //set this to false if you don't want tare to be performed in the next step
  LoadCell.start(stabilizingtime, _tare);
  if (LoadCell.getTareTimeoutFlag()) {
    Serial.println("Timeout, check MCU>HX711 wiring and pin designations");
    while (1);
  }
  else {
    LoadCell.setCalFactor(calibrationValue); // set calibration value (float)
    Serial.println("Startup is complete");
  }

}

void loop() {
  Serial.println("i am here 1");
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  val = thermocouple.readCelsius();
  lcd.print(val);
  if (val < 90){
    digitalWrite(relay_pin, HIGH);
  }
  else{
    digitalWrite(relay_pin, LOW);
  }
  Serial.println("i am here 2");
  static boolean newDataReady = 0;
  const int serialPrintInterval = 0; //increase value to slow down serial print activity

  // check for new data/start next conversion:
  if (LoadCell.update()) newDataReady = true;

  // get smoothed value from the dataset:
  float i = LoadCell.getData();
  Serial.print("Load_cell output val: ");
  Serial.println(i);
  newDataReady = 0;
  delay(1000);
}
