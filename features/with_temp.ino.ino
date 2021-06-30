#include <AverageThermocouple.h>
#include <MAX6675_Thermocouple.h>
#include <SmoothThermocouple.h>
#include <Thermocouple.h>
#include <LiquidCrystal.h>




// ThermoCouple
int thermo_so_pin  = 10;
int thermo_cs_pin  = 9;
int thermo_sck_pin = 8;

int relay_pin = 7; 

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2; 

float val = 0;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
MAX6675_Thermocouple thermocouple(thermo_sck_pin, thermo_cs_pin, thermo_so_pin);
  
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
//  pinMode(thermo_vcc_pin, OUTPUT); 
//  pinMode(thermo_gnd_pin, OUTPUT); 
//  digitalWrite(thermo_vcc_pin, HIGH);
//  digitalWrite(thermo_gnd_pin, LOW);
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  val = thermocouple.readCelsius();
  lcd.print(val);
  // print the number of seconds since reset:

  if (val < 90){
    digitalWrite(relay_pin, HIGH);
  }
  else{
    digitalWrite(relay_pin, LOW);
  }

  delay(1000);
}
