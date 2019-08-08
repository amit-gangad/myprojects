#include <Servo.h>

#define D2 47
#define D3 48
#define D4 49
#define D5 50
#define D6 51
#define D7 52
#define D8 53

#define motorA_pwm 2
#define motorB_pwm 3

#define motorA_dir1 4
#define motorA_dir2 5

#define motorB_dir1 6
#define motorB_dir2 7

#define S0 8
#define S1 9
#define S2 10
#define S3 11
#define sensorOut 12

Servo servo_arm;
Servo servo_grip;

bool sevo_sense_trans = true;
bool sevo_drop_trans = true;

int pos = 0;

int v1, v2, v3, v4, v5, v6, v7;

int motorA_speed = 60;
int motorB_speed = 100;

int motorA_speed_new, motorB_speed_new;

int error, prev_error;

float P, I, D;
float Kp = 11;
float Ki = 0;
float Kd = 5;

float output_pid;
int integral, derivative;

int junc_count = 0;
int pick_junc = 0;
boolean jc;

boolean c2 = true;
boolean c1 = true;

int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;

int redColor = 0;
int greenColor = 0;
int blueColor = 0;

int redMin = 87;
int redMax = 917;
int greenMin = 96;
int greenMax = 972;
int blueMin = 70 ;
int blueMax = 717;

int color = 0;
int desired_color = 1;
bool color_sense_enable = true;
void setup()
{
  servo_arm.attach(44);
  servo_grip.attach(45);

  pinMode(D2, INPUT);
  pinMode(D3, INPUT);
  pinMode(D4, INPUT);
  pinMode(D5, INPUT);
  pinMode(D6, INPUT);
  pinMode(D7, INPUT);
  pinMode(D8, INPUT);

  pinMode(motorA_pwm, OUTPUT);
  pinMode(motorB_pwm, OUTPUT);

  pinMode(motorA_dir1, OUTPUT);
  pinMode(motorA_dir2, OUTPUT);
  pinMode(motorB_dir1, OUTPUT);
  pinMode(motorB_dir2, OUTPUT);

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  servo_arm.write(180);
  servo_grip.write(40);

  Serial.begin(9600);
}

void loop()
{
  //Serial.println("I am here");
  rls_sense();
  counter_count();
  calculate_error();
  pid_calculation();
  //Serial.println(color);
  if (!(color == 1 && color == 2 && color == 3))
{
  if (junc_count == 0)
    {
      servo_up();
      move_forward();
    }
    else if (junc_count == 1)
    {
      if (c1 == true)
      {
        wait();
        servo_sense();
        delay(3000);
        c1 = false;
        //Serial.println("I will go aage");
      }
      else
      {
        color_sense();
        servo_sense();
        move_forward();
        //Serial.println("I will go aage");
      }
    }
    else if (junc_count > 1)
    {
      //Serial.println("I will go aage");
      color_sense();
      servo_sense();
      move_forward();
    }
  }
  else
  {
    if (color == desired_color)
    {
      servo_sense();
      wait();
      /*if (c2 == true && junc_count == pick_junc)
      {
        wait();
        servo_pick();
        //Serial.println("Picking Desired Color");
        delay(5000);
        c2 = false;
      }
      else
      {
        //Serial.println("Picked Desired Color");
        servo_up();
        move_forward();
      }*/
    }
    else
    {
      servo_sense();
      color = 0;
      //Serial.println("Don't like the color");
      color_sense_enable = true;
    }
  }
}
