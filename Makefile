blink: LED_array.c
	gcc -o blink LED_array.c -lwiringPi -std=c99  -lcurses

clean:
	rm blink
