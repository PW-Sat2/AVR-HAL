#include <util/delay.h>
#include "boards/boards.h"
#include "periph/Serial.h"

int main() {            
	hal::Serial0.init(9600);
	while( true ) {
		for(int i = 0; i <= 255; ++i) {
			hal::Serial0.print_byte(i);
		}
		if( hal::Serial0.available() ) {
			break;
		}
	}
	while( true ) {
		hal::Serial0.print_byte(hal::Serial0.read_byte());
	}
}
