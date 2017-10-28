# Central Infrastructure
**UNDER CONSTRUCTION**

This section describes setting up the central messaging components (eFTL and Kafka) and the data store used by the demo.

## TIBCO eFTL Messaging
I used the TIBCO eFTL Community Edition messaging suite  to show we can create an end-to-end secure path between the IoT Gateway on the car and the central infrastructure. It uses secure websockets with a more controlled messaging protocol on top of that.

The eFTL components in Flogo support both secure and unsecure communication. Setting up the secure part is a bit harder than the unsecure one. In both cases I stayed with the standard sample installation.

As eFTL is part of the FTL messaging suite, we will also install the Community Edition of that product.

### Install TIBCO FTL Community Edition
Get the FTL Community Edition [here](https://www.tibco.com/products/tibco-ftl)

Start FTL Realm Server:
`docker run -d -p 13131:13131 -p 13134:13134 ftl-tibrealmserver:5.3.0 --client.url discover://`

Start FTL Agent:
`docker run -d --restart=unless-stopped -v /var/run/docker.sock:/var/run/docker.sock -p 13139:13139 -p 13140:13140 ftl-tibagent:5.3.0 -rs http://<your_server_name>:13131`

Get the eFTL Community Edition [here](https://www.tibco.com/products/tibco-eftl)

Start eFTL Server:
`docker run -d -p 9191:9191 ftl-tibeftlserver:3.3.0`

## Install Kafka Messaging

## Install Redis Keystore