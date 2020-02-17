#include <ros.h>
#include <std_msgs/Int32.h>


#define dirPin 4
#define stepPin 3
#define EnabPin 8
#define dirPin2 7
#define stepPin2 6
#define EnabPin2 9
#define ActPin1 10
#define ActPin2 11



ros::NodeHandle  nh;
//-----------------------------------------------------------------------------------------
int z=0 ;
int xaxis=320;
int yaxis=240;
int c;
int up;
int down;
int posi;

//--------------------------------------------------------------------------------------------
void messageCb( const std_msgs::Int32& msg)
{
  xaxis=msg.data;
}

void messageCb1( const std_msgs::Int32& msg)
{
  yaxis=msg.data;
}

ros::Subscriber<std_msgs::Int32> sub("image_topic_1", messageCb );
ros::Subscriber<std_msgs::Int32> sub1("image_topic_2", messageCb1 );

//----------------------------------------------------------------------------------------------
void x_motor(int dir)
{
  if (dir==1)
  {
    digitalWrite(dirPin,HIGH);
    digitalWrite(stepPin,HIGH);
    delay(100);
    digitalWrite(stepPin,LOW);
    delay(100);
   }
  else if(dir==0)
  {
    digitalWrite(dirPin,LOW);
    digitalWrite(stepPin,HIGH);
    delay(100);
    digitalWrite(stepPin,LOW);
    delay(100);    
   }
}

void y_motor(int dire)
{
  if(dire==1)
  {
    digitalWrite(dirPin2,HIGH);
    digitalWrite(stepPin2,HIGH);
    delay(100);
    digitalWrite(stepPin2,LOW);
    delay(100);
  }
  else if(dire==0)
  {
    digitalWrite(dirPin2,HIGH);
    digitalWrite(stepPin2,HIGH);
    delay(100);
    digitalWrite(stepPin2,LOW);
    delay(100);
  }
}

void zmotor(int dr)
{
  if(dr==1)
  {
    digitalWrite(ActPin1, HIGH);
    digitalWrite(ActPin2, LOW);
  }
  else if(dr==2)
  {
    digitalWrite(ActPin1, LOW);
    digitalWrite(ActPin2, HIGH);
  }
  else if(dr==3)
  {
    digitalWrite(ActPin1,LOW);
    digitalWrite(ActPin2,LOW);
  }
}
//------------------------------------------------------------------------------------------
void camera(int ste,int axi,int yup)
{
  if(ste==0)
  {
      while(yup<40)
      {
        y_motor(1);
        ++yup;
      }
      if(yup==40)
      {
        z=1;
      }
    
    
  }
}
//--------------------------------------------------------------------------------------------

void searching(int w,int p,int lk, int kl)
{
  if(p==1)
  {
    if(w==320)
    {
      if(lk<100)
      {
      deac(0);
      x_motor(1);
      ++up;
      }
      else if(lk==100)
      {
        if(kl<100)
        {
          deac(0);
          x_motor(0);
          ++down;
        }
      }
    }
    
    else if(w!=320)
    {
      z=2;
      
    }
  }
}
//-----------------------------------------------------------------------------------------------
void grabx(int r,int t)
{
  if(t==2)
  {
    if(r<310)
    {
      deac(0);
      x_motor(1);
      posi=posi+1;
    }
    else if(r>330)
    {
      deac(0);
      x_motor(0);
      posi=posi-1;
    }
    else if(311<r<329)
    {
      //digitalWrite(13,HIGH);
      z=3;
    }
    
  }
}

void graby(int ret,int yx,int xc)
{
  if(ret==3)
  {
    if(311<xc<329)
    {
      if(yx<220)
      {
        y_motor(1);
      }
      else if(yx>250)
      {
        y_motor(0);
      }
      else if(220<yx<250)
      {
        z=4;
      }
    }
    else if(xc<311 || xc>329)
    {
      z=2;
    }
  }
 }


void actuator(int qw)
{
  if(qw==4)
  {
    zmotor(1);
  }
}

 //----------------------------------------------------------------------------------------------------

 
//-----------------------------------------------------------------------------------------------------
void pos(int op, int dp, int ap)
{
  if(op==100 && dp==100)
  {
    up=0;
    down=0;
    posi=up-down;
  }
  else if(op!=dp)
  {
    posi=op-dp;
  }
}
//---------------------------------------------------------------------------------------------------------


void deac(int dea)
{
  if(dea==1)
  {
  digitalWrite(EnabPin,HIGH);
  }
  else if(dea==0)
  {
  digitalWrite(EnabPin,LOW);
  }
}


//------------------------------------------------------------------------------------------------

void setup() {
  // put your setup code here, to run once:
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(EnabPin, OUTPUT);
  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  pinMode(EnabPin2, OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(ActPin1,OUTPUT);
  pinMode(ActPin2,OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
  nh.subscribe(sub1);

}

void loop() {
  nh.spinOnce();
  //delayMicroseconds(500);
  deac(1);
  pos(up,down,posi);
  searching(xaxis,z,up,down);
  grabx(xaxis,z);
  Serial.begin(9600);
  Serial.print(yaxis);
  
            }
