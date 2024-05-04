// ESP32 WiFi <-> 3x UART Bridge
// by AlphaLima
// www.LK8000.com

// Disclaimer: Don't use  for life support systems
// or any other situations where system failure may affect
// user or environmental safety.

// #include "config.h"



// start config: ////////////////////////////////////////////////////////////
//
bool WiFiMode = false;             // set WiFiMode = true and BTMode = false if OpenSoar, XCSoar should connect to the Larus via WiFi or set WiFiMode = false
bool BTMode = true;                // and BTMode = true if OpenSoar, XCSoar should connect to the Larus via Bluetooth
//

#define SSID_BUF_LENGTH 20
char finalSsid[SSID_BUF_LENGTH];               
const char *pw = "LarusSensor";    // and this is the WiFi password
//
IPAddress ip(192, 168, 4, 1);
IPAddress netmask(255, 255, 255, 0);
//
// You must connect OpenSoar, XCSoar to this AP, then:
// menu -> connect -> Internet(TCP) -> 192.168.4.1:8880
//
// end config: ////////////////////////////////////////////////////////////



#define NUM_COM   3                 // total number of COM Ports
/*************************  COM Port 0 (Programmer)*******************/
#define UART_BAUD0 38400            // Baudrate UART0
#define SERIAL_PARAM0 SERIAL_8N1    // Data/Parity/Stop UART0
#define SERIAL0_RXPIN 21            // receive Pin UART0
#define SERIAL0_TXPIN 1             // transmit Pin UART0
#define SERIAL0_TCP_PORT 8882      // Wifi Port UART0
/*************************  COM Port 1 (RS232) ***********************/
#define UART_BAUD1 38400            // Baudrate UART1
#define SERIAL_PARAM1 SERIAL_8N1    // Data/Parity/Stop UART1
#define SERIAL1_RXPIN 16            // receive Pin UART1
#define SERIAL1_TXPIN 17            // transmit Pin UART1
#define SERIAL1_TCP_PORT 8881       // Wifi Port UART1
/*************************  COM Port 2 (STM32) **********************/
#define UART_BAUD2 38400            // Baudrate UART2
#define SERIAL_PARAM2 SERIAL_8N1    // Data/Parity/Stop UART2
#define SERIAL2_RXPIN 15            // receive Pin UART2
#define SERIAL2_TXPIN 4             // transmit Pin UART2
#define SERIAL2_TCP_PORT 8880       // Wifi Port UART2

#define bufferSize 1024
#define MAX_NMEA_CLIENTS 4

// end config.h
#include <esp_wifi.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

HardwareSerial Serial_one(1);
HardwareSerial Serial_two(2);
HardwareSerial* COM[NUM_COM] = {&Serial, &Serial_one , &Serial_two};

WiFiServer server_0(SERIAL0_TCP_PORT);
WiFiServer server_1(SERIAL1_TCP_PORT);
WiFiServer server_2(SERIAL2_TCP_PORT);
WiFiServer *server[NUM_COM] = {&server_0, &server_1, &server_2};
WiFiClient TCPClient[NUM_COM][MAX_NMEA_CLIENTS];

uint8_t buf1[NUM_COM][bufferSize];
uint16_t i1[NUM_COM] = {0, 0, 0};

uint8_t buf2[NUM_COM][bufferSize];
uint16_t i2[NUM_COM] = {0, 0, 0};

uint8_t BTbuf[bufferSize];
uint16_t iBT = 0;

const int BTorWiFi = 14;

