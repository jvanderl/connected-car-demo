# Creating the IoT Gateway using Flogo Web
This section describes how to install the Flogo Web designer from scratch and then build the IoT Gateway application.
## Install Flogo Web
For this tutorial I will be running my Flogo design environment on Ubuntu, but the steps for all OS'es are similar. You can always find a complete description [here](https://github.com/TIBCOSoftware/flogo).
Below more of a qiuck guide:

 1. Install Docker
`sudo apt-get install docker`

 2. Get the latest Docker image for Flogo Web
 `docker pull flogo/flogo-docker`
 
 3. Start Flogo Web
 `docker run -it -p 3303:3303 flogo/flogo-docker eula-accept`
 
 4. Open a browser and point it to http://localhost:3303
 5. Install my custom components.
 As you may know, a flogo app consists of one or more flows that represent a certain integration logic. Each flow gets started by a **trigger**, all other logic parts are called **activities**.
 I created a number of these triggers and activities to make this project work the way I wanted it to work. This section describes how to add them to your flogo web installation. You only need to do this once. We'll create a dummy application to go through the motions af adding activities and triggers. These will stay available in your flogo web environment even after you delete this dummy application. Please follow the steps below:
 * Create a new Flogo App by pressing <kbd>**New**</kbd>
 * Choose **Microservice** as app type
 * Name the app ***tempApp***
 * Click on **+New Flow** just blow the app name
 * Name the flow ***tempFlow***, leave the Flow description empty
 * Click on **tempFlow**.  This will bring up a screen where you can select a trigger to start the process, but you can also use this screen to add new triggers and activities that are not available in the default flogo web Docker image.
 * Click on <kbd>**Install Now**</kbd>
	 * Install the **Combine** activity by pasting the following url and pressing the <kbd>**Install**</kbd> button.:
	 * https://github.com/jvanderl/flogo-components/activity/combine
	 * Press <kbd>**Okay**</kbd> after succesful installation of 
 * Repeat the above actions for the other activities and triggers:
	 * **Send MQTT**:
	 *  https://github.com/jvanderl/flogo-components/activity/mqtt
	 * **Recieve MQTT**:
	 * https://github.com/jvanderl/flogo-components/trigger/mqtt2
	 * **Split Path**:
	 *  https://github.com/jvanderl/flogo-components/activity/splitpath
	 * **Get JSON Elements**:
	 *  https://github.com/jvanderl/flogo-components/activity/getjson
	 * **State Change**:
	 *  https://github.com/jvanderl/flogo-components/activity/statechange
	 * **Send Kafka**:
	 *  https://github.com/jvanderl/flogo-components/activity/kafka
	 * **Filter Data**:
	 *  https://github.com/jvanderl/flogo-components/activity/filter
	 * **Throttle**:
	 *  https://github.com/jvanderl/flogo-components/activity/throttle
	 * **Send eFTL**:
	 *  https://github.com/jvanderl/flogo-components/activity/eftl

 6. Now all activities for the IoT Gateway app are in place we can import the the app.
 * Select the link to the application [here](iotgtw.json). 
* Save the raw version to disk on a temporary location
* Click on the <kbd>**Import**</kbd> button on the Flogo main screen
* Select the **iotgtw.json** file from the temporary location and open it.

 7. Build the IoT Gateway app in flogo web:
 * Select the app **Flogo IoT Gateway**
 * Press the <kbd>**Build**</kbd> button
 * Select **ARM/Linux** from the dropdown menu
 * Wait for the flogo app to be compiled (can take a while)
 * Save the file as **iotgtw**
 
 8. Make **iotgtw** executable. In a terminal:
 `chmod +x iotgtw`
 