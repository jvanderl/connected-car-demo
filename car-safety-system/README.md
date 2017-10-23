# Car Safety System
The on-board Car Safety System measures the actual distance to the car in front and determines the safety state; Too Close, Safe or Optimal. It is also capable of making the car keep optimal distance.

## Hardware Used

 - A [NodeMCU v3.0 ESP-12](https://www.aliexpress.com/item/V3-Wireless-module-NodeMcu-4M-bytes-Lua-WIFI-Internet-of-Things-development-board-based-ESP8266-esp/32647542733.html?spm=a2g0s.9042311.0.0.Nq0bHx) board 
 - A [HC-SR04](https://www.aliexpress.com/item/Free-shipping-1pcs-Ultrasonic-Module-HC-SR04-Distance-Measuring-Transducer-Sensor-for-Arduino-Samples-Best-prices/1967936408.html?spm=a2g0s.9042311.0.0.C2CePu) ultrasonic distance measuring module
 - A [L298N](https://www.aliexpress.com/item/Free-shipping-1pcs-lot-Special-promotions-2pcs-lot-L298N-motor-driver-board-module-stepper-motor-smart/1872427142.html?spm=a2g0s.9042311.0.0.7UNFIQ) motor driver board module
 - A 5mm [RGB LED](https://www.aliexpress.com/store/product/50Pcs-5mm-4pin-RGB-Tri-Color-Common-Anode-LED-Red-Green-Blue/612195_1852144523.html)
 - A [Standard breadboard](https://www.aliexpress.com/item/1pcs-DIY-400-Points-Solderless-Bread-Board-Breadboard-400-PCB-Test-Board-for-ATMEGA-PIC-Arduino/32802377725.html?spm=a2g0s.9042311.0.0.oXz7Ch) to hold the NodeMCU and the LED section.
 - A [Mini breadboard](https://www.aliexpress.com/item/free-shipping-10Pcs-Lot-Pro-Mini-Module-Atmega328-5V-16M-For-Arduino-Compatible-With-Nano/1656592084.html?spm=a2g0s.9042311.0.0.hgy8Mz) to hold the distance sensor
 - A standard 4-wheel [robot car chassis kit](https://www.aliexpress.com/item/5-colors-choose-one-color-4WD-Smart-Robot-Car-Chassis-Kits-for-arduino-with-Speed/32679090614.html?spm=a2g0s.9042311.0.0.oXz7Ch)

## Shema
![Car Safety System](schema.png)

## Arduino Code
The Source code used for the car safety system is [here](iot-car.ino).
