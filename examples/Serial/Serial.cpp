#include <util/delay.h>
#include "boards/boards.h"
#include "periph/Serial.h"

int main() {            
	Serial0.init(9600);

    while (true) {
		static int counter = 0;
		Serial0.printf("Counter value = %d\r\n", counter++);
        
        _delay_ms(200);
	}
}
