#include "tgvoice.h"
#include "tgnote.h"


void TGVoice::addNote(TGNote* note){
	note->setVoice(this);
	this->notes.push_back(note);
	this->setEmpty(false);
}


void TGVoice::removeNote(TGNote* note)
{
	std::vector<TGNote*>::iterator f = notes.begin();
	for(; f != notes.end(); f++)
	{
		if(*f==note){
			this->notes.erase(f);
			break;
		}
	}

}

void TGVoice::moveNote(int index, TGNote* note){
	removeNote(note);
	notes.push_back(note);
	notes[notes.size()-1]=notes[index];
	notes[index]=note;
}
