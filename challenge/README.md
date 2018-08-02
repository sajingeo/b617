## the DC617 Challenge

### STEP1 
burn the HEX file on to your badge.

### STEP2
Start cracking!!

### Did you crack it?
You will receive a unique code if you do!!


## How to burn the hex?

### Program the IC (using Tiny ISP)
I used the Tiny programmer from sparkfun to program the IC, The ATTiny85v will work at 1.8v to 5v.
![Step 3](img/img3.JPG)

more details on the hookup here.
https://learn.sparkfun.com/tutorials/tiny-avr-programmer-hookup-guide/all

### Programm the IC (using bus pirate)
use brew to install avrdude

#### MAC
brew install avrdude

#### Wiring
http://dangerousprototypes.com/docs/Bus_Pirate_AVR_Programming
http://wiki.attie.co.uk/wiki/Avrdude

#### Windows
http://fab.cba.mit.edu/classes/863.16/doc/projects/ftsmin/windows_avr.html


### Flash hex
avrdude -c buspirate -p t85 -P /dev/tty.usbserial-MEC1 -y -U flash:w:dc617badge_challenge.hex

OR

avrdude -p t85 -c usbtiny -b 19200 -y -U flash:w:dc617badge_challenge.hex
