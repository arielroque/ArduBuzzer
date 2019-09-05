
//ArduBuzzer Music Player
//author: Ariel Roque

#include <LiquidCrystal.h>

#define NOTE_C4 262
#define NOTE_D4 294
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_G4 392
#define NOTE_A4 440
#define NOTE_B4 494
#define NOTE_C5 523
#define B4 488
#define E5 648
#define G5 768
#define F5SUS 740
#define B5	976
#define A5	864
#define RE5SUS 622
#define F5	688

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //RS/ENABLE/D5/D6/D7

const int BUZZER1_PIN = 8;
const int BUZZER2_PIN = 9;
const int PREVIOUS_BUTTON_PIN = 10;
const int NEXT_BUTTON_PIN = 13;
const int LCD_WIDTH = 16;
const int LCD_HEIGHT = 2;

byte MUSIC_ICON[8] = {B00001,B00011,B00101,B01001,
                      B01001,B01011,B11011,B11000};

const float TUNE[] = {B4, E5, G5, F5SUS, E5, B5, A5, F5SUS,                
                      E5, G5, F5SUS, RE5SUS, F5, B4,
                      B4, E5, G5, F5SUS, E5, B5};
                      

const int SOUND3_LENGTH = sizeof(TUNE) / sizeof(TUNE[0]);                      
                        
const float SOUND_3_TIME[] = {0.5, 1.5, 0.125, 0.5, 1, 0.5, 2, 2,                 
                              1.5, 0.125, 0.5, 1, 0.5, 2,
                              0.5, 1.5, 0.125, 0.5, 1, 0.5};

const int SOUND_4_MELODY[] = {660,660,660,510,660,770,380,510,380,320,440,480,450,430,380,660,760,860,700,760,660,
                              520,580,480,510,380,320,440,480,450,430,380,660,760,860,700,760,660,520,580,480,500,
                              760,720,680,620,650,380,430,500,430,500,570,500,760,720,680,620,650,1020,1020,1020,
                              380,500,760,720,680,620,650,380,430,500,430,500,570,585,550,500,380,500,500,500,500,
                              760,720,680,620,650,380,430,500,430,500,570,500,760,720,680,620,650,1020,1020,1020,
                              380,500,760,720,680,620,650,380,430,500,430,500,570,585,550,500,380,500,500,500,500,
                              500,500,500,580,660,500,430,380,500,500,500,500,580,660,870,760,500,500,500,500,580,
                              660,500,430,380,660,660,660,510,660,770,380};
                 
const int SOUND_4_TIME[] = { 100,100,100,100,100,100,100,100,100,100,100,80,100,100,100,80,50,100,80,50,80
                             ,80,80,80,100,100,100,100,80,100,100,100,80,50,100,80,50,80,80,80,80,100,100,
                              100,100,150,150,100,100,100,100,100,100,100,100,100,100,150,200,80,80,80,100,
                              100,100,100,100,150,150,100,100,100,100,100,100,100,100,100,100,100,100,100,
                              100,100,100,100,150,150,100,100,100,100,100,100,100,100,100,100,150,200,80,80,
                              80,100,100,100,100,100,150,150,100,100,100,100,100,100,100,100,100,100,100,100,
                              100,60,80,60,80,80,80,80,80,80,60,80,60,80,80,80,80,80,60,80,60,80,80,80,80,80,
                              80,100,100,100,100,100,100,100};

const int SOUND_4_PAUSE[] = {150,300,300,100,300,550,575,450,400,500,300,330,150,300,200,200,150,300,
                            150,350,300,150,150,500,450,400,500,300,330,150,300,200,200,150,300,150,
                            350,300,150,150,500,300,100,150,150,300,300,150,150,300,150,100,220,300,
                            100,150,150,300,300,300,150,300,300,300,100,150,150,300,300,150,150,300,
                            150,100,420,450,420,360,300,300,150,300,300,100,150,150,300,300,150,150,
                            300,150,100,220,300,100,150,150,300,300,300,150,300,300,300,100,150,150,
                            300,300,150,150,300,150,100,420,450,420,360,300,300,150,300,150,300,350,
                            150,350,150,300,150,600,150,300,350,150,150,550,325,600,150,300,350,150,
                            350,150,300,150,600,150,300,300,100,300,550,575};

