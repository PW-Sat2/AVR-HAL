#include <util/delay.h>
#include "boards.h"
#include "Serial.h"

int main() {            
	hal::Serial0.init(9600);

    while (true) {
		static int counter = 0;
		hal::Serial0.printf("Counter value = %d\r\n", counter++);
        
        _delay_ms(200);
	}
}
