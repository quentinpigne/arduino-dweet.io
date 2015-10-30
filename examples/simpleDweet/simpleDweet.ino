#include <SPI.h>
#include <Ethernet.h>

#include <Dweet.h>

// Enter a MAC address for your controller
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// Initialize the Ethernet client library
EthernetClient client;

// Initialize the Dweet client library
Dweet dweet(client);

void setup() {
  // Start the Ethernet connection
  Ethernet.begin(mac);

  // Give the Ethernet shield a second to initialize
  delay(1000);

  // Dweet a thing !
  dweet.dweet("my-thing-name", "{\"hello\": \"world\"}");
}

void loop() {}
