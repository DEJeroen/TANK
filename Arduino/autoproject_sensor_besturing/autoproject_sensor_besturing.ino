#define trigPin 25
#define echoPinFront 31
#define echoPinBack 29

int motor_left[] = {4, 5};
int motor_right[] = {2, 3};                                                                                                                   //store serial input 

long durationFront, distanceFront, distanceBack, durationBack;

bool forward;

void setup() {
  Serial.begin(9600);

  int i;
  for (i = 0; i < 2; i++) {
    pinMode(motor_left[i], OUTPUT);                                               
    pinMode(motor_right[i], OUTPUT);
  }

  pinMode(trigPin, OUTPUT);
  pinMode(echoPinFront, INPUT);
  pinMode(echoPinBack, INPUT);
}

void loop() {
    digitalWrite(trigPin, LOW); 
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
  
    durationFront = pulseIn(echoPinFront, HIGH);
    distanceFront = (durationFront/2) / 29.1;
    Serial.print(distanceFront);
    Serial.println(" cm front");

    delay(100);
    
    digitalWrite(trigPin, LOW); 
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    durationBack = pulseIn(echoPinBack, HIGH);
    distanceBack = (durationBack/2) / 29.1;
    Serial.print(distanceBack);
    Serial.println(" cm back");    
    
    if (distanceFront > 10 /*&& forward == false*/) {
                                       
      Serial.println("Forward");           
    } 
    
    else {
      motor_stop();

      /*if (distanceFront < 10) {
        drive_right();
        delay(2200);
        if (distanceFront < 10) {
          drive_left();
          delay(1100);
          drive_backward();                              
        }
      }*/
    }

    delay(500);
}
                                                                                   
void motor_stop() {
  //forward = false;
  analogWrite(motor_left[0], 0);
  analogWrite(motor_left[1], 0);

  analogWrite(motor_right[0], 0);
  analogWrite(motor_right[1], 0);
  delay(25);
  
}

void drive_backward() {
  
  analogWrite(motor_left[0], 200);
  analogWrite(motor_left[1], 0);

  analogWrite(motor_right[0], 200);
  analogWrite(motor_right[1], 0);
}

void drive_forward() {
  //forward = true;
  analogWrite(motor_left[0], 0);
  analogWrite(motor_left[1], 200);

  analogWrite(motor_right[0], 0);
  analogWrite(motor_right[1], 200);
}

void drive_left() {
  analogWrite(motor_left[0], 0);
  analogWrite(motor_left[1], 200);

  analogWrite(motor_right[0], 200);
  analogWrite(motor_right[1], 0);
}

void drive_right() {
  analogWrite(motor_left[0], 200);
  analogWrite(motor_left[1], 0);

  analogWrite(motor_right[0], 0);
  analogWrite(motor_right[1], 200);
}
