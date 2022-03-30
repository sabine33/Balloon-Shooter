/*
Sabin Khanal
2013
Khwopa Engineering College
Third Semester
Minor project for C/C++
*/

#include < allegro.h >
#include < fstream.h >

// initialize important variables
int target, magic, delay = 30, flag1 = 0, p = 1000, score = 0, life = 5, count, pass = 0, level = 0;
int balloon_first_xpos = 400, balloon_first_ypos = 1200, balloon_second_xpos = 600, balloon_second_ypos = 900, balloon_third_xpos = 800, balloon_third_ypos = 1400, balloon_fourth_xpos = 1200, balloon_fourth_ypos = 1100, mx = 0, my = 100, px = 0, py = 100, cx = 0, cy = 0;

int bal1dec, bal2dec, bal3dec, bal4dec, win = 0;

// background music: pointer
SAMPLE *music;
int type = 3;

// Pointer for main assets
BITMAP *sc1, *sc2, *sc3, *sc4, *bal1, *bal2, *bal3, *bal4, *missile, *plane, *bg, *bg1, *flag;
BITMAP *bird, *bird1;
int hsflag = 0;
// buffer pointer for background
BITMAP *buffer;

int cx1 = 1000, cx2 = 1000, cy1 = 100, cy2 = 150, cx3 = 1800, cy3 = 100;
BITMAP *fire, *cloud1, *cloud2;
int scores;
// balloon movement
int bx = rand() % (500 - 100) + 1000;
int by = rand() % (700 - 100) + 100;

void init();
void deinit();
void start();
void play();
void checkballoon();
void smartmotion();

// set highscore
void highscore()
{

  ifstream fin;
  fin.open("score.txt");
  fin >> scores;

  if (score >= scores)
  {
    ofstream fout;
    fout.open("score.txt");
    fout << score;
  }
}

// start
int main()
{
  init();
  start();
  // system("balloon.vbs");
  install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
  // background buffer
  buffer = create_bitmap(1400, 800);

  srand(time(NULL));

  target = rand() % (10000) + 4000;

  // while life is
  while (life >= 0)
  {
    play();
  }
  deinit();
  return 0;
}
END_OF_MAIN()

void init()
{
  int depth, res;
  allegro_init();
  depth = desktop_color_depth();
  if (depth == 0)
    depth = 32;
  set_color_depth(depth);
  res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1300, 700, 0, 0);

  if (res != 0)
  {
    allegro_message(allegro_error);
    exit(-1);
  }

  install_timer();
  install_keyboard();
  install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
  buffer = create_bitmap(1400, 800);
}

void play()
{

  clear_to_color(buffer, makecol(0, 0, 0));
  int sound = play_sample(music, 50, 128, 1000, 0);
  blit(bg, buffer, 0, 0, 0, 0, bg - > w + 500, bg - > h + 400);
  draw_sprite(buffer, cloud1, cx1, cy1);
  draw_sprite(buffer, cloud2, cx2, cy2);
  draw_sprite(buffer, cloud2, cx3, cy3);
  srand(time(NULL));
  int n;
  n++;
  if (n % 2 == 0)
  {
    draw_sprite(buffer, bird, bx, by - 28);
  }
  else
  {
    draw_sprite(buffer, bird1, bx, by);
  }
  draw_sprite(buffer, flag, 1060, 150);

  draw_sprite(buffer, missile, mx + 10, my + 22);
  draw_sprite(buffer, plane, 0, py);
  draw_sprite(buffer, bal1, balloon_first_xpos, balloon_first_ypos);
  draw_sprite(buffer, bal2, balloon_second_xpos, balloon_second_ypos);
  draw_sprite(buffer, bal3, balloon_third_xpos, balloon_third_ypos);
  draw_sprite(buffer, bal4, balloon_fourth_xpos, balloon_fourth_ypos);

  draw_sprite(buffer, bg1, 0, 500);
  textprintf_ex(buffer, font, 20, 10, makecol(0, 255, 255), 1, "target:: %d  highscore::%d", target, scores);
  textprintf_ex(buffer, font, 1000, 10, makecol(0, 255, 255), 1, "score::  %d   life::  %d  level::  %d", score, life, level);
  if (life <= 2)
  {
    textprintf_ex(buffer, font, 400, 200, makecol(0, 0, 255), -1, "YOU ARE NEAR TO DEATH PRESS B TO BUY LIFE OVER 2000 score expense");
  }
  draw_sprite(screen, buffer, 0, 0);

  balloon_first_ypos -= rand() % (5 - 2) + 3;
  balloon_second_ypos -= rand() % (7 - 4) + 4;
  balloon_third_ypos -= rand() % (6 - 3) + 3;
  balloon_fourth_ypos -= rand() % (8 - 4) + 4;
  my = py;
  bx += 4;
  if (bx >= 1300)
  {
    bx = -100;
    by = rand() % (700 - 100) + 100;
  }
  checkballoon();
  smartmotion();
  bx += 3;
  if (score >= p && score <= p + 100)
  {

    allegro_message("level upped to:: %d \n life remained:: %d \n score to win:: %d", level + 1, life, target - score);
    p += 1000;
  }
  if (score >= scores && hsflag == 0)
  {
    allegro_message("YOU BROKE THE HIGH SCORE...HURRAY \n YOU ARE THE REAL PLAYER");
    hsflag = 1;
  }
  if (score >= target && win == 0)
  {

    allegro_message("YOU ARE WINNER...HURRAY");
    win = 1;
  }
  if (key[KEY_DOWN])
  {
    py += 10;
    if (py > 600)
      py = 600;
  }

  if (key[KEY_C])
    mx += 30;
  if (key[KEY_UP])
  {
    py -= 10;
    my -= 5;
  }
  if (life <= 2 && key[KEY_B] && score >= 2000)

  {
    rest(1000);
    score -= 2000;
    life += 1;
  }
  if (key[KEY_C])
  {

    count++;
  }
  if (count > 0)
    mx += 60;
  if (mx > 1250)
  {
    mx = 0;
    count = 0;
  }

  if (key[KEY_P])
  {
    system("pause");
  }
  if (key[KEY_Q])
  {
    allegro_message("GAME IS NOW ENDED \n score:: %d \n level::%d ", score, level);
    exit(0);
  }
  if (type == 2)
    delay = 20 - level;
  if (type == 3)
    delay = 25 - level;
  if (type == 1)
    delay = 15 - (level * 0.5);
  rest(delay);
  level = score / 1000;
  cx1 -= rand() % (2) + 1;
  cx3 -= rand() % (2) + 1;
  cx2 -= rand() % (1) + 1;
  magic = rand() % 2 + 1;
  if (magic == 1)
  {
    cy1 -= rand() % (1) + 1;
    cy2 += rand() % (1) + 1;
    cy3 -= rand() % 1 + 1;
  }
  else
  {
    cy1 += rand() % (1) + 1;
    cy2 -= rand() % (1) + 1;
    cy3 += rand() % 1 + 1;
  }
  if (cx1 <= 0)
  {
    cx1 = rand() % 300 + 1000;
    cy1 = rand() % 100 + 100;
  }
  if (cx2 <= 0)
  {
    cx2 = rand() % 300 + 1200;
    cy2 = rand() % 100 + 100;
  }
  if (cx3 <= 0)
  {
    cx3 = rand() % 300 + 1200;
    cy3 = rand() % 100 + 100;
  }

  clear_bitmap(buffer);
}

