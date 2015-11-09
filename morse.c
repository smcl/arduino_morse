#include <avr/io.h>
#include <ctype.h>
#include <util/delay.h>
#include "morse.h"

/* start of LED/buzzer setup - change DDRB, DDB5, PORTB and PORTB5
   if you want to connect your output to something other than 
   the digital5 output.
*/
void morse_setup() {
  DDRB |= _BV(DDB5);
}

void key_down() {
  PORTB |= _BV(PORTB5);
}

void key_up() {
  PORTB &= ~ _BV(PORTB5);
}
/* ... end of LED/buzzer setup */

void key_press(int n) {
  _delay_ms(MORSE_UNIT);
  key_down();

  // loop needed, because _delay_ms() needs a const :-/
  int i;
  for(i=0; i<n; i++) {
    _delay_ms(MORSE_UNIT);
  }

  key_up();
}  

void dit() {
  key_press(1);
}

void dah() {
  key_press(3);
}

void morse_nop() {
  _delay_ms(MORSE_UNIT*3);
}

char *morse_translate(char c) {
  c = tolower(c);
  
  switch(c) {
  case 'a':
    return ".-";
  case 'b':
    return "-...";
  case 'c':
    return "-.-.";
  case 'd':
    return "-..";
  case 'e':
    return ".";
  case 'f':
    return "..-.";
  case 'g':
    return "--.";
  case 'h':
    return "....";
  case 'i':
    return "..";
  case 'j': 
    return ".---";
  case 'k':
    return "-.-";
  case 'l':
    return ".-..";
  case 'm':
    return "--";
  case 'n':
    return "-.";
  case 'o':
    return "---";
  case 'p':
    return ".--.";
  case 'q':
    return "--.-";
  case 'r':
    return ".-.";
  case 's':
    return "...";
  case 't':
    return "-";
  case 'u':
    return "..-";
  case 'v':
    return "...-";
  case 'w':
    return ".--";
  case 'x':
    return "-..-";
  case 'y':
    return "-.--";
  case 'z':
    return "--..";
  case '0':
    return "-----";
  case '1':
    return ".----";
  case '2':
    return "..---";
  case '3':
    return "...--";
  case '4':
    return "....-";
  case '5':
    return ".....";
  case '6':
    return "-....";
  case '7':
    return "--...";
  case '8':
    return "---..";
  case '9':
    return "----.";
  default:
    return " ";
  }
}

void morse_transmit(char ascii_char) {
  char *morse_char = morse_translate(ascii_char);
  
  do {
    
    switch(*morse_char) {
    case '.':
      dit();
      break;
    case '-':
      dah();
      break;
    default:
      morse_nop();
      break;
    }
  } while(*morse_char++);
}
