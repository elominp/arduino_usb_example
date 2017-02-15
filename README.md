# arduino_usb_example
Example of emulating serial, keyboard and mouse over USB with Arduino

It's an example of how to emulate serial port, keyboard and mouse over USB with the Atmega16U2 and communicating with an Atmega328P on an Arduino UNO.

This repository contains the sketches for the Atmega16U2 and Atmega328P.

The two controllers communicate through a basic protocol :

COMMAND\r\n
DATA\esc

On the first line, the Atmega328P writes the command name, terminated by a "\r\n".
Next, it sends the data and close the command by sending an escape sequence (value 27 in ascii table).

The commands the Atmega16U2 recognizes are :

- KBD : Bytes sended through data are used to emulate keyboard writing
- MOUSE : Each sequences sended through data are formed like this : "x;y\n" where x and y are signed 8 bits integer values, representing a relative move of the mouse.
- CDC : Bytes sended through data are forwarded to host by emulating a serial interface CDC

Note : Keyboard and Mouse can't be implemented in the same time, you need to comment the command of one or the other before uploading to the Atmega16U2.
