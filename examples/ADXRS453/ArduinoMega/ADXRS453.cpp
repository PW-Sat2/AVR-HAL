#include "ADXRS453.h"
#include "boards.h"
#include "Serial.h"
#include <util/delay.h>

int main() {
	hal::Serial0.init(115200);
    constexpr hal::ADXRS453 gyro1(hal::bsp::pins::D53);
    
    hal::Serial0.printf("Start \r\n");
    gyro1.init();
	
	bool status = gyro1.deviceStatus();
   	hal::Serial0.printf("Sensor init = %d\r\n", status);


    while (true) {
	    float temperature = gyro1.getTemperature();
	    float rate = gyro1.getRate();
	    uint32_t sensor_data = gyro1.getSensorData();

	    hal::Serial0.printf("Temperature = %f;\t", temperature);
   	    hal::Serial0.printf("Rate = %f;\t", rate);
	    hal::Serial0.printf("Sensor data = %ul\r\n", sensor_data);

	    _delay_ms(500);
	}
	
}
