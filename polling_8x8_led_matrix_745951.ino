  
int fstones[] = {
  0, 185, 207, 233, 247, 277, 311, 349, 370, 293//293 D4
};
int etones[] = {
  0, 165, 185, 208, 220, 247, 277, 311, 330, 185//185 #F3
};
int me1[][2] = {
  {6,-1},{7,-1},{1,0} ,{2,0},{3,0} ,{6,0} ,{5,0} ,
  {3,0} ,{6,-1},{3,0} ,{2,0},{1,0} ,{7,-1},
  {6,-1},{7,-1},{1,0} ,{2,0},{3,0} ,{2,0} ,{1,0} ,
  {7,-1},{6,-1},{7,-1},{1,0},{7,-1},{6,-1},{9,-1},{7,-1},

  {6,-1},{7,-1},{1,0} ,{2,0},{3,0} ,{6,0} ,{5,0},
  {3,0} ,{6,-1},{3,0} ,{2,0},{1,0} ,{7,-1},
  {6,-1},{7,-1},{1,0} ,{2,0},{3,0} ,{2,0} ,{1,0},
  {7,-1},{1,0} ,{2,0} ,{3,0}

};

int me2[][2] = {
  {2,-1},{2,-1},{1,0},{5,-1},
  {6,-1},{6,-1},{6,-1},{5,-1}, {1,0},{1,0}, {0,0},{1,0},{5,-1},
  {6,-1},{6,-1},{6,-1},{5,-1}, {1,0},{3,0}, {0,0},{1,0},{5,-1},
  {6,0},{6,0},{6,0},{5,0}, {1,0},{1,0}, {1,0},{1,0},{2,0},
  {1,0},{1,0}, {0,0},{1,0},{6,-1}, {3,0}, {0,0},
  
  {1,0},{1,0}, {0,0},{2,0},{9,0}, {3,0},{1,0}, {0,0},{5,-1},{6,-1},
  {1,0},{1,0}, {0,0},{2,0},{9,0}, {3,0},{1,0}, {0,0},{6,-1},
  {1,0},{6,-1},{1,0}, {0,0},{6,-1}, {1,0},{6,-1},{1,0}, {0,0},{1,0},
  {4,0},{3,0},{1,0}, {1,0},{6,-1}, {3,0},{0,0},

  {1,0},{1,0}, {0,0},{2,0},{9,0}, {3,0},{1,0}, {0,0},{5,-1},{6,-1},
  {1,0},{1,0}, {0,0},{2,0},{9,0}, {3,0},{1,0}, {0,0},{6,-1},
  {1,0},{6,-1},{1,0}, {0,0},{6,-1}, {1,0},{6,-1},{1,0}, {0,0},{1,0},
  {4,0},{3,0},{1,0}, {1,0},{2,0},{1,0}, {0,0}
};

int lenMe1=28+24;
int noteDurationsMe1[] = {
  8,8,8,8,4,8,8,
  4,4,8,8,8,8,
  8,8,8,8,4,8,8,
  8,8,8,8,8,8,8,8,

  8,8,8,8,4,8,8,
  4,4,8,8,8,8,
  8,8,8,8,4,8,8,
  4,4,4,4
};

int lenMe2=38+36+35;
int noteDurationsMe2[] = {
  4,8,16,16,
  5,16,8 ,8 ,5,16,8 ,16,16,
  5,16,8 ,8 ,5,16,8 ,16,16,
  5,16,8 ,8 ,5,16,16,16,8,
  5,16,16,16,8,4 ,4 ,

  5 ,16,16,16,8,5,16,8 ,16,16,
  5 ,16,16,16,8,5,16,8 ,8 ,
  8 ,16,16,8, 8,8,16,16,8 ,8,
  16,8 ,16,8, 8,4,4 ,
  
  5 ,16,16,16,8,5,16,8 ,16,16,
  5 ,16,16,16,8,5,16,8 ,8 ,
  8 ,16,16,8 ,8,8,16,16,8 ,8,
  16,8 ,16,8 ,8,4
};

int FSTone(int i, int s){
  int b = fstones[i];
  //s++;
  while(s>0){
    b*=2;
    s--;
  }
  while(s<0){
    b/=2;
    s++;
  }
  return b;
}

int ETone(int i, int s){
  int a = etones[i];
  s++;
  while(s>0){
    a*=2;
    s--;
  }
  while(s<0){
    a/=2;
    s++;
  }
  return a;
}

long presentTime=0,previousTime,notesPause=0; 
int currentNote=0;
void TryPlay(int secLen,int melody[][2],int noteDurations[], int len,int (*GetTone)(int,int)){
  presentTime = millis();
  if(presentTime - previousTime >= notesPause){
    noTone(2);
    if(currentNote>=len){
      currentNote=0;
      notesPause =100;
    }else{
      int noteDuration = secLen/noteDurations[currentNote];
      tone(2, GetTone(melody[currentNote][0],melody[currentNote][1]), noteDuration);
      notesPause = noteDuration * 1.6;
      previousTime=millis();
      //delay(pauseBetweenNotes);
      //noTone(10);
      currentNote++;
    }
    previousTime = millis();


  }
  
}
//設定各接腳
int latchPin = 8;
int clockPin = 12;
int dataPin = 11;

byte colDataMatrix[8] = {
   B11111110,
   B11111101,
   B11111011,
   B11110111,
   B11101111,
   B11011111,
   B10111111,
   B01111111
}; //掃描

byte rowDataMatrix[][8] = {
  {
   B00001100,
   B00011000,
   B01101110,
   B10001001,
   B10000001,
   B10000001,
   B11011011,
   B01100110
  },
  {
   B01100110,
   B10011001,
   B10000001,
   B10000001,
   B10000001,
   B01000010,
   B00100100,
   B00011000
  }
}; //圖案
       
void setup() {
  pinMode(latchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(dataPin,OUTPUT);
  pinMode(5,INPUT_PULLUP);
  pinMode(6,INPUT_PULLUP);

  delay(100);
}
byte previousStateA=1, presentStateA=1;
byte previousStateB=1, presentStateB=1;
int patternNumber=0;
int songNumber=0;
void loop() {
  previousStateA=presentStateA;
  previousStateB=presentStateB;
  presentStateA = digitalRead(5);
  presentStateB = digitalRead(6);
  if(presentStateA == 0 && previousStateA == 1){

  	patternNumber++;
    if(patternNumber>1) patternNumber = 0;
  }
  if(presentStateB == 0 && previousStateB == 1){
  	songNumber++;
    presentTime=0,previousTime,notesPause=0; 
    currentNote=0;
    if(songNumber>1) songNumber = 0;
  }
  
  for(int i = 0; i < 8 ; i++){
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, colDataMatrix[i]);
    shiftOut(dataPin, clockPin, LSBFIRST, rowDataMatrix[patternNumber][i]);
    digitalWrite(latchPin,HIGH);

    if(songNumber==0)
      TryPlay(1000,me1,noteDurationsMe1,lenMe1,FSTone);
    else
      TryPlay(1200,me2,noteDurationsMe2,lenMe2,ETone);
    delay(20);
  }
  
}
