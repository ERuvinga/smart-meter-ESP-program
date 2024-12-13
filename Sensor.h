// Sensor Datas
#include <FlowSensor.h>

//Flow Senesor Datas
uint16_t type = YFS201; // type : Sensor type or pulse/liter
// uint16_t type = 450;

uint8_t pin_01 = 14; // pin D5 : interrupt pin
uint8_t pin_02 = 12; // pin D6 : interrupt pin

// define sensor 
FlowSensor Sensor_01(type, pin_01);
FlowSensor Sensor_02(type, pin_02);

void readCounterDatas() {
    Sensor_01.read();
    Sensor_02.read();
}

void resetCounterDatas() { // reset conter datas
    Sensor_01.getPulse();
    Sensor_02.getPulse();

    // reset Volumes datas
    Sensor_01.resetVolume();
    Sensor_02.resetVolume();

}
