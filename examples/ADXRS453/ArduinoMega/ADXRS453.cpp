#include "ADXRS453.h"
#include "boards.h"
#include "Serial.h"
#include <util/delay.h>

int main() {
	hal::Serial0.init(115200);
    constexpr hal::ADXRS453 gyro1(hal::bsp::pins::D53);
    
    hal::Serial0.printf("Start \r\n");
    gyro1.init();
	
	gyro1.deviceStatus();
	bool status = gyro1.deviceStatus();
   	hal::Serial0.printf("Sensor init = %d\r\n", status);


    while (true) {
    	gyro1.getTemperature();
	    float temperature = gyro1.getTemperature();
	    gyro1.getRate();
	    float rate = gyro1.getRate();

	    hal::Serial0.printf("Temperature = %f;\tRate = %f\r\n", temperature, rate);
	    _delay_ms(1000);
	}
	
}
