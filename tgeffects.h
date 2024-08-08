#ifndef TGEFFECTS_H
#define TGEFFECTS_H

#include <string>
#include <vector>
#include "tgduration.h"




struct TGVelocities {
	
	constexpr static  int MIN_VELOCITY = 15;
	constexpr static  int VELOCITY_INCREMENT = 16;
	constexpr static  int PIANO_PIANISSIMO = (MIN_VELOCITY);
	constexpr static  int PIANISSIMO = (MIN_VELOCITY + VELOCITY_INCREMENT);
	constexpr static  int PIANO = (MIN_VELOCITY + (VELOCITY_INCREMENT * 2));
	constexpr static  int MEZZO_PIANO = (MIN_VELOCITY + (VELOCITY_INCREMENT * 3));
	constexpr static  int MEZZO_FORTE = (MIN_VELOCITY + (VELOCITY_INCREMENT * 4));
	constexpr static  int FORTE = (MIN_VELOCITY + (VELOCITY_INCREMENT * 5));
	constexpr static  int FORTISSIMO = (MIN_VELOCITY + (VELOCITY_INCREMENT * 6));
	constexpr static  int FORTE_FORTISSIMO = (MIN_VELOCITY + (VELOCITY_INCREMENT * 7));
	constexpr static  int DEFAULT = FORTE;
	
};

struct BendPoint{
	
	int position;
	int value;
	
	BendPoint(int position,int value){
		this->position = position;
		this->value = value;
	}
	
	int getPosition() {
		return this->position;
	}
	
	int getValue() {
		return this->value;
	}
	
	long getTime(long duration){
		return (duration * getPosition() / MAX_POSITION_LENGTH);
	}
};


struct TremoloBarPoint{
	int position;
	int value;
	TremoloBarPoint(int position,int value){
		this->position = position;
		this->value = value;
	}
	
	int getPosition() {
		return this->position;
	}
	
	int getValue() {
		return this->value;
	}
	
	long getTime(long duration){
		return (duration * getPosition() / MAX_POSITION_LENGTH);
	}
};

struct TGEffectBend {
	
	constexpr static  int SEMITONE_LENGTH = 1;
	constexpr static  int MAX_VALUE_LENGTH = (SEMITONE_LENGTH * 12);
	
	std::vector<BendPoint> points;
	
	TGEffectBend(){
	}
	
	void addPoint(int position,int value){
		this->points.push_back(BendPoint(position,value));
	}
	
	std::vector<BendPoint>& getPoints(){
		return this->points;
	}
	
};


struct TGEffectGrace {
	
	constexpr static  int TRANSITION_NONE = 0;
	constexpr static  int TRANSITION_SLIDE = 1;
	constexpr static  int TRANSITION_BEND = 2;
	constexpr static  int TRANSITION_HAMMER = 3;
	
	int fret;
	int duration;
	int dynamic;
	int transition;
	bool onBeat;
	bool dead;
	
	TGEffectGrace() {
		this->fret = 0;
		this->duration = 1;
		this->dynamic = TGVelocities::DEFAULT;
		this->transition = TRANSITION_NONE;
		this->onBeat = false;
		this->dead = false;
	}
	
	bool isDead() {
		return this->dead;
	}
	
	void setDead(bool dead) {
		this->dead = dead;
	}
	
	int getDuration() {
		return this->duration;
	}
	
	void setDuration(int duration) {
		this->duration = duration;
	}
	
	int getDynamic() {
		return this->dynamic;
	}
	
	void setDynamic(int dynamic) {
		this->dynamic = dynamic;
	}
	
	int getFret() {
		return this->fret;
	}
	
	void setFret(int fret) {
		this->fret = fret;
	}
	
	bool isOnBeat() {
		return this->onBeat;
	}
	
	void setOnBeat(bool onBeat) {
		this->onBeat = onBeat;
	}
	
	int getTransition() {
		return this->transition;
	}
	
	void setTransition(int transition) {
		this->transition = transition;
	}
	
	int getDurationTime(){
		//return (int)(((float)TGDuration.QUARTER_TIME / 16.00 ) * (float)getDuration());
		return (int)((TGDuration::QUARTER_TIME / 16.00 ) * getDuration());
	}
};


struct TGEffectHarmonic {
	const static  std::string KEY_NATURAL;// = "N.H";
	const static  std::string KEY_ARTIFICIAL;// = "A.H";
	const static  std::string KEY_TAPPED; //= "T.H";
	const static  std::string KEY_PINCH;// = "P.H";
	const static  std::string KEY_SEMI;// = "S.H";
	constexpr static  int TYPE_NATURAL = 1;
	constexpr static  int TYPE_ARTIFICIAL = 2;
	constexpr static  int TYPE_TAPPED = 3;
	constexpr static  int TYPE_PINCH = 4;
	constexpr static  int TYPE_SEMI = 5;
	constexpr static  int MIN_ARTIFICIAL_OFFSET = -24;
	constexpr static  int MAX_ARTIFICIAL_OFFSET = 24;
	constexpr static  int MAX_TAPPED_OFFSET = 24;
	constexpr static  int NATURAL_FREQUENCIES[6][2] = {
		{12, 12}, //AH12 (+12 frets)
		{9 , 28}, //AH9 (+28 frets)
		{5 , 24}, //AH5 (+24 frets)
		{7 , 19}, //AH7 (+19 frets)
		{4 , 28}, //AH4 (+28 frets)
		{3 , 31}  //AH3 (+31 frets)
	};
	
	int type;
	int data;
	
	TGEffectHarmonic(){
		this->type = 0;
		this->data = 0;
	}
	
	int getData() {
		return this->data;
	}
	
	void setData(int data) {
		this->data = data;
	}
	
	int _getType() {
		return this->type;
	}
	
	void setType(int type) {
		this->type = type;
	}
	
	bool isNatural(){
		return (this->type == TYPE_NATURAL);
	}
	
	bool isArtificial(){
		return (this->type == TYPE_ARTIFICIAL);
	}
	
	bool isTapped(){
		return (this->type == TYPE_TAPPED);
	}
	
	bool isPinch(){
		return (this->type == TYPE_PINCH);
	}
	
	bool isSemi(){
		return (this->type == TYPE_SEMI);
	}
};

struct TGEffectTremoloBar {
	constexpr static  int MAX_VALUE_LENGTH = 12;
	
	std::vector<TremoloBarPoint> points;
	
	TGEffectTremoloBar(){
	}
	
	void addPoint(int position,int value){
		this->points.push_back(TremoloBarPoint(position,value));
	}
	
	std::vector<TremoloBarPoint>& getPoints(){
		return this->points;
	}
	
};

struct TGEffectTremoloPicking {
	
	TGDuration duration;
	
	TGEffectTremoloPicking() {
	}
	
	TGDuration& getDuration() {
		return this->duration;
	}
	
	void setDuration(TGDuration& duration) {
		this->duration = duration;
	}
};

struct TGEffectTrill {
	
	int fret;
	TGDuration duration;
	
	TGEffectTrill() {
		this->fret = 0;
	}
	
	int getFret() {
		return this->fret;
	}
	
	void setFret(int fret) {
		this->fret = fret;
	}
	
	TGDuration& getDuration() {
		return this->duration;
	}
	
	void setDuration(TGDuration& duration) {
		this->duration = duration;
	}
	
};


#endif // TGEFFECTS_H



