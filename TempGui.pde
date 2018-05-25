//ECE 303 Group Project
//Team 5C Design Project: Kombucha Temperature Regulator
//Chris Goralka, Lindsey Greathouse, Ricky Hubbard, Akhil Kanagaraj, and Isabelle Tessier

//Refernced http://www.interactiondesign.se/wiki/courses:intro.prototyping.spring.2015.jan19_20_21 for Arduino and Processing interaction


import processing.serial.*;
 
int linefeed = 10; // new line ASCII = 10
Serial myPort;
PFont f;
int startingTemperature = 70;
 
int value1 = 0; //this variable will contain the reading
int value2 = 0;
void setup () {
  size(800, 500);
  // change port!
  String portName = "COM3";
    
   myPort = new Serial(this, portName, 9600);
  // here we're saying that we need to buffer until 'NEW LINE'
  myPort.bufferUntil(linefeed);
  f = createFont("Arial",16,true);
}
 
void draw () 
{ 
  //do something with "value1"
  
  //draw temperature display circle
  background(255);
  fill(0);
  ellipse(200,200, 360, 360);
  
  //red if set temperature is greater than temperature reading
  if (value2 > (value1+5))
  {
  //blue color for cooling
  fill(0,0,153);
  ellipse(200, 200, 350, 350);
  }
  //if temperature is in green zome
  if (value2 == value1 || (value2 > value1 && value2 < (value1+5)))
  {
    fill(0,255,0);
    ellipse(200, 200, 350, 350);
    
  }
    
  //if system is heating
  if (value2 < value1)
  {
    fill(255,0,0);
    ellipse(200, 200, 350, 350);
  }
    
  //draw inner black circle 
  fill(0);
  ellipse(200, 200, 250, 250);
  fill(255);
  //rect(150, 200, 100, 50);
  //fill(0);
  //rect(155, 205, 90, 40);
  //displays temperature probe reading
  textFont(f,75);  // STEP 3 Specify font to be used                         // STEP 4 Specify font color
  fill(255);
  text(value2 + "°F",130,200);
  //textFont(f,16);  // STEP 3 Specify font to be used                         // STEP 4 Specify font color
  //fill(255);
  //text("The current temperature is:", 100,180);
  
  //system is heating...display heating
  if (value2 < value1)
  {
    textFont(f,32);  // STEP 3 Specify font to be used                         // STEP 4 Specify font color
    fill(204,0,0);
    text("Heating", 140,250);
  }
  //system is idle....display idle
  if (value1 == value2 || (value2 > value1 && value2 < value1+5))
  {
    textFont(f,32);  // STEP 3 Specify font to be used                         // STEP 4 Specify font color
    fill(255);
    text("Idle", 175,290);
  }
  
  //system is cooling...display cooling
  if (value2 > value1+5)
  {
    textFont(f,32);  // STEP 3 Specify font to be used                         // STEP 4 Specify font color
    fill(255);
    text("Cooling", 145,250);
  }
  
  //draw set temperature circle
  fill(0);
  ellipse(600, 200, 360, 360);
  //inner circle
  if (value1 < 60)
  {
    fill(0, 0, (value1 +190 ) );
  }
  if ((value1 == 60 || value1 > 60) && (value1 < 80))
  {
    fill((value1 +9), (value1 +9), 255);
  }
  if ((value1 > 80 || value1 == 80) && (value1 < 256))
  {
    fill(255, (255-value1), (255-value1));
  }
  if (value1 == 256 || value1 > 256)
  {
    fill(255,0,0);
  }
  
  ellipse(600, 200, 350, 350);
  //draw inner circle
  fill(0);
  ellipse(600, 200, 250, 250);
  //display set temperature
  textFont(f,75);  // STEP 3 Specify font to be used                         // STEP 4 Specify font color
  fill(255);
  if (value1 <100)
  {
    text(value1 + "°F",520,200);
  }
  if (value1 ==100 || value1 >100)
  {
  text(value1 + "°F",510,200);
  }
  textFont(f,36);  // STEP 3 Specify font to be used                         // STEP 4 Specify font color
  fill(0);
  text("Current Temperature", 40, 450);
  textFont(f,36);  // STEP 3 Specify font to be used                         // STEP 4 Specify font color
  fill(0);
  text("Temperature Set Point", 415, 450);

}
 
void serialEvent (Serial myPort) 
{
  // read serial buffer as string
  String myString = myPort.readString();
 
  // if we have any other bytes than linefeed
  if (myString != null) 
  {
    // trim crap
    myString = trim(myString);
     String sensors[] = split(myString, ',');
    if(sensors.length>1)
    {
      value1 = int(sensors[0]); 
      value2 = int(sensors[1]); //remember to create another value variable
      print(value1);
      print(',');
      println(value2);
  }
}
}