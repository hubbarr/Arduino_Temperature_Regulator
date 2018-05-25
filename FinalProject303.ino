//ECE 303 Group Project
//Team 5C Design Project: Kombucha Temperature Regulator
//Chris Goralka, Lindsey Greathouse, Ricky Hubbard, Akhil Kanagaraj, and Isabelle Tessier

//Refernced http://www.interactiondesign.se/wiki/courses:intro.prototyping.spring.2015.jan19_20_21 for Arduino and Processing interaction
//Referenced https://create.arduino.cc/projecthub/TheGadgetBoy/ds18b20-digital-temperature-sensor-and-arduino-9cc806 for Temperature Sensor code
//Referenced http://www.instructables.com/id/Play-Custom-Melodies-on-Arduino/ and https://www.arduino.cc/en/Tutorial/Melody for Speaker code


//declare libraries used in this project
//These libraries are used for the digital temperature probe

#include <OneWire.h>
#include <DallasTemperature.h>

//declare pins that will be used
int tempProbePin = 2;
int potPin = A5;
int HeatingPin = 8;
int DonePin=12;
int coolingPin= 13 ;
int speakerPin= 3;
int powerPin= 11;
int fanPin = 6;
int temp;

//setup for digital temperature probe
// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 2
 
// Setup a oneWire instance to communicate with any OneWire devices 
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
 
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

const int switchPin = 1;

//setup for pieze speaker song

//defines brackets and words as values 

char notes[] = "azbC"; //defines the notes as arbitrary letters
int length = sizeof(notes); // the number of notes
int beats[] = {2,3,3,16}; //sets the beats for the notes
int tempo = 75; //sets the tempo

//sets a function to play the tones at a certain time
void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}

//sets a function to play the notes at a certain times
void playNote(char note, int duration) {
  char names[] = { 'a', 'z', 'b', 'C' }; //names the notes as letters   
  int tones[] = {1126, 1063, 1001, 947}; //pairs tone values to the named characters
  
  // plays the tone corresponding to the note name
  for (int i = 0; i < 4; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}



void setup() {
 //declare pins as inputs or outputs
  pinMode(tempProbePin, INPUT);
  pinMode(HeatingPin, OUTPUT);
  pinMode(DonePin, OUTPUT);
  pinMode(coolingPin, OUTPUT);
  pinMode(powerPin, OUTPUT);
  pinMode(switchPin, INPUT);
  pinMode(potPin, INPUT);
  pinMode(fanPin, OUTPUT);
  // start serial port
  Serial.begin(9600);
  // Start up the library
  sensors.begin();
}

void loop() {
  //request temperature from temperature probe
  sensors.requestTemperatures();
  //compare temperature from probe to set temperature
  //if temperature is less than set temperature turn on heater
  while(sensors.getTempFByIndex(0) < (analogRead(potPin)/3))
  {
    //print the temperature and set temperature to serial port for processing to use
    //set temperature probe to an integer
    temp = sensors.getTempFByIndex(0);
    Serial.print(analogRead(A5)/3);
    Serial.print(",");
    Serial.println(temp);
    //turn on Red LED indicating heater is on
    digitalWrite(HeatingPin, HIGH);
    //set pin to transistor to high to turn on heater
    digitalWrite(powerPin, HIGH);
    //request temperature from probe again for comparison
    sensors.requestTemperatures();
    
  }
  //this code runs once the while loop has been broken
  //turn off heater
  digitalWrite(powerPin, LOW);
  //turn off RED LED
  digitalWrite(HeatingPin, LOW);
  //Turn on green LED indicating the temperature is in range
  digitalWrite(DonePin, HIGH);

  
  //code for piezo speaker goes here

   pinMode(speakerPin, OUTPUT); //sets the speaker pin to be the output
  
  //if something happens that triggers the switch to turn on 
  if (digitalRead(switchPin) == 1) {           

    //sets an indexed interval for the the notes to play over
    //each note plays at the value i, increases at intervals of 1
    for (int i = 0; i < length; i++) {
    
    //rest
    if (notes[i] == ' ') {
      delay(beats[i] * tempo); 
    } else {
      playNote(notes[i], beats[i] * tempo);
    }
    
    // pause between notes
    delay(tempo / 2); 
    
    //empty loop that stops the tune immediately after the last note is played
    }            
    {
    {
    }
    }
  }


  //request temperature for comparison
  sensors.requestTemperatures();

  //compare set temperature to temperature probe
  //if it is equal to the set temperature or within 5 degrees turn on green light

  while((sensors.getTempFByIndex(0) == (analogRead(potPin)/3)))
  {
    digitalWrite(DonePin, HIGH);
    temp = sensors.getTempFByIndex(0);
      //print the temperature from probe and set temperature to serial port
      Serial.print(analogRead(A5)/3);
      Serial.print(",");
      Serial.println(temp);
      sensors.requestTemperatures();
    
  }
  while((sensors.getTempFByIndex(0) > (analogRead(potPin)/3)))
  {
    while(sensors.getTempFByIndex(0) > ((analogRead(potPin)/3)+5))
    {
      temp = sensors.getTempFByIndex(0);
      //print the temperature from probe and set temperature to serial port
      Serial.print(analogRead(A5)/3);
      Serial.print(",");
      Serial.println(temp);
      digitalWrite(DonePin, LOW);
      digitalWrite(fanPin, HIGH);
      digitalWrite(coolingPin, HIGH);
      sensors.requestTemperatures();
    }
      temp = sensors.getTempFByIndex(0);
      Serial.print(analogRead(A5)/3);
      Serial.print(",");
      Serial.println(temp);
      digitalWrite(coolingPin, LOW);
      digitalWrite(fanPin, LOW);
      digitalWrite(coolingPin, LOW);
      //turn on green pin indicating system is in range
      digitalWrite(DonePin, HIGH);
      //request temperature for comparison
      sensors.requestTemperatures();
  }

  //once the while loop breaks turn off green LED
  digitalWrite(DonePin, LOW);
  sensors.requestTemperatures();
  }
  





