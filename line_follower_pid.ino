void rls_sense()
{
  v1 = digitalRead(D2);
  v2 = digitalRead(D3);
  v3 = digitalRead(D4);
  v4 = digitalRead(D5);
  v5 = digitalRead(D6);
  v6 = digitalRead(D7);
  v7 = digitalRead(D8);
}

void counter_count()
{
  rls_sense();
  while (v2 == 1 && v3 == 1 && v4 == 1 && v5 == 1 && v6 == 1 && v7 == 1)
  {
    rls_sense();
    jc = true;
  }

  if (jc == true)
  {
    junc_count++;
    jc = false;
  }
  //Serial.println(junc_count);
  //delay(1000);
}
void calculate_error()
{
  if (v1 == 0 && v2 == 0 && v3 == 0 && v4 == 0 && v5 == 0 && v6 == 0 && v7 == 1)
  {
    error = 6;
  }
  else if (v1 == 0 && v2 == 0 && v3 == 0 && v4 == 0 && v5 == 0 && v6 == 1 && v7 == 1)
  {
    error = 5;
  }
  else if (v1 == 0 && v2 == 0 && v3 == 0 && v4 == 0 && v5 == 0 && v6 == 1 && v7 == 0)
  {
    error = 4;
  }
  else if (v1 == 0 && v2 == 0 && v3 == 0 && v4 == 0 && v5 == 1 && v6 == 1 && v7 == 0)
  {
    error = 3;
  }
  else if (v1 == 0 && v2 == 0 && v3 == 0 && v4 == 0 && v5 == 1 && v6 == 0 && v7 == 0)
  {
    error = 2;
  }
  else if (v1 == 0 && v2 == 0 && v3 == 0 && v4 == 1 && v5 == 1 && v6 == 0 && v7 == 0)
  {
    error = 1;
  }
  else if (v1 == 0 && v2 == 0 && v3 == 0 && v4 == 1 && v5 == 0 && v6 == 0 && v7 == 0)
  {
    error = 0;
  }
  else if (v1 == 0 && v2 == 0 && v3 == 1 && v4 == 1 && v5 == 0 && v6 == 0 && v7 == 0)
  {
    error = -1;
  }
  else if (v1 == 0 && v2 == 0 && v3 == 1 && v4 == 0 && v5 == 0 && v6 == 0 && v7 == 0)
  {
    error = -2;
  }
  else if (v1 == 0 && v2 == 1 && v3 == 1 && v4 == 0 && v5 == 0 && v6 == 0 && v7 == 0)
  {
    error = -3;
  }
  else if (v1 == 0 && v2 == 1 && v3 == 0 && v4 == 0 && v5 == 0 && v6 == 0 && v7 == 0)
  {
    error = -4;
  }
  else if (v1 == 1 && v2 == 1 && v3 == 0 && v4 == 0 && v5 == 0 && v6 == 0 && v7 == 0)
  {
    error = -5;
  }
  else if (v1 == 1 && v2 == 0 && v3 == 0 && v4 == 0 && v5 == 0 && v6 == 0 && v7 == 0)
  {
    error = -6;
  }
  else if (v1 == 0 && v2 == 0 && v3 == 0 && v4 == 0 && v5 == 0 && v6 == 0 && v7 == 0)
  {
    if (prev_error = 6)
    {
      error = 7;
    }
    else if (prev_error == -6)
    {
      error = -7;
    }
    else
    {
      wait();
    }
  }
  else if (v1 == 1 && v2 == 1 && v3 == 1 && v4 == 1 && v5 == 1 && v6 == 1 && v7 == 1)
  {
    error = 0;
  }
}

void wait()
{
  analogWrite(motorA_pwm, 0);
  analogWrite(motorB_pwm, 0);
  Serial.println("wait");
}

void pid_calculation()
{
  P = Kp * error;
  integral += error;
  I = Ki * integral;
  derivative = error - prev_error;
  D = Kd * derivative;
  output_pid = P + I + D;
  prev_error = error;
}

void move_forward()
{
  rls_sense();
  counter_count();
  calculate_error();
  pid_calculation();
  
  digitalWrite(motorA_dir1, HIGH);
  digitalWrite(motorA_dir2, LOW);
  digitalWrite(motorB_dir1, HIGH);
  digitalWrite(motorB_dir2, LOW);

  motorA_speed_new = motorA_speed + output_pid;
  motorB_speed_new = motorB_speed - output_pid;

  analogWrite(motorA_pwm, motorA_speed_new);
  analogWrite(motorB_pwm, motorB_speed_new);
}
