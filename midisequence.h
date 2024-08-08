#ifndef MIDISEQUENCE_H
#define MIDISEQUENCE_H

#include <vector>
#include "miditrack.h"

class MidiSequence {
public:	
	MidiSequence(float _divisionType, int _resolution){
		this->_divisionType = _divisionType;
		this->_resolution = _resolution;
	}
	
	void addTrack(MidiTrack* track){
		this->_tracks.push_back(track);
	}
	
	MidiTrack* getTrack(int index){
		return (MidiTrack*)this->_tracks.at(index);
	}
	
	int countTracks(){
		return this->_tracks.size();
	}
	
	float getDivisionType() {
		return this->_divisionType;
	}
	
	int getResolution() {
		return this->_resolution;
	}
	
	void sort(){
		for(size_t i = 0; i < this->_tracks.size(); i ++){
			MidiTrack* track = (MidiTrack*)this->_tracks.at(i);
			track->sort();
		}
	}
	
	void finish(){
		for(size_t i = 0; i < this->_tracks.size(); i ++){
			MidiTrack* track = (MidiTrack*)this->_tracks.at(i);
			bytes bys;
			MidiMessage* pmm = MidiMessage::metaMessage(47, bys);
			MidiEvent* pme = new MidiEvent(pmm, track->ticks());
			track->add(pme);
			track->sort();
		}
	}

protected:	
	float					_divisionType;
	int						_resolution;
	std::vector<MidiTrack*>	_tracks;
	
public:
	constexpr static  float PPQ = 0.0f;
	constexpr static  float SMPTE_24 = 24.0f;
	constexpr static  float SMPTE_25 = 25.0f;
	constexpr static  float SMPTE_30DROP = 29.97f;
	constexpr static  float SMPTE_30 = 30.0f;
};


#endif // MIDISEQUENCE_H
