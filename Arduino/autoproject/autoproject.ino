#define trigPin 25
#define echoPinFrontR 31
#define echoPinFrontL 29
#define echoPinLeft 27
#define echoPinRight 33

long durationFrontR, distanceFrontR, distanceFrontL, durationFrontL;
long durationLeft, distanceLeft, distanceRight, durationRight;
int motor_left[] = {4, 5};
int motor_right[] = {2, 3};
int i;                                                                            //store motor left, right pins
int leftF, leftB, rightF, rightB;                                                 //variables for different motor states

byte inbyte;      //store serial input 
String serialDataIn;
String twoValSpeed;
int data[2];
int driveSpeed[4];
int currentSpeed[4];
int speedChanged;
int counter;
int randNumber;
bool automaticDrive = true;
String val;
bool mstop, mforward, mbackward, mleft, mright;

void setup() {
  mstop, mforward, mbackward, mleft, mright = false;

  Serial.begin(9600);     //USB Serial
  Serial1.begin(9600);  //Connection with Megalania (Android app)
  Serial2.begin(9600);  //Connection with other car

  int i;
  for (i = 0; i < 2; i++) {
    pinMode(motor_left[i], OUTPUT);                                               //set pins as outputpins
    pinMode(motor_right[i], OUTPUT);

      driveSpeed[0] = 200;
      driveSpeed[1] = 0;
      driveSpeed[2] = 200;
      driveSpeed[3] = 0;
  }
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPinFrontR, INPUT);
  pinMode(echoPinFrontL, INPUT);
  pinMode(echoPinLeft, INPUT);
  pinMode(echoPinRight, INPUT); 
}

void loop() {

    digitalWrite(trigPin, LOW); 
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
      

  if (Serial1.available()) {
        inbyte = Serial1.read();
        
        if(inbyte == 'm') {
          Serial.print("Manual");
          automaticDrive = false;

        }

       else if(inbyte == 'a') {
        Serial.print("Automatic");
        automaticDrive = true;

       }

       if (automaticDrive == false) {
        manualControl();
        
       }
  }
  if (automaticDrive) {
    automaticControl();
  }
    }

void manualControl() {

    //Reset (Here for when TANK is waiting for the input for the second motor)
 if(inbyte ==  'r'){
          counter = 0;
          }  
        if(inbyte >= '0' & inbyte <= '9')
            serialDataIn += inbyte - 48;
        if (inbyte == ','){  // Handle delimiter
            data[counter] = serialDataIn.toInt();
            counter = counter + 1;
            serialDataIn = ("");
            
        }
        if(counter >= 2){  // end of line

          

          if (data[0] <= 255) {
            driveSpeed[0] = data[0];
            driveSpeed[1] = 0;
          }
          else {
            driveSpeed[0] = 0;
            driveSpeed[1] = data[0] - 255;
          }

          if (data[1] <= 255) {
            driveSpeed[2] = data[1];
            driveSpeed[3] = 0;
          }
          else {
            driveSpeed[2] = 0;
            driveSpeed[3] = data[1] - 255;
            }
          //Reset wich motor is waiting for data
          counter = 0;



       //Set motor to driveSpeed
          analogWrite(motor_left[0], driveSpeed[0]);
          analogWrite(motor_left[1], driveSpeed[1]); 
          analogWrite(motor_right[0], driveSpeed[2]);  
          analogWrite(motor_right[1], driveSpeed[3]);



                  Serial.print(driveSpeed[0]);
                  Serial.print(driveSpeed[1]);
                  Serial.print(driveSpeed[2]);
                  Serial.print(driveSpeed[3]);



                  if (driveSpeed[0] == 0 && driveSpeed[1] == 0  && driveSpeed[2] == 0 && driveSpeed[3] == 0  )  {
    //stop the car
    Serial.println("stop");
    Serial2.print('0');
  }
  else if  (driveSpeed[0] > 100 && driveSpeed[1] == 0  && driveSpeed[2] > 100 && driveSpeed[3] == 0 )  {
    //drive car forward
        Serial.println("backwards");
     Serial2.print('6');

  }

  
  else if  (driveSpeed[0] == 0 && driveSpeed[1] > 100  && driveSpeed[2] == 0 && driveSpeed[3] > 100)  {
    //turn left fast

         Serial.println("forward");
    Serial2.print('1');
  }

  else if  (driveSpeed[0] > 100 && driveSpeed[1] == 0  && driveSpeed[2] == 0 && driveSpeed[3] > 100)  {
    //turn right fast
    
       Serial.println("right");
    Serial2.print('5');

 
  }
  else if  (driveSpeed[0] == 0 && driveSpeed[1] > 100  && driveSpeed[2] > 100 && driveSpeed[3] == 0 )  {
    //drive car backwards

            Serial.println("left");
    Serial2.print('3');
  }

  else {
    Serial.println("Recieving bogus data!");
        Serial2.print('0');
  }       
    }
}

