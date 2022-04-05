# TICtoMQTT
*interface from french electricity meters to MQTT.*

ENEDIS (former Electricité De France) electricity meter generates some informational signal as Serial ASCII frames e.g:
```
ADCO xxxxxxxxxxxx 2
OPTARIF BASE 0
ISOUSC 30 9
BASE 025298937 8
PTEC TH.. $
IINST 011 Y
IMAX 042 E
PAPP 02550 -
MOTDETAT 000000 B
```
full documentation (french) : https://www.enedis.fr/media/2027/download

## Hardware
Check [./Hardware](./Hardware) for kicad project
Only includes level conversion parts for UART
The present code was sucessfully tested on ESP32 boards, using ``Serial2`` (other attempts with ``SoftwareSerial`` gave good results).

## Sofware
### TICtoMQTT
Main software to pass BASE and PPAP values over MQTT
### HWtest
[HWtest](./HWtest) is a quick sketch to get raw frame content