#ifndef TEMPS_H
#define TEMPS_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "tgstring.h"
#include "tgsong.h"
#include "tgsongmanager.h"

struct TempNote
{
public:	
	int track;
	int channel;
	int value;
	long tick;
	
	TempNote(int track, int channel, int value,long tick) {
		this->track = track;
		this->channel = channel;
		this->value = value;
		this->tick = tick;
	}
	
	int getChannel() {
		return this->channel;
	}
	
	long getTick() {
		return this->tick;
	}
	
	int getTrack() {
		return this->track;
	}
	
	int getValue() {
		return this->value;
	}
};

struct TempChannel
{
public:	
	int channel;
	int instrument;
	int volume;
	int balance;
	int track;
	
	TempChannel(int channel) {
		this->channel = channel;
		this->instrument = 0;
		this->volume = 127;
		this->balance = 64;
		this->track = -1;
	}
	
	int getBalance() {
		return this->balance;
	}
	
	void setBalance(int balance) {
		this->balance = balance;
	}
	
	int getChannel() {
		return this->channel;
	}
	
	int getInstrument();
	
	void setInstrument(int instrument) {
		this->instrument = instrument;
	}
	
	int getTrack() {
		return this->track;
	}
	
	void setTrack(int track) {
		this->track = track;
	}
	
	int getVolume() {
		return this->volume;
	}
	
	void setVolume(int volume) {
		this->volume = volume;
	}
};

class TrackTuningHelper{
	
public:	
	int track;
	int maxValue;
	int minValue;
	
	TrackTuningHelper(int track){
		this->track = track;
		this->maxValue = -1;
		this->minValue = -1;
	}
	
	void checkValue(int value){
		if(this->minValue < 0 || value < this->minValue){
			this->minValue = value;
		}
		if(this->maxValue < 0 || value > this->maxValue){
			this->maxValue = value;
		}
	}
	
	void getStrings(std::vector<TGString*>& strings) 
	{
	
		int maxFret = 24;
		
		if(this->minValue >= 40 && this->maxValue <= 64 + maxFret){
			strings.push_back(TGSongManager::newString(1, 64));
			strings.push_back(TGSongManager::newString(2, 59));
			strings.push_back(TGSongManager::newString(3, 55));
			strings.push_back(TGSongManager::newString(4, 50));
			strings.push_back(TGSongManager::newString(5, 45));
			strings.push_back(TGSongManager::newString(6, 40));
		}
		else if(this->minValue >= 38 && this->maxValue <= 64 + maxFret){
			strings.push_back(TGSongManager::newString(1, 64));
			strings.push_back(TGSongManager::newString(2, 59));
			strings.push_back(TGSongManager::newString(3, 55));
			strings.push_back(TGSongManager::newString(4, 50));
			strings.push_back(TGSongManager::newString(5, 45));
			strings.push_back(TGSongManager::newString(6, 38));
		}
		else if(this->minValue >= 35 && this->maxValue <= 64 + maxFret){
			strings.push_back(TGSongManager::newString(1, 64));
			strings.push_back(TGSongManager::newString(2, 59));
			strings.push_back(TGSongManager::newString(3, 55));
			strings.push_back(TGSongManager::newString(4, 50));
			strings.push_back(TGSongManager::newString(5, 45));
			strings.push_back(TGSongManager::newString(6, 40));
			strings.push_back(TGSongManager::newString(7, 35));
		}
		else if(this->minValue >= 28 && this->maxValue <= 43 + maxFret){
			strings.push_back(TGSongManager::newString(1, 43));
			strings.push_back(TGSongManager::newString(2, 38));
			strings.push_back(TGSongManager::newString(3, 33));
			strings.push_back(TGSongManager::newString(4, 28));
		}
		else if(this->minValue >= 23 && this->maxValue <= 43 + maxFret){
			strings.push_back(TGSongManager::newString(1, 43));
			strings.push_back(TGSongManager::newString(2, 38));
			strings.push_back(TGSongManager::newString(3, 33));
			strings.push_back(TGSongManager::newString(4, 28));
			strings.push_back(TGSongManager::newString(5, 23));
		}else{
			size_t stringCount = 6;
			int stringSpacing = ((this->maxValue - (maxFret - 4) - 
								  this->minValue) / stringCount);
			if(stringSpacing > 5){
				stringCount = 7;
				stringSpacing = ((this->maxValue - (maxFret - 4) - 
								  this->minValue) / stringCount);
			}
			
			int maxStringValue = (this->minValue + (stringCount * stringSpacing));
			while(strings.size() < stringCount){
				maxStringValue -= stringSpacing;
				strings.push_back(TGSongManager::newString(strings.size() +
														   1,maxStringValue));
			}
		}
	}
	
	int getTrack() {
		return this->track;
	}
	
};

#define ITER(c,e) std::find(c.begin(),c.end(),e)


#endif // TEMPS_H
