#include <Arduino.h>
#include "LyraController.h"

#include "Lyra.h"
#include "PlayList.h"


LyraController::LyraController(){};
LyraController::LyraController(Lyra **lyraList, int count) {
	lyraList_ = lyraList;
	instrumentCount__ = count;
	instruments_ = new LyraEnvironment[count];
	for (int i = 0; i < count; i += 1) {
		LyraEnvironment instrument;
		instrument.lyra = lyraList[i];
		instrument.playList = new PlayList();
		instruments_[i] = instrument;
	}
}

void LyraController::nextTick() {
	this->run();
}

void LyraController::run() {
	for (int i = 0; i < this->instrumentCount__; i += 1) {
		Lyra *lyra = instruments_[i].lyra;
		lyra->run();
	}
}

void LyraController::press(byte channel, byte note, byte velocity){
	Lyra *lyra = instruments_[channel-1].lyra;
	PlayList *playList = instruments_[channel-1].playList;
	playList->press(note, velocity);
	lyra->play(note, velocity);
}

void LyraController::release(byte channel, byte aNote, byte aVelocity) {
	PlayList *playList = instruments_[channel-1].playList;
	playList->release(aNote);

	Note *nextNote = playList->getCurrentNote();

	Lyra *lyra = instruments_[channel-1].lyra;

	if (nextNote != NULL) {
		lyra->play(nextNote->note, nextNote->velocity);
	} else {
		lyra->release(aNote, aVelocity);
	}
}

void LyraController::setContinousController(byte chanel, byte controller, byte value) {
	Serial.print("LyraController::setContinousController: ");
	Serial.print(controller);Serial.print("/");Serial.println(value);
}

void LyraController::aftertouch(byte channel, byte range) {
	Lyra *lyra = instruments_[channel-1].lyra;
	lyra->vibrato(range);
}

void LyraController::pitch(byte channel, int range) {
	Lyra *lyra = instruments_[channel-1].lyra;
	int pitchRange = map(range,-8192, 8191, -127, 127);
	lyra->pitch(pitchRange);
}
