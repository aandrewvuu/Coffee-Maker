#include <Servo.h>

#include <MAX6675_Thermocouple.h>
#include <SmoothThermocouple.h>
#include <Thermocouple.h>
#include <LiquidCrystal.h>
#include <Servo.h>
#include <math.h>

// Pins
int thermo_so_pin  = 10, thermo_cs_pin  = 9, thermo_sck_pin = 8;

int Xservo_pin = 2, Yservo_pin = 3;

int kettle_relay_pin = 5; 

int pump_relay_pin = 4;

int button_pin = 11, led_pin = 12;


// Constants
int radius1 = 30, radius2 = 15, radius3 = 0;
float target_temp = 90, temp =0;
//in millis
unsigned long duration1 = 3000, duration2 = 5000;
//duration1 ~ 
//duration2 ~ 180ml

//Initialize Devices
Thermocouple* thermocouple;
Servo Xservo;
Servo Yservo;
  
void setup() {
  Serial.begin(9600);
  
  thermocouple = new MAX6675_Thermocouple(thermo_sck_pin, thermo_cs_pin, thermo_so_pin);
  Xservo.attach(Xservo_pin);
  Yservo.attach(Yservo_pin);
  pinMode(pump_relay_pin, OUTPUT);
  pinMode(kettle_relay_pin, OUTPUT);
  pinMode(led_pin, OUTPUT);
  pinMode(button_pin, INPUT_PULLUP);
}


void loop() {
  temp_ctrl(kettle_relay_pin, target_temp);
  check_next(button_pin,led_pin);
  servo_circle(Xservo, Yservo, radius1, duration2, pump_relay_pin);
  check_next(button_pin,led_pin);
  servo_circle(Xservo, Yservo, radius1, duration1, pump_relay_pin);
  check_next(button_pin,led_pin);
  servo_circle(Xservo, Yservo, radius1, duration2, pump_relay_pin);
  check_next(button_pin,led_pin);
  servo_circle(Xservo, Yservo, radius3, duration2, pump_relay_pin);
  exit(0);
}


void servo_circle(Servo Xservo, Servo Yservo, int radius, unsigned long duration, int pump_relay_pin){
  duration = duration + millis();
  boolean cycle = false;
  while(cycle == false){
    for (int i=0; i<360;i++){
      
      double radians = 2*i * PI/180;
      double px = radius * cos(radians)+110;
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

void temp_ctrl(int kettle_relay_pin, float target_temp){
  while(temp < target_temp){
    temp = thermocouple->readCelsius();
    Serial.print(temp);
    Serial.print("\n");
    digitalWrite(kettle_relay_pin, HIGH);
    delay(500);
  }
  digitalWrite(kettle_relay_pin, LOW);
}

//int temp_check(int kettle_relay_pin, float target_temp){
//  temp = thermocouple->readCelsius();
//  Serial.print(val);
//  Serial.print("\n");
//  if (val < target_temp + 2) {
//    digitalWrite(kettle_relay_pin, HIGH);
//  }
//  
//  else if (val > target_temp - 2){
//    digitalWrite(kettle_relay_pin, LOW);
//  }
//
//  return temp;
//}



void check_next(int button_pin,int led_pin){
  int button_state = HIGH;
  while (button_state == HIGH){
    button_state = digitalRead(button_pin);
    digitalWrite(led_pin,HIGH);
    delay(10);
  }
  digitalWrite(led_pin,LOW);
}
