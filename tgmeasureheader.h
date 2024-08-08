#ifndef TGMEASUREHEADER_H
#define TGMEASUREHEADER_H

#include "tgmarker.h"
#include "tgtempo.h"
#include "tgtimesignature.h"


class TGSong;
class TGMeasureHeader 
{
public:	
	TGMeasureHeader(){
		this->number = 0;
		this->start = TGDuration::QUARTER_TIME;
		this->tripletFeel = TRIPLET_FEEL_NONE;
		this->repeatOpen = false;
		this->repeatClose = 0;
		this->repeatAlternative = 0;
		this->checkMarker();
		_maxWidth = 0;
	}
	
	int getNumber()const {
		return this->number;
	}
	
	void setNumber(int number) {
		this->number = number;
		this->checkMarker();
	}
	
	int getRepeatClose()const {
		return this->repeatClose;
	}
	
	void setRepeatClose(int repeatClose) {
		this->repeatClose = repeatClose;
	}
	
	int getRepeatAlternative()const {
		return this->repeatAlternative;
	}
	void setRepeatAlternative(int repeatAlternative) {
		this->repeatAlternative = repeatAlternative;
	}
	
	bool isRepeatOpen()const {
		return this->repeatOpen;
	}
	
	void setRepeatOpen(bool repeatOpen) {
		this->repeatOpen = repeatOpen;
	}
	
	long getStart()const {
		return this->start;
	}
	
	void setStart(long start) {
		this->start = start;
	}
	
	int getTripletFeel()const {
		return this->tripletFeel;
	}
	
	void setTripletFeel(int tripletFeel) {
		this->tripletFeel = tripletFeel;
	}
	
	TGTempo& getTempo(){
		return this->tempo;
	}
	
	void setTempo(TGTempo& tempo) {
		this->tempo = tempo;
	}
	
	TGTimeSignature& getTimeSignature(){
		return this->_timeSignature;
	}
	
	void setTimeSignature(TGTimeSignature& ts) {
		this->_timeSignature = ts;
	}
	
	const TGMarker& getMarker()const {
		return this->marker;
	}
	
	void setMarker(const TGMarker& marker) {
		this->marker = marker;
	}
	
	bool hasMarker()const{
		return marker.getMeasure()!=0;
	}
	
	void checkMarker(){
		if(hasMarker()){
			this->marker.setMeasure(getNumber());
		}
	}
	
	long getLength(){
		return getTimeSignature().getNumerator() *
				getTimeSignature()._denominator.getTime();
	}
	
	TGSong* getSong()const {
		return this->song;
	}
	
	void setSong(TGSong* song) {
		this->song = song;
	}
	
	TGMeasureHeader&  operator=( TGMeasureHeader& header){
		this->setNumber(header.getNumber());
		this->setStart(header.getStart());
		this->setRepeatOpen(header.isRepeatOpen());
		this->setRepeatAlternative(header.getRepeatAlternative());
		this->setRepeatClose(header.getRepeatClose());
		this->setTripletFeel(header.getTripletFeel());
		this->_timeSignature=header._timeSignature;
		tempo = header.tempo;
		this->setMarker(header.getMarker());
		this->checkMarker();
		return *this;
	}
	
	void reset() {
		this->_maxWidth = 0;
		this->_paintFlags = 0;
		this->_maxQuarterSpacing = 0;
		this->_maxClefSpacing = 0;
		this->_maxKeySignatureSpacing = 0;
	}
	
		
	float getMaxQuarterSpacing() {
		return this->_maxQuarterSpacing;
	}
	
	void notifyQuarterSpacing(float spacing) {
		this->_maxQuarterSpacing = ((spacing > this->_maxQuarterSpacing) ? 
										spacing : this->_maxQuarterSpacing );
	}
	
	void notifyClefSpacing(float spacing){
		this->_maxClefSpacing = ((spacing > this->_maxClefSpacing) ? 
									 spacing : this->_maxClefSpacing);
	}
	
	void notifyKeySignatureSpacing(float spacing){
		this->_maxKeySignatureSpacing = ((spacing > this->_maxKeySignatureSpacing) ? 
											spacing : this->_maxKeySignatureSpacing);
	}
	
	void notifyWidth(float width){
		this->_maxWidth = ((width > this->_maxWidth)?width:this->_maxWidth);
	}
	
	float getMaxWidth(){
		return this->_maxWidth;
	}



	int _paintFlags=0;
	
	float _maxQuarterSpacing=0;
	
	float _maxClefSpacing=0;
	
	float _maxKeySignatureSpacing=0;
	
	float _maxWidth=0;
	
	int number=0;
	long start=0;
	TGTimeSignature _timeSignature;
	TGTempo tempo;
	TGMarker marker;
	bool repeatOpen=false;
	int repeatAlternative=0;
	int repeatClose=0;
	int tripletFeel=0;
	TGSong* song = nullptr;
	
	constexpr static  int TRIPLET_FEEL_NONE = 1;
	constexpr static  int TRIPLET_FEEL_EIGHTH = 2;
	constexpr static  int TRIPLET_FEEL_SIXTEENTH = 3;
	constexpr static float DEFAULT_TEMPO_WIDTH = 45;
	constexpr static float DEFAULT_TRIPLET_FEEL_WIDTH = 55;
	constexpr static float DEFAULT_TIME_SIGNATURE_WIDTH = 10;
	constexpr static int PAINT_TEMPO = 0x01;
	constexpr static int PAINT_TRIPLET_FEEL = 0x02;
	constexpr static int PAINT_TIME_SIGNATURE = 0x04;
	
};


#endif // TGMEASUREHEADER_H
