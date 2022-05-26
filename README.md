# Coffee Maker

As an avid coffee consumer, I always wanted to try different technques to make my coffee. Combine my love for coffee and my passion for engineering, I sought to engineer a coffee machine that would utilize the pour over techinque to consistently create a delicious and flavourful coffee. I will cover a step by step guide as well as share my thought process while tackling this project.

## Preliminary Brainstorming

This is a brief overview of the logic behind this:

![alt text](https://github.com/vua6/Coffee-Maker/blob/main/images/Logic.png?raw=true) 

This is a basic wiring diagram:

![alt text](https://github.com/vua6/Coffee-Maker/blob/main/images/Wiring.png?raw=true)

## Bill of Materials

| Item | Amount | 
| -----|--------|
|Arduino|1|
|IoT Relay|1|
|Pump|1|
|Kettle|1|
|Thermocouple|1|
|Load cell|1|
|Load cell ADC|1|
|Servo Motor|2|
|Plastic tubing|1|
|Copper Wire|1|
|Gasket|4|
|1/4 inch nuts|4|
|Brass nozzle fitting|1|
|Screws|8|

## Hardware Part

### Preparing the Kettle

1. Using a drill, drill 2 1/4 inch holes at the bottom of the kettle with the holes being seperated by at least 1 inch.
2. Put a rubber gasket on the thermocouple and then stick it into the kettle. Put a rubber gasket on the other side of the thermocouple and a 1/4 inch nut and tighten it so that the thermocouple is soundly installed
3. Similiarly, put a rubber gasket on the 1/4 inch brass nozzle fitting. Stick the fitting into the kettle. Put a rubber gasket on the other side of the brass fitting and a 1/4 inch nut and tighten it so that the nozzle fitting is secured in place.

### Preparing the frame, nozzle system, and load cell

1. Connect a sufficient amount of food safe and heat tolerant plastic piping between brass nozzle fitting and the pump.
2. Install the 2 servo motors with one servo motor installed to the arm of the second servo motor (refer to the image).
3. Connect plastic piping from the other end of the pump to the arm of the servo motor and tie it in place with a zip tie (again refer to the images mate).
4. Glue to the tip os the load cell a 5 inch diameter platform that the cup would be placed on. Glue to the other size of the load cell a shim to raise the load cell of the ground (Images again).

Images here

### Wiring

Wire everything according to the wiring diagram provided with the Arduino being the center of it all.

Images here

## Software Part

The code is located at: Coffee-Maker/full_proj/full_proj.ino

## conclusion

With the software and harware aspects of this project coming together, the coffee machine is complete and creates the most delicious coffee everyday.

Images here




