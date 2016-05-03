#define trigPin 25
#define echoPinFront 31
#define echoPinBack 29
#define echoPinLeft 27
#define echoPinRight 33

int motor_left[] = {4, 5};
int motor_right[] = {2, 3};                                                                                                                   //store serial input 

long durationFront, distanceFront, distanceBack, durationBack;
long durationLeft, distanceLeft, distanceRight, durationRight;

int mstop, mforward, mbackward, mleft, mright;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);

  mstop, mforward, mbackward, mleft, mright = 0;

  int i;
  for (i = 0; i < 2; i++) {
    pinMode(motor_left[i], OUTPUT);                                               
    pinMode(motor_right[i], OUTPUT);
  }

  pinMode(trigPin, OUTPUT);
  pinMode(echoPinFront, INPUT);
  pinMode(echoPinBack, INPUT);
  pinMode(echoPinLeft, INPUT);
  pinMode(echoPinRight, INPUT);
}

void loop() {
  /*if (Serial1.available()) {
    byteRead = Serial1.read();
    Serial.println(byteRead);

    if (byteRead==70) {
    }
  }*/
    digitalWrite(trigPin, LOW); 
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
  
    durationFront = pulseIn(echoPinFront, HIGH);
    distanceFront = (durationFront/2) / 29.1;
    Serial.print(distanceFront);
    Serial.println(" cm FRONT");
    
    if (distanceFront > 15) {                             
      Serial.println("drive_forward");
    } else {
      Serial.println("motor_stop");
      motor_stop();
    }

    delay(200);
    
    digitalWrite(trigPin, LOW); 
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    durationBack = pulseIn(echoPinBack, HIGH);
    distanceBack = (durationBack/2) / 29.1;
    Serial.print(distanceBack);
    Serial.println(" cm BACK");    

    delay(200);
    
    digitalWrite(trigPin, LOW); 
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    durationLeft = pulseIn(echoPinLeft, HIGH);
    distanceLeft = (durationLeft/2) / 29.1;
    Serial.print(distanceLeft);
    Serial.println(" cm LEFT");

    if (mstop == 1) {
      if (distanceLeft > 15) {
        Serial.println("drive_left");
      } 
      else if (distanceRight > 15) {
        Serial.println("drive_right");
      }
      else {
        Serial.println("drive_backward");
      }
    }

    delay(200);
    
    digitalWrite(trigPin, LOW); 
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    durationRight = pulseIn(echoPinRight, HIGH);
    distanceRight = (durationRight/2) / 29.1;
    Serial.print(distanceRight);
    Serial.println(" cm RIGHT");
    Serial.println("");
    
    

    delay(500);
}
                                                                                   
void motor_stop() {
  mstop = 1;
  analogWrite(motor_left[0], 0);
  analogWrite(motor_left[1], 0);

  analogWrite(motor_right[0], 0);
  analogWrite(motor_right[1], 0);
  delay(25);
  
}

void drive_backward() {
  mbackward = 1;
  analogWrite(motor_left[0], 200);
  analogWrite(motor_left[1], 0);

  analogWrite(motor_right[0], 200);
  analogWrite(motor_right[1], 0);
}

void drive_forward() {
  mforward = 1;
  analogWrite(motor_left[0], 0);
  analogWrite(motor_left[1], 200);

  analogWrite(motor_right[0], 0);
  analogWrite(motor_right[1], 200);
}

void drive_left() {
  mleft = 1;
  analogWrite(motor_left[0], 0);
  analogWrite(motor_left[1], 200);

  analogWrite(motor_right[0], 200);
  analogWrite(motor_right[1], 0);
}

void drive_right() {
  mright = 1;
  analogWrite(motor_left[0], 200);
  analogWrite(motor_left[1], 0);

  analogWrite(motor_right[0], 0);
  analogWrite(motor_right[1], 200);
}
