int motor_left[] = {4, 5};
int motor_right[] = {2, 3};
int i;                                                                            //store motor left, right pins
int leftF, leftB, rightF, rightB;                                                 //variables for different motor states

byte inbyte;      //store serial input 
String serialDataIn;
int data[4];
int counter;
String val;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);  //start serial monitor

  int i;
  for (i = 0; i < 2; i++) {
    pinMode(motor_left[i], OUTPUT);                                               //set pins as outputpins
    pinMode(motor_right[i], OUTPUT);
  }
}

void loop() {
      

  if (Serial.available()) {
        inbyte = Serial.read();

  
        
        if(inbyte >= '0' & inbyte <= '9')
            serialDataIn += inbyte - 48;
        if (inbyte == ',' || inbyte == 'r' ){  // Handle delimiter
            data[counter] = serialDataIn.toInt();
            serialDataIn = ("");
            counter = counter + 1;
        }
        if(inbyte ==  'r' || counter >= 4){  // end of line
    
            
            analogWrite(motor_left[0], data[0]);
            analogWrite(motor_left[1], data[1]);
            analogWrite(motor_right[0], data[2]);
            analogWrite(motor_right[1], data[3]);
            counter = 0;
            
          }

       

Serial.println(motor_left[0]);
Serial.println(motor_left[1]);
Serial.println(motor_right[0]);
Serial.println(motor_right[1]);
}
}

