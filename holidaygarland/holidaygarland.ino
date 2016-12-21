#include <Adafruit_NeoPixel.h>

#define PIN 11
#define NUM 49 // The string has 50 but I broke one.

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM, PIN, NEO_RGB + NEO_KHZ400);
#define BRIGHT 64 // The default of 255 was SUPER bright, so this cuts it down to 25% of max
#define PAUSE 250

uint32_t colors[] = { strip.Color(255,0,0), strip.Color(0,255,0), strip.Color(255,215,0), strip.Color(0, 0, 255) };
int string[NUM];

void setup() {
  strip.begin();
  strip.setBrightness(BRIGHT);
  Serial.begin(9600);

  int y = 0;
  for(int x=0 ; x < strip.numPixels() ; x++) {
      strip.setPixelColor(x, colors[y%4]);
      string[x] = y%4;
      Serial.print("Setting ");
      Serial.print(x);
      Serial.print(" to ");
      Serial.print(y%4);
      Serial.println();
      y++;
  }
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
    int x=random(1,strip.numPixels()-1);
    int b=chooseOne(x);
    Serial.print("Setting ");
    Serial.print(x);
    Serial.print(" to ");
    Serial.print(b);
    Serial.println();
    strip.setPixelColor(x, colors[b]);
    strip.show();
    string[x]=b;
    delay(PAUSE);
}

int chooseOne(int x) {
  int avail[] = {0};
  int pos = 0;
  int current = string[x];
  int prev = string[x-1];
  int next = string[x+1];
  Serial.print(prev);
  Serial.print(" ");
  Serial.print(current);
  Serial.print(" ");
  Serial.print(next);
  Serial.println();

  Serial.print("Adding ");
  for (int x=0 ; x<4 ; x++) {
    if( (x != current) && (x != prev) && (x != next) ) {
      Serial.print(x);
      Serial.print(" ");
      avail[pos] = x;
      pos++;
    }
  }
  Serial.println(" to list");

  int n = random(sizeof(avail));
  return avail[n];
}

