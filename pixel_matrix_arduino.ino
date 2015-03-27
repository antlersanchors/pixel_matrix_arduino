

#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            3

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      256

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int color[3] = {100, 100, 100}; //the Array that defines the color of the light

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete


void setup() {

  pixels.begin(); // This initializes the NeoPixel library.
  Serial.begin(115200);

  pinMode(13, OUTPUT);

}

void loop() {
  // print the string when a newline arrives:
  if (stringComplete) {

    //Serial.println(inputString);

    int sharpindex = inputString.indexOf('#');
    //Serial.println(sharpindex);

    int pixeltoChange = inputString.substring(0, sharpindex).toInt();
    // Serial.println(pixeltoChange);

    String colorhex=inputString.substring(sharpindex);
    // Serial.println(colorhex);

    // clear the string:
    hexColorConverter(colorhex);

    pixels.setPixelColor(pixeltoChange, pixels.Color(color[0], color[1], color[2]));
    pixels.show();
    stringComplete = false;
    inputString="";

  }

}

void colorChange(const String& topic, const String& subtopic, const String& message) {
  Serial.println(message);

  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);

  hexColorConverter(message);
  changeAllLedColors(color[0], color[1], color[2]);
}


void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}




void changeAllLedColors(int r, int g, int b) {
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(r, g, b)); // Moderately bright green color.
  }
  pixels.show();

  digitalWrite(13, HIGH);
  delay(30);
  digitalWrite(13,LOW);
}

void changeSinglePixel(int index, int r, int g, int b) {
  pixels.setPixelColor(index, pixels.Color(r, g, b)); // Moderately bright green color.
  pixels.show();
}

void hexColorConverter(String c) {


  String hexstring = c.substring(1);

  //Serial.print(hexstring);
  //Serial.print("-");

  long number = (long) strtol( &hexstring[0], NULL, 16);
  color[0] = number >> 16;
  color[1] = number >> 8 & 0xFF;
  color[2] = number & 0xFF;

  //  Serial.print(color[0]);
  //  Serial.print("-");
  //  Serial.print(color[1]);
  //  Serial.print("-");
  //  Serial.println(color[2]);

}



