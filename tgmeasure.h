#ifndef TGMEASURE_H
#define TGMEASURE_H

#include <vector>
#include "tgtrack.h"
#include "tgmeasureheader.h"

class TGBeat;
class TGMeasure {
public:
	
	constexpr static  int CLEF_TREBLE = 1;
	constexpr static  int CLEF_BASS = 2;
	constexpr static  int CLEF_TENOR = 3;
	constexpr static  int CLEF_ALTO = 4;
	
	constexpr static  int DEFAULT_CLEF = CLEF_TREBLE;
	constexpr static  int DEFAULT_KEY_SIGNATURE= 0;
	
	TGMeasureHeader* header;
	TGTrack*		track;
	int				clef;
	int				keySignature;
	
	std::vector<TGBeat*> beats; 
	
	TGMeasure(TGMeasureHeader* header){
		this->header = header;
		this->clef = DEFAULT_CLEF;
		this->keySignature = DEFAULT_KEY_SIGNATURE;
	}
	
	TGTrack* getTrack() {
		return this->track;
	}
	
	void setTrack(TGTrack* track) {
		this->track = track;
	}
	
	int getClef() {
		return this->clef;
	}
	
	void setClef(int clef) {
		this->clef = clef;
	}
	
	int getKeySignature() {
		return this->keySignature;
	}
	
	void setKeySignature(int keySignature) {
		this->keySignature = keySignature;
	}
	
	std::vector<TGBeat*> getBeats() {
		return this->beats;
	}
	
	void addBeat(TGBeat* beat);
	
	void moveBeat(int index,TGBeat* beat);
	
	void removeBeat(TGBeat* beat);
	
	TGBeat* getBeat(int index){
		if(index >= 0 && index < countBeats()){
			return this->beats.at(index);
		}
		return nullptr;
	}
	
	int countBeats(){
		return this->beats.size();
	}
	
	TGMeasureHeader* getHeader() {
		return this->header;
	}
	
	void setHeader(TGMeasureHeader* header) {
		this->header = header;
	}
	
	int getNumber() {
		return this->header->number;
	}
	
	int getRepeatClose() {
		return this->header->getRepeatClose();
	}
	
	long getStart() {
		return this->header->getStart();
	}
	
	TGTempo& getTempo() {
		return this->header->getTempo();
	}
	
	TGTimeSignature getTimeSignature()const {
		return this->header->getTimeSignature();
	}
	
	bool isRepeatOpen() {
		return this->header->isRepeatOpen();
	}
	
	int getTripletFeel() {
		return this->header->getTripletFeel();
	}
	
	long getLength() {
		return this->header->getLength();
	}
	
	const TGMarker& getMarker()const {
		return this->header->getMarker();
	}
	
	bool hasMarker() {
		return this->header->hasMarker();
	}
	
	void clear();

};

#endif // TGMEASURE_H
