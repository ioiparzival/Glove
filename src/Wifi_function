void Transmit_string_wifi()  // Передаем строку по wifi машинке
{
  if (sens_val[1] > 0 && sens_val[0] == 0 && sens_val[2] == 0) master.print("A" + String(sens_val[1]) + " B" + String(sens_val[1]) + " C" + String(sens_val[1]) + " D" + String(sens_val[1]) + " ");
  else if (sens_val[2] > 0 && sens_val[0] == 0 && sens_val[1] == 0) master.print("A" + String(-sens_val[2]) + " B" + String(-sens_val[2]) + " C" + String(-sens_val[2]) + " D" + String(-sens_val[2]) + " ");
  else if (sens_val[1] > 0 && sens_val[0] > 0 && sens_val[2] == 0) master.print("A" + String(-sens_val[1]*0.7) + " B" + String(sens_val[1]*0.7) + " C" + String(-sens_val[1]*0.7) + " D" + String(sens_val[1]*0.7) + " ");
  else if (sens_val[0] > 0 && sens_val[2] > 0 && sens_val[1] == 0) master.print("A" + String(sens_val[0]*0.7) + " B" + String(-sens_val[0]*0.7) + " C" + String(sens_val[0]*0.7) + " D" + String(-sens_val[0]*0.7) + " ");
  else master.print("A0 B0 C0 D0 ");
  master.flush();
}

void Wifi_check()  // Проверяем контакт с wifi
{
  if (checkConnection() == false){ connectToWiFi();connectToServer();Blink_conect(2);}
  else Serial.println("WifiConnect");
}

bool checkConnection()  // Проверка соединения с Wi-Fi...
{
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(F("."));
    attempts++;

    if (attempts > 20) {
      Serial.println("Нет соединения с Wi-Fi!");
      return false;
    }
  }

  Serial.println("Соединение с Wi-Fi существует!");
  return true;
}

void connectToWiFi()  // Создание сети wifi
{
  Serial.println("Подключение к Wi-Fi...");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }
  Blink_conect(1);

  Serial.println(" ");
  Serial.print(F("Connected to Wifi! IP address : "));
  Serial.println(WiFi.localIP());
}

void connectToServer()  // Подключение через сервер  с машинкой
{
  Serial.println("Подключение к серверу...");

  if (master.connect("192.168.4.1", 80)) {
    Serial.println("Connected to server!");
    Blink_conect(1);
  } else Serial.println("Connected to server error!");
}
