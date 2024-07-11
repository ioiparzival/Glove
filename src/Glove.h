#include <WiFi.h>
#include <Wifi_function.h>
#include <Other_function.h>

const char *ssid = "CAR_WIFI";
const char *password = "12345678";
int sens_val[3], PIN_SENS[3] = {33, 32, 35}, PIN_LED[3] = {19, 18, 5};

WiFiClient master;

void setup()
{
  Serial.begin(115200);
  Serial.println("Start!");

  for(int i = 0; i < 3; i++)
    {
      ledcSetup(i, 40000, 8); // настройка шим для светодиодов
    }
  // (i-канал;40000-частота;8(біт)-разрешение)
  for(int i = 0; i < 3; i++)
    {
      ledcAttachPin(PIN_LED[i], i); // настройка связи пинов с их каналами
    }
}

void loop()
{
  if(WiFi.status() != WL_CONNECTED){                           // Автоконнект/Реконнект
    connectToWiFi();
    connectToServer();
  }
  Enter_and_convert_values(); // Ввод c АЦП значений напряжения и
                              // преобразование в нужний диапозон для
                              // последующей подачи значений машинке
  Values_per_LED(); // Подача значений в виде шим сигнала на светодиод
  for(int i = 0; i < 3; i++)
    {
      Serial.printf("sens_val[%d] = %d\n", i, sens_val[i]);
    }
  // Выводим значения в Serial порт
  Transmit_string_wifi(); // Передаем строку по wifi машинке
  delay(50);
}