int count = 0;
int player = 0;


int chooseBuzzer(int n){
 
  if (n % 2 == 0){
     return BUZZER1_PIN;
  }
  
  return BUZZER2_PIN; 
}

void starterMessage(){
 
  lcd.setCursor(0,0);
  lcd.write(1);
  
  lcd.print(" ArduBuzzer");
  
  lcd.setCursor(15,0);
  lcd.write(1);
  
  lcd.setCursor(0,1);
  
  lcd.print("<Previous  Next>");
  
}

void showMusicName(String music,int start){
  
  lcd.setCursor(0,0);
  lcd.write(1);
  
  lcd.print("  Playing...");
  lcd.setCursor(0,1);
 
  lcd.print("                ");
  lcd.setCursor(start,1);
  
  lcd.print(music);
}


void setup()
{
  lcd.begin(LCD_WIDTH,LCD_HEIGHT);
  
  pinMode(BUZZER1_PIN, OUTPUT);
  pinMode(BUZZER2_PIN, OUTPUT);
  
  pinMode(PREVIOUS_BUTTON_PIN,INPUT);
  pinMode(NEXT_BUTTON_PIN,INPUT);
  
  lcd.createChar(1,MUSIC_ICON);
  lcd.setCursor(0,0);
  lcd.write(1);
  
  lcd.print("  ArduBuzzer");
  
  lcd.setCursor(15,0);
  lcd.write(1);
  
  lcd.setCursor(1,1);
  lcd.print("Press. a button");
  
  Serial.begin(9600);
  
}

void sound5(int count){
  
  showMusicName("Sirene",5);
 
  for(int x=0;x<1080;x++){
  
  float sine=(sin(x*3.1416/180));
  
  int frequency = 2000+(int(sine*1000));
  
  tone(chooseBuzzer(count),frequency);  
  delay(10);
  }
  
  noTone(chooseBuzzer(count));
  
  starterMessage();
  
  
}

void sound4(int count){
  
  showMusicName("Mario game",2);
  
  lcd.print("Mario game");
  
  for (int note = 0; note < 156; note++) {
      int noteDuration = SOUND_4_TIME[note];
      
      tone(BUZZER1_PIN, SOUND_4_MELODY[note],noteDuration);
      delay(SOUND_4_PAUSE[note]);}

     noTone(BUZZER1_PIN);
  
  starterMessage();
}  


void sound3(int count){
  
  showMusicName("Harry Potter",4);
 
  for(int x=0; x<SOUND3_LENGTH; x++){
    tone(chooseBuzzer(count), TUNE[x]);
    delay(1000 * SOUND_3_TIME[x]);
    noTone(chooseBuzzer(count));
  }
  
  starterMessage();
}



void sound2(int count){
  
 showMusicName("Star Wars",4);
  
 tone(chooseBuzzer(count), NOTE_C4);
 delay(1000);
 tone(chooseBuzzer(count), NOTE_G4);
 delay(1000);
 tone(chooseBuzzer(count), NOTE_F4);
 delay(250);
 tone(chooseBuzzer(count), NOTE_E4);
 delay(250);
 tone(chooseBuzzer(count), NOTE_D4);
 delay(250);
 tone(chooseBuzzer(count), NOTE_C5);
 delay(1000);
 tone(chooseBuzzer(count), NOTE_G4);
 delay(500);
 tone(chooseBuzzer(count), NOTE_F4);
 delay(250);
 tone(chooseBuzzer(count), NOTE_E4);
 delay(250);
 tone(chooseBuzzer(count), NOTE_D4);
 delay(250);
 tone(chooseBuzzer(count), NOTE_C5);
 delay(1000);
 tone(chooseBuzzer(count), NOTE_G4);
 delay(500);
 tone(chooseBuzzer(count), NOTE_F4);
 delay(250);
 tone(chooseBuzzer(count), NOTE_E4);
 delay(250);
 tone(chooseBuzzer(count), NOTE_F4);
 delay(250);
 tone(chooseBuzzer(count), NOTE_D4);
 delay(2000);
  
 noTone(chooseBuzzer(count));

  starterMessage();
 
}


