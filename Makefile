CC = avr-gcc
PROCESSOR = atmega328p
FREQ = 16000000
AVRDUDE_CONFIG = arduino
AVRDUDE_PART = ATMEGA328P
AVRDUDE_PROGRAMMING_DEVICE = /dev/tty.usbmodem1411
AVRDUDE_BAUD = 115200

all: clean buildhex

main.o: 
	$(CC) -Os -DF_CPU=$(FREQ)UL -mmcu=$(PROCESSOR) -c -o main.o main.c

morse.o:
	$(CC) -Os -DF_CPU=$(FREQ)UL -mmcu=$(PROCESSOR) -c -o morse.o morse.c

clean:
	rm *.o *.hex morse

build: main.o morse.o
	$(CC) -mmcu=$(PROCESSOR) main.o morse.o -o morse

buildhex: build
	avr-objcopy -O ihex -R .eeprom morse morse.hex

flash: buildhex
	avrdude -F -V -c $(AVRDUDE_CONFIG) -p $(AVRDUDE_PART) -P $(AVRDUDE_PROGRAMMING_DEVICE) -b $(AVRDUDE_BAUD) -U flash:w:morse.hex
