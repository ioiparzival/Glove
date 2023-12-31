#include <WiFi.h>

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
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(F("."));
    attempts++;

    if (attempts > 20)
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
  while (WiFi.status() != WL_CONNECTED)
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

  if (master.connect("192.168.4.1", 80))
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

  if (s1 < 30)
    s1 = 0;
  if (s1 > 255)
    s1 = 255;

  if (s2 < 30)
    s2 = 0;
  if (s2 > 255)
    s2 = 255;

  if (s3 < 30)
    s3 = 0;
  if (s3 > 255)
    s3 = 255;

  if (s2 > 0 && s1 == 0 && s3 == 0)
  {
    /*master.print('A'); master.print(s2); master.print(' ');
    master.print('B'); master.print(s2); master.print(' ');
    master.print('C'); master.print(s2); master.print(' ');
    master.print('D'); master.print(s2); master.print(' ');*/
    master.print("A" + String(s2) + " B" + String(s2) + " C" + String(s2) + " D" + String(s2) + " ");
    master.flush();
  }
  else if (s3 > 0 && s1 == 0 && s2 == 0)
  {
    /*master.print('A'); master.print(-s3); master.print(' ');
    master.print('B'); master.print(-s3); master.print(' ');
    master.print('C'); master.print(-s3); master.print(' ');
    master.print('D'); master.print(-s3); master.print(' ');*/
    master.print("A" + String(-s3) + " B" + String(-s3) + " C" + String(-s3) + " D" + String(-s3) + " ");
    master.flush();
  }
  else if (s2 > 0 && s1 > 0 && s3 == 0)
  {
    /*master.print('A'); master.print(-s2); master.print(' ');
    master.print('B'); master.print(s2); master.print(' ');
    master.print('C'); master.print(-s2); master.print(' ');
    master.print('D'); master.print(s2); master.print(' ');*/
    master.print("A" + String(-s2) + " B" + String(s2) + " C" + String(-s2) + " D" + String(s2) + " ");
    master.flush();
  }
  else if (s2 > 0 && s3 > 0 && s1 == 0)
  {
    /*master.print('A'); master.print(s2); master.print(' ');
    master.print('B'); master.print(-s2); master.print(' ');
    master.print('C'); master.print(s2); master.print(' ');
    master.print('D'); master.print(-s2); master.print(' ');*/
    master.print("A" + String(s2) + " B" + String(-s2) + " C" + String(s2) + " D" + String(-s2) + " ");
    master.flush();
  }
  else
  {
    /*master.print("A0 ");
    master.print("B0 ");
    master.print("C0 ");
    master.print("D0 ");*/
    master.print("A0 B0 C0 D0 ");
    master.flush();
  }

  /*Serial.print(analogRead(SENS_0));
  Serial.print(" ");*/
  Serial.print(s1);
  Serial.print("   ");
  /*Serial.print(analogRead(SENS_1));
  Serial.print(" ");*/
  Serial.print(s2);
  Serial.print("   ");
  /*Serial.print(analogRead(SENS_2));
  Serial.print(" ");*/
  Serial.print(s3);
  Serial.println("");
  // delay(10);

  if (checkConnection() == false)
  {
    connectToWiFi();
  }
}