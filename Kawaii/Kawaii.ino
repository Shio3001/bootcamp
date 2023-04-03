#include <M5Core2.h>


class GameClass {
private:
public:
  virtual void game_loop() const;
};

class Kakurenbo : public GameClass {
public:
  void game_loop() const override{

  };
};
class Darumasan : public GameClass {
public:
  void game_loop() const override{

  };
};


int gamemode = 0;
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

class FaseControl {
  void face_draw() {
    //表情を描画する
  }

  void eye() {
    //目
  }

  void mouth() {
  }
};
