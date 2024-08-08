#ifndef TGTEXT_H
#define TGTEXT_H

#include <string>

class TGBeat;
class TGText{
public:
	std::string value;
	TGBeat* beat;
	
	TGText(){
	}
	
	TGBeat* getBeat() {
		return this->beat;
	}
	
	void setBeat(TGBeat* beat) {
		this->beat = beat;
	}
	
	std::string getValue() {
		return this->value;
	}
	
	void setValue(std::string value) {
		this->value = value;
	}
	
	bool isEmpty(){
		return (this->value.empty());
	}
	
	
};

#endif // TGTEXT_H
