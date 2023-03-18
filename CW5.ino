#define BUZZ_PIN 7
#define LED_PIN_1 12
#define LED_PIN_2 3
#define BUT_PIN_1 13
#define BUT_PIN_2 2


void setup()
{
  pinMode(BUZZ_PIN, OUTPUT);  // pinMode(НОМЕР ПИНА, ЧТО ПИН ДЕЛАЕТ)
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
  pinMode(BUT_PIN_1, INPUT);
  pinMode(BUT_PIN_2, INPUT);

}

int random_time;

bool Button_1 = false;
bool Button_2 = false;

bool flag_but1 = false;
bool flag_but2 = false;

bool Button_press_1 = false;
bool Button_press_2 = false;

void loop()
{
  random_time = random(1000, 10000+1);   // random(1, 5+1); (1,5)
  delay(random_time);
  
  tone(BUZZ_PIN, 2000, 100);  // tone(пин динамика, частота (Гц), продолжительность (миллисекундах))
  
  while (1){
    
    Button_1 = digitalRead(BUT_PIN_1);
    Button_2 = digitalRead(BUT_PIN_2);

    // Button_1 = 1;  flag_but1 = 0; 
    if (Button_1 && !flag_but1){
      flag_but1 = true;
      Button_press_1 = true;
    }

    if (!Button_1 && flag_but1){
      flag_but1 = false;
    }

    if (Button_2 && !flag_but2){
      flag_but2 = true;
      Button_press_2 = true;
    }

    if (!Button_2 && flag_but2){
      flag_but2 = false;
    }

        
    if (Button_press_1) {
      Button_press_1 = false;
      digitalWrite(LED_PIN_1, HIGH);
      tone(BUZZ_PIN, 1000, 500);
      delay(1000);
      digitalWrite(LED_PIN_1, LOW);
      break;    
      }

    if (Button_press_2) {
      Button_press_2 = false;
      digitalWrite(LED_PIN_2, HIGH);
      tone(BUZZ_PIN, 1000, 500);
      delay(1000);
      digitalWrite(LED_PIN_2, LOW);
      break;    
      }
    
    
  }
  

}