void start()
{

  sc1 = load_bitmap("screen1.bmp", NULL);
  sc2 = load_bitmap("screen2.bmp", NULL);
  sc3 = load_bitmap("screen3.bmp", NULL);
  sc4 = load_bitmap("screen4.bmp", NULL);
  fire = load_bitmap("fire.bmp", NULL);
  bg = load_bitmap("bge.bmp", NULL);
  bg1 = load_bitmap("bg1.bmp", NULL);
  bal1 = load_bitmap("bal1.bmp", NULL);
  bal2 = load_bitmap("bal2.bmp", NULL);
  bal3 = load_bitmap("bal3.bmp", NULL);
  bal4 = load_bitmap("bal4.bmp", NULL);
  plane = load_bitmap("plane.bmp", NULL);
  missile = load_bitmap("missile.bmp", NULL);
  music = load_sample("music.wav");
  bird = load_bitmap("bi.bmp", NULL);
  bird1 = load_bitmap("bi1.bmp", NULL);
  flag = load_bitmap("flag.bmp", NULL);
  missile = load_bitmap("missile.bmp", NULL);
  cloud1 = load_bitmap("c1.bmp", NULL);
  cloud2 = load_bitmap("c.bmp", NULL);
  clear_to_color(buffer, makecol(0, 0, 0));

  blit(sc1, screen, 0, 0, 0, 0, sc1 - > w, sc1 - > h);
  readkey();
  blit(sc2, screen, 0, 0, 0, 0, sc2 - > w, sc2 - > h);
  readkey();
  blit(sc3, screen, 0, 0, 0, 0, sc3 - > w, sc3 - > h);
  char ch = readkey();
  if (ch == 'e' || ch == 'q')
    exit(1);
  if (ch == 'i')
  {
    clear_to_color(buffer, makecol(0, 0, 0));
    blit(sc2, screen, 0, 0, 0, 0, sc2 - > w, sc2 - > h);
    readkey();
  }
  if (ch == 'h')
  {
    type = 1;
  }
  if (ch == 'm')
  {
    type = 2;
  }
  ifstream fin;
  fin.open("score.txt");
  fin >> scores;
}

void deinit()
{
  ifstream fin;
  fin.open("score.txt");
  fin >> scores;
  if (score > scores)
  {
    allegro_message("HIGH SCORE BREAKED");
  }

  scores = score;
  allegro_message("GAME IS NOW ENDED \n score:: %d \n level::%d ", score, level);
  highscore();
  exit(0);
  clear_keybuf();
}

