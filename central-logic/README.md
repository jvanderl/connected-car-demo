# Central Logic

## Outline
Just like the IoT Gateway described earlier, the central logic is also built as a [Project Flogo](http://flogo.io) app.

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

## Build the Central Logic app
### Download the Flogo app description
* Download the raw version of **central.json** from [here](central.json).

### Flogo Web
The motions for  creating the central logic app in Flogo Web are similar to the ones described in the [**IoT Gateway Flogo Web**](../iot-gateway/flogo-web/) section.
Check that section if you need to know how to perfrom the steps below. You can reuse the **tempApp** and **tempFlow** you created earlier.

 - Make sure you have the following custom activities installed in Flogo Web (copy  the links below to install the activities in flogo web just like describe in the [**Iot Gateway**](../iot-gateway/flogo-web) section:
	 - https://github.com/jvanderl/flogo-components/trigger/kafka
	 - https://github.com/jvanderl/flogo-components/trigger/eftl
	 - https://github.com/jvanderl/flogo-components/activity/splitpath
	 - https://github.com/jvanderl/flogo-components/activity/replace
	 - https://github.com/jvanderl/flogo-components/activity/combine
	 - https://github.com/jvanderl/flogo-components/activity/redis
	 - https://github.com/jvanderl/flogo-components/activity/getjson
 - Import **central.json**
 - Adjust the configuration parameters
	 * Select app **IoT Central Logic**
	 * Select flow **Car Safety Central**
		 * In **Receive eFTL Message**
			 * **server** - Should match the central eFTL server parameters
		 * In **Store Dist**
			 * **server** - Should match the central Redis server parameters
		 * In **Store ID**
			 * **server** - Should match the central Redis server parameters
	 * Select flow **Handle Road Conditions**
		 * In **Redis**
			 * **server** - Should match the central Redis server parameters
		 * This is the only tweak left in this setup: I have hardwired sending the distance factor to two cars. If you have one car, just remove the second call. For each:
			 * **uri** - Replace IP address and port number to reflect the HTTP listener on the IoT Gateway on the car.
			 * **queryParams** - replace the value for deviceID with the actual Mac Address of the car safety system on the car.
	 *  Select flow **Car Safety Central**
		 * In **Receive Kafka Message**
			 * **server** - Should match the central Kafka server parameters
		 * In **Store Safety**
 * Build and save as **central**
 * Make the app executable. In a terminal:
 `chmod +x central`

### Flogo CLI
The motions for  creating the central logic app in Flogo CLI are similar to the ones described in the [IoT Gateway Flogo CLI](../iot-gateway/flogo-cli/) section.

* Copy downloaded **central.json** to your flogo project folder.
* Edit **central.json** and adjust the configuration parameters in similar to the section above.
* Create the app based on the json file:
 `flogo create -f central.json central`
* Build the **central** app (assumed this is the machine you're running on, no compiler environment is necessary)
`cd central`
`flogo build`
This will give you an executable called **central** in the **bin/** folder