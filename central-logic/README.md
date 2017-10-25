# Central Logic

Just like the IoT Gateway described earlier, the central logic is also built as a    [Project Flogo](http://flogo.io) app.

This app will communicate with the IoT gateways, store real-time data from the car(s) into a Redis data store. It also is capable of receiving a road condition from the front-end, look up what distance factor is associated with the condition, and then forward the distance facor to the car(s). The effect will be that cars take more distance whenever a condition occurs (like fog, accident or sun glare). When everything's back to normal the cars will return to their normal optimal distance.
 
The Central Logic app contains 3 flows:

 - The **Car Safety Central** flow:
	 - Reads messages coming from the IoT Gateway on the car over eFTL
	 - Stores Car Safety System address and Actual Distance in a Redis store
 - The **Insurance Company** flow:
	 - Reads messages coming from the IoT Gateway on the car over Kafka
	 - Stores Safety State in a Redis store
 - The **Handle Road Conditions** flow:
	 - Reads messages coming from the IoT Gateway on the car over Kafka
	 - Stores Safety State in a Redis store

##Build the Central Logic app
### Flogo Web
The motions for  creating the central logic app in Flogo Web are similar to the ones described in the [IoT Gateway Flogo Web](../iot-gateway/flogo-web/) section.

### Flogo CLI
The motions for  creating the central logic app in Flogo CLI are similar to the ones described in the [IoT Gateway Flogo CLI](../iot-gateway/flogo-cli/) section.
