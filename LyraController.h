#ifndef _LYRA_CONTROLLER_H_
#define _LYRA_CONTROLLER_H_

#include <Arduino.h>

#include "Lyra.h"
#include "PlayList.h"


struct LyraEnvironment {
	Lyra *lyra;
	PlayList *playList;
};


class LyraController {
public:
	LyraController();
	LyraController(Lyra **lyraList, int count);

	void nextTick();
	void run();

	void press(byte chanel, byte note, byte velocity);
	void release(byte chanel, byte note, byte velocity);
	void aftertouch(byte chanel, byte velocity);
	void pitch(byte chanel, int velocity);
	void setContinousController(byte chanel, byte controller, byte value);

private:
	Lyra **lyraList_;
	LyraEnvironment *instruments_;
	int instrumentCount__;
};

#endif //_LYRA_CONTROLLER_H_
