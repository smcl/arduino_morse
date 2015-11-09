#include <util/delay.h>
#include "morse.h"

#define SECONDS 1000

char *blink_message = "hello world";

int main() {
  morse_setup();

  while(1) {
    char *c = blink_message;

    do {
      morse_transmit(*c);
    } while(*c++);

    _delay_ms(2*SECONDS);
  }
}
