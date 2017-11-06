# Central Infrastructure

This section describes setting up the central messaging components (eFTL and Kafka) and the data store (Redis) used by the demo.

## TIBCO eFTL Messaging
I used the TIBCO eFTL Community Edition messaging suite  to show we can create an end-to-end secure path between the IoT Gateway on the car and the central infrastructure. It uses secure websockets with a more controlled messaging protocol on top of that.

The eFTL components in Flogo support both secure and unsecure communication. Setting up the secure part is a bit harder than the unsecure one. In both cases I stayed with the standard sample installation.

As eFTL is part of the FTL messaging suite, we will also install the Community Edition of that product.

### Install TIBCO FTL Community Edition
* Get the FTL Community Edition [here](https://www.tibco.com/products/tibco-ftl)
* Install the FTL Community Edition
	* Just follow the instructions using the installer
* Load the FTL images into Docker
	* In a terminal:
	* `cd /opt/tibco/ftl/5.3/docker-images/`
	* `docker load -i ftl-tibagent-5.3.0.dockerimage.xz` 
	* `docker load -i ftl-tibrealmserver-5.3.0.dockerimage.xz`
* Start FTL Realm Server:
`docker run -d -p 13131:13131 -p 13134:13134 ftl-tibrealmserver:5.3.0 --client.url discover://`
* Start FTL Agent:
`docker run -d --restart=unless-stopped --add-host <your_server_name>:<your_server_IPAddress> -v /var/run/docker.sock:/var/run/docker.sock -p 13139:13139 -p 13140:13140 ftl-tibagent:5.3.0 -rs http://<your_server_name>:13131`

### Install TIBCO eFTL Community Edition
* Get the eFTL Community Edition [here](https://www.tibco.com/products/tibco-eftl)
* Install the eFTL Community Edition
	* Just follow the instructions using the installer
* Load the eFTL images into Docker
	* In a terminal:
	* `cd /opt/tibco/eftl/3.3/docker-images/`
	* `docker load -i ftl-tibeftlserver-3.3.0.dockerimage.xz`
* Prepare FTL setup for eFTL
	* Open FTL Realmserver Web Administration [http://localhost:13131/login](http://localhost:13131/login) and press <kbd>**Sign In**</kbd>
	* Switch **Edit Mode** to **On**
	* Select **Actions** -> **Upload Config**
	* Browse to folder **/opt/tibco/eftl/3.3/samples**
	* Select file **tibrealmserver.json** and press <kbd>**Open**</kbd>
	* Select **Deploy**
	* Enter Description **Load eFTL Config** and press <kbd>Deploy</kbd>
* Start eFTL Server
	* In a terminal: 
	* `docker run -d -p 9191:9191 --add-host <your_server_name>:<your_server_IPAddress> ftl-tibeftlserver:3.3.0 -rs discover:// -l ws://*:9191`

## Install Kafka Messaging
The message system used by our "Insurance Company" uses [Kafka](https://kafka.apache.org/) as messaging protocol. Here's how to install. As I'm using a Mac, it's easiest to install Kafka using Homebrew. If you don't have it yet, install from [here](https://brew.sh/).

### Install Zookeeper

In a terminal:

* `brew install zookeeper`
* `brew services start zookeeper`

### Install Kafka
In a terminal:

* `brew install kafka`
* `brew services start kafka`


## Install Redis Keystore
The External Keystore is based on [Redis](https://redis.io/) used to store real-time data coming from the cars, but also acts as the link between a condition name (fog, accident, glare) and a distance factor that needs to be sent to the cars eventually. Here's how to set it up.

### Get Redis
* `brew install redis`
* `bres services start redis`

### Configure Redis
As we need to setup the distance factor we shoud add a few key value pairs in the Redis store. I use [FastoRedis](http://fastoredis.com/) to do visualize the redis store, but for the setup we'll do command line.
In a terminal:
`redis-cli set condition:normal:factor 1`
`redis-cli set condition:accident:factor 1.5`
`redis-cli set condition:glare:factor 2`
`redis-cli set condition:fog:factor 3`

