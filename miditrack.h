#ifndef MIDITRACK_H
#define MIDITRACK_H

#include <vector>
#include <algorithm>
#include "midievent.h"

class MidiTrack 
{
	
public:
	MidiTrack(){}
	~MidiTrack(){}
	
	void add(MidiEvent* event) {
		this->_aevents.push_back(event);
		this->_ticks = std::max(this->_ticks, event->getTick());
	}
	
	MidiEvent* get(int index)const{
		return (MidiEvent*)this->_aevents.at(index);
	}
	
	int size()const{
		return this->_aevents.size();
	}
	
	long ticks()const{
		return this->_ticks;
	}
	
	static bool myfunction (MidiEvent* e1,MidiEvent* e2)
	{
		if (e1 != nullptr && e2 != nullptr)
		{
			if (e1->getTick() == e2->getTick())
			{
				return 0;
			}
			return (e1->getTick() > e2->getTick() ? 1 : -1);
		}
		return 0;
	}
	
	void sort(){
		std::sort(_aevents.begin(),_aevents.end(), MidiTrack::myfunction); 
	}
	
	long	_ticks=0;
	std::vector<MidiEvent*> _aevents;
	
};

#endif // MIDITRACK_H

