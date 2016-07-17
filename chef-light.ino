/*
    CHEF-LIGHT
    DEVICEID: [YOUR DEVICE ID]
    ACCESS TOKEN: [YOUR ACCESS TOKEN]
    
    //turnLedOn
    curl https://api.spark.io/v1/devices/[YOUR DEVICE ID]/turnLedOn -d access_token=[YOUR ACCESS TOKEN]
    
    //turnLedOff
    curl https://api.spark.io/v1/devices/[YOUR DEVICE ID]/turnLedOff -d access_token=[YOUR ACCESS TOKEN]
    
    //pass the values for the LED strip as the arg value at the end
    //set white led strip value
    curl https://api.spark.io/v1/devices/[YOUR DEVICE ID]/setWhiteLed -d access_token=[YOUR ACCESS TOKEN] -d "args=128"
    
    //set blue led strip value
    curl https://api.spark.io/v1/devices/[YOUR DEVICE ID]/setWhiteLed -d access_token=[YOUR ACCESS TOKEN] -d "args=128"
    
    //set red led strip value
    curl https://api.spark.io/v1/devices/[YOUR DEVICE ID]/setRedLed -d access_token=[YOUR ACCESS TOKEN] -d "args=128"
    
    //set green led strip value
    curl https://api.spark.io/v1/devices/[YOUR DEVICE ID]/setGreenLed -d access_token=[YOUR ACCESS TOKEN] -d "args=128"
    
    //set ALL led strip value
    curl https://api.spark.io/v1/devices/[YOUR DEVICE ID]/setAllLed -d access_token=[YOUR ACCESS TOKEN] -d "args=128"
    
    //show sirens
    curl https://api.spark.io/v1/devices/[YOUR DEVICE ID]/showSirens -d access_token=[YOUR ACCESS TOKEN] -d "args=5"
    
    //show basic sirens (no arguments)
    curl https://api.spark.io/v1/devices/[YOUR DEVICE ID]/showSirens -d access_token=[YOUR ACCESS TOKEN]  
    
*/



int blueLEDPin = D7;
int ledStripWhitePin = A0;
int ledStripBluePin = A1;
int ledStripRedPin = A4;
int ledStripGreenPin = A5;

void setup() {
    
    //set the PWM analog pins as outputs
    pinMode(ledStripWhitePin, OUTPUT);  // sets the white LED strip pin as output
    pinMode(ledStripBluePin, OUTPUT);  // sets the white LED strip pin as output
    pinMode(ledStripRedPin, OUTPUT);  // sets the white LED strip pin as output
    pinMode(ledStripGreenPin, OUTPUT);  // sets the white LED strip pin as output
    
    //set the default output to 0 (off)
    analogWrite(ledStripWhitePin, 0); 
    analogWrite(ledStripBluePin, 0); 
    analogWrite(ledStripRedPin, 0); 
    analogWrite(ledStripGreenPin, 0); 
    
    // register the cloud function calls
    Particle.function("turnLedOn", turnLedOn);//turn white strip on to my default
    Particle.function("turnLedOff", turnLedOff);//
    Particle.function("setWhiteLed", setWhiteLedStrip);
    Particle.function("setBlueLed", setBlueLedStrip);
    Particle.function("setRedLed", setRedLedStrip);
    Particle.function("setGreenLed", setGreenLedStrip);
    Particle.function("setAllLed", setAllLedStrip);
 
    Particle.function("showSirens", showSirens);   
    Particle.function("basicSirens", showBasicSirens);       
    
    //flash LED to indicate a restart
    flashLeds(3,50);
    
    //wait to show the cyan indication of web access
    delay(5000);    
    
    //take control of the RGB LED
    RGB.control(true);
}


void loop() {
    //set the onboard rgb LED to indicated cloud connection status
    if(Particle.connected()){
        // Sets the LED to blue
        RGB.color(0, 0, 255);
    }else{
        // Set the LED to red
        RGB.color(255, 0, 0);
    }

    delay(200);     
}


// this is where the logic of your original loop would come in
// if you send the respective number, you can use this
int setWhiteLedStrip(String command)
{
  int cmd = command.toInt();

  analogWrite(ledStripWhitePin, cmd); 

  return cmd;  // report back what was received
}

int setBlueLedStrip(String command)
{
  int cmd = command.toInt();

  analogWrite(ledStripBluePin, cmd); 

  return cmd;  // report back what was received
}

int setRedLedStrip(String command)
{
  int cmd = command.toInt();

  analogWrite(ledStripRedPin, cmd); 

  return cmd;  // report back what was received
}

int setGreenLedStrip(String command)
{
  int cmd = command.toInt();

  analogWrite(ledStripGreenPin, cmd); 

  return cmd;  // report back what was received
}


int setAllLedStrip(String command)
{
  int cmd = command.toInt();

  analogWrite(ledStripWhitePin, cmd); 
  analogWrite(ledStripRedPin, cmd); 
  analogWrite(ledStripBluePin, cmd); 
  analogWrite(ledStripGreenPin, cmd); 
  
  Particle.publish("setAllLedStrip()", command);

  return cmd;  // report back what was received
}

int showSirens(String command){
    resetAll();
    int cmd = command.toInt();
    int spaceLength = 200;
    int index = 0;

    while(index<cmd){
        analogWrite(ledStripRedPin, 255); 
        delay(spaceLength);               // wait for a second
        analogWrite(ledStripRedPin, 0); 
        delay(spaceLength); 
        
        analogWrite(ledStripBluePin, 255); 
        delay(spaceLength);               // wait for a second
        analogWrite(ledStripBluePin, 0); 
        delay(spaceLength);    
        delay(spaceLength);   
        index++;
    }
    return cmd;  // report back what was received
}


int showBasicSirens(String command){
    Particle.publish("showBasicSirens()");
    resetAll();
    int cmd = 20;
    int spaceLength = 200;
    int index = 0;

    while(index<cmd){
        analogWrite(ledStripRedPin, 255); 
        delay(spaceLength);               // wait for a second
        analogWrite(ledStripRedPin, 0); 
        delay(spaceLength); 
    
        analogWrite(ledStripBluePin, 255); 
        delay(spaceLength);               // wait for a second
        analogWrite(ledStripBluePin, 0); 
        delay(spaceLength);    
        delay(spaceLength);   
        index++;
    }
    return cmd;  // report back what was received
}

void flashLeds(int number, int spaceLength){
    // Set the LED to green
    RGB.color(0, 255, 0);
    
    int index = 0;
    while(index<=number){
        analogWrite(ledStripWhitePin, 255); 
        delay(spaceLength);               // wait for a second
        analogWrite(ledStripWhitePin, 0); 
        delay(spaceLength); 
    
        index++;
    }
}

int turnLedOn(String args){
    Particle.publish("turnLedOn()");
    analogWrite(ledStripWhitePin, 200); 
    return(1);
}

int turnLedOff(String args){
    resetAll();
    Particle.publish("turnLedOff()");
    return(0);
}

//private
void resetAll(){
    analogWrite(ledStripRedPin, 0); 
    analogWrite(ledStripGreenPin, 0); 
    analogWrite(ledStripBluePin, 0); 
    analogWrite(ledStripWhitePin, 0); 
}
