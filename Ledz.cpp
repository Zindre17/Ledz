#include "Arduino.h"
#include "Ledz.h"

int Ledz::getBrightness(int level) {
	int b;
	switch (level)
	{
	case 0:
		b = 0;
		break;
	case 1:
		b = 16;
		break;
	case 2:
		b = 64;
		break;
	case 3:
		b = 128;
		break;
	case 4:
		b = 255;
		break;
	default:
		b = 0;
		break;
	}
	return b;
}
CRGB Ledz::getColor(int color) {
	switch (color) {
	case 1:
		return CRGB(255, 0, 0);
	case 2:
		return CRGB(0, 255, 0);
	default:
		return CRGB(100, 100, 0);
	}
}
CRGB Ledz::getRandomColor() {
	int type = random(0, 6);
	int comp1 = random(0, 256);
	int comp2 = random(0, 256 - comp1);
	switch (type) {
	case 0:
		return CRGB(comp1, comp2, 0);
	case 1:
		return CRGB(comp1, 0, comp2);
	case 2:
		return CRGB(0, comp1, comp2);
	case 3:
		return CRGB(comp2, comp1, 0);
	case 4:
		return CRGB(comp2, 0, comp1);
	case 5:
		return CRGB(0, comp2, comp1);
	}
}
void Ledz::updateColor() {
	if (r >= 255) {
		ir = -1;
		ig = 1;
		ib = 0;
	}
	if (g >= 255) {
		ir = 0;
		ig = -1;
		ib = 1;
	}
	if (b >= 255) {
		ir = 1;
		ig = 0;
		ib = -1;
	}
	r += ir;
	g += ig;
	b += ib;
}

void Ledz::resetCounter() {
	counter = 0;
}
void Ledz::setBrightness(int level) {
	brightness = getBrightness(level);
	FastLED.setBrightness(brightness);
	FastLED.show();
}

void Ledz::solidWhite() {
	CRGB c = Candle;//CRGB(255, 244, 229); // warm fluorescent
	for (int i = 0; i < size; i++) {
		leds[i] = c;
	}
	FastLED.show();
}

void Ledz::solidColor(int color) {
	CRGB c = Ledz::getColor(color);
	for (int i = 0; i < size; i++) {
		leds[i] = c;
	}
	FastLED.show();
}

void Ledz::breathing(int speed) {
	counter++;
	if (counter >= speed) {
		for (int i = 0; i < size; i++) {
			leds[i] = CRGB(r, g, b);
		}
		FastLED.show();
		updateColor();
		counter = 0;
	}
}
void Ledz::movingRainbow(int speed) {
	moveLeft(size - 1, 1);
	leds[0] = CRGB(r,g,b);
	FastLED.show();
	counter++;
	if (counter >= speed) {
		counter = 0;
		updateColor();
	}
}
void Ledz::beams(bool l, int length) {
	counter++;
	if (counter >= length) {
		counter = 0;
		color = getRandomColor();
	}
	if (l) {
		moveLeft(size - 1, 1);
		leds[0] = color;
	}
	else {
		moveRight(size, 0);
		leds[size-1] = color;
	}
	FastLED.show();
}
void Ledz::bars(bool l, int length, int speed) {
	counter++;
	if (counter >= speed) {
		counter = 0;
		color = getRandomColor();
		CRGB next;
		int parts = size / length;
		parts = size % length == 0 ? parts - 1 : parts;
		if (l) {
			for (int i = 0; i <= parts; i++) {
				if (i == parts) {
					fill(i*length, size - 1);
				}
				else {
					next = leds[i*length];
					fill(i*length, (i + 1)*length - 1);
					color = next;
				}
			}
		}
		else {
			for (int i = 0; i <= parts; i++) {
				if (parts == i) {
					fill((size - 1) - (length*i), 0);
				}
				else {
					next = leds[(size - 1) - (length*i)];
					fill((size - 1) - (length*i), (size)-(length*(i + 1)));
					color = next;
				}
			}
		}
		FastLED.show();
	}
}

void Ledz::fill(int start, int end) {
	if (start > end) {
		int t = start;
		start = end;
		end = t;
	}
	if (start < 0) start = 0;
	if (end > size - 1) end = size - 1;
	for (int i = start; i < end + 1; i++) {
		leds[i] = color;
	}
}
void Ledz::moveLeft(int end, int start) {
	if (end < start) {
		int t = end;
		end = start;
		start = t;
	}
	if (start <= 0) start = 1;
	if (end >= size) end = size - 1;
	for (int i = end; i > start-1; i--) {
		leds[i] = leds[i - 1];
	}
}
void Ledz::moveRight(int end, int start) {
	if (end < start) {
		int t = end;
		end = start;
		start = t;
	}
	if (start < 0) start = 0;
	if (end >= size) end = size - 1;
	for (int i = start; i < end; i++) {
		leds[i] = leds[i + 1];
	}
}
//void moveLeftAndAddSynced(CRGB nextColor) {
//	for (int i = numLongLeds - 1; i > 0; i--) {
//		if (i > 11 && i < numLongLeds - 12) {
//			shortLeds[i - 12] = longLeds[i - 1];
//		}
//		longLeds[i] = longLeds[i - 1];
//	}
//	longLeds[0] = nextColor;
//	FastLED.show();
//}