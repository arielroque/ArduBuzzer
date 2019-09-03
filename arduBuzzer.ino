
 #define NOTE_C4 262
 #define NOTE_D4 294
 #define NOTE_E4 330
 #define NOTE_F4 349
 #define NOTE_G4 392
 #define NOTE_A4 440
 #define NOTE_B4 494
 #define NOTE_C5 523
 #define B4     488
 #define E5     648
 #define G5     768
 #define F5SUS  740
 #define B5   976
 #define A5   864
 #define RE5SUS   622
 #define F5   688


const int BUZZER_PIN = 10;
const int BUTTON_PIN = 8;

int player = 0;


float tune[] = {B4, E5, G5, F5SUS, E5, B5, A5, F5SUS,                
                E5, G5, F5SUS, RE5SUS, F5, B4,
                B4, E5, G5, F5SUS, E5, B5};
              
float sound3Time[] = {0.5, 1.5, 0.125, 0.5, 1, 0.5, 2, 2,                 
                 1.5, 0.125, 0.5, 1, 0.5, 2,
                 0.5, 1.5, 0.125, 0.5, 1, 0.5};
                 
int sound4Melody[] = {660,660,660,510,660,770,380,510,380,320,440,480,450,430,380,660,760,860,
                 700,760,660,520,580,480,510,380,320,440,480,450,430,380,660,760,860,700,
                 760,660,520,580,480,500,760,720,680,620,650,380,430,500,430,500,570,500,
                 760,720,680,620,650,1020,1020,1020,380,500,760,720,680,620,650,380,430,
                 500,430,500,570,585,550,500,380,500,500,500,500,760,720,680,620,650,380,
                 430,500,430,500,570,500,760,720,680,620,650,1020,1020,1020,380,500,760,
                 720,680,620,650,380,430,500,430,500,570,585,550,500,380,500,500,500,500,
                 500,500,500,580,660,500,430,380,500,500,500,500,580,660,870,760,500,500,
                 500,500,580,660,500,430,380,660,660,660,510,660,770,380};


int sound4Time[] = {100,100,100,100,100,100,100,100,100,100,100,80,100,100,
                         100,80,50,100,80,50,80,80,80,80,100,100,100,100,80,100,
                         100,100,80,50,100,80,50,80,80,80,80,100,100,100,100,150,
                         150,100,100,100,100,100,100,100,100,100,100,150,200,80,80,
                         80,100,100,100,100,100,150,150,100,100,100,100,100,100,100,
                         100,100,100,100,100,100,100,100,100,100,150,150,100,100,100,
                         100,100,100,100,100,100,100,150,200,80,80,80,100,100,100,100,
                         100,150,150,100,100,100,100,100,100,100,100,100,100,100,100,100
                         ,60,80,60,80,80,80,80,80,80,60,80,60,80,80,80,80,80,60,80,60,80,
                         80,80,80,80,80,100,100,100,100,100,100,100};

int sound4PauseNotes[] ={150,300,300,100,300,550,575,450,400,500,300,330,150,300,200,200,150,300,
                         150,350,300,150,150,500,450,400,500,300,330,150,300,200,200,150,300,150,
                         350,300,150,150,500,300,100,150,150,300,300,150,150,300,150,100,220,300,
                         100,150,150,300,300,300,150,300,300,300,100,150,150,300,300,150,150,300,
                         150,100,420,450,420,360,300,300,150,300,300,100,150,150,300,300,150,150,
                         300,150,100,220,300,100,150,150,300,300,300,150,300,300,300,100,150,150,
                         300,300,150,150,300,150,100,420,450,420,360,300,300,150,300,150,300,350,
                         50,350,150,300,150,600,150,300,350,150,150,550,325,600,150,300,350,150,
                         350,150,300,150,600,150,300,300,100,300,550,575};

int sound3Len = 20;


void setup() {
  Serial.begin(9600);
  pinMode(BUZZER_PIN,OUTPUT);
  pinMode(BUTTON_PIN, INPUT);

}

void loop() {

  int buttonListening = digitalRead(BUTTON_PIN);
  Serial.println(buttonListening);
  if (buttonListening == HIGH){
    switch(player){
      case 0:
      sound1();
      player++;
      break;

      case 1:
      sound2();
      player++;
      break;

      case 2:
      sound3();
      player++;
      break;

      case 3:
      sound4();
      player++;
      break;

      case 4:
      sound5();
      player++;
      break;
    }
  }
  if (player > 4){
     player = 0;
  }

}


