#include <M5Core2.h>


//画面が縦向きの場合：高さ（240px）、幅（320px)
//画面が横向きの場合：高さ（320px）、幅（240px）**

int gamemode = 0;

int lcd_width = M5.Lcd.width();
int lcd_height = M5.Lcd.height();

class FaseClass {
public:
  void face_draw() {
    draw();
    clear();
    //表情を描画する
  }

  virtual void draw() const {
    //目
  }

  virtual void clear() const {
  }
};

class FaseClassPeace : public FaseClass {
public:
  void draw() const override {
    M5.Lcd.fillRect(10, 10, 10, 100, RED);
    M5.Lcd.fillRect(300, 10, 10, 100, RED);
  }
  void clear() const override {
    M5.Lcd.fillRect(0, 0, lcd_width, lcd_height, BLACK);
  }
};

// FaseClassPeace fase_class_peace;

class GameClass {
public:
  int game_transition;
  virtual void game_loop() const;
};

class Kakurenbo : public GameClass {
private:
public:
  int game_transition = 0;
  void game_loop() const override{

  };
};

class Darumasan : public GameClass {
public:
  int game_transition = 0;
  void game_loop() const override{

  };
};

GameClass *game_class = nullptr;

void setup() {
  M5.begin(true, true, true, true);
  M5.Lcd.setTextSize(2);
  
  // put your setup code here, to run once:
}
FaseClassPeace fase_class_peace = FaseClassPeace();
int count = 0;
void loop() {  //ボタンの入力処理用
M5.Lcd.setCursor(10, 10);
count ++;
M5.Lcd.printf("count    : [%d]\n",count);
M5.Lcd.printf("gamemode : [%d]\n",gamemode);
// M5.Lcd.fillRect(0, 0, lcd_width, lcd_height, BLACK);
  switch (gamemode) {
    case 0:
      M5.Lcd.printf("case 0 input\n");
      gamemode = gamemode_select();
      break;
    case 1:  //かくれんぼ
      M5.Lcd.printf("case 1 input\n");
      gamemode = gamemode_end();
      break;
    case 2:  //ダルマさん
      gamemode = gamemode_end();
      break;
  }
}

int gamemode_end(){
    M5.update();

    if (M5.BtnC.isPressed()){
      M5.Lcd.printf("gamemode_end\n");
      return 0;
    }
    return gamemode;
}

int gamemode_select() {
  M5.Lcd.printf("gamemode_select now input\n");
  M5.update();
  if (M5.BtnA.isPressed()) {  //かくれんぼに誘導
    game_class = new Kakurenbo();
    M5.Lcd.printf("gamemode_select 1 input\n");
    delay(500);
    return 1;
  }
  if (M5.BtnB.isPressed()) {  //ダルマさんが転んだに誘導
    game_class = new Darumasan();
    M5.Lcd.printf("gamemode_select 2 input\n");
    return 2;
  }
  return 0;
}
