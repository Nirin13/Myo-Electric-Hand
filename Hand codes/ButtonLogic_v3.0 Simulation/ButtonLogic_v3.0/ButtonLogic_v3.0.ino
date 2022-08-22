int lastButtonState = HIGH;   // the previous reading from the input pin
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 30;    // the debounce time; increase if the output flickers
bool buttonState = HIGH; //saving state of the switch
byte tapCounter; //for saving no. of times the switch is pressed
int timediff; //for saving the time in between each press and release of the switch
bool flag1, flag2; //just two variables

int analogpin = 0;
int val = 0;
int ledPin = 13;

//calibration
int temp=0;
int sens_max = 0;
int sens_min = 1023;
int threshold = 0;
bool state = HIGH;

//fist release should be last state
int prev_state = 0;
int hand_state = 0;

long double presstime, releasetime; //for saving millis at press and millis at release
void setup() {
  Serial.begin(115200); //for serial monitor
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  hand_calibration();
  digitalWrite(ledPin, LOW);
  threshold = sens_min + ((sens_max - sens_min) * 0.3);

//  digitalWrite(red, LOW);
//  delay(1000);
//  digitalWrite(red, HIGH);
//  delay(1000);
//  digitalWrite(green, LOW);
//  delay(1000);
//  digitalWrite(green, HIGH);
//  delay(1000);
//  digitalWrite(blue, LOW);
//  delay(1000);
//  digitalWrite(blue, HIGH);

}

void loop() {
  
  val = analogRead(analogpin); //muscle sensor connected to pin A0 being stated as val
  //Serial.println(val);
  
  if( val < threshold) //if you flex and the sensor value is greater than 550 then close servos--adjust this value to your muscle sensor value
    {
        digitalWrite(ledPin, LOW);
        delay(20);
        //Serial.println("LOW");
        state = HIGH;
    }
    
  else if(val > threshold)
    {
        digitalWrite(ledPin, HIGH);
        delay(20);
        //Serial.println("HIGH");
        state = LOW;
    }


  int reading = state;

  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;
    }
  }
  //Serial.println(buttonState);

  //when switch is pressed
  if (buttonState == 0 && flag2 == 0)
  {
    presstime = millis(); //time from millis fn will save to presstime variable
    flag1 = 0;
    flag2 = 1;
    tapCounter++; //tap counter will increase by 1
    //delay(10); //for avoiding debouncing of the switch
  }
  //when sw is released
  if (buttonState == 1 && flag1 == 0)
  {
    releasetime = millis(); //time from millis fn will be saved to releasetime var
    flag1 = 1;
    flag2 = 0;

    timediff = releasetime - presstime; //here we find the time gap between press and release and stored to timediff var
    //Serial.println(timediff);
    //delay(10);
  }

  if ((millis() - presstime) > 500 && buttonState == 1) //wait for some time and if sw is in release position
  {
    if (tapCounter == 1) //if tap counter is 1
    {
      if (timediff >= 500) //if time diff is larger than 400 then its a hold
      {
        //Serial.println("Fist release");
        hold(); //fn to call when the button is hold
      }
      else //if timediff is less than 400 then its a single tap
      {
        //Serial.println("fist full close");
        singleTap(); //fn to call when the button is single taped
      }
    }
    else if (tapCounter == 2 ) //if tapcounter is 2
    {
      if (timediff >= 500) // if timediff is greater than  400 then its single tap and hold
      {
        //Serial.println("Fist half close");
        tapAndHold(); //fn to call when the button is single tap and hold
      }
      else // if timediff is less than 400 then its just double tap
      {
        //Serial.println("point");
        doubleTap(); //fn to call when doubletap
      }
    }
    else if (tapCounter == 3) //if tapcounter is 3 //then its triple tap
    {
      //Serial.println("pinch");
      tripleTap(); //fn to call when triple tap
    }
    else if (tapCounter == 4) //if tapcounter is 4 then its 4 tap
    {
      //Serial.println("fingers close and open");
      fourTap();//fn to call when four tap
    }
    tapCounter = 0;
  }
  lastButtonState = reading;
  //Serial.print("status = ");
  //Serial.println(threshold);
  //delay(100);
  //Serial.print("/");
  Serial.print(hand_state);
  Serial.print("/");
//  Serial.print(prev_state);
//  Serial.print("/");
  Serial.println(val);
}

void nolight()
{
  //digitalWrite(red, HIGH);
  //digitalWrite(green, HIGH);
  //digitalWrite(blue, HIGH);
  //Serial.println("No light");
}

void singleTap()
{
  nolight();
  if(prev_state == 0)
  {
    hand_state = 1;
    prev_state = hand_state;
  }
  else
  {
    hand_state = prev_state;
  }
  return hand_state;
  return prev_state;
}

void doubleTap()
{
  nolight();
  if(prev_state == 0)
  {
    hand_state = 3;
    prev_state = hand_state;
  }
  else
  {
    hand_state = prev_state;
  }
  return hand_state;
  return prev_state;
}

void tripleTap()
{
  nolight();
  if(prev_state == 0)
  {
    hand_state = 4;
    prev_state = hand_state;
  }
  else
  {
    hand_state = prev_state;
  }
  return hand_state;
  return prev_state;
}

void fourTap()
{
  nolight();
  if(prev_state == 0)
  {
    hand_state = 5;
    prev_state = hand_state;
  }
  else
  {
    hand_state = prev_state;
  }
  return hand_state;
  return prev_state;
}

void hold()
{
  nolight();
    hand_state = 0;
    prev_state = 0;
    return hand_state;
    return prev_state;
}

void tapAndHold()
{
  nolight();
  if(prev_state == 0)
  {
    hand_state = 2;
    prev_state = 2;
  }
  else
  {
    hand_state = prev_state;
  }
  return hand_state;
  return prev_state;
}

void hand_calibration()
  {
    //Serial.println("Calibrating");
    while(millis() < 5000)
    {
      temp = analogRead(analogpin);
      if(temp < sens_min)
      {
        sens_min = temp;
      }
      if(temp > sens_max)
      {
        sens_max = temp;
      }    
    }
  }
