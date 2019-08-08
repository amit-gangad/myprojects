void readColor()
{
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  redFrequency = pulseIn(sensorOut, LOW);
  redColor = map(redFrequency, redMin, redMax, 255, 0);
  delay(100);

  //green:
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  greenFrequency = pulseIn(sensorOut, LOW);
  greenColor = map(greenFrequency, greenMin, greenMax, 255, 0);
  delay(100);

  //blue:
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  blueFrequency = pulseIn(sensorOut, LOW);
  blueColor = map(blueFrequency, blueMin, blueMax, 255, 0);
  delay(100);
}

void decideColor()
{
  redColor = constrain(redColor, 0, 255);
  greenColor = constrain(greenColor, 0, 255);
  blueColor = constrain(blueColor, 0, 255);


  int maxVal = max(redColor, blueColor);
  maxVal = max(maxVal, greenColor);

  redColor = map(redColor, 0, maxVal, 0, 255);
  greenColor = map(greenColor, 0, maxVal, 0, 255);
  blueColor = map(blueColor, 0, maxVal, 0, 255);
  
  redColor = constrain(redColor, 0, 255);
  greenColor = constrain(greenColor, 0, 255);
  blueColor = constrain(blueColor, 0, 255);
  
  if (color_sense_enable == true)
  {
    if (redColor > 250 && greenColor < 225 && blueColor < 225)
    {
      pick_junc = junc_count + 1;
      color = 1;//red
      color_sense_enable = false;
    }
    else if (redColor < 225 && greenColor > 250 && blueColor < 250)
    {
      pick_junc = junc_count + 1;
      color = 2;//green
      color_sense_enable = false;
    }
    else if (redColor < 225 && greenColor < 255 && blueColor > 250)
    {
      pick_junc = junc_count + 1;
      color = 3;//blue
      color_sense_enable = false;
    }
    else
    {
      color = 0;//unknown
    }
  }
}

void color_sense()
{
  readColor();
  decideColor();
}
