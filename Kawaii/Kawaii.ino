#include <M5Core2.h>
#include <time.h>


//画面が縦向きの場合：高さ（240px）、幅（320px)
//画面が横向きの場合：高さ（320px）、幅（240px）**

int lcd_width = M5.Lcd.width();
int lcd_height = M5.Lcd.height();

void lcd_clear() {
  M5.Lcd.fillRect(0, 0, lcd_width, lcd_height, BLACK);
}

time_t last_operation_time;
void set_operation_time() {  //チャタリング対策
  last_operation_time = time(NULL);
}
bool get_operation_time() {
  time_t ot_now_time = time(NULL);
  return (ot_now_time - last_operation_time) > 1;
}

void debug_text(int row, String text) {
  M5.Lcd.setCursor(10, 15 * row);
  // M5.Lcd.printf(text);
  // M5.Lcd.drawString(text,10,100*row);
  M5.Lcd.println(text + "\n");
}

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

class FaseClass {
public:
  void face_draw() {
    draw();
    //表情を描画する
  }

  virtual void draw() const {
  }
};

class FaseClass1 : public FaseClass {
public:
  void draw() const override {
    M5.Lcd.fillRect(50, 30, 5, 30, WHITE);
    M5.Lcd.fillRect(70, 30, 5, 30, WHITE);
    M5.Lcd.fillRect(60, 50, 30, 5, WHITE);
  }
};


class FaseClass2 : public FaseClass {
public:
  void draw() const override {
    M5.Lcd.fillRect(50, 30, 30, 5, WHITE);
    M5.Lcd.fillRect(70, 30, 30, 5, WHITE);
    M5.Lcd.fillRect(60, 50, 30, 5, WHITE);
  }
};


FaseClass *fase_class1 = new FaseClass1();
FaseClass *fase_class2 = new FaseClass2();

class GameClass {
public:
  int game_transition;
  virtual void game_loop(){};
  virtual void game_start(){};
  virtual void set_game_transition(int v){};
  void test_func(){};
};

class Kakurenbo : public GameClass {
private:
public:
  int game_transition = 0;
  time_t start_time;

  void set_game_transition(int v) {
    game_transition = v;
  }

  int sec[6] = { 0, 10, 30, 50, 60, 10000 };  //ゲーム進行の切り替え

  void game_sec0() {
    fase_class1->face_draw();
  }
  void game_sec1() {
    fase_class2->face_draw();
  }

  void game_clear() {  //見つかった時の処理
    TouchPoint_t pos = M5.Touch.getPressPoint();
    const int xpos = pos.x;
    const int ypos = pos.y;

    if (xpos == -1) { return; };
    set_game_transition(102);
    set_operation_time();
  }

  void game_sec102() {
    TouchPoint_t pos = M5.Touch.getPressPoint();
    const int xpos = pos.x;
    const int ypos = pos.y;
    if (xpos == -1) { return; };
    set_game_transition(900);
  }

  void game_exit() {  //ゲーム終了処理
    set_game_transition(0);
    gamemode = 0;
    // M5.Speaker.end();
  }

  void game_sec2() {
    game_clear();
  }
  void game_sec3() {
    // M5.Speaker.beep();        // ビープ開始
    game_clear();
  }


  int then_loop_sec(time_t nt) {  //今どのセクションなのかを返す関数
    for (int i = 0; i < sizeof(sec) / sizeof(int) - 1; i++) {
      if (sec[i] <= nt && nt < sec[i + 1]) {
        return i;
      }
    }
    return -1;
  }

  void game_loop() override {
    time_t now_time = time(NULL) - start_time;
    const int tlss = then_loop_sec(now_time);

    set_game_transition(max_int(tlss, game_transition));

    debug_text(1, "gamemode kakurenbo");
    debug_text(2, "now_time.  " + String(now_time));
    debug_text(3, "start_time " + String(start_time));
    debug_text(4, "game_transition " + String(game_transition));

    switch (game_transition) {
      case 0:  //説明時間
        game_sec0();
        break;
      case 1:  //隠す時間
        game_sec1();
        break;
      case 2:  //探す時間
        game_sec2();
        break;
      case 3:  //探す時間（ヒントタイム）
        game_sec3();
        break;
      case 4:  //見つからなかった
        break;
      case 102:  //見つかった！

        if (get_operation_time()) {
          game_sec102();
        }


        break;
      case 900:  //終了関数

        game_exit();
        clear();


        break;
    }
  }

  //最遅延限度設定として、タイマーの設定を利用する
  //max / min 関数を利用して、進行が早ければ先先進められるようにすること ,

  void game_start() override {
    start_time = time(NULL);
    // M5.Speaker.setVolume(4);
  }
};

class Darumasan : public GameClass {
public:
  int game_transition = 0;
  time_t start_time;
  void game_loop() override{};
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

  count++;
  debug_text(0, "count" + String(count));

  // M5.Lcd.fillRect(0, 0, lcd_width, lcd_height, BLACK);
  switch (gamemode) {
    case 0:
      gamemode = gamemode_select();
      break;
    case 1:  //かくれんぼ
      {
        game_class->game_loop();

        gamemode = gamemode_end();
        break;
      }

      // case 2:  //ダルマさん
      //   game_class->game_loop();
      //   gamemode = gamemode_end();
      //   break;
  }
}

int gamemode_end() {
  M5.update();

  if (M5.BtnC.isPressed()) {
    return 0;
  }
  return gamemode;
}

int gamemode_select() {

  M5.update();
  if (M5.BtnA.isPressed()) {  //かくれんぼに誘導
    // fase_class_peace->clear();
    game_class = new Kakurenbo();
    game_class->game_start();
    return 1;
  }
  if (M5.BtnB.isPressed()) {  //ダルマさんが転んだに誘導
    game_class = new Darumasan();
    return 2;
  }
  return 0;
}
