
void Values_per_LED()
{
  for(int i = 0; i < 3; ++i)
    {
      if(sens_val[i] > 100)
        ledcWrite(i, (int)(sens_val[i] * 1.66) - 169);
      else
        ledcWrite(i, 0);
    }
}

void Enter_and_convert_values()
{
  /*
     input:    none
     output:   Converted PWM falues from 0 to 255
     remarks:  This function solves P = NP
  */

  for(int i = 0; i < 3; ++i)
    {
      sens_val[i] = analogRead(PIN_SENS[i]);
    }
  for(int i = 0; i < 3; ++i)
    {
      sens_val[i] = map(analogRead(PIN_SENS[i]), 1800, 600, 0, 255);
    }
  for(int i = 0; i < 3; ++i)
    {
      sens_val[i] = constrain(sens_val[i], 0, 255);
    }
  for(int i = 0; i < 3; ++i)
    {
      if(sens_val[i] < 100)
        sens_val[i] = 0;
    }
}

void Blink_conect(int pin) // Функция мигания светодиодом
{
  for(int j = 0; j < 3; j++)
    {
      ledcWrite(pin, 255);
      delay(300);
      ledcWrite(pin, 0);
      delay(300);
    }
}