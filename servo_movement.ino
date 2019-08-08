void servo_up()
{
  servo_arm.write(180);
  servo_grip.write(40);
}

void servo_sense()
{
  if (sevo_sense_trans == true)
  {
    for (pos = 180; pos >= 125; pos -= 1)
    {
      servo_arm.write(pos);
      servo_grip.write(0);
      delay(20);
    }
    sevo_sense_trans = false;
  }
  else
  {
    servo_arm.write(125);
    servo_grip.write(0);
  }
}

void servo_pick()
{
  servo_arm.write(115);
  servo_grip.write(40);
  delay(3000);
  servo_arm.write(180);
  servo_grip.write(40);
  delay(1000);
}

void servo_drop()
{
  if (sevo_drop_trans == true)
  {
    for (pos = 180; pos >= 115; pos -= 1)
    {
      servo_arm.write(pos);
      servo_grip.write(40);
      delay(20);
    }
    sevo_sense_trans = false;
  }
  else
  {
    servo_arm.write(115);
    servo_grip.write(40);
    delay(1000);
    servo_arm.write(115);
    servo_grip.write(0);
    delay(1000);
  }
}

