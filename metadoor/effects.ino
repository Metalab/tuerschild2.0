
// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait, Adafruit_NeoPixel &strip) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();

      delay(wait);
  }
}

void rainbow(uint8_t wait, Adafruit_NeoPixel &strip) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255,strip));
    }
    strip.show();   
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait, Adafruit_NeoPixel &strip) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255,strip));

    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait, Adafruit_NeoPixel &strip) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();
     
      delay(wait);
     
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait, Adafruit_NeoPixel &strip) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, Wheel( (i+j) % 255,strip));    //turn every third pixel on
        }
        strip.show();
       
        delay(wait);
       
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}













// draw ONE inanimated rainbow
void rainbow(int wait, Adafruit_NeoPixel &strip) {
  int i, j;

  for (j=0; j < 256; j++) {     // 3 cycles of all 256 colors in the wheel
    for (i=0; i < LEDCOUNT; i++) {
      strip.setPixelColor(i, Wheel( (i + j) % 255,strip));
    }
    
    
    
    
    strip.show();   // write all the pixels out
    delay(wait);
  }
}







#define PI 3.14159265

void plasma(uint32_t c, int cycles, int wait, Adafruit_NeoPixel &strip) 
{



  


  float y;
  byte  r, g, b, r2, g2, b2;

  // Need to decompose color into its r, g, b elements
  g = (c >> 16) & 0x7f;
  r = (c >>  8) & 0x7f;
  b =  c        & 0x7f; 

  for(int x=0; x<(strip.numPixels()*5); x++)
  {
    for(int i=0; i<strip.numPixels(); i++) {
      y = sin(PI * (float)cycles * (float)(x + i) / (float)strip.numPixels());
      if(y >= 0.0) {
        // Peaks of sine wave are white
        y  = 1.0 - y; // Translate Y to 0.0 (top) to 1.0 (center)
        r2 = 255 - (byte)((float)(255 - r) * y);
        g2 = 255 - (byte)((float)(255 - g) * y);
        b2 = 255 - (byte)((float)(255 - b) * y);
      } else {
        // Troughs of sine wave are black
        y += 1.0; // Translate Y to 0.0 (bottom) to 1.0 (center)
        r2 = (byte)((float)r * y);
        g2 = (byte)((float)g * y);
        b2 = (byte)((float)b * y);
      }
      strip.setPixelColor(i, r2, g2, b2);
    }
    

    
    strip.show();
    delay(wait);

  }
}
  
    

    
    
    // "Larson scanner" = Cylon/KITT bouncing light effect
void scanner_both(uint8_t r, uint8_t g, uint8_t b,  uint8_t wait, uint8_t rounds) {
  int i, j, k, pos, dir;


  for(k=0;k<rounds;k++)
  {
  pos = 0;
  dir = 1;

  for(i=0; i<topstrip.numPixels()-1*8; i++) {
    // Draw 5 pixels centered on pos.  setPixelColor() will clip
    // any pixels off the ends of the strip, no worries there.
    // we'll make the colors dimmer at the edges for a nice pulse
    // look
    topstrip.setPixelColor(pos - 2, topstrip.Color(r/4, g/4, b/4));
    topstrip.setPixelColor(pos - 1, topstrip.Color(r/2, g/2, b/2));
    topstrip.setPixelColor(pos, topstrip.Color(r, g, b));
    topstrip.setPixelColor(pos + 1, topstrip.Color(r/2, g/2, b/2));
    topstrip.setPixelColor(pos + 2, topstrip.Color(r/4, g/4, b/4));

    bottomstrip.setPixelColor(pos - 2, topstrip.Color(r/4, g/4, b/4));
    bottomstrip.setPixelColor(pos - 1, topstrip.Color(r/2, g/2, b/2));
    bottomstrip.setPixelColor(pos, topstrip.Color(r, g, b));
    bottomstrip.setPixelColor(pos + 1, topstrip.Color(r/2, g/2, b/2));
    bottomstrip.setPixelColor(pos + 2, topstrip.Color(r/4, g/4, b/4));

    bottomstrip.show();
    topstrip.show();
    delay(wait);
    // If we wanted to be sneaky we could erase just the tail end
    // pixel, but it's much easier just to erase the whole thing
    // and draw a new one next time.
   // for(j=-2; j<= 2; j++)
   //{ 
   //     topstrip.setPixelColor(pos+j, topstrip.Color(0,0,0));
   //     bottomstrip.setPixelColor(pos+j, topstrip.Color(0,0,0));        
   //}    
   
   
    // Bounce off ends of strip
    pos += dir;
    if(pos < 0) {
      pos = 1;
      dir = -dir;
    } else if(pos >= topstrip.numPixels()-1) {
      pos = topstrip.numPixels() - 2;
      dir = -dir;
    }
  }
  } // rounds
}
    
    
    
    
 























void all_on(uint32_t c, Adafruit_NeoPixel &strip) 
{
 

    for(int i=0; i<strip.numPixels(); i++) 
    {
         strip.setPixelColor(i,c);
    }
  
  strip.show();
}


void rainbow_circle_whole(uint8_t wait, uint8_t rounds) {
  uint16_t i, j,k;

 for(k=0;k<rounds;k++)
 {

  for(j=0; j<256; j++) {
    for(i=0; i<topstrip.numPixels(); i++) {
      topstrip.setPixelColor(i, Wheel((i+j) & 255,topstrip));
      bottomstrip.setPixelColor(bottomstrip.numPixels()-i, Wheel((i+j) & 255,topstrip));
    }
    topstrip.show();   
    bottomstrip.show();   
    delay(wait);
  }
 }
}



void rainbow_cycle_both(uint8_t wait, uint8_t rounds) {
  uint16_t i, j,k;

 for(k=0;k<rounds;k++)
 {

  for(j=0; j<256; j++) {
    for(i=0; i<topstrip.numPixels(); i++) {
      topstrip.setPixelColor(i, Wheel((i+j) & 255,topstrip));
      bottomstrip.setPixelColor(i, Wheel((i+j) & 255,topstrip));
    }
    topstrip.show();   
    bottomstrip.show();   
    delay(wait);
  }
 }
}


void rainbow_whole_both(uint8_t wait, uint8_t rounds) {
  uint16_t i, j,k;
  uint32_t color =0;

 for(k=0;k<rounds;k++)
 {


    for(j=0; j<256; j++) 
    {

      color = Wheel((i+j) & 255,topstrip);
      
      for(i=0; i<topstrip.numPixels(); i++) 
      {  
      
      topstrip.setPixelColor(i, color);
      bottomstrip.setPixelColor(i, color);
      
      }
     topstrip.show();   
     bottomstrip.show();   
     delay(wait);
    
  }
 }
}



void all_off()
{
  
    for(int i=0; i<topstrip.numPixels(); i++) 
    {
         topstrip.setPixelColor(i,0);
    }
  
  topstrip.show();
  
    for(int i=0; i<bottomstrip.numPixels(); i++) 
    {
         bottomstrip.setPixelColor(i,0);
    }
  
  bottomstrip.show();



}










// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos, Adafruit_NeoPixel &strip) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}



