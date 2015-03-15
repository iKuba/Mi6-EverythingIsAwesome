const int pin_A_1 = 53;  // Enocder 1 A Channel
const int pin_B_1= 49;  // Enocder 1 B Channel
const int pin_A_2 = 51;  // Encoder 2 A Channel
const int pin_B_2 = 47;  // Encoder 2 B Channel

volatile int lastEncoded_1 = 0;
volatile int lastEncoded_2 = 0;

//Used for time calculations
unsigned long prev_time_1;
unsigned long curr_time_1;
double delta_time_1;
unsigned long prev_time_2;
unsigned long curr_time_2;
double delta_time_2;

double dis; //Distance per tick of encoder

//Encoder 1
double v_1; //Speed of Encoder 1
double t_1; // 
double t_sec_1; //Measured time in between ticks (in seconds)
int dir_1; //Direction of Encoder 1
int count_1;  //Count of Encoder 1, to determine # of ticks

//Encoder 2
double v_2; //Speed of Encoder 2
double t_2;
double t_sec_2; //Measured time in between ticks (in seconds)
int dir_2; //Direction of Encoder 1
int count_2; //Count of Encoder 2, to determine # of ticks

void setup()  {
  Serial.begin(9600); 
  
  curr_time_1 = micros();
  curr_time_1 = micros();
  prev_time_1 = 0;
  prev_time_2 = 0;
  dis = 18.0f*3.14f/180.0f *(17.5f/1000.0f);
  
  dir_1 = 0;
  dir_2 = 0;
  t_sec_1 = 0;
  t_sec_2 = 0;
  count_1 = 0;
  count_2 = 0;

  pinMode(pin_A_1, INPUT);
  pinMode(pin_B_1, INPUT);
  digitalWrite(pin_A_1, HIGH); //turn pullup resistor on
  digitalWrite(pin_B_1, HIGH); //turn pullup resistor on

  pinMode(pin_A_2, INPUT);
  pinMode(pin_B_2, INPUT);
  digitalWrite(pin_A_2, HIGH); //turn pullup resistor on
  digitalWrite(pin_B_2, HIGH); //turn pullup resistor on

  attachInterrupt(53, updateEncoder_1, CHANGE); 
  attachInterrupt(49, updateEncoder_1, CHANGE);
  attachInterrupt(51, updateEncoder_2, CHANGE); 
  attachInterrupt(47, updateEncoder_2, CHANGE);
} 

void calculateSpeed() {
  curr_time_1 = micros();
  curr_time_2 = micros(); 

  if (count_1%4 == 0) 
  { 
    delta_time_1 = curr_time_1 - prev_time_1;
    prev_time_1 = curr_time_1;
    t_sec_1 = delta_time_1/1000000;
    
    if (t_sec_1 != 0) 
    {
      v_1 = dis/t_sec_1;
    }
    else 
    {
      v_1 = 0;
    }
  } 

  if (count_2%4 == 0) 
  { 
    delta_time_2 = curr_time_2 - prev_time_2;
    prev_time_2 = curr_time_2;
    t_sec_2 = delta_time_2/1000000;
    
    if (t_sec_2 != 0) 
    {
      v_2 = dis/t_sec_2;
    }
    else 
    {
      v_2 = 0;
    }
  }
}

//ISR for Encoder 1
void updateEncoder_1(){
  count_1++;
  int MSB = digitalRead(pin_A_1); //MSB = most significant bit
  int LSB = digitalRead(pin_B_1); //LSB = least significant bit

  int encoded = (MSB << 1) | LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded_1 << 2) | encoded; //adding it to the previous encoded value

  //CW direction
  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) {
    dir_1 = 1;
  }

  //CCW direction
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) {
    dir_1 = 2;
  }
  calculateSpeed();
  lastEncoded_1 = encoded;
}

//ISR for Encoder 2
void updateEncoder_2(){
  count_2++;
  int MSB = digitalRead(pin_A_2); //MSB = most significant bit
  int LSB = digitalRead(pin_B_2); //LSB = least significant bit

  int encoded = (MSB << 1) | LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded_2 << 2) | encoded; //adding it to the previous encoded value

  //CW direction
  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) {
    dir_2 = 1;
  }

  //CCW direction
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) {
    dir_2 = 2;
  }
  calculateSpeed();
  lastEncoded_2 = encoded;
}

void loop()  {

  // Serial.print("Delta Time: ");
  // Serial.print(t_sec,4);
  // Serial.println(" s");
  // Serial.print("Distance: ");
  // Serial.print(dis,4);
  // Serial.println(" m");
  // Serial.print("Speed: ");
  // Serial.print(v,4);
  // Serial.println(" m/s");  
  
//  Serial.println(delta_time);
//  Serial.println(test,4);
  Serial.println();

//  Serial.println(getSpeed());
  delay(100);

}
