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
 
 5. Create a new flogo app
 For now we assume that you will create your flogo apps in **/home/userxx/projects/flogo**
 `cd /home/userxx/projects/flogo`
 `flogo create iotgtw`
 `cd iotgtw`

 5. Add activities and triggers to the project
 As you may know, a flogo app consists of one or more flows that represent a certain integration logic. Each flow gets started by a **trigger**, all other logic parts are called **activities**.
 I created a number of these triggers and activities to make this project work the way I wanted it to work. This section describes how to add them to your flogo cli project.
 `flogo install github.com/jvanderl/flogo-components/activity/combine`
 `flogo install github.com/jvanderl/flogo-components/activity/mqtt`
 `flogo install github.com/jvanderl/flogo-components/trigger/mqtt2`
 `flogo install github.com/jvanderl/flogo-components/activity/splitpath`
 `flogo install github.com/jvanderl/flogo-components/activity/getjson`
 `flogo install github.com/jvanderl/flogo-components/activity/statechange`
 `flogo install github.com/jvanderl/flogo-components/activity/kafka`
 `flogo install github.com/jvanderl/flogo-components/activity/filter`
 `flogo install github.com/jvanderl/flogo-components/activity/throttle`
 `flogo install github.com/jvanderl/flogo-components/activity/eftl`

 6. Now import the flogo.json
 * Select the link to the application [here](iotgtw.json). 
* Save the raw version to your iotgtw projcet folder as **flogo.json**

 7. Build the IoT Gateway app in flogo cli:
 `flogo build`
 This will give you **iotgtw** executable in the **bin/** folder
 