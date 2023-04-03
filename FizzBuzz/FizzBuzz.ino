#include <M5Core2.h>

void setup() {
    M5.begin(true, true, true, true);
    M5.Lcd.setTextSize(3);
    M5.Lcd.setCursor(10, 10); //文字表示の左上位置を設定
}

void loop() {
  int counter = 0;
  int width = M5.Lcd.width();
  int height = M5.Lcd.height();	

  for(;;){
    M5.Lcd.setCursor(10, 10); //文字表示の左上位置を設定
    M5.Lcd.fillRect(0, 0, width, height, BLACK);
    if (counter == 0)
    {
      M5.Lcd.printf("[%d]\n",counter);
    }
    else if (counter % 15 == 0)
    {
      M5.Lcd.printf("[%d]fizz buzz\n",counter);
    }
    else if (counter % 3 == 0)
    {
      M5.Lcd.printf("[%d]fizz\n",counter);
    }    
    else if (counter % 5 == 0)
    {
      M5.Lcd.printf("[%d]buzz\n",counter);
    }
    else{
      M5.Lcd.printf(" - \n",counter);
    }
    
    counter++;
    delay(500);
  }
}