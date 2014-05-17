#include <Arduino.h>

#include <MIDI.h>

#include "MidiController.h"
#include "LyraController.h"

//struct mev{
//	bool on;
//	byte note;
//	byte velocity;
//};
//
//int ticks__ = 0;
//int step__ = 0;
//const dur__ = 10000;
//mev symphonie[] = {
//	{true, 2, 3},
//	{true, 3, 3},
//	{true, 4, 3},
//	{true, 5, 3},
//	{false, 5, 3},
//	{false, 4, 3},
//	{false, 3, 3},
//	{false, 2, 3}
//};

LyraController *MidiController::lyraController = new LyraController();

void MidiController::setLyraController(LyraController *controller) {
	MidiController::lyraController = controller;
}

void MidiController::initMIDI() {
	MIDI.begin(MIDI_CHANNEL_OMNI);

	MIDI.setHandleNoteOff(MidiController::handleNoteOff);
	MIDI.setHandleNoteOn(MidiController::handleNoteOn);
	MIDI.setHandleAfterTouchPoly(MidiController::handleAfterTouchPoly);
	MIDI.setHandleControlChange(MidiController::handleControlChange);
	MIDI.setHandleProgramChange(MidiController::handleProgramChange);
	MIDI.setHandleAfterTouchChannel(MidiController::handleAfterTouchChannel);
	MIDI.setHandlePitchBend(MidiController::handlePitchBend);
}

void MidiController::nextTick() {
	MIDI.read();
}

void MidiController::handleNoteOff(byte val1, byte val2, byte val3) {
	lyraController->release(val1, val2, val3);
}

void MidiController::handleNoteOn(byte val1, byte val2, byte val3) {
	lyraController->press(val1, val2, val3);
}

void MidiController::handleAfterTouchPoly(byte val1, byte val2, byte val3) {
	Serial.print("AfterTouchPoly: ");
	MidiController::logMidi_3(val1, val2, val3);
}

void MidiController::handleControlChange(byte chanel, byte controller, byte value) {
	lyraController->setContinousController(chanel, controller, value);
}

void MidiController::handleProgramChange(byte val1, byte val2) {
	Serial.print("ProgramChange: ");
	MidiController::logMidi_2(val1, val2);
}

void MidiController::handleAfterTouchChannel(byte val1, byte val2) {
	lyraController->aftertouch(val1, val2);
}

void MidiController::handlePitchBend(byte val1, int val2) {
	Serial.print("PitchBend: ");
	MidiController::logMidi_1(val1, val2);
	lyraController->pitch(val1, val2);
}

void MidiController::logMidi_1(byte val1, int val2) {
	Serial.print(val1); Serial.print(":");Serial.println(val2);
}

void MidiController::logMidi_2(byte val1, byte val2) {
	Serial.print(val1); Serial.print(":");Serial.println(val2);
}

void MidiController::logMidi_3(byte val1, byte val2, byte val3) {
	Serial.print(val1); Serial.print(":");Serial.print(val2);Serial.print(":");Serial.println(val3);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*
 *
bool shouldSwitchOff() {
	return velocitySum() == 0;
}

void switchOff() {
	digitalWrite(ledPin, LOW);
	digitalWrite(motor2CPin, LOW);
}

int velocitySum() {
	int sum = 0;
	for (int i = C_FIRST_PITCH; i <= C_LAST_PITCH; i += 1) {
		sum += gVelocities[i];
	}

	return sum;
}

void HandleNoteOn (byte channel, byte pitch, byte velocity) {
	Serial.print(pitch); Serial.print(":");Serial.println(velocity);
	gVelocities[pitch] = velocity;

	if (velocity > 0) {
		int newPosition = getNotePosition(pitch);
		//replace this with some kind of
		//moveTo(newPosition);
		//run();
		//- concept, to achieve a non-blocking behaviour
		//to enable to control more than one stepper at once
		//see:
		//http://forum.arduino.cc/index.php?topic=96654.msg725449#msg725449
		stepper3.runToNewPosition(newPosition);
	}


	if (velocity > 3) {
		if (pitch >= C_FIRST_PITCH && pitch <= C_LAST_PITCH) {
			turnWheel(velocity);
		}
	}


	if (shouldSwitchOff()) {
		switchOff();
	}

}

void HandleAfterTouchPoly (byte channel, byte note, byte pressure) {
	int velocity = gVelocities[note] + pressure;
	turnWheel(velocity);
}

void HandleControlChange (byte channel, byte number, byte value) {
	if (number == 7) {

		if (value <= 10) {
			stepper3.setMaxSpeed(300);
			stepper3.setAcceleration(1000);
			delay(300);
		}

		if (value > 10 && value <= 117)	{
			stepper3.setMaxSpeed(1000);
			stepper3.setAcceleration(4000);
			delay(300);
		}

		if (value > 117) {
			stepper3.setMaxSpeed(4000);
			stepper3.setAcceleration(80000);
			delay(300);
		}
	}
}
*/
