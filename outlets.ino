#include <EtherCard.h>
#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

// TODO handle multiple remotes
#define remote1_offset 5330227


static BufferFiller bfill;  // used as cursor while filling the buffer

// ethernet mac address - must be unique on your network
static byte mymac[] = { 0x74, 0x69, 0x69, 0x2D, 0x30, 0x31 };

byte Ethernet::buffer[800]; // tcp/ip send and receive buffer

void setup() {
  Serial.begin(115200);
  Serial.println("\nEtekCity Light Controller");

  if (ether.begin(sizeof Ethernet::buffer, mymac) == 0)
    Serial.println( "Failed to access Ethernet controller");

  if (!ether.dhcpSetup())
    Serial.println("DHCP failed");

  ether.printIp("IP:  ", ether.myip);
  ether.printIp("GW:  ", ether.gwip);
  ether.printIp("DNS: ", ether.dnsip);

  Serial.println("Network initialized\n");
  ether.printIp("Got to http://", ether.myip);

  // Switch transmitter settings
  mySwitch.enableTransmit(2);
  mySwitch.setPulseLength(192);
 // mySwitch.setProtocol(1);

}

void loop() {

  word len = ether.packetReceive();
  word pos = ether.packetLoop(len);
  // check if valid tcp data is received
  // TODO: Somehow this results in duplicate processing...
  if (pos) {
    bfill = ether.tcpOffset();
    char* data = (char *) Ethernet::buffer + pos;
    Serial.println(data);


    if (strncmp("GET / ", data, 6) == 0)
      homePage(bfill);
    else if (strncmp("GET /?", data, 6) == 0)
      apiPage(data, bfill);
    else
      bfill.emit_p(PSTR(
                     "HTTP/1.0 404 Not Found\r\n"
                     "Content-Type: text/html\r\n"
                     "\r\n"
                     "<h1>404 Not Found</h1>"));
    ether.httpServerReply(bfill.position()); // send web page data

  }
}



