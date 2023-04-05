#include <M5Core2.h>
#include <time.h>

//画面が縦向きの場合：高さ（240px）、幅（320px)
//画面が横向きの場合：高さ（320px）、幅（240px）**

int breadth = 5;
bool debug = false;

void lcd_clear() {
  int lcd_width = M5.Lcd.width();
  int lcd_height = M5.Lcd.height();
  M5.Lcd.fillScreen(LIGHTGREY);
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
  if (!debug) {
    return;
  }

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

int face_draw_number = -1;

class FaseClass {
public:
  void face_draw() {
    draw();
    //表情を描画する
  }

  int face_draw_class_number = -1;

  void run_draw_clear(int this_number){
    if (this_number != face_draw_number){
      face_draw_number = this_number;
      lcd_clear();
    }
  }

  virtual void draw() {
  }

  void text_center_draw(int x, int y, int font_size, String text) {
    int lcd_width = M5.Lcd.width();
    int lcd_height = M5.Lcd.height();
    int lcd_width_center = lcd_width / 2;
    int lcd_height_center = lcd_height / 2;
    M5.Lcd.setTextSize(font_size);
    M5.Lcd.setTextColor(BLACK, BLACK);
    M5.Lcd.drawString(text, lcd_width_center + x, lcd_height_center + y);
  }

  void fill_rect_center_draw(int x, int y, int width, int height) {
    int lcd_width = M5.Lcd.width();
    int lcd_height = M5.Lcd.height();
    int lcd_width_center = lcd_width / 2;
    int lcd_height_center = lcd_height / 2;

    int H_width = width / 2;
    int H_height = height / 2;
    //WHITE

    M5.Lcd.fillRect(lcd_width_center + (x - H_width), lcd_height_center + (y - H_height), width, height, BLACK);  //（x1, y1) (x2, y2)
  }


  // int calculation_x(int shift_x) {
  //   return lcd_width_center + shift_x;
  // }
  // int calculation_y(int shift_y) {
  //   return lcd_height_center + shift_y;
  // }
};

class FaseClassStartUp : public FaseClass {
public:
  int face_draw_class_number = 1000;
  void draw() override {
    this->run_draw_clear(face_draw_class_number);
    text_center_draw(-120,100,2,"kakurenbo");
  }
};


class FaseClass0 : public FaseClass {
public:
  int face_draw_class_number = 0;
  void draw() override {
    this->run_draw_clear(face_draw_class_number);
    // fill_rect_center_draw(-70, -40, 20, 100);
    // fill_rect_center_draw(70, -40, 20, 100);
    // fill_rect_center_draw(0, 60, 100, 20);
    text_center_draw(80,20,5,"!");
  }
};


class FaseClass1 : public FaseClass {
public:
  int face_draw_class_number = 1;
  void draw() override {
    this->run_draw_clear(face_draw_class_number);
    fill_rect_center_draw(-70, -40, 20, 100);
    fill_rect_center_draw(70, -40, 20, 100);
    fill_rect_center_draw(0, 60, 100, 20);
  }
};


class FaseClass2 : public FaseClass {
public:
  int face_draw_class_number = 2;
  void draw() override {
    this->run_draw_clear(face_draw_class_number);
    fill_rect_center_draw(-70, -40, 20, 100);
    fill_rect_center_draw(70, -40, 20, 100);
    fill_rect_center_draw(0, 60, 100, 20);
  }
};

class FaseClass3 : public FaseClass {
public:
  int face_draw_class_number = 3;
  void draw() override {
    this->run_draw_clear(face_draw_class_number);
    fill_rect_center_draw(-70, -40, 20, 100);
    fill_rect_center_draw(70, -40, 20, 100);
    fill_rect_center_draw(0, 60, 100, 20);
  }
};

class FaseClass4 : public FaseClass {
public:
  int face_draw_class_number = 4;
  void draw() override {
    this->run_draw_clear(face_draw_class_number);
    fill_rect_center_draw(-70, -40, 20, 100);
    fill_rect_center_draw(70, -40, 20, 100);
    fill_rect_center_draw(0, 60, 100, 20);
  }
};

class FaseClass102 : public FaseClass {
public:
  int face_draw_class_number = 102;
  void draw() override {
    fill_rect_center_draw(-70, -40, 20, 100);
    fill_rect_center_draw(70, -40, 20, 100);
    fill_rect_center_draw(0, 60, 100, 20);
  }
};

FaseClass *face_class_start_up = new FaseClassStartUp();
FaseClass *fase_class0 = new FaseClass0();
FaseClass *fase_class1 = new FaseClass1();
FaseClass *fase_class3 = new FaseClass2();
FaseClass *fase_class4 = new FaseClass3();
FaseClass *fase_class102 = new FaseClass102();

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
    fase_class0->face_draw();
  }
  void game_sec1() {
    // fase_class2->face_draw();
  }

  void game_clear() {  //見つかった時の処理
    TouchPoint_t pos = M5.Touch.getPressPoint();
    const int xpos = pos.x;
    const int ypos = pos.y;

    if (xpos == -1) { return; };
    set_game_transition(102);
    set_operation_time();
  }

  void game_loss() {  //見つからなかった時の処理
    TouchPoint_t pos = M5.Touch.getPressPoint();
    const int xpos = pos.x;
    const int ypos = pos.y;

    if (xpos == -1) { return; };
    set_game_transition(102);
    set_operation_time();
  }

  void game_sec102() {  //ユーザー終了待機処理
    TouchPoint_t pos = M5.Touch.getPressPoint();
    const int xpos = pos.x;
    const int ypos = pos.y;
    if (xpos == -1) { return; };
    set_game_transition(900);
    // fase_class1->face_draw();
  }

  void game_exit() {  //ゲーム終了処理
    set_game_transition(0);
    gamemode = 0;
    // M5.Speaker.end();
  }

  void game_sec2() {
    game_clear();
    // fase_class2->face_draw();
  }
  void game_sec3() {
    // M5.Speaker.beep();        // ビープ開始
    game_clear();
    // fase_class1->face_draw();
  }
  void game_sec4() {
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
        game_sec4();
        break;
      case 102:  //見つかった！

        if (get_operation_time()) {
          game_sec102();
        }


        break;
      case 900:  //終了関数

        game_exit();
        lcd_clear();


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
  M5.Lcd.fillScreen(LIGHTGREY);
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
      face_class_start_up->draw();
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
