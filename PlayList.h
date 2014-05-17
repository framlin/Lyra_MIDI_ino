#ifndef _PLAY_LIST_H_
#define _PLAY_LIST_H_

#include <Arduino.h>

struct Note {
	Note(byte value, byte velocity);
	byte note;
	byte velocity;
	Note *previous;
	Note *next;
};

class PlayList {
public:
	PlayList();
	void press(byte note, byte velocity);
	void release(byte note);
	Note *getCurrentNote();
	bool isEmpty();
private:
	Note *noteList_;

	Note *findNote(Note *noteList, byte note);
	void removeNote(byte note);
	void appendNote(byte note, byte velocity);

	void printNoteList(char *msg);
};

#endif //_PLAY_LIST_H_
