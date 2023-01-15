
#include <HCSR04.h>
#include <MPU6050_tockn.h>
#include <Wire.h>
//#define offsetx
//#define offsety
//#define offsetz

#define SLAVE_ADDRESS 4
int leftMotorspeed,rightMotorspeed,servoAngle;
float offsetY = 2.16;
float offsetX = -2.81;
float offsetZ = -11.40;

HCSR04 hc(4, 5); //initialisation class HCSR04 (trig pin , echo pin)
MPU6050 mpu6050(Wire);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu6050.calcGyroOffsets(true);
  stop();
  spin90();
  forward_halfsec();
  //forward_onesec();
  spin90to180();
  stop();
  driveUntil10cm();
  stop();
  forward_halfsec();
  Wallrest();
  stop();


}

// Steering angle straight = 120
// note about functions
// Forward - (123,255,120)
// Backward - (-123,-255,120)


void loop() {
  // put your main code here, to run repeatedly:
  //int angle;
  //mpu6050.update();
  //angle = mpu6050.getAngleZ();
  //Serial.println(angle);
  sendData(0,0,160);

}


void forward_onesec(){
  int startTime = millis();
  while (millis() - startTime < 1000){
    // Drive forward
    sendData(135,255,120);
  }
  sendData(0,0,125);

}

void forward_halfsec(){
  int startTime = millis();
  while (millis() - startTime < 500){
    // Drive forward
    sendData(135,255,120);
  }
  sendData(0,0,125);

}

/*

void spin180(){
  unsigned long startTime = millis();  // record the start time
  // turn the car 90 degrees and time it:
  do{
    sendData(123,255,0)
    int angle = mpu6050.getAngleZ();
  }while(Angle != 90) // MPU not angle
  unsigned long elapsedTime = millis() - startTime;  // calculate the elapsed
  startTime2 = millis();
  while (angle != 180){
    // reverse motors
    int angle = mpu6050.getAngleZ()
    sendData(-123,-255,180);
    startTime2 = millis();
  }
}
*/
void spin90() {

    unsigned long startTime = millis();  // record the start time
    // turn the car 90 degrees and time it:
    int angle;
    do {
        // set the motor speeds to turn the car
        sendData(123,255,80);
        mpu6050.update();        
        angle = mpu6050.getAngleZ();
        Serial.println(angle);
    } while (angle < 90);
    
    unsigned long elapsedTime = millis() - startTime;  // calculate the elapsed time
    startTime = millis();
    // turn the car another 90 degrees:
}

void spin90to180(){
    unsigned long startTime = millis();  // record the start time
    // turn the car 90 degrees and time it:
    int angle;
    do {
        // set the motor speeds to turn the car
        sendData(-123,-255,160);
        mpu6050.update();        
        angle = mpu6050.getAngleZ();
        Serial.println(angle);
    } while (angle < 330);
}

/*
void spin180() {

    unsigned long startTime = millis();  // record the start time
    // turn the car 90 degrees and time it:
    int angle;
    do {
        // set the motor speeds to turn the car
        sendData(123,255,80);
        mpu6050.update();        
        angle = mpu6050.getAngleZ();
        Serial.println(angle);
    } while (angle < 90);
    
    unsigned long elapsedTime = millis() - startTime;  // calculate the elapsed time
    startTime = millis();
    // turn the car another 90 degrees:

    do {
        sendData(-123,-255,160);
        mpu6050.update();
        int angle = mpu6050.getAngleZ();
        Serial.println(angle);

    } while (millis() - startTime < elapsedTime);
}

*/
void driveUntil10cm() {
  float x;
  // keep driving until an object is 10cm away
  do{
    x = hc.dist();
    Serial.println(x);
    sendData(-135,-225,120);    
  }while(x > 10);
}


void Wallrest(){
  //perform a 90 to wall ( angle 270 )
    int startTime = millis();
    int dist;
  while ((millis() - startTime < 1000) && dist > 10 ){
    // Drive forwar
    dist = hc.dist();
    sendData(-125,-255,80);
    
  }
}



void sendData(int16_t leftMotorspeed, int16_t rightMotorspeed, int16_t servoAngle) {

  Wire.beginTransmission(SLAVE_ADDRESS); // Call slave

  Wire.write((byte)((leftMotorspeed & 0x0000FF00) >> 8));    // first byte of leftMotor_speed, containing bits 16 to 9
  Wire.write((byte)(leftMotorspeed & 0x000000FF));           // second byte of leftMotor_speed, containing bits 8 to 1
  Wire.write((byte)((rightMotorspeed & 0x0000FF00) >> 8));   // rest follows the same logic
  Wire.write((byte)(rightMotorspeed & 0x000000FF));          
  Wire.write((byte)((servoAngle & 0x0000FF00) >> 8));         
  Wire.write((byte)(servoAngle & 0x000000FF));               
  Wire.endTransmission();   // stop transmitting
}

void stop(){
  sendData(0,0,125);
}
