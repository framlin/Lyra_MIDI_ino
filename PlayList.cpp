#include "PlayList.h"


Note::Note(byte aNote, byte aVelocity) {
	note = aNote;
	velocity = aVelocity;
	previous = NULL;
	next = NULL;
}



PlayList::PlayList() {
	this->noteList_ = NULL;
}

void PlayList::press(byte note, byte velocity) {
	this->appendNote(note, velocity);
}

void PlayList::release(byte note) {
	this->removeNote(note);
}

Note *PlayList::getCurrentNote() {
	return this->noteList_;
}

bool PlayList::isEmpty() {
	return (this->noteList_ == NULL);
}

Note *PlayList::findNote(Note *noteList, byte note) {
	if (noteList->note == note) {
		return noteList;
	} else {
		if (noteList->previous != NULL) {
			return this->findNote(noteList->previous, note);
		} else {
			return NULL;
		}
	}
}

void PlayList::removeNote(byte note) {
	if (!this->isEmpty()) {
		Note *toRemove = this->findNote(this->noteList_, note);
		if (toRemove != NULL) {
			Note *previous = toRemove->previous;
			Note *next = toRemove->next;
			if (previous != NULL) {
				previous->next = next;
			}
			if (next != NULL) {
				next->previous = previous;
			} else {
				this->noteList_ = previous;
			}
			delete toRemove;
		}
	}

}

void PlayList::appendNote(byte note, byte velocity) {
	Note *newNote = new Note(note, velocity);

	if (!this->isEmpty()) {
		newNote->previous = this->noteList_;
		this->noteList_->next = newNote;
	}

	this->noteList_ = newNote;

}



void PlayList::printNoteList(char *msg) {
	if (!this->isEmpty()) {
		Note *previous = this->getCurrentNote();
		while(previous != NULL) {
			previous = previous->previous;
		}
	} else {
		Serial.println("PlayList::printNoteList -- EMPTY NoteList");
	}

}

