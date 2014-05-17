#include <Arduino.h>
#include "Lyra.h"

Lyra::Lyra(LyraConfiguration config) {
	this->initPositions(config);
	this->initUI(config);
	this->initTuner(config);
	this->initWheel(config);

	this->currentNote_ = 0;
}

void Lyra::tracePositions__() {
	for (int p = this->firstNote_; p <= this->lastNote_; p += 1) {
		Serial.print("note@: ");Serial.print(p);Serial.print(" :=> ");Serial.println(this->notePositions_[p]);
	}
	Serial.print("firstNote: ");Serial.println(this->firstNote_);
	Serial.print("lastNote: ");Serial.println(this->lastNote_);
}

void Lyra::initPositions(LyraConfiguration config) {
	this->firstNote_ = config.firstNote;
	this->lastNote_ = config.lastNote;
	notePositions_ = config.notePositions;

	this->tracePositions__();

	//fill up the rest of the array with the last position
	for (int i = this->lastNote_ + 1; i < Lyra::NOTE_COUNT; i += 1) {
		this->notePositions_[i] = this->notePositions_[this->lastNote_];
	}
}

void Lyra::initUI(LyraConfiguration config) {
	this->uiPinout_ = config.uiPinout;
	pinMode(this->uiPinout_.led, OUTPUT);
}

void Lyra::initTuner(LyraConfiguration config) {
	this->tunerPinout_ = config.tunerPinout;

	pinMode(this->tunerPinout_.EN,   OUTPUT);
	pinMode(this->tunerPinout_.MS_1, OUTPUT);
	pinMode(this->tunerPinout_.MS_2, OUTPUT);
	pinMode(this->tunerPinout_.MS_3, OUTPUT);

	digitalWrite(this->tunerPinout_.MS_1, HIGH);
	digitalWrite(this->tunerPinout_.MS_2, LOW);
	digitalWrite(this->tunerPinout_.MS_3, LOW);

	this->calibrationPinout_ = config.calibrationPinout;
	pinMode(this->calibrationPinout_.min, INPUT);
	attachInterrupt(4, config.minIRQ, RISING);

	pinMode(this->calibrationPinout_.max, INPUT);
	attachInterrupt(5, config.maxIRQ, RISING);

	tuner_ = new AccelStepper(1, this->tunerPinout_.Step, this->tunerPinout_.Direction);

	tuner_->setMaxSpeed(1000);
	tuner_->setAcceleration(10000);

	delay(400);

	this->minPosition_ = config.minPosition;
	this->maxPosition_ = config.maxPosition;

	tuner_->runToNewPosition(this->maxPosition_ + 4);

	tuner_->setMaxSpeed(4000);
	tuner_->setAcceleration(60000);
}

void Lyra::initWheel(LyraConfiguration config) {

	this->wheelPinout_ = config.wheelPinout;
	pinMode(this->wheelPinout_.speed, OUTPUT);
	pinMode(this->wheelPinout_.direction_1, OUTPUT);
	pinMode(this->wheelPinout_.direction_2, OUTPUT);
}

void Lyra::turnWheel(byte speed, WheelDirection direction) {
	digitalWrite(this->uiPinout_.led, HIGH);
	digitalWrite(this->wheelPinout_.direction_1, LOW);
	digitalWrite(this->wheelPinout_.direction_2, HIGH);

	analogWrite(this->wheelPinout_.speed, speed);
}

void Lyra::stopWheel(int speed) {
	digitalWrite(this->uiPinout_.led, LOW);

	digitalWrite(this->wheelPinout_.direction_1, LOW);
	digitalWrite(this->wheelPinout_.direction_2, HIGH);

	analogWrite(this->wheelPinout_.speed, 0);
}

void Lyra::minIRQ() {
	this->tuner_->setCurrentPosition(this->getMinPosition());
	this->tuner_->moveTo(this->getMaxPosition());
}

void Lyra::maxIRQ() {
	this->tuner_->setCurrentPosition(this->getMaxPosition());
	this->tuner_->moveTo(this->getMinPosition());
}

int Lyra::getNotePosition(int note) {
	return this->notePositions_[note];
}

int Lyra::getMinPosition() {
	return this->minPosition_;
}

int Lyra::getMaxPosition() {
	return this->maxPosition_;
}

void Lyra::play(byte note, byte velocity) {
	WheelDirection dir = left;
	this->selectNote(note);
	this->turnWheel(velocity, dir);
}

void Lyra::release(byte note, byte velocity) {
	this->stopWheel(velocity);
}

void Lyra::vibrato(byte range) {
	int currPosition = this->getNotePosition(this->currentNote_ );
	this->tuner_->moveTo(currPosition + range);
}

void Lyra::pitch(int range) {
	int currPosition = this->getNotePosition(this->currentNote_ );
	this->tuner_->moveTo(currPosition + range);
}

void Lyra::selectNote(byte note){
	this->currentNote_ = note;
	int pos = this->getNotePosition(note);
	this->tuner_->moveTo(pos);
}

void Lyra::run() {
	this->tuner_->run();
}
