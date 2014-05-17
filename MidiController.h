#ifndef _MIDI_CONTROLLER_H_
#define _MIDI_CONTROLLER_H_

#include <Arduino.h>
#include <MIDI.h>

#include "LyraController.h"

class MidiController {
public:
	MidiController();

	static LyraController *lyraController;

	static void initMIDI();
	static void setLyraController(LyraController *controller);

	static void nextTick();

	static void handleNoteOff(byte val1, byte val2, byte val3);
	static void handleNoteOn(byte val1, byte val2, byte val3);
	static void handleAfterTouchPoly(byte val1, byte val2, byte val3);
	static void handleControlChange(byte val1, byte val2, byte val3);

	static void handleProgramChange(byte val1, byte val2);
	static void handleAfterTouchChannel(byte val1, byte val2);

	static void handlePitchBend(byte val1, int val2);
	//-----------------------------------------------------------


private:
	static void logMidi_1(byte val1, int val2);
	static void logMidi_2(byte val1, byte val2);
	static void logMidi_3(byte val1, byte val2, byte val3);


};

#endif //_MIDI_CONTROLLER_H_


/* ============================================
//MIDI.setHandleSystemExclusive(
//MIDI.setHandleTimeCodeQuarterFrame(
//MIDI.setHandleSongPosition(
//MIDI.setHandleSongSelect(
//MIDI.setHandleTuneRequest(
//MIDI.setHandleClock(
//MIDI.setHandleStart(
//MIDI.setHandleContinue(
//MIDI.setHandleStop(
//MIDI.setHandleActiveSensing(
//MIDI.setHandleSystemReset(
===============================================
 */
