/*
    BikeDisplay
    Copyright (C) 2018 Ben Schattinger

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "LEDController.h"

void LEDController::show() {
	effectFunction(leds, numLEDs, offset);
	leds->show();
}

void LEDController::setEffect(std::function<void(Adafruit_NeoPixel_ZeroDMA *, uint16_t, uint16_t)> effectFunctionIn) {
	effectFunction = effectFunctionIn;
}

void LEDController::allColor(Adafruit_NeoPixel_ZeroDMA *leds, uint16_t numLEDs, uint16_t offset, uint32_t color) {
	for (uint16_t i = offset; i < numLEDs + offset; i++) leds->setPixelColor(i, color);
}

void LEDController::off(Adafruit_NeoPixel_ZeroDMA *leds, uint16_t numLEDs, uint16_t offset) {
	allColor(leds, numLEDs, offset);
}

void LEDController::blinker(Adafruit_NeoPixel_ZeroDMA *leds, uint16_t numLEDs, uint16_t offset) {
	// Number of flashes (on and off) per minute
	const int desiredFrequency = 80;
	const uint32_t color = Adafruit_NeoPixel_ZeroDMA::Color(255, 255, 0);
	const int cycleTime = 1000 * 60 / desiredFrequency;
	if (millis() % cycleTime > cycleTime / 2) allColor(leds, numLEDs, offset, color);
	else allColor(leds, numLEDs, offset);
}

void LEDController::rainbow(Adafruit_NeoPixel_ZeroDMA *leds, uint16_t numLEDs, uint16_t offset) {
	static uint8_t startIndex = 0;
	static unsigned long lastTime = 0;
	startIndex += (millis() - lastTime) / 10;
	lastTime = millis();
	uint8_t colorIndex = startIndex++;
	for (uint16_t i = offset; i < numLEDs + offset; i++) {
		CRGB color = ColorFromPalette(RainbowColors_p, colorIndex, 255, LINEARBLEND);
		leds->setPixelColor(i, color.r, color.g, color.b);
		colorIndex += 3;
	}
}

void LEDController::solidWhite(Adafruit_NeoPixel_ZeroDMA *leds, uint16_t numLEDs, uint16_t offset) {
	allColor(leds, numLEDs, offset, Adafruit_NeoPixel_ZeroDMA::Color(255, 255, 255));
}
