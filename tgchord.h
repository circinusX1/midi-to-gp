#ifndef TGCHORD_H
#define TGCHORD_H

#include <string>
#include <vector>
#include "tgstring.h"

class TGBeat;
class TGChord {
public:	
	int			firstFret;
	std::vector<int>	strings;
	std::string	name;
	TGBeat*		beat;
	
	TGChord(int length){
		this->strings.resize(length);
		for(int i = 0;i < length;i++){
			this->strings[i] = -1;
		}
	}
	
	TGBeat* getBeat() {
		return this->beat;
	}
	
	void setBeat(TGBeat* beat) {
		this->beat = beat;
	}
	
	void addFretValue(int string,int fret){
		if(string >= 0 && string < (int)this->strings.size()){
			this->strings[string] = fret;
		}
	}
	
	int getFretValue(int string){
		if(string >= 0 && string < (int)this->strings.size()){
			return this->strings[string];
		}
		return -1;
	}
	
	int getFirstFret() {
		return this->firstFret;
	}
	
	void setFirstFret(int firstFret) {
		this->firstFret = firstFret;
	}
	
	std::vector<int>& getStrings() {
		return this->strings;
	}
	
	int countStrings(){
		return this->strings.size();
	}
	
	int countNotes(){
		int count = 0;
		for(size_t i = 0;i < this->strings.size();i++){
			if(this->strings[i] >= 0){
				count ++;
			}
		}
		return count;
	}
	
	std::string& getName() {
		return this->name;
	}
	
	void setName(std::string name) {
		this->name = name;
	}
	
};

#endif // TGCHORD_H
