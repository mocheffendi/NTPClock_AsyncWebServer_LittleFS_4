void newDelay(unsigned long miliseconds)
{
  unsigned long timeStart = millis();
  unsigned long diff = (millis() - timeStart);
  while (diff < miliseconds) //delay miliseconds
  {
    diff = (millis() - timeStart);
    yield();  //Important! prevent Soft WDT reset.
  }
}

/*
  timer.disable(TimerNTP);
  timer.disable(TimerJam);
  timer.disable(TimerTanggal);
  timer.disable(TimerWeatherUpdate);
*/

/*
  timer.enable(TimerNTP);
  timer.enable(TimerJam);
  timer.enable(TimerTanggal);
  timer.enable(TimerWeatherUpdate);
*/
