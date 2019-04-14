#include "Arduino.h"
#include "Button.h"

Button::Button(int pin) {
	pinMode(pin, INPUT);
	_pin = pin;
	_prevState = LOW;
	_buffer = 250;
	_lastPress = millis();
}

bool Button::check() {
	int state = digitalRead(_pin);
	if (state == _prevState) {
		return false;
	}
	else {
		if (!state) {
			_prevState = LOW;
			return false;
		}
		else {
			unsigned long time = millis();
			if (time - _lastPress > _buffer) {
				_lastPress = time;
				_prevState = HIGH;
				return true;
			}
			return false;
		}
	}
}