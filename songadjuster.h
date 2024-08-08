#ifndef SONGADJUSTER_H
#define SONGADJUSTER_H

#include "tgmeasure.h"
#include "tgsong.h"

class SongAdjuster
{
private:
	TGSong *song;
	long long minDurationTime = 0;
	
public:
	~SongAdjuster()
	{
	}
	
	SongAdjuster(TGSong *song);
	TGSong *adjustSong();
	
private:
	void adjustTrack(TGTrack *track);
	
public:
	void process(TGMeasure *measure);
	void joinBeats(TGMeasure *measure);
	void orderBeats(TGMeasure *measure);
	
private:
	void adjustStrings(TGMeasure *measure);
	void adjustStrings(TGBeat *beat);
	int getStringForValue(std::vector<TGString*> &strings, int value);
};


#endif // SONGADJUSTER_H
