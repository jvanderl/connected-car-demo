# IoT Gateway
## Outline
The IoT Gateway receives distance and safety state from the Car Safety System and passes this on to the Central Logic.
It runs an Mosquitto MQTT broker to communicatie with the Car Safety System and a [Project Flogo](http://www.flogo.io/) app for the integration logic between car and central.
All of this on a [C.H.I.P. computer](https://getchip.com/pages/chip) which is a $9  ARM based computer capable of running  a linux kernel, much like a Raspberry Pi.

## Setup The IoT Gateway on the C.H.I.P.

### Flash the C.H.I.P. with the headless kernel
First you need to install the linux operating system onto the C.H.I.P.
Instructions can be found [here](http://flash.getchip.com/img/4).

### Connect the C.H.I.P. to WiFi
You need to setup connection to an available wireless network.
Instructions can be found [here](https://www.dexterindustries.com/howto/connect-to-chip-headless-mode/).

### Install Mosquitto MQTT broker
To install the Mosquitto MQTT broker on the C.H.I.P. you can follow [these instructions](https://medium.com/@rossdanderson/installing-mosquitto-broker-on-debian-2a341fe88981).

### Generate IoT Gateway app in Project Flogo
The aim here is to craeate a single executable that will run the integration logic defined in Flogo. No need to install anything on the C.H.I.P., just use your PC to generate the executable.

There are two ways of doing this:

 - Via Flogo Web - Complete instructions can be found [here](flogo-web)
 - Via Flogo CLI - Complete instructions can be found [here](flogo-cli)
 
### Copy the IoT Gateway executable to the C.H.I.P. 
 You can use ssh copy to get the executable on the machine:
 `scp ./iotgtw chip@[chip_ip]:~/iotgtw`

### Run the IoT Gateway executable on the C.H.I.P.
You can use ssh command from another PC to start the IoT gateway:
`ssh chip@[chip_ip] ~/iotgtw`

## What's Next?
Now you can choose to do one of the following:

 - Assemble the complete [Robot Car](../robot-car)
 - Create the [Demo Workspace](../workspace/)
 - Test the communications in [Running the Demo](../running-the-demo/)