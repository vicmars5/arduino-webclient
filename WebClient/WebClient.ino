#include <SPI.h>
#include <Ethernet.h>
/*
  Web client

 This sketch connects to a website (http://www.google.com)
 using an Arduino Wiznet Ethernet shield.

 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13

 created 18 Dec 2009
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe, based on work by Adrian McEwen
 modified 27 Fen 2017
 by Victor Diaz
 */
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; // MAC address

const char SERVER[] = "192.168.1.80";    // Server IP address. Check your computer ip address.
const int PORT = 3000; // Server port

// Arduino static IP address to use if the DHCP fails to assign
IPAddress ip(192, 168, 0, 177);

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println("connecting...");

  
  // if you get a connection, report back via serial:
  if (client.connect(SERVER, PORT)) {
      // data = "msg=hello";
      reqPost("msg=hello");
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}

void loop() {
  // if there are incoming bytes available
  // from the server, read them and print them:
  while (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();

    // do nothing forevermore:
    while (true);
  }
}

void reqGet() {
  Serial.println("connected");
  // Make a HTTP request:
  client.println("GET / HTTP/1.1");
  client.print("Host: ");
  client.println(SERVER);
  client.println("Connection: close");
  
}

void reqPost(String data) {
    Serial.println("connected");
    // Make a HTTP request:
    client.println("POST / HTTP/1.1");
    client.print("Host:");
    client.println(SERVER);
    client.println("Connection: close");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.print("Content-Length: ");
    client.println(data.length());
    client.println();
    client.print(data);
}

