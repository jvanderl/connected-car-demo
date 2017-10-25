# Creating the IoT Gateway using Flogo CLI
This section describes how to install the Flogo Command Line Interface from scratch and then build the IoT Gateway application from the command line.
## Install Flogo CLI
For this tutorial I will be running my flogo CLI  on Ubuntu, but the steps for all OS'es are similar. You can always find a complete description [here](https://github.com/TIBCOSoftware/flogo).
Below more of a qiuck guide:

 1. Install **golang**
 You could follow the instructions posted [here](https://golang.org/doc/install) but I did the following:
`sudo apt-get-repository ppa:gophers/archive`
`sudo apt-get update`
`sudo apt-get install golang-1.9-go`

 2. Adjust PATH and set GOPATH environment variable
 `nano ~/.profile` or any editor of your choice
add **/usr/lib/go-1.9/bin** to your PATH
add **/home/userxx/go/bin** to your PATH
add line **GOPATH="/home/userxx/projects/go"**
Save and exit the editor
Make the changes effective
`source ~/.profile`

 3. Install gb project tooling
 `go get github.com/constabulary/gb/...`

 4. Install Flogo CLI
 `go get github.com/TIBCOSoftware/flogo-cli/...`

 5. Download the application definition **iotgtw.json**
 * Select the link to the application [here](iotgtw.json). 
* Save the raw version to your flogo projects folder

 6. Adjust the configuration parameters in  **iotgtw.json**
 * Open the file in an editor. Look for the following items and adjust to match your setup:
	 * In **Receive MQTT Message 2**
		 * **broker** - Should match the MQTT broker you're running. Default should be OK if you're running it on the IoT Gateway itself.
	 * In **Send to Kafka**
		 * **server**:**value** - Should match the paramters of your central Kafka server.
	 * In **Send eFTL Message**
		 * **server**:**value** - Should match the parameters of your central eFTL endpoint.
	 * In **Send MQTT Message**
		 * **broker** - Should match the MQTT broker you're running. Default should be OK if you're running it on the IoT Gateway itself.

	* Save your changes and exit the editor
 
 7. Create a new flogo app based on the definition file
 For now we assume that you will create your flogo apps in **/home/userxx/projects/flogo**
 `cd /home/userxx/projects/flogo`
 `flogo create -f iotgtw.json iotgtw`
 This will create the complete project structure and import all the dependencies.
 
 8. Build the IoT Gateway app in flogo cli:
 * Go to the newly created iotgtw project folder
 `cd iotgtw`
 * Build the app optimized for the C.H.I.P.'s ARM processor
 `env GOARM=7 GOARCH=arm GOOS=linux flogo build -o`
 * This will give you **iotgtw-linux-arm** executable in the **bin/** folder
 * Rename the executable to **iotgtw**
 `cd bin`
 `mv iotgtw-linux-arm iotgtw`
 