void checkballoon()
{
  if (balloon_first_ypos < -100)
  {
    balloon_first_xpos = rand() % (1100 - 700) + 300;
    balloon_first_ypos = rand() % (1600 - 1000) + 1000;
    pass = 0;
    bal1dec = 0;
  }
  if (balloon_second_ypos < -100)
  {
    balloon_second_xpos = rand() % (1300 - 700) + 300;
    balloon_second_ypos = rand() % (1200 - 1000) + 1000;
    pass = 0;
    bal2dec = 0;
  }
  if (balloon_third_ypos < -100)
  {
    balloon_third_xpos = rand() % (1300 - 700) + 600;
    balloon_third_ypos = rand() % (1800 - 1000) + 1000;
    pass = 0;
    bal3dec = 0;
  }
  if (balloon_fourth_ypos < -100)
  {
    balloon_fourth_xpos = rand() % (1300 - 700) + 400;
    balloon_fourth_ypos = rand() % (1600 - 1400) + 1400;
    pass = 0;
    bal4dec = 0;
  }
  if (balloon_first_ypos <= -10 && balloon_first_ypos >= -30 && bal1dec == 0)
  {
    life -= 1;
    bal1dec = 1;
  }
  if (balloon_second_ypos <= -10 && balloon_second_ypos >= -30 && bal2dec == 0)
  {
    life -= 1;
    bal2dec = 1;
  }
  if (balloon_third_ypos <= -10 && balloon_third_ypos >= -30 && bal3dec == 0)
  {
    life -= 1;
    bal3dec = 1;
  }
  if (balloon_fourth_ypos <= -10 && balloon_fourth_ypos >= -30 && bal4dec == 0)
  {
    life -= 1;
    bal4dec = 1;
  }
  if (mx + 40 >= balloon_first_xpos && my >= balloon_first_ypos - 40 && my <= balloon_first_ypos + 40)
  {

    draw_sprite(screen, fire, balloon_first_xpos, balloon_first_ypos);

    balloon_first_ypos = -300;
    score += 100;
    int sound = play_sample(music, 300, 128, 1000, 0);
    pass = 1;
  }
  if (mx + 40 >= balloon_second_xpos && my >= balloon_second_ypos - 40 && my <= balloon_second_ypos + 40)
  {

    draw_sprite(screen, fire, balloon_second_xpos, balloon_second_ypos);
    balloon_second_ypos = -300;
    score += 75;
    int sound = play_sample(music, 300, 128, 1000, 0);
    pass = 1;
  }
  if (mx + 40 >= balloon_third_xpos && my >= balloon_third_ypos - 40 && my <= balloon_third_ypos + 40)
  {
    draw_sprite(screen, fire, balloon_third_xpos, balloon_third_ypos);
    balloon_third_ypos = -300;
    score += 25;
    int sound = play_sample(music, 300, 128, 1000, 0);
    pass = 1;
  }
  if (mx + 40 >= balloon_fourth_xpos && my >= balloon_fourth_ypos - 40 && my <= balloon_fourth_ypos + 40)
  {
    draw_sprite(screen, fire, balloon_fourth_xpos, balloon_fourth_ypos);
    balloon_fourth_ypos = -300;
    score += 50;
    int sound = play_sample(music, 300, 128, 1000, 0);
    pass = 1;
  }
}

void smartmotion()
{

  if (balloon_third_xpos >= 1300)
    balloon_third_xpos -= 200;
  if (balloon_second_xpos >= 1300)
    balloon_second_xpos -= 200;
  if (balloon_first_xpos >= 1300)
    balloon_first_xpos -= 200;
  if (balloon_fourth_xpos >= 1300)
    balloon_fourth_xpos -= 200;
  if (balloon_first_xpos <= 100)
    balloon_first_xpos = 200;
  if (balloon_second_xpos <= 100)
    balloon_second_xpos = 200;
  if (balloon_third_xpos <= 100)
    balloon_third_xpos = 200;
  if (balloon_fourth_xpos <= 100)
    balloon_fourth_xpos = 200;

  if (level >= 1)
  {
    srand(time(NULL));
    magic = rand() % 2 + 1;
    if (magic == 1)
    {
      balloon_first_xpos += 2;
      balloon_second_xpos += 1;
      balloon_third_xpos -= 2;
      balloon_fourth_xpos -= 0.5;
      balloon_second_ypos += 1;
      balloon_third_ypos += 2;
    }
    if (magic == 2)
    {
      balloon_first_xpos -= 1;
      balloon_second_xpos -= 2;
      balloon_third_xpos += 1;
      balloon_fourth_xpos += 0.5;
      balloon_third_ypos -= 2;
    }
  }

  if (my >= balloon_first_ypos - 30 && my <= balloon_first_ypos - 20)
  {
    balloon_first_ypos += rand() % (120 - 100) + 100;
  }
  if (my >= balloon_first_ypos - 50 && my <= balloon_first_ypos - 30)
  {
    balloon_first_ypos -= rand() % (120 - 100) + 100;
  }
  if (my >= balloon_fourth_ypos - 30 && my <= balloon_fourth_ypos - 20)
  {
    balloon_fourth_ypos += rand() % (120 - 100) + 100;
  }
  if (my >= balloon_fourth_ypos - 50 && my <= balloon_fourth_ypos - 30)
  {
    balloon_fourth_ypos -= rand() % (120 - 100) + 100;
  }
}