void automaticControl() {
   /*if (Serial1.available()) {
    byteRead = Serial1.read();
    Serial.println(byteRead);

    if (byteRead==70) {
    }
  }*/

    drive_forward();
    
    trigger();  
  
    durationFrontR = pulseIn(echoPinFrontR, HIGH);
    distanceFrontR = (durationFrontR / 2) / 29.1;
    Serial.print(distanceFrontR);
    Serial.println(" cm FRONT1");

    delay(100);
    
    trigger();
    
    durationFrontL = pulseIn(echoPinFrontL, HIGH);
    distanceFrontL = (durationFrontL / 2) / 29.1;
    Serial.print(distanceFrontL);
    Serial.println(" cm FRONT2");
    
    delay(100);

    if (distanceFrontR > 15 && distanceFrontL > 15) {                             
      Serial.println("drive_forward");                          //if no object in front of neither front sensor, drive forward
      drive_forward();
    }
    else if (distanceFrontR <= 15 && distanceFrontL > 15) {
      Serial.println("drive_left");                             //if an object is in front of the right sensor, drive left
      drive_left();
    }
    else if (distanceFrontL <= 15 && distanceFrontR > 15) {
      Serial.println("drive_right");                            //if an object is in front of the left sensor, drive right
      drive_right();
    }
    else if (distanceFrontR <= 15 && distanceFrontL <= 15) {
      Serial.println("motor_stop");
      motor_stop();
    }
    
    trigger();

    durationLeft = pulseIn(echoPinLeft, HIGH);
    distanceLeft = (durationLeft / 2) / 29.1;
    Serial.print(distanceLeft);
    Serial.println(" cm LEFT");
    
    delay(100);
    
    trigger();

    durationRight = pulseIn(echoPinRight, HIGH);
    distanceRight = (durationRight / 2) / 29.1;
    Serial.print(distanceRight);
    Serial.println(" cm RIGHT");

    delay(100);

    if (mforward == true) {
      if (distanceLeft <= 7) {
        Serial.println("drive_right");
        drive_right_short();
      }
      else if (distanceRight <= 7) {
        Serial.println("drive_left");
        drive_left_short();
      }
    }
    
    if (mstop == true) {
      // Pick random number
      Random();
      if (distanceLeft >= 9) {
        if (randNumber == 0)
        {
          Serial.println("drive_left");
          drive_left();                
        }
        else if (randNumber == 1) {
          Serial.println("drive_right");
          drive_right();        
        }
      }
      else if (distanceRight >= 9) {
         if (randNumber == 1)
         {
           Serial.println("drive_right");
           drive_right();     
         }
         else if (randNumber == 0) {
          Serial.println("drive_left");
          drive_left();
         }
       }
       else {
        Serial.println("drive_backward");
        drive_backward();
        Serial.println("drive_left");
        drive_left();        
       }
     }
        
    Serial.println("");
    delay(50); 
    String comma = ",";
    String sendBack = distanceFrontR + comma  + distanceFrontL + comma + distanceLeft + comma +  distanceLeft + comma;
    Serial1.print(sendBack);
}

void trigger() {
   digitalWrite(trigPin, LOW); 
   delayMicroseconds(2);
   digitalWrite(trigPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(trigPin, LOW);
}
                                                                                   
void motor_stop() {
  mstop = true;
  mforward = false;
  analogWrite(motor_left[0], 0);
  analogWrite(motor_left[1], 0);

  analogWrite(motor_right[0], 0);
  analogWrite(motor_right[1], 0);
  delay(25);
  
}

void drive_backward() {
  mbackward = true;
  mstop = false;
  analogWrite(motor_left[0], 200);
  analogWrite(motor_left[1], 0);

  analogWrite(motor_right[0], 200);
  analogWrite(motor_right[1], 0);
  delay(500);
}

void drive_forward() {
  mforward = true;
  mstop = false;
  analogWrite(motor_left[0], 0);
  analogWrite(motor_left[1], 200);

  analogWrite(motor_right[0], 0);
  analogWrite(motor_right[1], 200);
}

void drive_left() {
  mleft = true;
  mstop = false;
  analogWrite(motor_left[0], 0);
  analogWrite(motor_left[1], 200);

  analogWrite(motor_right[0], 200);
  analogWrite(motor_right[1], 0);
  delay(500);
}

void drive_left_short() {
  mleft = true;
  mstop = false;
  analogWrite(motor_left[0], 0);
  analogWrite(motor_left[1], 200);

  analogWrite(motor_right[0], 200);
  analogWrite(motor_right[1], 0);
  delay(200);
}

void drive_right() {
  mright = true;
  mstop = false;
  analogWrite(motor_left[0], 200);
  analogWrite(motor_left[1], 0);

  analogWrite(motor_right[0], 0);
  analogWrite(motor_right[1], 200);
  delay(500);
}

void drive_right_short() {
  mright = true;
  mstop = false;
  analogWrite(motor_left[0], 200);
  analogWrite(motor_left[1], 0);

  analogWrite(motor_right[0], 0);
  analogWrite(motor_right[1], 200);
  delay(200);
}

void Random()
{
  // Random number, 0 OR 1
  randNumber = random(2);
}

    




 


 

