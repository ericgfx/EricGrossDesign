/*EricGrossDesign.com
This is designed to automate the Navigational sounds 
required when operating a sailboat in the US during 
low visibility (ie Fog).

Depending on whether a vessel is:
under motor vs sail, and 
moving vs stopped vs anchored.
Each requires a different sound pattern 
(short horn blasts, long horn blasts) refer to this image
http://ericgrossdesign.com/wp-content/uploads/2019/03/Fog-Sound-Signals.png
*/

// set pins:
const int buttonPin = 2;    // the number of the pushbutton pin
const int buttonAlarm = 1;	// this button triggers the ALARM! Five Dash Alert
const int signalPin = 9;    // the Green Wire for Relay
const int ledPin1 = 11;     // Red LED = Powder Driven Vessel
const int ledPin2 = 12;     // Green LED = Making Way
const int ledPin3 = 13;		// Blue LED = Anchored
const int testPin = 6;		// LED pin for testing stuff Blue LED
const int potPin = A0;		// for the sensor to adjust timing

// set sound info:
const int dash = 3000;       // length of time (milisec) for dash
const int dot = 600;     	 // length of time (milisec) for dot
const int betweenSounds=400; // length of time (milisec) between a dot or a dash
long betweenPattern = 10000;        // used for 2 minute time between sound pattern be cool to use POT for busy ports = more frequent
int sensorValue = 0;				// from potPin
int outputValue = 1023;				// to store mapped value
int signalData[][9]={       		// first 3 numbers indicate lights on or off for Power, Making Way, Anchored_Next is the Sound Pattern up to five_time between
  {0,0,0,0,0,0,0,0,1000} ,			// standby mode (ready for emergency sound)
  {1,1,0,dash,0,0,0,0,betweenPattern} ,		 // Under Power, Making Way
  {1,0,0,dash,dash,0,0,0,betweenPattern},    // Under Power, Stopped
  {0,1,0,dash,dot,dot,0,0,betweenPattern},	 // SAIL, NUC, RAM, FISH
  {0,0,1,dot,dash,dot,0,0,betweenPattern/2}, // Anchored - Ideally a bell
};										// did you know you can use variables, math, but not an array in an array?

const int soundStart = 3;   			// position in sub-arrays where the sound pattern starts
const int lastSound = 8;				// last position in sub-arrays where the sound ends
const int numPatterns = 4;				// number of sound pattern plus the Blank increase if adding more

// variables that will change:
int currentState = 0;

void setup() 
{
  pinMode(signalPin, OUTPUT);
  pinMode(testPin, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(buttonAlarm, INPUT);

  //This test loop turns pins on and then off
  //in the real world, nice to see the LEDs are working
  for (int i=1; i>=0; i--) 
  {
    digitalWrite(signalPin, i);
    digitalWrite(testPin, i);
    delay(betweenSounds);
 	digitalWrite(ledPin1, i);
    delay(betweenSounds);
  	digitalWrite(ledPin2, i);
    delay(betweenSounds);
  	digitalWrite(ledPin3, i);
    delay(betweenSounds);
  }
}

/*****************************
****** MAIN LOOP HERE ********
*****************************/

void loop() {
      displayIndicator(currentState);
  
// 3 second Delay before starting the Sound Pattern, 
// incase user is cycling to the next Sound Pattern
      for (int t=1; t<=3000 ; t++)  
      { 
        readButton;
      }
  
// iterate playing the dots or dashes of the Sound Pattern
 	  for (int x=soundStart; x<=lastSound; x++)
      {    				
        readButton;
    	playSound(currentState,x);
   	  }  
  
}


/*****************************
****** FUNCTIONS BELOW *******
*****************************/

/*******playSound***********/
//This function plays either the dot, dash or silence,
//while checking to see if the button has been pushed.
  
void playSound(int cstate, int x) 
{	
  if (signalData[cstate][x] > 0) 
      {
         for(long length=1; length*100 < signalData[cstate][x]; length++) 
         {
           if (x==lastSound) 
           {
		   //if this is the last sound, silence until repeat of Pattern
             digitalWrite(signalPin,LOW);
             digitalWrite(testPin,LOW);
           } 
           
           else 
           
           {
           //if not play the sound and the test pin
             digitalWrite(signalPin,HIGH);
             digitalWrite(testPin,HIGH);
           }
	       delay(100); //prevents jumps
           readButton();
         }
         digitalWrite(signalPin,LOW);
         delay(betweenSounds); //delay between a sigle dot or dash of the pattern
       }
}




/*********   readButton   ************/

void readButton()
{
int selectButton=digitalRead(buttonPin);
int alarmButton=digitalRead(buttonAlarm);
if (selectButton == HIGH) 
	{
		currentState=currentState+1;
	   	if (currentState > numPatterns) currentState=0; // cycle thru array of patterns
		digitalWrite(testPin,HIGH);						// indicate button pressed
  		displayIndicator(currentState);
  		delay(100);										// prevent jumping
  	}
  
if (alarmButton == HIGH) 
	{
  		playAlarm();
  		delay(400);
	}
digitalWrite(testPin,LOW);
}


/*********   playAlarm   ************/     
void playAlarm()
{
  for (int x=1; x<=5; x++)
  {
	digitalWrite(signalPin,HIGH);
    digitalWrite(testPin,HIGH);
	delay(dot);
	digitalWrite(signalPin,LOW);
    digitalWrite(testPin,LOW);
	delay(betweenSounds);
  }
//  displayIndicator(currentState); 
}
    
/*************** Display Indicator LEDs *********/
void displayIndicator(int state) 
{
  digitalWrite(ledPin1,signalData[state][0]);
  digitalWrite(ledPin2,signalData[state][1]);
  digitalWrite(ledPin3,signalData[state][2]);
}