#ifndef _LYRA_H_
#define _LYRA_H_

#include <Arduino.h>
#include <AccelStepper.h>

enum WheelDirection {left, right};

struct WheelPinout {
	int speed; //PWM
	int direction_1;
	int direction_2;
};

struct TunerPinout{
	int EN;
	int MS_1;
	int MS_2;
	int MS_3;
	int Step;
	int Direction;
};

struct CalibrationPinout {
	int min;
	int max;
};

struct UIPinout {
	int led;
	int poti;
};

enum LyraFeature {
	Break,
	Lift,
	Speed,
	Acceleration,
	Tune
};

struct LyraConfiguration {
	int firstNote;
	int lastNote;
	int *notePositions;

	int minPosition;
	int maxPosition;

	WheelPinout wheelPinout;
	TunerPinout tunerPinout;
	CalibrationPinout calibrationPinout;
	UIPinout uiPinout;

	//LyraFeature *featureList;

	void (* minIRQ)();
	void (* maxIRQ)();

};

class Lyra {
public:
	Lyra(LyraConfiguration config);

	void play(byte note, byte velocity);
	void release(byte note, byte velocity);

	void vibrato(byte range);
	void pitch(int range);

	bool hasFeature(LyraFeature feature);

	int calibrate();

	void run();
	void minIRQ();
	void maxIRQ();

	static const int NOTE_COUNT = 128;


private:
	int firstNote_;
	int lastNote_;
	int *notePositions_;
	int minPosition_;
	int maxPosition_;

	WheelPinout wheelPinout_;
	TunerPinout tunerPinout_;
	CalibrationPinout calibrationPinout_;
	UIPinout uiPinout_;

	void initPositions(LyraConfiguration config);
	void initUI(LyraConfiguration config);

	void initWheel(LyraConfiguration config);
	void initTuner(LyraConfiguration config);

	void turnWheel(byte speed, WheelDirection direction);
	void stopWheel(int speed);

	int getNotePosition(int note);
	int getLowestNote();
	int getHighestNote();

	int getMinPosition();
	int getMaxPosition();


	void bendWheel(int angle);

	void selectNote(byte note);

	void tracePositions__();

	LyraFeature *featureList_;

	AccelStepper *tuner_;

	byte currentNote_;

};

//const static int val4;           //für FETs

#endif //_LYRA_H_

