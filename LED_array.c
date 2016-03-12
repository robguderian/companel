#include <stdint.h>
#include <stdio.h>
#include <wiringPi.h>

// for reading from stdin non-blocking
#include <curses.h>

// stuff for randomization
#include <time.h>
#include <stdlib.h>

#define numrows 8
#define numcols 18

// nice output to console, but slows the LED refresh
// set to 1 for output, 0 for no output
#define DEBUG 0

// change interval in seconds
#define changeInterval 1
#define debounceInterval 5

// assign the gpio pins - basically a mapping
uint8_t row_pins[numrows]    = { 3, 5, 7, 8, 10, 11, 12, 13};
uint8_t column_pins[numcols] = { 15, 18, 16, 19, 23, 24, 21, 22, 26, 29, 31, 32, 33, 35, 36, 37, 38, 40};


static void init(uint8_t pattern[numrows][numcols]) {

    // seed random generator
    srand(time(NULL));

    /* Turn all columns off by setting then low. */
    for (uint8_t x=0; x<numcols; x++) {
        pinMode(column_pins[x], OUTPUT);
        digitalWrite(column_pins[x], HIGH);
    }

    /* Turn all rows off by setting then high. */
    for (uint8_t y=0; y<numrows; y++) {
        pinMode(row_pins[y], OUTPUT);
        digitalWrite(row_pins[y], LOW);
    }

    // create a default pattern
    for (uint8_t row=0; row<numrows; ++row)
        for (uint8_t column=0; column<numcols; ++column)
            pattern[row][column] = 1; 
}

void draw(uint8_t buffer[numrows][numcols]) {
    /* draw the pattern on the LEDs, and to console */

    for (uint8_t row=0; row<numrows; ++row) {
        /* Connect or disconnect columns as needed. */
        for (uint8_t column=0; column<numcols; ++column) {
            // could be optimized. Written for clarity
            // the LEDs are lit when the column is grounded, that is
            // LOW is written to them.
            if (buffer[row][column] == 1)
                digitalWrite(column_pins[column], LOW);
            else
                digitalWrite(column_pins[column], HIGH);
        }

        /* Turn on whole row. */
        digitalWrite(row_pins[row], HIGH);

        delay(1);

        /* Turn off whole row. */
        digitalWrite(row_pins[row], LOW);
    }
    if (DEBUG)
        printf("\n");
}

void cylon(){
    printf("cylon!\n");
    for (uint8_t col = 0; col < numcols; col++)
        digitalWrite(column_pins[col], HIGH);
    for (uint8_t row = 0; row < numrows; row++)
        digitalWrite(row_pins[row], HIGH);
    for (uint8_t col = 0; col < numcols; col++)
    {
        digitalWrite(column_pins[col], LOW);
        printf("%d\n", col);
        delay(100);
        // reset
        digitalWrite(column_pins[col], HIGH);
    }
    for (int col = numcols - 1; col >=0 ; col--)
    {
        digitalWrite(column_pins[col], LOW);
        printf("%d\n", col);
        delay(100);
        // reset
        digitalWrite(column_pins[col], HIGH);
    }

}

void iterate(){
    for (uint8_t row = 0; row < numrows; row++)
    {
        for(uint8_t col = 0; col < numcols; col++)
        {
            // light up light at row:col only.
            digitalWrite(row_pins[row], HIGH);
            digitalWrite(column_pins[col], LOW);
            printf("%d:%d\n", row, col);
            delay(10);
            // reset
            digitalWrite(row_pins[row], LOW);
            digitalWrite(column_pins[col], HIGH);

        }
    }
}

void randomize(uint8_t pattern[numrows][numcols]) {
    // change the pattern we want to show
    for (uint8_t row=0; row<numrows; ++row) {
        for (uint8_t column=0; column<numcols; ++column) {
            // rand() returns number between 0 and RAND_MAX
            // mod 2 will give us a 0 (off) or 1 (on)
            pattern[row][column] = (uint8_t)rand()%2;
        }
    }
}


int main(void) {
    // pattern array - use stack-based array, pass by reference
    // Set a default pattern
    uint8_t pattern[numrows][numcols];

    // time holder. Change random pattern every so often
    time_t lastchange = 0;


    wiringPiSetupPhys();
    init(pattern);
    //WINDOW *w = initscr();
    cbreak();
    //nodelay(w, TRUE);

    printf("Starto\n");
    // do some interesting startup sequence
    for (int i = 0; i < 3; i++) 
        iterate();
    for (int i = 0; i < 2; i++) 
        cylon();


    // show the pattern
    // change on key input
    int count = 0;
    while (1) {
        if (changeInterval < time(NULL) - lastchange || (getch() > 0 && debounceInterval < count))
        {
            printf("Randomizing\n");
            uint8_t rando = (uint8_t)rand()%100;
            if (rando < 5)
                cylon();
            else if (rando < 10)
                iterate();
            else
                randomize(pattern);
            lastchange = time(NULL);
            count = 0;
        }
        count++;
        draw(pattern);
    }
    // we can't get here... but for completeness.
    endwin();
    return 0;
}
