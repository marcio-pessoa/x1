# x1 Mark I - Useless Machine

[Change log](CHANGELOG.md)

[Bill of materials](BOM.md)

[Kanban](KANBAN.md)

![x1 working](Documents/Pictures/x1.gif)

# Mechanics

## Case
Tecnical specifications:
- Material: Anodized aluminum
- Width: 55 mm
- Height: 105 mm
- Depth: 150 mm

## Finger
![Mechanical design](Mechanics/x1.svg)

# Electronics

## Arduino
Technical specifications:
- Model: [Arduino Leonardo] R3

### Pin designation table
 id | pin |   type    | direction |               description
----|-----|-----------|-----------|--------------------------------------------
  0 |   0 | digital   | input     | Serial communication
  1 |   1 | digital   | output    | Serial communication
  2 |   0 | digital   | input     | Power switch
  3 |   3 | digital   | output    | Relay
  4 |   4 | -         | -         | -
  5 |   5 | PWM       | output    | Speaker
  6 |   6 | PWM       | output    | Angry LED
  7 |   7 | -         | -         | -
  8 |   8 | -         | -         | -
  9 |   9 | PWM       | output    | Servo motor
 10 |  10 | -         | -         | -
 11 |  11 | -         | -         | -
 12 |  12 | -         | -         | -
 13 |  13 | digital   | output    | Status LED
 14 |   0 | -         | -         | -
 15 |   1 | -         | -         | -
 16 |   2 | -         | -         | -
 17 |   3 | -         | -         | -
 18 |   4 | -         | -         | -
 19 |   5 | analog    | input     | Random number generator Seed input

### Diagram
                                 +-----+
    +----[PWR]-------------------| USB |--+
    |                            +-----+  |
    |                                     |
    |                           A5/SCL[ ] |   C5 
    |                           A4/SDA[ ] |   C4 
    |                             AREF[ ] |
    |                              GND[ ] |
    | [ ]N/C                    SCK/13[x]~|   B5
    | [ ]v.ref                 MISO/12[ ] |   .
    | [ ]RST                   MOSI/11[ ]~|   .
    | [ ]3V3   +-----+              10[ ]~|   .
    | [ ]5v    |     |               9[x]~|   .
    | [ ]GND   | MCU |               8[ ] |   B0
    | [ ]GND   |     |                    |
    | [x]Vin   +-----+               7[ ] |   D7
    |                                6[x]~|   .
    | [ ]A0                          5[ ]~|   .
    | [ ]A1                          4[ ] |   .
    | [ ]A2                     INT1/3[x]~|   .
    | [ ]A3                     INT0/2[x] |   .
    | [ ]A4/SDA  RST SCK MISO     TX>1[x] |   .
    | [x]A5/SCL  [ ] [ ] [ ]      RX<0[x] |   D0
    |            [ ] [ ] [ ]              |
    |  Leonardo  GND MOSI 5V  ____________/
     \_______________________/

Adapted from: http://busyducks.com/ascii-art-arduinos

## Prototype shield
Technical specifications:
- Version: 5

### Diagram

    +----[PWR]----------------------------+
    |                                     |
    |         GND/RST2  [ ][ ]            |
    |       MOSI2/SCK2  [ ][ ]  A5/SCL[ ] |   C5 
    |          5V/MISO2 [ ][ ]  A4/SDA[ ] |   C4 
    |                             AREF[ ] |
    |                              GND[ ] |
    | [ ]N/C                    SCK/13[x] |   B5
    | [ ]v.ref                 MISO/12[ ] |   .
    | [ ]RST                   MOSI/11[ ]~|   .
    | [ ]3V3                        10[ ]~|   .
    | [ ]5v                          9[x]~|   .
    | [ ]GND                         8[ ] |   B0
    | [ ]GND                              |
    | [ ]Vin                         7[ ] |   D7
    |                                6[ ]~|   .
    | [ ]A0                          5[ ]~|   .
    | [ ]A1                          4[ ] |   .
    | [ ]A2                     INT1/3[x]~|   .
    | [ ]A3                     INT0/2[x] |   .
    | [ ]A4/SDA  RST SCK MISO     TX>1[x] |   .
    | [x]A5/SCL  [ ] [ ] [ ]      RX<0[x] |   D0
    |            [ ] [ ] [ ]              |
    |            GND MOSI 5V  ____________/
     \_______________________/


## Battery
Technical specifications:
- Technology: Rechargeable Li-ion
- Voltage: 3.7V
- Capacity: 3200 mAh
- Model: 18650

# Software


---
[Arduino Leonardo]: https://www.arduino.cc/en/Main/arduinoBoardLeonardo/#techspecs
