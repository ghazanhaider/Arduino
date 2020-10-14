/* ============================================
Code by Max B. 06.07.2014 written for Arduino Uno R3 building up on the I2C library and example code and the ReadWriteSDdFat Library and example code.
No copyrights are claimed.
===============================================*/

/* ============================================
I2Cdev device library code is placed under the MIT license
Copyright (c) 10/7/2011 by Jeff Rowberg <jeff@rowberg.net>

SD Library created   Nov 2010 by David A. Mellis, updated 2 Dec 2010 by Tom Igoe and modified by Bill Greiman 11 Apr 2011
The example code is in the public domain.
===============================================*/

//-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-MPU Init-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X
// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files for both classes must be in the include path of your project
//Pins:  SCL - A5  SDA - A4  INT - D2    XDA,XCL,ADO hanging
   #include "I2Cdev.h"
   #include "MPU6050.h"
   // Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation is used in I2Cdev.h
   #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
   #include "Wire.h"
   #endif
   MPU6050 accelgyro;
   int16_t ax, ay, az;
//-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-SD-Writer Init-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X
//Pins:  MOSI -resistor- D11    MISO - D12    CLK -resistor- D13    CS -resistor- D4    5V,W/P,C/D hanging

   const int chipSelect = 10;
   #include <SdFat.h>
   SdFat sd;
   SdFile myFile;
//-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X
    int i=0;
    long startupmillis;
    long time;

void setup() {
   // join I2C bus (I2Cdev library doesn't do this automatically)
   #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
       Wire.begin();
   #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
       Fastwire::setup(400, true);
   #endif

   Serial.begin(38400);
   
         /*while (!Serial) {
         }
         Serial.println("Type RAKATA to start");
         while (Serial.read() <= 0) {
         }
         delay(400);  // catch Due reset problem
         */
   
   // initialize Accelerometer
   Serial.println("Initializing accelerometer connection...");
   accelgyro.initialize();
   accelgyro.setFullScaleAccelRange(MPU6050_ACCEL_FS_8);
   // verify connection
   Serial.println("Testing connection...");
   Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  // initialize SD-Card
   Serial.println("Initializing Connection to SD-Card...");
   if (!sd.begin(chipSelect, SPI_FULL_SPEED)){
     sd.initErrorHalt();
   }
   else{
   Serial.println("Connection seems to be okay.");
   }
   if (!myFile.open("datalog.txt", O_RDWR | O_CREAT | O_AT_END)) {
      sd.errorHalt("SD Karte entfernt!");
   }
   Serial.println("Starting measurements...");
   startupmillis = millis();
   
   // use the code below to change accel/gyro offset values
   /*
   Serial.println("Updating internal sensor offsets...");
   accelgyro.setXAccelOffset(335);
   accelgyro.setYAccelOffset(-5631);
   accelgyro.setZAccelOffset(2250);
   Serial.print(accelgyro.getXAccelOffset()); Serial.print("\t"); // 335
   Serial.print(accelgyro.getYAccelOffset()); Serial.print("\t"); // -5631
   Serial.print(accelgyro.getZAccelOffset()); Serial.print("\t"); // 2250
   Serial.print("\n");
   */
}

void loop() {
 
 if(i==100){ myFile.sync(); i=0;}
 
 accelgyro.getAcceleration(&ax, &ay, &az);
 time = millis() - startupmillis;
 
 //Serial.print("t,ax,ay,az:\t");
 //Serial.print(time); Serial.print("\t");
 //Serial.print(ax); Serial.print("\t");
 //Serial.print(ay); Serial.print("\t");
 //Serial.println(az);
 
 myFile.print("t,ax,ay,az:\t");
 myFile.print(time); myFile.print("\t");
 myFile.print(ax); myFile.print("\t");
 myFile.print(ay); myFile.print("\t");
 myFile.println(az);        
 i++;
}
