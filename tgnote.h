#ifndef TGNOTE_H
#define TGNOTE_H

#include "tgeffects.h"
#include "tgnoteeffect.h"
#include "tgvoice.h"

class TGNote {
public:	
	int value;
	int velocity;
	int string;
	bool tiedNote;
	TGNoteEffect* effect=nullptr;
	TGVoice*      voice=nullptr;
	
	TGNote() {
		this->value = 0;
		this->velocity = TGVelocities::DEFAULT;
		this->string = 1;
		this->tiedNote = false;
		effect = new TGNoteEffect;
	}
	
	~TGNote(){
		
	}
	
	int getValue() {
		return this->value;
	}
	
	void setValue(int value) {
		this->value = value;
	}
	
	int getVelocity() {
		return this->velocity;
	}
	
	void setVelocity(int velocity) {
		this->velocity = velocity;
	}
	
	int getString() {
		return this->string;
	}
	
	void setString(int string) {
		this->string = string;
	}
	
	bool isTiedNote() {
		return this->tiedNote;
	}
	
	void setTiedNote(bool tiedNote) {
		this->tiedNote = tiedNote;
	}
	
	TGNoteEffect* getEffect() {
			return this->effect;
	}
	
	void setEffect(TGNoteEffect* peffect) {
		delete effect;
		this->effect = peffect;
	}
	
	TGVoice* getVoice() {
		return this->voice;
	}
	
	void setVoice(TGVoice* voice) {
		this->voice = voice;
	}

};

#endif // TGNOTE_H
