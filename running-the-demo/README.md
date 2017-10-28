# Running the Demo
**Under Construction, check back soon!**
Now everything is in place, we can run the demo.

## Start Central Infrastucture Components
Folow these instructions to make sure all components are up and running:

* Start **TIBCO eFTL** messaging:
	* Start FTL **JAAS Server**:
 		* `cd [jetty folder]/demo-base`
  		* `java -jar ../start.jar`
	* Start **FTL Realm Server**:
		* `cd [tibco folder]/eftl/3.2/samples`
		* `[tibco folder]/ftl/5.2/bin/tibrealmserver --auth.url http://[central host name]:8080/FTL-JAAS/login -ht 0.0.0.0:13131 -c ./tibrealmserver.json --secure pass:sslpass`
	* Start **eFTL Server**
		* `cd [tibco folder]/tibco/eftl/3.2/samples`
		* `[tibco folder]/eftl/3.2/bin/tibeftlserver --realmserver https://localhost:13131 --listen wss://0.0.0.0:9291 --password-file ./jaas/eftl.pass --trust-file ./ftl-trust.pem --server-cert server.pem --private-key server.key --private-key-password password`

* Start **Kafka**
	* `brew services start zookeeper`
	* `brew services start kafka`
* Start **Redis**
	* `brew services start redis`

* Check if services are running
	* 	`brew services list`

	
## Start Flogo Components

### On the central site
* Run **Central Logic** on central machine
	* `cd [your flogo build folder]`
	* `./central`

* Run **IoT Gateway** on each Car
	* `ssh [user]@[chip_ip_address] ./iotgtw`


## Execute the Demo

* Start the **Dizmo Viewer**
* **Dock** the **Accident** dizmo to the **IoT Central** dizmo
* Show how the cars take **1.5x more distance**
* **Undock** the **Accident** dizmo
* Show how the cars go back to **original distance**
* **Dock** the **Fog** dizmo to the **IoT Central** dizmo
* Show how the cars take **3x more distance**
* **Undock** the **Fog** dizmo
* Show how the cars go back to **original distance**
* **Dock** the **Glare** dizmo to the **IoT Central** dizmo
* Show how the cars take **2x more distance**
* **Undock** the **Glare** dizmo
* Show how the cars go back to **original distance** 