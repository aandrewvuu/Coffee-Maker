#include <Servo.h>

#include <AverageThermocouple.h>
#include <MAX6675_Thermocouple.h>
#include <SmoothThermocouple.h>
#include <Thermocouple.h>
#include <LiquidCrystal.h>
#include <Servo.h>
#include <math.h>

// Pins
int thermo_so_pin  = 10, thermo_cs_pin  = 9, thermo_sck_pin = 8;

int Xservo_pin = 2, Yservo_pin = 3;

int kettle_relay_pin = 7; 

int pump_relay_pin = 6;

//const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2; 

// Constants
float temp = 0;
int radius = 45, target_temp = 90;
//in millis
unsigned long duration = 2000;

//Initialize Devices
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
MAX6675_Thermocouple thermocouple(thermo_sck_pin, thermo_cs_pin, thermo_so_pin);
Servo Xservo;
Servo Yservo;
  
void setup() {
  Serial.begin(9600);
  

  Xservo.attach(Xservo_pin);
  Yservo.attach(Yservo_pin);

  
//  lcd.begin(16, 2);
//  // Print a message to the LCD.
//  lcd.print("hello, world!");
//  pinMode(thermo_vcc_pin, OUTPUT); 
//  pinMode(thermo_gnd_pin, OUTPUT); 
//  digitalWrite(thermo_vcc_pin, HIGH);
//  digitalWrite(thermo_gnd_pin, LOW);
}


void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
//  lcd.setCursor(0, 1);
  temp = temp_ctrl(kettle_relay_pin, target_temp);

//  lcd.print(val);

  if (temp > target_temp -2){

    servo_circle(Xservo, Yservo, radius, duration, pump_relay_pin);
    char input = check_next();
    exit(0);
  }
  delay(5);
}


void servo_circle(Servo Xservo, Servo Yservo, int radius, unsigned long duration, int pump_relay_pin){
  duration = duration + millis();
  boolean cycle = false;
  while(cycle == false){
    for (int i=0; i<360;i++){
      
      double radians = i * PI/180;
      double px = radius * cos(radians)+90;
      double py = radius * sin(radians)+90;
      Xservo.write(px);
      Yservo.write(py);
      Serial.print(px);
      Serial.print(py);
      Serial.print("\n");
      
      cycle = motor_ctrl(duration, pump_relay_pin);
      if (cycle == true) break;
      delay(5);
    }
  }
}

boolean motor_ctrl(unsigned long duration, int pump_relay_pin){
  unsigned long t = millis();

  if (duration > t){
    digitalWrite(pump_relay_pin, HIGH);
    return false;
  }
  else{
    digitalWrite(pump_relay_pin, LOW);
    return true;
  }
}

int temp_ctrl(int kettle_relay_pin, int target_temp){
  int val = thermocouple.readCelsius();
  
  if (val < target_temp + 2) digitalWrite(kettle_relay_pin, HIGH);
  
  else if (val > target_temp - 2) digitalWrite(kettle_relay_pin, LOW);

  return val;
}

char check_next(){
  boolean go_next = false;
  char input;
  Serial.print("Press t to go next: \n");
  while (go_next == false){
    input = Serial.read();
    delay(5);
    if (input == 't') go_next = true;
  }
  return input;
}