void sound5(){
 
  for(int x=0;x<1080;x++){
  
  float soundSin=(sin(x*3.1416/180));
  
  int frequency = 2000+(int(soundSin*1000));
  
  tone(BUZZER_PIN,frequency);  
  delay(10);
  }
  
  noTone(BUZZER_PIN);
  
  
  
}

void sound4(){
  
  for (int note = 0; note < 156; note++) {

      int noteDuration = sound4Time[note];
      tone(BUZZER_PIN, sound4Melody[note],noteDuration);
      delay(sound4PauseNotes[note]);}
     noTone(BUZZER_PIN);
}  

void sound3(){
  for(int x=0; x<sound3Len; x++){
    tone(BUZZER_PIN, tune[x]);
    delay(1000 * sound3Time[x]);
    noTone(BUZZER_PIN);
  }

  
  
}



void sound2(){
  
 tone(BUZZER_PIN, NOTE_C4);
 delay(1000);
 tone(BUZZER_PIN, NOTE_G4);
 delay(1000);
 tone(BUZZER_PIN, NOTE_F4);
 delay(250);
 tone(BUZZER_PIN, NOTE_E4);
 delay(250);
 tone(BUZZER_PIN, NOTE_D4);
 delay(250);
 tone(BUZZER_PIN, NOTE_C5);
 delay(1000);
 tone(BUZZER_PIN, NOTE_G4);
 delay(500);
 tone(BUZZER_PIN, NOTE_F4);
 delay(250);
 tone(BUZZER_PIN, NOTE_E4);
 delay(250);
 tone(BUZZER_PIN, NOTE_D4);
 delay(250);
 tone(BUZZER_PIN, NOTE_C5);
 delay(1000);
 tone(BUZZER_PIN, NOTE_G4);
 delay(500);
 tone(BUZZER_PIN, NOTE_F4);
 delay(250);
 tone(BUZZER_PIN, NOTE_E4);
 delay(250);
 tone(BUZZER_PIN, NOTE_F4);
 delay(250);
 tone(BUZZER_PIN, NOTE_D4);
 delay(2000);
  
 noTone(BUZZER_PIN);
 
  
  
}


void sound1(){
 
    tone(BUZZER_PIN,146.83,400);//D
      delay(400);
    
    tone(BUZZER_PIN,146.83,400);//D
       delay(400);
    
    tone(BUZZER_PIN,146.83,250);//D
       delay(250);
    
    tone(BUZZER_PIN,174.61,250);//F
       delay(250);
    
    tone(BUZZER_PIN,196.00,350);//G
       delay(400);
    
    tone(BUZZER_PIN,146.83,350);//D
      delay(400);
    
    tone(BUZZER_PIN,146.83,200);//D
       delay(250);
    
    tone(BUZZER_PIN,146.83,200);//D
       delay(250);
    
     tone(BUZZER_PIN,130.81,400);//C
       delay(450);
    
     tone(BUZZER_PIN,130.81,400);//C
       delay(450);
    
    tone(BUZZER_PIN,146.83,400);//D
       delay(450);
    
    tone(BUZZER_PIN,146.83,400);//D
       delay(450);
    
     tone(BUZZER_PIN,146.83,400);//D
       delay(450);
    
    tone(BUZZER_PIN,174.61,400);//F
       delay(300);
    
    tone(BUZZER_PIN,196.00,400);//G
       delay(450);
    
     tone(BUZZER_PIN,146.83,400);//D
       delay(450);
    
    tone(BUZZER_PIN,146.83,400);//D
       delay(450);
    
     tone(BUZZER_PIN,146.83,400);//D
       delay(450);
    
    tone(BUZZER_PIN,130.81,400);//C
       delay(300);
    
     tone(BUZZER_PIN,130.81,400);//C
       delay(300);
    
    tone(BUZZER_PIN,130.81,400);//C
       delay(450);
    
    tone(BUZZER_PIN,174.61,400);//F
       delay(450);
    
    tone(BUZZER_PIN,146.83,400);//D
       delay(450);
    
    tone(BUZZER_PIN,220.00,400);//A
       delay(450);
    
     tone(BUZZER_PIN,174.61,400);//D
       delay(450);
    
    tone(BUZZER_PIN,146.83,400);//D
       delay(450);
    
    tone(BUZZER_PIN,207.65,400);//GSHARP
       delay(450);
  
  
}
