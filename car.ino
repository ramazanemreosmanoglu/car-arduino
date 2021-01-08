/*
 * Created by Ramazan Emre Osmanoglu, 2020
 * 
 * github.com/ramazanemreosmanoglu
 * t.me/RamazanEmre
 * ramazanemre@pm.me
 * 
 */

#include <IRremote.h> 

#define STEPPER_PIN_1 9
#define STEPPER_PIN_2 10
#define STEPPER_PIN_3 11
#define STEPPER_PIN_4 12

const int BACK = -8161;
const int FORWARD =  -22441;
const int STOP = 25245;
const int DELAY = 1000;
const int RECV_PIN =3; 

int step_number = 0;


IRrecv irrecv(RECV_PIN); 

decode_results results; 

 

void setup(){ 
  Serial.begin(9600); 

  irrecv.enableIRIn(); 

  pinMode(STEPPER_PIN_1, OUTPUT);
  pinMode(STEPPER_PIN_2, OUTPUT);
  pinMode(STEPPER_PIN_3, OUTPUT);
  pinMode(STEPPER_PIN_4, OUTPUT);
} 

void OneStep(bool dir){
    if(dir){
switch(step_number){
  case 0:
  digitalWrite(STEPPER_PIN_1, HIGH);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 1:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, HIGH);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 2:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, HIGH);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 3:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, HIGH);
  break;
} 
  }else{
    switch(step_number){
  case 0:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, HIGH);
  break;
  case 1:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, HIGH);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 2:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, HIGH);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 3:
  digitalWrite(STEPPER_PIN_1, HIGH);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
 
  
} 
  }
step_number++;
  if(step_number > 3){
    step_number = 0;
  }
}

int last = 0;

void loop(){ 

    if (irrecv.decode(&results)){ 

      int value = results.value;
      
      if(value==-1) {
        // Same value again.
        value = last;
      }
      Serial.println(value);
      
      switch(value) {

        
        case FORWARD:
          // Step Forward

          for(int i=0; i<DELAY; i++) {
            OneStep(false);
            delay(2);
          }
          
          last = FORWARD;
          Serial.println("FORWARD");
          break;


          
        case BACK:
          // Step Back
          for(int i=0; i<DELAY; i++) {
            OneStep(true);
            delay(2);
          }
          
 
          Serial.println("BACK");

          last = BACK;
        
          
      }
      irrecv.resume();  

    } 

}
