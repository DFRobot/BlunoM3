/*
 DHCP Chat  Server
 
 A simple server that distributes any incoming messages to all
 connected clients.  To use telnet to  your device's IP address and type.
 You can see the client's input in the Serial1 monitor as well.
 Using an Arduino Wiznet Ethernet shield. 
 
 THis version attempts to get an IP address using DHCP
 
 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 
 created 21 May 2011
 by Tom Igoe
 Based on ChatServer example by David A. Mellis
 
 */

#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network.
// gateway and subnet are optional:
byte mac[] = { 
  0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };
IPAddress ip(192,168,1, 177);
IPAddress gateway(192,168,1, 1);
IPAddress subnet(255, 255, 0, 0);

// telnet defaults to port 23
EthernetServer server(23);
boolean gotAMessage = false; // whether or not you got a message from the client yet

void setup() {
   // open the Serial1 port
  Serial1.begin(9600);
  // start the Ethernet connection:
  Serial1.println("Trying to get an IP address using DHCP");
  if (Ethernet.begin(mac) == 0) {
    Serial1.println("Failed to configure Ethernet using DHCP");
    // initialize the ethernet device not using DHCP:
    Ethernet.begin(mac, ip, gateway, subnet);
  }
  // print your local IP address:
  Serial1.print("My IP address: ");
  ip = Ethernet.localIP();
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial1.print(ip[thisByte], DEC);
    Serial1.print("."); 
  }
  Serial1.println();
  // start listening for clients
  server.begin();
 
}

void loop() {
  // wait for a new client:
  EthernetClient client = server.available();

  // when the client sends the first byte, say hello:
  if (client) {
    if (!gotAMessage) {
      Serial1.println("We have a new client");
      client.println("Hello, client!"); 
      gotAMessage = true;
    }

    // read the bytes incoming from the client:
    char thisChar = client.read();
    // echo the bytes back to the client:
    server.write(thisChar);
    // echo the bytes to the server as well:
    Serial1.print(thisChar);
  }
}

