#include<Servo.h>

Servo pan, tilt;

const int ldr1 = 0;
const int ldr2 = 1;
const int ldr3 = 2;
const int ldr4 = 3;

double bright1, bright2, bright3, bright4;

double left, right, top, bottom;

int panDesired, tiltDesired;
int panCur, tiltCur;
int lAdj, rAdj;

void setup()
{
  Serial.begin(9600);

  pan.attach(5);
  tilt.attach(6);
  pan.write(90);
  tilt.write(91);

  while(true)
  {
    if(Serial.available() > 0)
    {
      byte mes = Serial.read();
      if (mes == 's') //start program
        break;
    }
    delay(100);
  }
}

void loop()
{
  if(Serial.available() > 0)
  {
    if(Serial.read() == 't');
      setup();
  }

  bright1 = (double)analogRead(ldr1);
  bright2 = (double)analogRead(ldr2) * 610.0/274;
  bright3 = (double)analogRead(ldr3) * 610.0/335;
  bright4 = (double)analogRead(ldr4) * 610.0/209;

  left = (bright1 + bright2) / 2.0;
  right = (bright3 + bright4) / 2.0;
  top = (bright3 + bright1) / 2.0;
  bottom = (bright2 + bright4) / 2.0;

  panCur = pan.read();
  tiltCur = tilt.read();

  if(tiltCur > 90)
  {
    lAdj = -3;
    rAdj = 3;
  }
  else
  {
    lAdj = 3;
    rAdj = -3;
  }

	if(left > right + 10) //pos pan
	{
	  panDesired = panCur + lAdj;
	}
	else if(right > left + 10)
	{
	  panDesired = panCur = rAdj;
	}
	else
	{
	  panDesired = panCur;
	}

  if(top > bottom + 10) //neg tilt
  {
    tiltDesired = tiltCur - 3;
  }
  else if(bottom > top + 10) //pos tilt
  {
    tiltDesired = tiltCur + 3;
  }
  else
  {
    tiltDesired = tiltCur;
  }

  if(panDesired == panCur && tiltDesired == tiltCur)
  {
    Serial.println('f');
    delay(500);
    Serial.print("pan: ");
    Serial.println(String(panCur));
    delay(500);
    Serial.print("tilt: ");
    Serial.println(String(tiltCur));
  }
  if(panDesired >= 170 || panDesired <= 10)
  {
    panDesired = panCur;
  }
  if(tiltDesired >= 170 || tiltDesired <= 10)
  {
    tiltDesired = tiltCur;
  }

  pan.write(panDesired);
  tilt.write(tiltDesired);


  delay(1000);
}
//mark 4
