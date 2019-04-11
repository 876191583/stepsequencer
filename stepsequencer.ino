
int led[4] = {39, 38, 37, 36};
int ledReverse[4] = {36, 37, 38,39};
int potS =  A16;
int tempo;
int s1 = 32;

int cha = 2;
int C4midi = 64;
int F4midi = 66;


int currentStep = 0;
unsigned long lastStepTime = 0;

int buttonPin[4] = {25, 26, 27, 28};
int buttonPinReverse[4] = {28,27,26,25};
boolean lastButtonState[4] ={LOW,LOW,LOW,LOW};
boolean buttonState[4] = {LOW,LOW,LOW,LOW};
boolean on[4] = {false,false,false,false};

void setup() {
  pinMode(s1, INPUT);
  pinMode(led[0], OUTPUT);
  pinMode(led[1], OUTPUT);
  pinMode(led[2], OUTPUT);
  pinMode(led[3], OUTPUT);
  pinMode(buttonPin[0], INPUT);
  pinMode(buttonPin[1], INPUT);
  pinMode(buttonPin[2], INPUT);
  pinMode(buttonPin[3], INPUT);
  Serial.begin(9600);

}

void loop() {
  
  
  if (digitalRead(s1) == HIGH){
    sequencer(led, buttonPin);
  }
  else{
    sequencerback(ledReverse, buttonPinReverse);
  }
  
}

void sequencer(int led[4], int buttonPinn[4]){
  checkbutton( buttonPinn);
  tempo = analogRead(potS);
  
  if (millis() > lastStepTime + tempo){
     digitalWrite(led[currentStep],LOW);
     usbMIDI.sendNoteOff(C4midi + (currentStep*2), 127,cha);
     currentStep = currentStep +1 ;
     if (currentStep>3){
        currentStep = 0;
      }
     lastStepTime = millis();
     
     if(on[currentStep] == true) {
      digitalWrite(led[currentStep], HIGH);
      usbMIDI.sendNoteOn(C4midi + (currentStep*2), 127,cha);
    } 
    else if(on[currentStep] == false) {
       digitalWrite(led[currentStep], LOW);
      
  }  
}
}

void sequencerback(int led[4], int buttonPinn[4]){
  checkbutton( buttonPinn);
  tempo = analogRead(potS);
  
  if (millis() > lastStepTime + tempo){
     digitalWrite(led[currentStep],LOW);
     usbMIDI.sendNoteOff(F4midi - (currentStep*2), 127,cha);
     currentStep = currentStep +1 ;
     if (currentStep>3){
        currentStep = 0;
      }
     lastStepTime = millis();
     
     if(on[currentStep] == true) {
      digitalWrite(led[currentStep], HIGH);
      usbMIDI.sendNoteOn(F4midi - (currentStep*2), 127,cha);
    } 
    else if(on[currentStep] == false) {
       digitalWrite(led[currentStep], LOW);
      
  }  
}
}

void checkbutton(int buttonPins[4]) {
  for (int i = 0; i<4; i++){
  lastButtonState[i] = buttonState[i];    
  buttonState[i] = digitalRead(buttonPins[i]);
  
    if(buttonState[i] == HIGH && lastButtonState[i] == LOW) {
      on[i] = !on[i];
    }
}
}
