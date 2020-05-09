#include "DCMotorControl.h"
#include "MPU9250.h"
#include "AHRSImu.h"


// an MPU9250 object with the MPU-9250 sensor on I2C bus 0 with address 0x68
MPU9250 IMU(Wire,0x68);
int status;

// char AccX[20];
// char AccY[20];
// char AccZ[20];
// char GyroX[20];
// char GyroY[20];
// char GyroZ[20];
// char MagX[20];
// char MagY[20];
// char MagZ[20];

long SensorReadCycle = 200000; // in micro seconds
long PreviousSensorReadCycle = 0; // in micro seconds

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); //PC
    // start communication with IMU 
  status = IMU.begin();
  
  if (status < 0) 
  {
    Serial.println("IMU initialization unsuccessful");
    Serial.println("Check IMU wiring or try cycling power");
    Serial.print("Status: ");
    Serial.println(status);
    while(1) {}
  }
  IMU.setAccelRange(MPU9250::ACCEL_RANGE_2G);
  IMU.setGyroRange(MPU9250::GYRO_RANGE_250DPS);
  IMU.setSrd(19);
  
  PreviousSensorReadCycle = micros();

}

void loop() {
  // put your main code here, to run repeatedly:
  if (micros() < PreviousSensorReadCycle)
  {
    PreviousSensorReadCycle = SensorReadCycle - (4294967295 - PreviousSensorReadCycle);
  }
  //IMU Read And Transmit logic
  if (micros() - PreviousSensorReadCycle >= SensorReadCycle)
  {
    IMU.readSensor();
    // display the data
    // dtostrf(IMU.getAccelX_mss(), 10, 7, AccX);
    // dtostrf(IMU.getAccelY_mss(), 10, 7, AccY);
    // dtostrf(IMU.getAccelZ_mss(), 10, 7, AccZ);
    // dtostrf(IMU.getGyroX_rads(), 10, 7, GyroX);
    // dtostrf(IMU.getGyroY_rads(), 10, 7, GyroY);
    // dtostrf(IMU.getGyroZ_rads(), 10, 7, GyroZ);
    // dtostrf(IMU.getMagX_uT(), 10, 7, MagX);
    // dtostrf(IMU.getMagY_uT(), 10, 7, MagY);
    // dtostrf(IMU.getMagZ_uT(), 10, 7, MagZ);
    ax = IMU.getAccelX_mss();
    ay = IMU.getAccelY_mss();
    az = IMU.getAccelZ_mss();
    gx = IMU.getGyroX_rads();
    gy = IMU.getGyroY_rads();
    gz = IMU.getGyroZ_rads();
    mx = IMU.getMagX_uT();
    my = IMU.getMagY_uT();
    mz = IMU.getMagZ_uT();
  }

}
