#line 1 "./Firmware/Test_Compass/I2CDriver_HMC5883L.pde"
/*******************************************
*   Sample sketch that configures an HMC5883L 3 axis
*   magnetometer to continuous mode and reads back
*   the three axis of data.
*******************************************/

#include <AP_Common.h>
#include <AP_Math.h>
#include <AP_Param.h>
#include <AP_Progmem.h>

#include <AP_HAL.h>
#include <AP_HAL_VRBRAIN.h>


  void setup() ;
  void loop() ;
#line 16 "./Firmware/Test_Compass/I2CDriver_HMC5883L.pde"
const AP_HAL::HAL& hal = AP_HAL_VRBRAIN;

#define HMC5883L  0x3C

void setup() {
    hal.console->printf_P(PSTR("Initializing HMC5883L at address %x\r\n"),
                                HMC5883L);

    uint8_t stat = hal.i2c->writeRegister(HMC5883L,(uint8_t)0x02,(uint8_t)0x00);
    if (stat == 0) {
        hal.console->printf_P(PSTR("successful init\r\n"));
    } else {
        hal.console->printf_P(PSTR("failed init: return status %d\r\n"),
                (int)stat);
        for(;;);
    }
    //hal.console->printf_P(PSTR("failed init: return status %d\r\n"),(int)stat);
}

void loop() {
    uint8_t data[6];
    //read 6 bytes (x,y,z) from the device
    uint8_t stat = hal.i2c->readRegisters(HMC5883L,0x03,6, data);

    if (stat == 0){
        int16_t x, y, z;
        x = (int16_t)data[0] << 8;
        x |= (int16_t)data[1];
        z = (int16_t)data[2] << 8;
        z |= (int16_t)data[3];
        y = (int16_t)data[4] << 8;
        y |= (int16_t)data[5];
        hal.console->printf_P(PSTR("x: %d y: %d z: %d \r\n"), -x, y, -z);
        hal.console->println();
    } else {
        hal.console->printf_P(PSTR("i2c error: status %d\r\n"), (int)stat);
    }
        hal.scheduler->delay(10);
}

AP_HAL_MAIN();
