#include "tgmeasure.h"
#include "tgbeat.h"

void TGMeasure::addBeat(TGBeat* beat){
	beat->setMeasure(this);
	this->beats.push_back(beat);
}

void TGMeasure::clear(){
	for(auto &a : beats)
		delete a;
	this->beats.clear();
}

void TGMeasure::moveBeat(int index,TGBeat* beat){
	removeBeat(beat);
	beats.push_back(beat);
	beats[beats.size()-1]=beats[index];
	beats[index]=beat;
}

void TGMeasure::removeBeat(TGBeat* beat){
	std::vector<TGBeat*>::iterator f = beats.begin();
	for(; f!= beats.end(); f++)
	{
		if(*f==beat){
			this->beats.erase(f);
			break;
		}
	}
}
