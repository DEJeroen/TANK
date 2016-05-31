#define trigPin 25
#define echoPinFront1 31
#define echoPinFront2 29
#define echoPinLeft 27
#define echoPinRight 33


long durationFront1, distanceFront1, distanceFront2, durationFront2;
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
bool automaticDrive = true;
String val;

void setup() {
  Serial.begin(9600);     //USB Serial
  Serial1.begin(9600);  //Connection with Megalania (Android app)
  Serial2.begin(9600);  //Connection with other car

  int i;
  for (i = 0; i < 2; i++) {
    pinMode(motor_left[i], OUTPUT);                                               //set pins as outputpins
    pinMode(motor_right[i], OUTPUT);
  }



  pinMode(trigPin, OUTPUT);
  pinMode(echoPinFront1, INPUT);
  pinMode(echoPinFront2, INPUT);
  pinMode(echoPinLeft, INPUT);
  pinMode(echoPinRight, INPUT);


    attachInterrupt(echoPinFront1, setSensorFront1, CHANGE );
    attachInterrupt(echoPinFront2, setSensorFront2, CHANGE );
    attachInterrupt(echoPinLeft, setSensorLeft, CHANGE );
    attachInterrupt(echoPinRight, setSensorRight, CHANGE );
  
}

void loop() {
      

  if (Serial1.available()) {
        inbyte = Serial1.read();
        
        if(inbyte == 'm') {
          Serial.print("Manual");
          automaticDrive = false;
         detachInterrupt(echoPinFront1);
         detachInterrupt(echoPinFront2);
         detachInterrupt(echoPinLeft);
         detachInterrupt(echoPinRight);
        }

       else if(inbyte == 'a') {
        Serial.print("Automatic");
        automaticDrive = true;
    attachInterrupt(echoPinFront1, setSensorFront1, CHANGE );
    attachInterrupt(echoPinFront2, setSensorFront2, CHANGE );
    attachInterrupt(echoPinLeft, setSensorLeft, CHANGE );
    attachInterrupt(echoPinRight, setSensorRight, CHANGE );
       }

       if (automaticDrive == false) {
        manualControl();
        
       }
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

         setMotors();

          //Set Antwerp car to new speed

          
          
          

       


        
    }
}

void setSensorFront1() {
    durationFront1 = pulseIn(echoPinFront1, HIGH);
    distanceFront1 = (durationFront1 / 2) / 29.1;
    automaticControl();
}
void setSensorFront2() {
    durationFront1 = pulseIn(echoPinFront1, HIGH);
    distanceFront1 = (durationFront1 / 2) / 29.1;
    automaticControl();
}
void setSensorLeft() {
    durationFront1 = pulseIn(echoPinFront1, HIGH);
    distanceFront1 = (durationFront1 / 2) / 29.1;
    automaticControl();
}
void setSensorRight() {
    durationFront1 = pulseIn(echoPinFront1, HIGH);
    distanceFront1 = (durationFront1 / 2) / 29.1;
    automaticControl();
}

void automaticControl() {
  Serial.print("Drive or not to drive");

      if (distanceFront1 > 15 && distanceFront2 > 15) {                             
      //Serial.println("drive_forward");                          //if no object in front of neither front sensor, drive forward
      driveSpeed[0] = 200;
      driveSpeed[1] = 0;
      driveSpeed[2] = 200;
      driveSpeed[3] = 0;
    }
    else if (distanceFront1 <= 15 && distanceFront2 > 15) {
      //Serial.println("drive_left");                             //if an object is in front of the right sensor, drive left
      driveSpeed[0] = 200;
      driveSpeed[1] = 0;
      driveSpeed[2] = 0;
      driveSpeed[3] = 200;
    }
    else if (distanceFront2 <= 15 && distanceFront1 > 15) {
      //Serial.println("drive_right");                            //if an object is in front of the left sensor, drive right
      driveSpeed[0] = 0;
      driveSpeed[1] = 200;
      driveSpeed[2] = 200;
      driveSpeed[3] = 0;
    }
    else if (distanceFront1 <= 15 && distanceFront2 <= 15) {
      //Serial.println("motor_stop");
      driveSpeed[0] = 0;
      driveSpeed[1] = 0;
      driveSpeed[2] = 0;
      driveSpeed[3] = 0;
    }
    setMotors();
}

    void setMotors() {

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
    Serial2.write("0");
  }
  else if  (driveSpeed[0] > 100 && driveSpeed[1] == 0  && driveSpeed[2] > 100 && driveSpeed[3] == 0 )  {
    //drive car forward
    Serial.println("forward");
    Serial2.write("1");
  }

  
  else if  (driveSpeed[0] == 0 && driveSpeed[1] > 100  && driveSpeed[2] == 0 && driveSpeed[3] > 100)  {
    //turn left fast
    Serial.println("backwards");
     Serial2.write("3");
  }

  else if  (driveSpeed[0] > 100 && driveSpeed[1] == 0  && driveSpeed[2] == 0 && driveSpeed[3] > 100)  {
    //turn right fast
    Serial.println("right");
    Serial2.write("5");
  }
  else if  (driveSpeed[0] == 0 && driveSpeed[1] > 100  && driveSpeed[2] > 100 && driveSpeed[3] == 0 )  {
    //drive car backwards
    Serial.println("left");
    Serial2.write("6");
  }

  else {
    Serial.println("Recieving bogus data!");
  }

      
    }




 


 

