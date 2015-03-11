#include <Adafruit_NeoPixel.h>

#define TOP_STRIP_PIN 8
#define BOTTOM_STRIP_PIN 9

#define LEDCOUNT 58



















const int brighnessSensporInPin = A0;  // Analog input pin that the potentiometer is attached to
unsigned int brightnessValue = 0;        // value read from the pot
unsigned long last_time;
unsigned long now_time;
int turn_leds_on=0;
unsigned int stripBrightnessValue = 0; 



// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel topstrip = Adafruit_NeoPixel(LEDCOUNT, TOP_STRIP_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel bottomstrip = Adafruit_NeoPixel(LEDCOUNT, BOTTOM_STRIP_PIN, NEO_GRB + NEO_KHZ800);








void setup(void)
{

 Serial.begin(9600); 
  
 last_time=micros();
 
  topstrip.begin();
  topstrip.show(); // Initialize all pixels to 'off'

  bottomstrip.begin();
  bottomstrip.show(); // Initialize all pixels to 'off'
 
 
  
}



void checkBrightnessSensor()
{
  
  Serial.print("checkBrightnessSensor() ");
  
  
  now_time=millis();
  
  //check every ten minutes..
  if(now_time<last_time || (now_time-last_time) >(1000 * 60 * 10))
  {

    last_time=now_time;

  
  
  
  
  //turn off all the leds
  
  all_off();
  delay(50);
  
  
  // measure brightness

  brightnessValue = analogRead(brighnessSensporInPin);      

 
  // set turn on/off flag according to sunshine
  if (brightnessValue>200) 
  {
   turn_leds_on=0;
   stripBrightnessValue=1;
   all_off();
   Serial.println("says its too bright. turning off.");
   
  }
  else
  {
 
  // from library .cpp file  
  // Stored brightness value is different than what's passed.
  // This simplifies the actual scaling math later, allowing a fast
  // 8x8-bit multiply and taking the MSB.  'brightness' is a uint8_t,
  // adding 1 here may (intentionally) roll over...so 0 = max brightness
  // (color values are interpreted literally; no scaling), 1 = min
  // brightness (off), 255 = just below max brightness.
    
    
    
   /*
    7-8  wenn aus bei nacht
    70-78 wenn an bei nacht
    58 bei daemmerung wenn aus
    229 bei tag (bewoelkt) 17:00
  */   
  
   // normal voll an
   stripBrightnessValue = 255;

   
   // je mehr daemmerung desto dunkler
   if(brightnessValue<50) stripBrightnessValue = 127;    
   
      
   // in der nacht mach dunkler
   if(brightnessValue<20) stripBrightnessValue = 50;

      Serial.print("brightnessValue: ");
      Serial.print(brightnessValue);
      Serial.print(" stripBrightnessValue: ");
      Serial.println(stripBrightnessValue);   
   
  
    
    
  // set strip brightness
   topstrip.setBrightness(stripBrightnessValue);
   topstrip.setBrightness(stripBrightnessValue);  
   turn_leds_on=1;
  }
  
  
  } // if time has come


}














void loop(void)
{
  
  checkBrightnessSensor();
  scanner_both(255,0,0, 100, 10);


  checkBrightnessSensor();
  scanner_both(0,255,0, 100, 10);
  
  
  checkBrightnessSensor();
  scanner_both(0,0,255, 100, 10);



  
  
  checkBrightnessSensor();
  rainbow_circle_whole(10,10); 
  
  checkBrightnessSensor();
  rainbow_whole_both(100,10);     
 
  checkBrightnessSensor();
  rainbow_cycle_both(10,10);

  
 
  

}
