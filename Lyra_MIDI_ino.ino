#include <Arduino.h>
#include <MIDI.h>
#include <AccelStepper.h>

#include "MidiController.h"
#include "LyraController.h"
#include "Lyra.h"

//we have a MidiController, that controls a LyraController, that controlls someLyras
LyraController *lyraController;
MidiController *midiController;
Lyra *lyra_1;

void minIRQ_1() {
	Serial.println("minIRQ_1");
	lyra_1->minIRQ();
}

void maxIRQ_1() {
	Serial.println("maxIRQ_1");
	lyra_1->maxIRQ();
}

Lyra *createLyra_1(int *positions) {
	Lyra *result = NULL;

	positions[24] = 0;
	positions[25] = 100;
	positions[26] = 290;
	positions[27] = 430;
	positions[28] = 574;
	positions[29] = 702;
	positions[30] = 805;
	positions[31] = 941;
	positions[32] = 1043;
	positions[33] = 1145;
	positions[34] = 1230;
	positions[35] = 1320;
	positions[36] = 1410;
	positions[37] = 1490;
	positions[38] = 1564;
	positions[39] = 1632;
	positions[40] = 1696;
	positions[41] = 1760;
	positions[42] = 1804;
	positions[43] = 1849;

	//============  LYRA - 1 (big) ============================================
	//----- Wheel
	////const static int speedPin3 = 6;
	////const static int motor1CPin = 5;
	////const static int motor2CPin = 4;

	//----- Tuner
	////	pinMode(50, OUTPUT);    // EN3
	////	pinMode(51, OUTPUT);    // MS1
	////	pinMode(52, OUTPUT);    // MS2
	////	pinMode(53, OUTPUT);    // MS2

	//----- Calibration
	////const static int E = 19;
	////const static int F = 18;

	//----- UI
	////const static int ledPin = 13;
	////const static int potpin3 = 3;

	LyraConfiguration lc_1 = {
		24, 				//	int firstNote;
		43, 				//	int lastNote;
		positions, 		//	int *notePositions;
		0,					// int minPosition;
		1851,				// int maxPosition;
		{7, 6, 5},			//	WheelPinout wheelPinout;
		{33, 31, 29, 27, 25, 23},	//	TunerPinout tunerPinout;
		{19, 18},			//	CalibrationPinout calibrationPinout;
		{13, 3},			//	UIPinout uiPinout;
		&minIRQ_1,
		&maxIRQ_1
	};
	//=========================================================================

	result = new Lyra(lc_1);
	return result;
}

void setup() {

	while (!Serial);
	Serial.begin(115200);
	Serial.println("setup");

	//creating and initializing the Lyras
	int positions_l1[Lyra::NOTE_COUNT];
	lyra_1 = createLyra_1(positions_l1);

	Lyra *lyraList[] = {lyra_1};

	lyraController = new LyraController(lyraList, 1);

	MidiController::setLyraController(lyraController);
	MidiController::initMIDI();
}


void loop() {
	MidiController::nextTick();
	lyraController->nextTick();
}


