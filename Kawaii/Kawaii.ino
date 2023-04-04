#include <M5Core2.h>
#include <time.h>


//画面が縦向きの場合：高さ（240px）、幅（320px)
//画面が横向きの場合：高さ（320px）、幅（240px）**

int max_int(int a, int b) {
  if (a > b) {
    return a;
  }
  return b;
}

int min_int(int a, int b) {
  if (a < b) {
    return a;
  }
  return b;
}

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

FaseClassPeace *fase_class_peace = new FaseClassPeace();

class GameClass {
public:
  int game_transition;
  virtual void game_loop(){};
  virtual void game_start(){};
  void test_func(){};
};

class Kakurenbo : public GameClass {
private:
public:
  int game_transition = 0;
  int sec[5] = { 0, 10 ,30, 130, 140 };  //ゲーム進行の切り替え

  void game_sec0(){
    M5.Lcd.printf("kakurenbo sec0 \n", game_transition);
  }
  void game_sec1(){
    M5.Lcd.printf("kakurenbo sec1 \n", game_transition);
  }

  int then_loop_sec(time_t nt) {  //今どのセクションなのかを返す関数
    for (int i = 0; i < sizeof(sec) / sizeof(int); i++) {
      M5.Lcd.printf("game sec%d\n", sec[i]);
      if (sec[i] <= nt && nt < sec[i + 1]) {
        return i;
      }
    }
  }

  void game_loop() override {
    time_t now_time = time(NULL);
    M5.Lcd.printf("now_time:(%d) \n", now_time);
    int tm = then_loop_sec(now_time);
    M5.Lcd.printf("kakurenbo secTM(%d) \n", tm);

    switch (tm) {
      case 0:
        game_sec0();
        break;
      case 1:
        game_sec1();
        break;
    }
  }

  //最遅延限度設定として、タイマーの設定を利用する
  //max / min 関数を利用して、進行が早ければ先先進められるようにすること ,

  void game_start() override {
    time_t start_time = time(NULL);
  }
};

class Darumasan : public GameClass {
public:
  int game_transition = 0;
  void game_loop() override{
  };
};

GameClass *game_class = nullptr;

void setup() {
  M5.begin(true, true, true, true);
  M5.Lcd.setTextSize(2);

  // put your setup code here, to run once:
}
// FaseClassPeace fase_class_peace = new FaseClassPeace();
int count = 0;
void loop() {  //ボタンの入力処理用
  M5.Lcd.setCursor(10, 10);
  count++;
  M5.Lcd.printf("count    : [%d] \n", count);
  M5.Lcd.printf("gamemode : [%d] \n", gamemode);
  // M5.Lcd.fillRect(0, 0, lcd_width, lcd_height, BLACK);
  switch (gamemode) {
    case 0:
      M5.Lcd.printf("case 0 input \n");
      gamemode = gamemode_select();
      break;
    case 1:  //かくれんぼ
      M5.Lcd.printf("case 1 input \n");
      game_class->game_loop();
      gamemode = gamemode_end();
      break;
    case 2:  //ダルマさん
      game_class->game_loop();
      gamemode = gamemode_end();
      break;
  }
}

int gamemode_end() {
  M5.update();

  if (M5.BtnC.isPressed()) {
    M5.Lcd.printf("gamemode_end \n");
    return 0;
  }
  return gamemode;
}

int gamemode_select() {
  M5.Lcd.printf("gamemode_select now input \n");
  M5.update();
  if (M5.BtnA.isPressed()) {  //かくれんぼに誘導
    fase_class_peace->clear();
    game_class = new Kakurenbo();
    M5.Lcd.printf("gamemode_select 1 input \n");
    return 1;
  }
  if (M5.BtnB.isPressed()) {  //ダルマさんが転んだに誘導
    game_class = new Darumasan();
    M5.Lcd.printf("gamemode_select 2 input \n");
    return 2;
  }
  return 0;
}
