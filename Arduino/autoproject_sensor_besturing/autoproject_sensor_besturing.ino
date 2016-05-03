#define trigPin 25
#define echoPinFront 31
#define echoPinBack 33

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
  
    // Calculate to seconds.
    durationFront = pulseIn(echoPinFront, HIGH);
    distanceFront = (durationFront/2) / 29.1;
    durationBack = pulseIn(echoPinFront, HIGH);
    distanceBack = (durationBack/2) / 29.1;
    Serial.print(distanceFront);
    Serial.println(" cm");
    Serial.print(distanceBack);
    Serial.println(" cm back");
    
    if (distanceFront > 10 && forward == false) {
      drive_forward();                                 
      Serial.println("Forward");           
    } 
    
    else {
      drive_left();
      delay(1100);

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

    delay(50);
}
                                                                                   
void motor_stop() {
  forward = false;
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
  forward = true;
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
