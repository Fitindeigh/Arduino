
// сегодня напишем игру на arduino
// пинг понг, мы это делали на занятии 4
// однако делали это с помощью блоков, что очень неудобно
//  а также крупные проекты никто блоками не пишет ( кто пишет уже давно в палате номер 6)
// начнем
// в программе SimuIDЕ создал схему игры

// в данном коде мы не будем использовать delay
// а будем использовать таймеры millis();
// подробнее о нем вы можете почитать в интернете
// начнем написание игры



void setup(){
  Serial.begin(9600);
  
  pinMode(2, INPUT_PULLUP); // подтяжка резитсора к 5V
  pinMode(3, INPUT_PULLUP);
  
  for (int i = 4; i <= 13; i++){
    pinMode(i, OUTPUT);   // ОБОЗНАЧАЕМ пины на светодиоды
  }
  
}

bool GameOver = 1; // переменная окончания игры, пока она 1 то игра продолжается
bool Button1;
bool Button2;

bool button_flag_1 = false; // флаги обработчика нажатия кнопки в условии
bool button_flag_2 = false;

bool Button1_press = false; // перменные по которым мы будем определться
bool Button2_press = false; // в общем коде программы что какя либо кнопка нажата

uint32_t timer1;
uint32_t timer2;
uint32_t timer3;
uint32_t timer4;
uint32_t timer5;

int animationScore = 300;

byte count_1 = 5;   // будет использоваться при счете от 5 до 12
byte count_2 = 12;  // будет использоваться при счете от 12 до 5

bool change_light = true; // чтобы в начале желтый светодиод загорался

bool running_1 = false;
bool running_2 = false;
bool work_allow_1 = true;
bool work_allow_2 = true;

bool first_time = true; // флаг по которому мы будем определять что условие 
            // ((Button1_press || running_1) && work_allow_1) {
            // выполняется первый раз и после первого раза его обнуляем
bool change_direction = false; // флаг отвественный за изменение направления


bool led_lose;


// создадим функцию которая возвращает все начальные параметры игры

void reset_param(){
  
  GameOver = 1;
  animationScore = 300;
  count_1 = 5;
  count_2 = 12;
  change_light = true;
  running_1 = false;
  running_2 = false;
  work_allow_1 = true;
  work_allow_2 = true;
  first_time = true;
  change_direction = false;
  
}


