#ifndef TGVOICE_H
#define TGVOICE_H

#include <list>
#include "tgduration.h"
#include "temps.h"

class TGBeat;
class TGNote;
class TGVoice {
public:
	
	constexpr static  int DIRECTION_NONE = 0;
	constexpr static  int DIRECTION_UP = 1;
	constexpr static  int DIRECTION_DOWN = 2;
	
	TGBeat*				 beat=nullptr;
	TGDuration			 duration; 
	std::vector<TGNote*> notes;
	int					 index = 0;
	int					 direction;
	bool				 empty = true;
	
	TGVoice(int index=0) {
		this->index = index;
		this->empty = true;
		this->direction = DIRECTION_NONE;
	}
	
	int getIndex() {
		return this->index;
	}
	
	void setIndex(int index) {
		this->index = index;
	}
	
	bool isEmpty() {
		return this->empty;
	}
	
	void setEmpty(bool empty) {
		this->empty = empty;
	}
	
	int getDirection() {
		return this->direction;
	}
	
	void setDirection(int direction) {
		this->direction = direction;
	}
	
	TGDuration& getDuration() {
		return this->duration;
	}
	
	void setDuration(TGDuration& duration) {
		this->duration = duration;
	}
	
	TGBeat* getBeat() {
		return this->beat;
	}
	
	void setBeat(TGBeat* beat) {
		this->beat = beat;
	}
	
	std::vector<TGNote*>& getNotes() {
		return this->notes;
	}
	
	void addNote(TGNote* note);
	
	void moveNote(int index, TGNote* note);
	
	void removeNote(TGNote* note);
	
	TGNote* getNote(int index){
		if(index >= 0 && index < countNotes()){
			return this->notes.at(index);
		}
		return nullptr;
	}
	
	int countNotes(){
		return this->notes.size();
	}
	
	bool isRestVoice(){
		return this->notes.empty();
	}

};

#endif // TGVOICE_H
