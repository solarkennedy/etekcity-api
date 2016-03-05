# etekcity-api
[![Build Status](https://travis-ci.org/solarkennedy/etekcity-api.svg?branch=master)](https://travis-ci.org/solarkennedy/etekcity-api)

Arduino to RF bridge to make an HTTP API to control EtekCity Remote Control Outlets

## Build It

### BOM

* Arduino
* [Inexpensive 433 RF Module](http://www.instructables.com/id/RF-315433-MHz-Transmitter-receiver-Module-and-Ardu/)
* ENC28J60 Module (I like the kind with built-in 5v converters)
* [Etekcity Wireless Outlets](http://www.amazon.com/Etekcity-Wireless-Electrical-Household-Appliances/dp/B00DQELHBS/ref=sr_1_1?ie=UTF8&qid=1456012964&sr=8-1&keywords=etekcity+ZAP)

![etekcity outlets](https://raw.githubusercontent.com/solarkennedy/etekcity-api/master/outlets.jpg)

### Connections

![breadboard](https://raw.githubusercontent.com/solarkennedy/etekcity-api/master/breadboard.jpg)

## Software

### Libraries Used

* [Ethercard](https://github.com/jcw/ethercard/)
* [rc-switch](https://github.com/sui77/rc-switch)

## API

![web interface](https://raw.githubusercontent.com/solarkennedy/etekcity-api/master/web%20interface.png)

See the `/help/` page for more API docs. Here is a snippet:

    # Where N is the outlet number
    curl http://arduino-ip/?N=(Off|On)

    # Send out an arbitrary RF code:
    curl http://arduino-ip/code/?code=NUM

## TODO

 - [x] Raw code API
 - [x] Online help
 - [ ] Multi remote capability
 - [ ] Use eeprom to store remote number or outlet offset instead of DEFINE
 - [ ] Better web interface
