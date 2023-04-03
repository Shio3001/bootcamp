#include <M5Core2.h>


int gamemode = 0;

int lcd_width = M5.Lcd.width();
int lcd_height = M5.Lcd.height();

class FaseClass {
public:
  void face_draw() {
    eye();
    mouth();
    //表情を描画する
  }

  virtual void eye() const {
    //目
  }

  virtual void mouth() const {
  }
};

class FaseClassPeace : public FaseClass {
public:
  void eye() const override {
  }
  void mouth() const override {
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
  // put your setup code here, to run once:
}

void loop() {  //ボタンの入力処理用
  switch (gamemode) {
    case 0:
      gamemode = gamemode_select();
      break;
    case 1:  //かくれんぼ
      break;
    case 2:  //ダルマさん
      break;
  }
}

int gamemode_select() {
  if (M5.BtnA.wasPressed()) {  //かくれんぼに誘導
    game_class = new Kakurenbo();
    return 1;
  }
  if (M5.BtnB.wasPressed()) {  //ダルマさんが転んだに誘導
    game_class = new Darumasan();
    return 2;
  }
  return 0;
}
