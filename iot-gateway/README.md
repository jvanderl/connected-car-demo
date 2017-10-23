# IoT Gateway
The IoT Gateway receives distance and safety state from the Car Safety System and passes this on to the Central Logic.
It runs an Mosquitto MQTT broker to communicatie with the Car Safety System and a [Project Flogo](http://www.flogo.io/) Process for the integration logic between car and central.
All of this on a [C.H.I.P. computer](https://getchip.com/pages/chip) which is a $9  ARM based computer capable of running  a linux kernel, much like a Raspberry Pi.

## Setup The IoT Gateway on the C.H.I.P.

### 1. Flash the C.H.I.P. with the headless kernel
First you need to install the linux operating system onto the C.H.I.P.
Instructions can be found [here](http://flash.getchip.com/img/4).

### 2. Connect the C.H.I.P. to WiFi
You need to setup connection to an available wireless network.
Instructions can be found [here](ps://www.dexterindustries.com/howto/connect-to-chip-headless-mode/).

### 3. Install Mosquitto MQTT broker
To install the Mosquitto MQTT broker on the C.H.I.P. you can follow [these instructions](https://medium.com/@rossdanderson/installing-mosquitto-broker-on-debian-2a341fe88981).

### 4. Generate IoT Gateway flow in Project Flogo

 - Install Flogo CLI or Flogo Web designer using instructions that can be found [here](https://github.com/TIBCOSoftware/flogo).
 - Create a new application or import [this flow](iotgtw.json).
 - Import my custom flogo activities:
	 - [Combine](https://github.com/jvanderl/flogo-components/tree/master/activity/combine)
	 - [Send MQTT](https://github.com/jvanderl/flogo-components/tree/master/activity/mqtt)
	 - [Receive MQTT](https://github.com/jvanderl/flogo-components/tree/master/trigger/mqtt2)
	 - [Split Path](https://github.com/jvanderl/flogo-components/tree/master/activity/splitpath)
	 - [Get JSON Elements](https://github.com/jvanderl/flogo-components/tree/master/activity/getjson)
	 - [State Change](https://github.com/jvanderl/flogo-components/tree/master/activity/statechange)
	 - [Send Kafka](https://github.com/jvanderl/flogo-components/tree/master/activity/kafka)
	 - [Filter Data](https://github.com/jvanderl/flogo-components/tree/master/activity/filter)
	 - [Throttle](https://github.com/jvanderl/flogo-components/tree/master/activity/throttle)
	 - [Send eFTL](https://github.com/jvanderl/flogo-components/tree/master/activity/eftl)
 - Build the Project for ARM processor. Name it "iotgtw" and place it in a temporary directory
 - Make "iotgtw" executable (chmod +x iotgtw)
 
### 5. Copy the IoT Gateway executable to the C.H.I.P. 
 You can use ssh copy to get the executable on the machine:
 scp ./iotgtw chip@[chip_ip]:~/iotgtw

### 6. Run the IoT Gateway executable on the C.H.I.P.
You can use ssh command from another PC to start the IoT gateway:
ssh chip@[chip_ip] ~/iotgtw