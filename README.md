# SerialNotify
A small toolbar program to show what serial ports are available
and notify the user with a notification when a new port is found
This is especialy useful on windows when using with multiple usb
serial ports, however it also works perfectly on linux.

# Build
Import into QTCreator and build
OR
run "qmake && make"

# Libs
uses QSerialPort

# Known bugs
Linux: When no serial ports are available, all ports are listed
