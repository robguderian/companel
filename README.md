# The boy's Com Panel
Rasperry pi communication panel for my boy. Uses a n by n LED array,
reassigning the lights as buttons are mashed.


## Project Goals

Build a scalable platform for teaching programming and electronics to my kid.
The concept is that I'll build a Star-trek original series inspired com-panel.
When the keyboard is mashed, update the LED array with a new setting.

Then, let the boy play with it. The dream is that he'll become interested in either
programming, or electronics.

If he gets interested in programming:

- Change randomization. Add blinking LEDs.
- pre-set images in the LED array, choose them with certain keystrokes
- Animate the LED array, change it to pre-set animations
- Make it internet connected, changable via a website.
    - Use polling
    - Use MQTT

If he gets interested in electronics:

- Add more LEDs with a multiplexer
- Add EL wire

## Components

The components are fairly simple:

- old keyboard. I was paritially inspired by a broken keyboard I have.
- a raspberry pi. The code can work with any setup, but the pins will change,
  but, that's only on the electronics side. The pin mapping will help you out here.
- LEDs, wire, and resistors.

## Contributing

This is a funny one. The whole idea is that this is a starting block.
Please feel free to add ideas for the extensions. We can even add a
forked project section to the readme.

Overall, I'm open to ideas on how to grow this, but still keep it a challenge.

## References

I used http://www.appelsiini.net/2011/how-does-led-matrix-work
as a reference. I used common-row anode as the matrix setup, since
it made more sense in my head.

The code in wrote in the tutorial was written in wiring for Arduino.
I modified the code to work with [Wiring Pi](http://wiringpi.com/) which 
uses the arduino wiring as inspiration/a starting point. Realistically,
it's in C.

