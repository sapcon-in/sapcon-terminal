Abobut sapcon-terminal
A Qt-based cross platform serial terminal, developed by Sapcon Instruments(www.sapconinstruments.com) with options for:
    * Profile based commands
    * Timer based commnads
    * Auto responses
    * File logging
This project is not in active development.

Features that may be added in the future:

* Modbus-RTU support
Developers:
* Dhananjay Palshikar(@djpalshikar)
* Pankaj Jain

Licence: GPL V3, see LICENCE for more information
Installation(short):
   *Install Qt(>Qt 4.0) development environment 
   *Import and build the project
 Operating System Specific Installation:
   *Ubuntu
      - Opent the terminal:
         sudo adduser <user_name> dialout
      - You may need a reboot to operate the serial device

Hardware Requirements:
   sapcon-terminal works well with devices with FTDI232(https://www.ftdichip.com/Products/ICs/FT232R.htm),
   however other USB to serial USART interfaces should work as well.