void sound1(int count){
  
  showMusicName("Missao Imposs.",2);
 
  tone(chooseBuzzer(count),146.83,400);//D
  delay(400);
    
  tone(chooseBuzzer(count),146.83,400);//D
  delay(400);
    
  tone(chooseBuzzer(count),146.83,250);//D
  delay(250);
    
  tone(chooseBuzzer(count),174.61,250);//F
  delay(250);
    
  tone(chooseBuzzer(count),196.00,350);//G
  delay(400);
    
  tone(chooseBuzzer(count),146.83,350);//D
  delay(400);
    
  tone(chooseBuzzer(count),146.83,200);//D
  delay(250);
    
  tone(chooseBuzzer(count),146.83,200);//D
  delay(250);
    
  tone(chooseBuzzer(count),130.81,400);//C
  delay(450);
    
  tone(chooseBuzzer(count),130.81,400);//C
  delay(450);
    
  tone(chooseBuzzer(count),146.83,400);//D
  delay(450);
    
  tone(chooseBuzzer(count),146.83,400);//D
  delay(450);
    
  tone(chooseBuzzer(count),146.83,400);//D
  delay(450);
    
  tone(chooseBuzzer(count),174.61,400);//F
  delay(300);
    
  tone(chooseBuzzer(count),196.00,400);//G
  delay(450);
    
  tone(chooseBuzzer(count),146.83,400);//D
  delay(450);
    
  tone(chooseBuzzer(count),146.83,400);//D
  delay(450);
    
  tone(chooseBuzzer(count),146.83,400);//D
  delay(450);
    
  tone(chooseBuzzer(count),130.81,400);//C
  delay(300);
    
  tone(chooseBuzzer(count),130.81,400);//C
  delay(300);
    
  tone(chooseBuzzer(count),130.81,400);//C
  delay(450);
    
  tone(chooseBuzzer(count),174.61,400);//F
  delay(450);
    
  tone(chooseBuzzer(count),146.83,400);//D
  delay(450);
    
  tone(chooseBuzzer(count),220.00,400);//A
  delay(450);
    
  tone(chooseBuzzer(count),174.61,400);//D
  delay(450);
    
  tone(chooseBuzzer(count),146.83,400);//D
  delay(450);
    
  tone(chooseBuzzer(count),207.65,400);//GSHARP
  delay(450);
  
  starterMessage(); 
}

void loop()
{
  int previousButtonState = digitalRead(PREVIOUS_BUTTON_PIN);
  int nextButtonState = digitalRead(NEXT_BUTTON_PIN);
  
  if(previousButtonState == 1){

    switch(count){
      case 1:
          sound1(count);
          break;

      case 2:
          sound2(count);
          break;

      case 3:
          sound3(count);
          break;
      
      case 4:
           sound4(count);
           break;
           
      case 5:
           sound5(count);
           break;
           
      default:
           count = 1;
           break;
    }
   
  }
  
  if(nextButtonState == 1){
    count = count +1;

    switch(count){
      case 1:
          sound1(count);
          break;

      case 2:
          sound2(count);
          break;

      case 3:
          sound3(count);
          break;
      
      case 4:
           sound4(count);
           break;
           
      case 5:
           sound5(count);
           break;
           
      default:
           count = 1;
           break;
    }
  }
 
}
