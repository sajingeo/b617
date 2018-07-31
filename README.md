# DC617 Badge challenge for DC26

Credits to [@Eber24](https://twitter.com/eber) [@sajingeo](https://github.com/sajingeo)


## Resources
board support https://cdn.sparkfun.com/assets/learn_tutorials/1/5/0/attiny-ide-1.6.x.zip


place the atiny folder in /Documents/Arduino/hardware


i2c library https://github.com/lucullusTheOnly/TinyWire

place the TineyWire folder in /Documents/Arduino/library

### How to program the attiny85 SOIC 
https://learn.sparkfun.com/tutorials/tiny-avr-programmer-hookup-guide/all

### Setup the board

Cut the traces


![Step 1](img/img1.jpg)

Solder the I2C Pullups and the IC (U1)


![Step 2](img/img2.jpg)

### Program the IC
I used the Tiny programmer from sparkfun to program the IC, The ATTiny85v will work at 1.8v to 5v.
![Step 3](img/img3.jpg)

more details on the hookup here.
https://learn.sparkfun.com/tutorials/tiny-avr-programmer-hookup-guide/all

### NOTEs
This will not work with Bus pirate / RPI [ does not implement full i2c] [link to why](https://github.com/rambo/TinyWire)

### tools
https://www.sparkfun.com/products/13153

https://www.sparkfun.com/products/11801

https://www.sparkfun.com/products/9194
