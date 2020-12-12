#define L_COUNT   5
#define R_COUNT   5

unsigned int Ell = 12;
unsigned int Tll = 13;
unsigned int Tl = 11;
unsigned int El = 10;
unsigned int Tr = 9;
unsigned int Er = 8;
unsigned int Trr = 3;
unsigned int Err = 2;
unsigned int outl = 5;
unsigned int outll= 4;
unsigned int outr=6;
unsigned int outrr=7;

double cm;
int threshold = 50;
 
void setup()
 
{
 
    Serial.begin(9600);
    pinMode(Ell, INPUT);
    pinMode(Tll, OUTPUT);
    pinMode(El, INPUT);
    pinMode(Tl, OUTPUT);
    pinMode(Er, INPUT);
    pinMode(Tr, OUTPUT);
    pinMode(Err, INPUT);
    pinMode(Trr, OUTPUT);
    pinMode(outl, OUTPUT);
    pinMode(outll, OUTPUT);
    pinMode(outrr, OUTPUT);
    pinMode(outr, OUTPUT);
    digitalWrite(outl,HIGH);
    digitalWrite(outll,HIGH);
    digitalWrite(outrr,HIGH);
    digitalWrite(outr,HIGH);
}

void LL()
{
//  Serial.print("LL:");
  digitalWrite(Tll, LOW); //低高低电平发一个短时间脉冲去TrigPin 
  delayMicroseconds(2);       // delayMicroseconds在更小的时间内延时准确
  digitalWrite(Tll, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(Tll, LOW); //通过这里控制超声波的发射
  
  cm = pulseIn(Ell, HIGH) / 58.0; //将回波时间换算成cm 
  cm = (long(cm * 100.0)) / 100.0; //保留两位小数 
//  Serial.print("Distance:"); 
//  Serial.print(cm); 
//  Serial.print("cm"); 
//  Serial.println(); 
//  delay(20);
  digitalWrite(outll,HIGH);
  if(cm>threshold) 
  {
    Serial.println("ll");
    digitalWrite(outll,HIGH);
  }
  else 
    digitalWrite(outll,LOW);
}

int l_count = 0;

void L()
{
//  Serial.print("L:");
  digitalWrite(Tl, LOW); //低高低电平发一个短时间脉冲去TrigPin 
  delayMicroseconds(2);       // delayMicroseconds在更小的时间内延时准确
  digitalWrite(Tl, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(Tl, LOW); //通过这里控制超声波的发射
  
  cm = pulseIn(El, HIGH) / 58.0; //将回波时间换算成cm 
  cm = (long(cm * 100.0)) / 100.0; //保留两位小数 
//  Serial.print("Distance:"); 
//  Serial.print(cm); 
//  Serial.print("cm"); 
//  Serial.println(); 
  if(cm>threshold) 
  {
    l_count = 0;
    digitalWrite(outl,HIGH);
  }
  else 
  {
    l_count++;
    if (l_count >= L_COUNT)
    {
      digitalWrite(outl,LOW);
      l_count = 0;
//      Serial.println("l");
    }  
  }
  delay(10);
}

int r_count = 0;

void R()
{
//  Serial.print("R:");
  digitalWrite(Tr, LOW); //低高低电平发一个短时间脉冲去TrigPin 
  delayMicroseconds(2);       // delayMicroseconds在更小的时间内延时准确
  digitalWrite(Tr, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(Tr, LOW); //通过这里控制超声波的发射
  
  cm = pulseIn(Er, HIGH) / 58.0; //将回波时间换算成cm 
  cm = (long(cm * 100.0)) / 100.0; //保留两位小数 
//  Serial.print("Distance:"); 
//  Serial.print(cm); 
//  Serial.print("cm"); 
//  Serial.println(); 
  if(cm  >threshold) 
  {
    r_count = 0;
    digitalWrite(outr,HIGH);
  }
  else 
  {
    r_count++;
    if (r_count >= R_COUNT)
    {
      digitalWrite(outr,LOW);
      r_count = 0;
//      Serial.println("r");
    }
  }
  delay(5);
}

void RR()
{
//  Serial.print("RR:");
  digitalWrite(Trr, LOW); //低高低电平发一个短时间脉冲去TrigPin 
  delayMicroseconds(2);       // delayMicroseconds在更小的时间内延时准确
  digitalWrite(Trr, HIGH); 
  delayMicroseconds(10);
  digitalWrite(Trr, LOW); //通过这里控制超声波的发射
  
  cm = pulseIn(Err, HIGH) / 58.0; //将回波时间换算成cm 
  cm = (long(cm * 100.0)) / 100.0; //保留两位小数 
//  Serial.print("Distance:"); 
//  Serial.print(cm); 
//  Serial.print("cm"); 
//  Serial.println(); 
  if(cm>threshold) 
  {
    Serial.println("rr");
    digitalWrite(outrr,HIGH);
  }
  else 
    digitalWrite(outrr,LOW);
  delay(5);
}

void loop() 
{ 
//  LL();
  L();
  R();
//  RR();
}
