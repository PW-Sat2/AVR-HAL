#include <util/delay.h>
#include "boards/boards.h"
#include "periph/Serial.h"

int main() {            
	Serial0.init(9600);
	while( true ) {
		for(int i = 0; i <= 255; ++i) {
			Serial0.print_byte(i);
		}
		if( Serial0.available() ) {
			break;
		}
	}
	while( true ) {
		Serial0.print_byte(Serial0.read_byte());
	}
}
