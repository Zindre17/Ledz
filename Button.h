#ifndef Button_h
#define Button_h

#include "Arduino.h"

class Button {
	public:
		Button(int pin);
		bool check();
	private:
		int _pin;
		int _prevState;
		unsigned long _buffer;
		unsigned long _lastPress;
};
#endif