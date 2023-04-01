#include <LiquidCrystal.h>

#define LED_RED A0 // red led pin
#define LED_BLUE1 6 // blue led pin
#define LED_BLUE2 7 // blue led pin
#define LED_BLUE3 8 // blue led pin
#define LED_BLUE4 9 // blue led pin
#define LED_BLUE5 10 // blue led pin
#define BUTTON_PIN 13

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int myPins[] = {LED_RED, LED_BLUE1, LED_BLUE2,
                LED_BLUE3, LED_BLUE4, LED_BLUE5
               };

int pin = 0; // random choose for turn on led
int millisec = 500;
int gameStatus = 0;
int score = 0;

void setup() {
  lcd.begin(16, 2);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // configurate
  // pin on INPUT for connect button
  for (int i = 0; i < (sizeof(myPins) /
                       sizeof(myPins[0]));
       i++) {
    pinMode(myPins[i], OUTPUT); // configurate pin on
    // OUTPUT in cycle
    digitalWrite(myPins[i], LOW);
  }
}

bool Button = 0;
bool flag = 0;
bool Button_press = 0;
uint32_t timer;

void loop() {
  // In what mode are we?
  switch (gameStatus) {
    case 0:
      playGame();
      break;
    case 1:
      playerWin();
      break;
    case 2:
      playerLose();
      break;
    case 3:
      Game_over();
      break;
    
  }
}


void LCDstart() {
  lcd.display();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SCORE:");
  lcd.setCursor(7, 0);
  lcd.print(score);
}

void playGame() {
  LCDstart();
  pin = random((sizeof(myPins) / sizeof(myPins[0])));
  // random choose pin
  digitalWrite(myPins[pin], HIGH); // turn on this pin
  // if button pushed
  timer = millis();
  while (millis() - timer <= millisec){
    Button = !digitalRead(BUTTON_PIN);
    if (Button && !flag){
      flag = 1;
      Button_press = 1;  
    }
    if (!Button && flag){
      flag = 0;
    }
  
    if (Button_press) {
      Button_press = 0;
      if (myPins[pin] == LED_RED) {
         gameStatus = 1;
      }
      else {
        gameStatus = 2;
      }
  }
}
  digitalWrite(myPins[pin], LOW); //swich off led
}

//void for blinf leds when player win
void playerWin() {
  gameStatus = 0;
  score += 2;
  if (millisec > 50) {
    millisec -= 20;
  }
  int mas_len = sizeof(myPins) / sizeof(myPins[0]);
  for (int i = 1; i >= 0; i--) {
    for (int j = 0; j < mas_len; j++) {
      digitalWrite(myPins[j], i);
    }
    delay(600);
  }
}

void playerLose() {
  gameStatus = 0;
  score -= 2;
  millisec += 10;
  if (score < 0) {
    gameStatus = 3;
  }

   delay(600);
}

void Game_over(){
  lcd.display();
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("!Game  Over!");
  lcd.setCursor(1, 1);
  lcd.print("prs but 2 rest");
  while(1){
      Button = !digitalRead(BUTTON_PIN);
    if (Button && !flag){
      flag = 1;
      Button_press = 1;  
    }
    if (!Button && flag){
      flag = 0;
    }
    if (Button_press){
      Button_press = 0;
      score = 0;
      gameStatus = 0;
      return;
    }
  }
}
