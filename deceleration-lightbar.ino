
#include "LED.h"
#include "LightBar.h"
#include "Vec3D.h"

int inp = A1;

const int NUM_PINS = 4;
const int PINS[NUM_PINS] = {3, 6, 10, 11};

LightBar bar(PINS, NUM_PINS);
float t = 0;

void setup() {
  //bar = LightBar(PINS, NUM_PINS);
  pinMode(inp, INPUT);
  Serial.begin(9600);
}

void loop() {
  bar.update(analogRead(inp));
  bar.display();

  //Serial.println(analogRead(inp));
  t += analogRead(inp)/10.0;
}
