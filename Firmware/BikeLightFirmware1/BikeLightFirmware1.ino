#include <Adafruit_NeoPixel.h>
#include <math.h>
const float Pi = 3.14159;

  int r = 1;
// create a pixel strand with 1 pixel on PIN_NEOPIXEL
Adafruit_NeoPixel pixels(1, PIN_NEOPIXEL);
 
void setup() {
    pixels.begin();  // initialize the pixel
    Serial.begin(9600);
}
 


void loop() {
  for (int x = 0; x < (2*Pi); x = x + 1) {
    int r = (255/2)*sin(x)+(255/2);
    int g = (255/2)*sin(x+((2*Pi)/3))+(255/2);
    int b = (255/2)*sin(x+((4*Pi)/3))+(255/2);

    pixels.setPixelColor(0, pixels.Color(r, g, b));
    // and write the data
    pixels.show();
    delay(100);
  
  
 Serial.print("  r"); Serial.print(r);
  //Serial.print("  g");Serial.print(g);
  //Serial.print("  b");Serial.println(b);

}
}