void loop() {
  
  // при поражении
  if (!GameOver){
    
    
    Button1 = !digitalRead(2);
    Button2 = !digitalRead(3);
    // тепреь как в прошлом уроке
    
    if (Button1 && !button_flag_1){
      button_flag_1 = true;
      reset_param(); // вызываем функцию  
    }
    if (!Button1 && button_flag_1){
      button_flag_1 = false;
    }
    if (Button2 && !button_flag_2){
      button_flag_2 = true; 
      reset_param();      
    }
    if (!Button2 && button_flag_2){
      button_flag_2 = false;
    }     
      
    if (millis() - timer5 >= 400){
      timer5 = millis();
      digitalWrite(4, led_lose);
      digitalWrite(13, led_lose);
      led_lose = !led_lose;
    }
    
  }
  
  while (GameOver){
    // напишем обработчик кнопки
    
    Button1 = !digitalRead(2);
    Button2 = !digitalRead(3);
    // тепреь как в прошлом уроке
    
    if (Button1 && !button_flag_1){
      button_flag_1 = true;
      Button1_press = true; 
    }
    if (!Button1 && button_flag_1){
      button_flag_1 = false;
    }
    if (Button2 && !button_flag_2){
      button_flag_2 = true;
      Button2_press = true; 
    }
    if (!Button2 && button_flag_2){
      button_flag_2 = false;
    }
    // теперь если будет нажата кнопка то соответствующий ей флаг 
    // Button1_press или Button2_press будет true;
    // теперь начнем писать саму игру
    
    // начнем с условия если нажата кнопка 1
    //  теперь возникает проблема, данный код в условии будет запускаться каждый раз
    // когда будет нажиматься кнопка
    // нам необходим флаг работы и флаг разрешения на работу, чтобы 2 условия
    // одновременно не запускались
    // теперь условие будет выполняться только тогда, когда либо нажата кнопка (Button1_press)
    // либо эта часть кода выполняется в данный момент (running_1)
    // и при этом у нее есть разрешение на выполннеие (work_allow_1)
  if ((Button1_press || running_1) && work_allow_1) {
      Button1_press = false;
      running_1 = true;
      work_allow_1 = true;
      // и запрещаем соответственно работу второму условию
      running_2 = false;
      work_allow_2 = false;
      
      // теперь нам необходимо по таймерам переключать светодиоды
      // создадим 2 штуки
      if (millis() - timer1 >= animationScore){ // т.е светодиод должен 300 мс быть включен и 300 мс выключен
        timer1 = millis();
        Serial.println(count_1);
        
        // сменяться светодидоы будут следующим образом
        if (!first_time){
          digitalWrite(count_1, change_light);
          change_light = !change_light;
        }
        // сейчас 2 таймера начинают работать одновременно
        // при этом у нас проскакивает отключаение светодиода
        // исправим это
        
        
        // теперь напишем блок, который будет отвечать за "отбитие" шарика
        // в виде светодиода по кнопке
        // желтый светодиод во время которго надо нажимать кнопку находится
        // на 12 пине
        
        if (count_1 == 12){
          // теперь если кнопка 2 была нажата 
          if (Button2_press){
            Button2_press = false;
            // т.к мы будет выходить из этого условияif ((Button1_press || running_1) && work_allow_1)
            // нам необходимо запретить его работу
            running_1 = false;
            work_allow_1 = false;
            // и разрешаем соответственно работу второму условию
            running_2 = true;
            work_allow_2 = true;
            first_time = true; 
            change_light = true;
            change_direction = true;
            
            for (int i = 4; i<= 13; i++){
              digitalWrite(i, LOW);
            }
            
            // уменьшаем animationScore
            animationScore -= 20;
            // если animationScore будет 0 то игра заканчивается
            if (animationScore < 20) {
              GameOver = 0;
              break;
            }
            // теперь еще допишем востановление переменных;
            count_1 = 5;
          }
        }
            

      }
      // пишем еще один таймер, поскольку менять номер пина нам небоходимо
      // раз в 600 мс
      if (millis() - timer2 >= 2 * animationScore + 20){
        timer2 = millis();
        // создадим переменную count которая будет считать проходы по светодиодам
        // напишем ограничения для count_1
        // она считает от 5 до 12
        // теперь если была нажата кнопка 2 в момент когда 
        // count_1 < 12 то игра окончена
        if (count_1 < 12){
          if (Button2_press){
            Button2_press = false; // всегда надо обнулять значиние кнопки после ее использования (коненчо в зависимости от программы)
            GameOver = 0;
            break; // оператор выхода из цикла while
          }
        }       
        // теперь если челвоек не успел нажать на кнопку и загорелся
        // светодиод 13 (красный) то он проиграл
        // опишем это       
        if (count_1 > 12){
          GameOver = 0;
        }
        
        if (first_time){
          first_time = false;
          if (change_direction){
            count_1 ++;
            change_direction = false;
          }
        }
        else {
          count_1++;
        }
        
      }
  }
      
      
      // делаем все то же для 2 кнопки
  if ((Button2_press|| running_2) && work_allow_2) {
      Button2_press = false;
      running_2 = true;
      work_allow_2 = true;
      // и запрещаем соответственно работу первому условию
      running_1 = false;
      work_allow_1 = false;
      
      // теперь нам необходимо по таймерам переключать светодиоды
      // создадим 2 штуки
      if (millis() - timer3 >= animationScore){ // т.е светодиод должен 300 мс быть включен и 300 мс выключен
        timer3 = millis();
        
        if (!first_time){
          digitalWrite(count_2, change_light);
          change_light = !change_light;
        }
        Serial.println(count_2);
        // повторим то же самое со 2ой кнопкой
        if (count_1 == 5){
          // теперь если кнопка 2 была нажата 
          if (Button1_press){
            Button1_press = false;
            // т.к мы будет выходить из этого условияif ((Button1_press || running_1) && work_allow_1)
            // нам необходимо запретить его работу
            running_2 = false;
            work_allow_2 = false;
            // и разрешаем соответственно работу первому условию
            running_1 = true;
            work_allow_1 = true;
            first_time = true;          
            change_light = true; // чтобы перед сменой направления
                      // светодиод в начале зажигался
                      // а не гас
            change_direction = true;
            // уменьшаем animationScore
            animationScore -= 20;
            // если animationScore будет 0 то игра заканчивается
            if (animationScore < 20) {
              GameOver = 0;
              break;
            }
            // теперь еще допишем востановление переменных;
            count_2 = 12;
            
            for (int i = 4; i<= 13; i++){
              digitalWrite(i, LOW);
            }
          }
        }
      }
      // пишем еще один таймер, поскольку менять номер пина нам небоходимо
      // раз в 600 мс
      if (millis() - timer4 >= 2 * animationScore + 20){
        timer4 = millis();
        // создадим переменную count которая будет считать проходы по светодиодам
        // повторим то же самое и со 2 кнопккой
        
        if (count_2 > 5){
          if (Button1_press){
            Button1_press = false;
            GameOver = 0;
          }
        }
        
        if (count_2 < 5){
          GameOver = 0;
        }
        
        if (first_time){
          first_time = false;         
          if (change_direction){
            count_2--;
            change_direction = false;
          }
        } else {
          count_2--; // -- поскольку у нас идет счет от 12 до 5
        }
      } 
        

      
    }
    
    
  }
    
  
}
