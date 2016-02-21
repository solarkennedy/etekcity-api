# etekcity-api
Arduino to RF bridge to make an HTTP API to control EtekCity Remote Control Outlets

## Build It

### BOM

* Arduino
* [Inexpensive 433 RF Module](http://www.instructables.com/id/RF-315433-MHz-Transmitter-receiver-Module-and-Ardu/)
* ENC28J60 Module (I like the kind with built-in 5v converters)
* [Etekcity Wireless Outlets](http://www.amazon.com/Etekcity-Wireless-Electrical-Household-Appliances/dp/B00DQELHBS/ref=sr_1_1?ie=UTF8&qid=1456012964&sr=8-1&keywords=etekcity+ZAP)

### Connections

## Software

### Libraries Used

* [Ethercard](https://github.com/jcw/ethercard/)
* [rc-switch](https://github.com/sui77/rc-switch)

## API

    curl http://arduino-ip/?N=(Off|On)
    # Where N is the outlet number

## TODO

 - [ ] Multi remote capability
 - [ ] Use eeprom to store remote number or outlet offset instead of DEFINE
 - [ ] Better web interface
