#ifndef TGTRACK_H
#define TGTRACK_H

#include <iostream>
#include <string>
#include <vector>
#include "tgmarker.h"

extern int TracksVolume;


class TGMeasure;
class TGString;
class TGColor;
class TGLyric;
class TGSong;
class TGTrack {
public:
	constexpr static  int MAX_STRINGS = 25;
	constexpr static  int MIN_STRINGS = 1;
	constexpr static  int MAX_OFFSET = 24;
	constexpr static  int MIN_OFFSET = -24;
	
	int						number=0;
	int						offset=0;
	int						channelId=1;
	bool					solo=false;
	bool					mute=false;
	std::string				name;
	std::vector<TGMeasure*> measures;
	std::vector<TGString*>	strings;
	TGColor 				color = TGColor::RED;
	TGLyric*				lyrics=nullptr;
	TGSong*					song=nullptr;
	
	TGTrack() {
		this->number = 0;
		this->offset = 0;
		this->channelId = -1;
		this->solo = false;
		this->mute = false;
	}
	
	int getNumber() {
		return this->number;
	}
	
	void setNumber(int number) {
		this->number = number;
	}
	
	void addMeasure(TGMeasure* measure);
	void addMeasure(int index,TGMeasure* measure);
	
	TGMeasure* getMeasure(int index){
		if(index >= 0 && index < countMeasures()){
			return this->measures.at(index);
		}
		return nullptr;
	}
	
	void removeMeasure(int index);
	
	int countMeasures(){
		return this->measures.size();
	}
	
	std::vector<TGString*>& getStrings() {
		return this->strings;
	}
	
	void setStrings(std::vector<TGString*>& strings) {
		this->strings = strings;
	}
	
	TGColor& getColor() {
		return this->color;
	}
	
	void setColor(TGColor& color) {
		this->color = color;
	}
	
	std::string& getName() {
		return this->name;
	}
	
	void setName(std::string& name) {
		this->name = name;
	}
	
	int getOffset() {
		return this->offset;
	}
	
	void setOffset(int offset) {
		this->offset = offset;
	}
	
	bool isSolo() {
		return this->solo;
	}
	
	void setSolo(bool solo) {
		this->solo = solo;
	}
	
	bool isMute() {
		return this->mute;
	}
	
	void setMute(bool mute) {
		this->mute = mute;
	}
	
	int getChannelId() {
		return this->channelId;
	}
	
	void setChannelId(int channelId) {
		this->channelId = channelId;
	}
	
	TGLyric* getLyrics() {
		return this->lyrics;
	}
	
	void setLyrics(TGLyric* lyrics) {
		this->lyrics = lyrics;
	}
	
	TGString* getString(int number){
		return this->strings.at(number - 1);
	}
	
	int stringCount(){
		return this->strings.size();
	}
	
	TGSong* getSong() {
		return this->song;
	}
	
	void setSong(TGSong* song) {
		this->song = song;
	}
	
	void clear();
	
};

#endif // TGTRACK_H
