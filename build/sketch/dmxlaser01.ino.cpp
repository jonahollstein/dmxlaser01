#include <Arduino.h>
#line 1 "/Users/jona/Documents/code/dmxlaser01/dmxlaser01.ino"




//include cpp types
#include <string>
using namespace std;


//include libraries
#include <ESP32Lib.h>
#include <Ressources/Font6x8.h>


//pin configuration
const int redPin = 32;
const int greenPin = 33;
const int bluePin = 25;
const int hsyncPin = 23;
const int vsyncPin = 22;

//VGA Device
VGA3Bit vga;


void(* resetFunc) (void) = 0;


// the setup function runs once when you press reset or power the board
#line 30 "/Users/jona/Documents/code/dmxlaser01/dmxlaser01.ino"
void setup();
#line 69 "/Users/jona/Documents/code/dmxlaser01/dmxlaser01.ino"
void loop();
#line 30 "/Users/jona/Documents/code/dmxlaser01/dmxlaser01.ino"
void setup() {

  //setting up serial monitor

  Serial.begin(115200);
  while(!Serial);

  //bool setCpuFrequencyMhz(uint32_t 240);

  int cpu = getCpuFrequencyMhz();

  int xtal = getXtalFrequencyMhz();

  Serial.println("serial setup - done");

  Serial.println(cpu);
  Serial.println(xtal);

  //we need double buffering for smooth animations??????
  vga.setFrameBufferCount(2);
  //initializing i2s vga (with only one framebuffer)
  vga.init(vga.MODE320x240, redPin, greenPin, bluePin, hsyncPin, vsyncPin);
  //setting the font
  vga.setFont(Font6x8);

  Serial.println("vga setup - done");

  

  //Serial.println("hello - done");

  
  
}




// the loop function runs over and over again forever
void loop() {

  static GraphicsR1G1B1A1X2S2Swapped::Color bgcolor = vga.RGB(0,0,0);

  // check serial input

/*
  if (Serial.available()){
    

    String input = Serial.readString();
    if (input = "stop"){
      //while(Serial.available()==0);
      Serial.println("stop");
    }

    if (input = "bgred"){
      bgcolor = vga.RGB(255, 0, 0);
      Serial.println("stop");
    }
    if (input = "bgwhite"){
      bgcolor = vga.RGB(255, 255, 255);
      Serial.println("white");
    }

    if (input = "bgblack"){
      bgcolor = vga.RGB(0, 0, 0);
      Serial.println("black");
    }

    if (input = "reset"){
      Serial.write("reset");
      resetFunc();
    }

  }

  */


  //rotate..

  static int x1 = 100;
  static int y1 = 50;
  static int x2 = 100;
  static int y2 = 150;

  static int x1mod = 1;
  static int y1mod = 1;
  static int x2mod = -1;
  static int y2mod = -1;

  static int count = 0;



    x1 += x1mod;
    //Serial.println(x1);
    y1 += y1mod;
    x2 += x2mod;
    y2 += y2mod;

    if ( x1 >= 150  || x1 <= 50){
      x1mod = x1mod *-1;
    }

    if ( y1 >= 150  || y1 <= 50){
      y1mod = y1mod *-1;
    }
    if ( x2 >= 150  || x2 <= 50){
      x2mod = x2mod *-1;
    }
    if ( y2 >= 150  || y2 <= 50){
      y2mod = y2mod *-1;
    }

  //read DMX...


  //clear the frame with color
  vga.clear(bgcolor);

  vga.line(x1, y1, x2, y2, vga.RGB(0, 255, 255));

  vga.circle((x1 + x2) / 2, (y1 + y2)/2, 40, vga.RGB(0, 0, 255));


  vga.setCursor(200, 200);
  vga.print("hello");
  vga.setTextColor(vga.RGB(0, 0, 0));


  vga.show();

}
