
// Description:
// This code is designed to establish a connection to a Wi-Fi network and a
// server, read sensor values, and send them to the server in a specific format.

// Libraries Used:
// - WiFi.h: This library provides the ability to connect to a Wi-Fi network
// and interact with it.
// - WiFiClient: This class allows creating a client that can connect to a
// specified internet IP address and port.

// Global Variables:
// - ssid: A string variable storing the SSID of the Wi-Fi network to connect
// to.
// - password: A string variable storing the password of the Wi-Fi network.
// - master: A WiFiClient object used for connecting to the server.

// Constants:
// - SENS_0, SENS_1, SENS_2: Pin definitions for sensors.

// Functions:
// 1. void setup(): Initializes serial communication, connects to Wi-Fi, and
// connects to the server.
// 2. bool checkConnection(): Checks the connection status to Wi-Fi.
// 3. void connectToWiFi(): Attempts to connect to the Wi-Fi network using the
// provided SSID and password.
// 4. void connectToServer(): Attempts to connect to the server with the IP
// address "192.168.4.1" and port 80.
// 5. void loop(): Reads sensor values, processes them, sends data to the
// server, and handles Wi-Fi reconnection if needed.

// Flow of Execution:
// 1. In the setup function, serial communication is initialized, followed by
// connection to Wi-Fi and the server.
// 2. In the loop function, sensor values are read and processed.
// 3. Depending on the sensor values, data is sent to the server in a specific
// format.
// 4. The connection to Wi-Fi is periodically checked, and if lost, the device
// attempts to reconnect.

// Data Processing:
// - Sensor values are mapped to a range of 0-255.
// - Limit values are set for each sensor.
// - Based on sensor conditions, specific data strings are sent to the server.
// - If no specific conditions are met, a default data string with all sensors
// set to 0 is sent.

// Serial Output:
// - Sensor values are printed to the serial monitor for debugging purposes.

#include <WiFi.h>
#include <Other_function.h>
#include <Wifi_function.h>

#define SENS_0 33
#define SENS_1 32
#define SENS_2 35

const char *ssid = "CAR_WIFI";
const char *password = "12345678";

WiFiClient master;

void setup()
{
  Serial.begin(115200);
  Serial.println("Start!");

  connectToWiFi();
  connectToServer();
}

bool checkConnection()
{
  // Serial.println("Проверка соединения с Wi-Fi...");

  int attempts = 0;
  while(WiFi.status() != WL_CONNECTED)
    {
      delay(1000);
      Serial.print(F("."));
      attempts++;

      if(attempts > 20)
        {
          Serial.println("Не удалось установить соединение с Wi-Fi!");
          return false;
        }
    }

  Serial.println("Соединение с Wi-Fi установлено!");
  return true;
}

void connectToWiFi()
{
  Serial.println("Подключение к Wi-Fi...");

  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED)
    {
      delay(500);
      Serial.print(F("."));
    }

  Serial.println(" ");
  Serial.print(F("Connected to Wifi! IP address : "));
  Serial.println(WiFi.localIP());
}

void connectToServer()
{
  Serial.println("Подключение к серверу...");

  if(master.connect("192.168.4.1", 80))
    {
      Serial.println("Connected to server!");
    }
  else
    {
      Serial.println("Connected to server error!");
    }
}
void loop()
{
  int s1 = map(analogRead(SENS_0), 2000, 600, 0, 255);
  int s2 = map(analogRead(SENS_1), 2000, 600, 0, 255);
  int s3 = map(analogRead(SENS_2), 2000, 600, 0, 255);

  // Limit values
  if(s1 < 30)
    s1 = 0;
  if(s1 > 255)
    s1 = 255;

  if(s2 < 30)
    s2 = 0;
  if(s2 > 255)
    s2 = 255;

  if(s3 < 30)
    s3 = 0;
  if(s3 > 255)
    s3 = 255;

  // Check for conditions and send data
  if(s2 > 0 && s1 == 0 && s3 == 0)
    {
      master.print("A" + String(s2) + " B" + String(s2) + " C" + String(s2)
                   + " D" + String(s2) + " ");
      master.flush();
    }
  else if(s3 > 0 && s1 == 0 && s2 == 0)
    {
      master.print("A" + String(-s3) + " B" + String(-s3) + " C" + String(-s3)
                   + " D" + String(-s3) + " ");
      master.flush();
    }
  else if(s2 > 0 && s1 > 0 && s3 == 0)
    {
      master.print("A" + String(-s2) + " B" + String(s2) + " C" + String(-s2)
                   + " D" + String(s2) + " ");
      master.flush();
    }
  else if(s2 > 0 && s3 > 0 && s1 == 0)
    {
      master.print("A" + String(s2) + " B" + String(-s2) + " C" + String(s2)
                   + " D" + String(-s2) + " ");
      master.flush();
    }
  else
    {
      master.print("A0 B0 C0 D0 ");
      master.flush();
    }

  Serial.print(s1);
  Serial.print("   ");

  Serial.print(s2);
  Serial.print("   ");

  Serial.print(s3);
  Serial.println("");

  if(checkConnection() == false)
    {
      connectToWiFi();
    }
}