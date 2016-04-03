#include "Serial.h"

int main() {
	Serial0.begin(9600);
	while(1) {
		Serial0.print_byte(Serial0.read_byte());
	}
}