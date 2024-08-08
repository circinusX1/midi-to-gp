#ifndef TGBEAT_H
#define TGBEAT_H

#include "tgduration.h"
#include "tgmeasure.h"
#include "tgchord.h"
#include "tgtext.h"
#include "tgvoice.h"
#include "tgstroke.h"

class TGBeat {
public:
	constexpr static  int MAX_VOICES = 2;
	
	long		start = 0;
	TGMeasure*	measure = nullptr; 
	TGChord*	chord = nullptr;
	TGText*		text = nullptr;
	std::vector<TGVoice*>	voices;
	TGStroke	stroke;
	
	TGBeat() {
		
		this->start = TGDuration::QUARTER_TIME;
		for( int i = 0 ; i < MAX_VOICES ; i ++ ){
			TGVoice* pv = new TGVoice;
			pv->setBeat(this);
			voices.push_back(pv);
		}
	}
	
	TGMeasure* getMeasure() {
		return this->measure;
	}
	
	void setMeasure(TGMeasure* measure) {
		this->measure = measure;
	}
	
	long getStart() {
		return this->start;
	}
	
	void setStart(long start) {
		this->start = start;
	}
	
	void setVoice(int index, TGVoice* voice){
		if( index >= 0 && index < (int)this->voices.size() ){
			this->voices[index] = voice;
			this->voices[index]->setBeat( this );
		}
	}
	
	TGVoice* getVoice(int index){
		if( index >= 0 && index < (int)this->voices.size() ){
			return this->voices[index];
		}
		return nullptr;
	}
	
	int countVoices(){
		return this->voices.size();
	}
	
	void setChord(TGChord* chord) {
		this->chord = chord;
		this->chord->setBeat(this);
	}
	
	TGChord* getChord() {
		return this->chord;
	}
	
	void removeChord() {
		this->chord = nullptr;
	}
	
	TGText* getText() {
		return this->text;
	}
	
	void setText(TGText* text) {
		this->text = text;
		this->text->setBeat(this);
	}
	
	void removeText(){
		this->text = nullptr;
	}
	
	bool isChordBeat(){
		return ( this->chord != nullptr );
	}
	
	bool isTextBeat(){
		return ( this->text != nullptr );
	}
	
	TGStroke& getStroke() {
		return this->stroke;
	}
	
	bool isRestBeat(){
		for(int v = 0; v < this->countVoices() ; v ++ ){
			TGVoice* voice = this->getVoice( v );
			if( !voice->isEmpty() && !voice->isRestVoice() )
			{
				return false;
			}
		}
		return true;
	}
	
};

#endif // TGBEAT_H
