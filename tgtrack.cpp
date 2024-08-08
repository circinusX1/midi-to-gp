
#include "temps.h"
#include "tgmeasure.h"
#include "tgstring.h"
#include "tglayout.h"
#include "tgsong.h"
#include "tglyric.h"
#include "tgtrack.h"

void TGTrack::addMeasure(TGMeasure* measure)
{
	measure->setTrack(this);
	this->measures.push_back(measure);
}

void TGTrack::addMeasure(int index,TGMeasure* measure)
{
	measure->setTrack(this);
	this->measures.resize(index+1);
	this->measures[index]=measure;
}

void TGTrack::removeMeasure(int index)
{
	this->measures.erase(this->measures.begin() + index);
}

void TGTrack::clear()
{
	int measureCount = this->countMeasures();
	for(int i = 0 ; i < measureCount ; i ++) {
		TGMeasure* tgMeasure = this->getMeasure(i);
		tgMeasure->clear();
	}
	for(auto a: this->strings)
		delete a;
	for(auto a: this->measures)	
		delete a;
	this->strings.clear();
	this->measures.clear();
}