void setup() {

  delay(500);

  pinMode(BTorWiFi, INPUT_PULLUP);

  COM[0]->begin(UART_BAUD0, SERIAL_PARAM0, SERIAL0_RXPIN, SERIAL0_TXPIN);
  COM[1]->begin(UART_BAUD1, SERIAL_PARAM1, SERIAL1_RXPIN, SERIAL1_TXPIN);
  COM[2]->begin(UART_BAUD2, SERIAL_PARAM2, SERIAL2_RXPIN, SERIAL2_TXPIN);

  // Create custom bluetooth / wifi ssid
  uint64_t macid = ESP.getEfuseMac();
  uint16_t uid = macid & 0xFFFF;
  sprintf(finalSsid, "Larus_%X", uid);

  //if (digitalRead(Varioschalter) == 0)
  if ((BTMode == false) && (WiFiMode == true))
  {
    SerialBT.end();
    WiFi.mode(WIFI_AP);
    WiFi.softAP(finalSsid, pw); // configure ssid and password for softAP
    delay(2000); // VERY IMPORTANT
    WiFi.softAPConfig(ip, ip, netmask); // configure ip address for softAP
  }

  //if (digitalRead(Varioschalter) == 1)
  if ((BTMode == true) && (WiFiMode == false))
  {
    WiFi.mode(WIFI_OFF);
    SerialBT.begin(finalSsid); //Bluetooth device name
  }

  //if (digitalRead(Varioschalter) == 0)
  if ((BTMode == false) && (WiFiMode == true))
  {
    COM[0]->println("Starting TCP Server 1");
    server[0]->begin(); // start TCP server
    server[0]->setNoDelay(true);
    COM[1]->println("Starting TCP Server 2");
    server[1]->begin(); // start TCP server
    server[1]->setNoDelay(true);
    COM[2]->println("Starting TCP Server 3");
    server[2]->begin(); // start TCP server
    server[2]->setNoDelay(true);
  }

  esp_err_t esp_wifi_set_max_tx_power(50);  //lower WiFi Power
}

void loop()
{
  //if (digitalRead(Varioschalter) == 1)
  if ((BTMode == true) && (WiFiMode == false))
  {
    // receive from Bluetooth:
    if (SerialBT.hasClient())
    {
      while (SerialBT.available())
      {
        BTbuf[iBT] = SerialBT.read(); // read char from client (LK8000 app)
        if (iBT < bufferSize - 1) iBT++;
      }
      for (int num = 0; num < NUM_COM ; num++)
        COM[num]->write(BTbuf, iBT); // now send to UART(num):
      iBT = 0;
    }
  }
  //if (digitalRead(Varioschalter) == 0)
  if ((BTMode == false) && (WiFiMode == true))
  {
    for (int num = 0; num < NUM_COM ; num++)
    {
      if (server[num]->hasClient())
      {
        for (byte i = 0; i < MAX_NMEA_CLIENTS; i++) {
          //find free/disconnected spot
          if (!TCPClient[num][i] || !TCPClient[num][i].connected()) {
            if (TCPClient[num][i]) TCPClient[num][i].stop();
            TCPClient[num][i] = server[num]->available();
            continue;
          }
        }
        //no free/disconnected spot so reject
        WiFiClient TmpserverClient = server[num]->available();
        TmpserverClient.stop();
      }
    }
  }

  for (int num = 0; num < NUM_COM ; num++)
  {
    if (COM[num] != NULL)
    {

      //if (digitalRead(Varioschalter) == 0)
      if ((BTMode == false) && (WiFiMode == true))
      {
        for (byte cln = 0; cln < MAX_NMEA_CLIENTS; cln++)
        {
          if (TCPClient[num][cln])
          {
            while (TCPClient[num][cln].available())
            {
              buf1[num][i1[num]] = TCPClient[num][cln].read(); // read char from client (LK8000 app)
              if (i1[num] < bufferSize - 1) i1[num]++;
            }

            COM[num]->write(buf1[num], i1[num]); // now send to UART(num):
            i1[num] = 0;
          }
        }
      }

      if (COM[num]->available())
      {
        while (COM[num]->available())
        {
          buf2[num][i2[num]] = COM[num]->read(); // read char from UART(num)
          if (i2[num] < bufferSize - 1) i2[num]++;
        }

        //if (digitalRead(Varioschalter) == 0)
        if ((BTMode == false) && (WiFiMode == true))
        {
          // now send to WiFi:
          for (byte cln = 0; cln < MAX_NMEA_CLIENTS; cln++)
          {
            if (TCPClient[num][cln])
              TCPClient[num][cln].write(buf2[num], i2[num]);
          }
        }

        //if (digitalRead(Varioschalter) == 1)
        if ((BTMode == true) && (WiFiMode == false))
        {
          // now send to Bluetooth:
          if (SerialBT.hasClient())
          {
            SerialBT.write(buf2[num], i2[num]);
          }
        }

        COM[0]->write(buf2[num], i2[num]); // echo to RS232 output
        COM[1]->write(buf2[num], i2[num]); // echo to RS232 output
        i2[num] = 0;
      }
    }
  }
}
