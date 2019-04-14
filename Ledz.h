#ifndef Ledz_h
#define Ledz_h

#include "Arduino.h"
#include "FastLED.h"
#include "Button.h"

struct CRGB;

class Ledz {
	
public:
	template<int _pin> void setup(int size);
	void setBrightness(int level);
	void resetCounter();

	void solidWhite();
	void solidColor(int color);
	void breathing(int speed);
	void movingRainbow(int speed);
	void beams(bool left, int length);
	void bars(bool left, int length, int speed);

private:
	struct CRGB* leds;
	struct CRGB color;
	int brightness, size;
	byte r, g, b, ir, ig, ib;
	int counter = 0;
	int getBrightness(int level);
	struct CRGB getColor(int color);
	struct CRGB getRandomColor(void);
	struct CRGB getNextColor(void);
	void updateColor();
	void moveLeft(int end, int start);
	void moveRight(int end, int start);
	void fill(int start, int end);
};

template<int p>
void Ledz::setup(int _size) {
	size = _size;
	leds = new CRGB[size];
	r = 255; g = 0; b = 0;
	ir = -1; ig = 1; ib = 0;
	for (int i = 0; i < size; i++) {
		leds[i] = CRGB::Black;
	}
	pinMode(p, OUTPUT);
	FastLED.addLeds<NEOPIXEL, p>(leds, size);
}

#endif // !Ledz_h
