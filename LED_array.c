#include <stdint.h>
#include <stdio.h>
#include <wiringPi.h>

#define numrows 2
#define numcols 2

// assign the gpio pins - basically a mapping
uint8_t row_pins[numrows]    = { 0, 1};
uint8_t column_pins[numcols] = { 2, 3};


static void init(void) {

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
}

void draw(uint8_t buffer[numrows][numcols], unsigned int delaytime) {

    for (uint8_t row=0; row<numrows; ++row) {
        /* Connect or disconnect columns as needed. */
        for (uint8_t column=0; column<numcols; ++column) {
            digitalWrite(column_pins[column], buffer[row][column]);
        }

        /* Turn on whole row. */
        digitalWrite(row_pins[row], HIGH);

        delay(100);

        /* Turn off whole row. */
        digitalWrite(row_pins[row], LOW);
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
            delay(5000);
            // reset
            digitalWrite(row_pins[row], LOW);
            digitalWrite(column_pins[col], HIGH);

        }
    }
}

int main(void) {
    wiringPiSetup();
    // TODO: Set a default pattern
    init();
    printf("Starto\n");
    // do some interesting startup sequence
    while (1) {
        iterate();
    }


    // show the pattern
    // change on key input

    return 0;
}
