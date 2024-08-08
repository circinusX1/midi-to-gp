#ifndef MIDISONGREADER_H
#define MIDISONGREADER_H

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "tgfactory.h"
#include "gmchannelrouter.h"
#include "midievent.h"
#include "temps.h"
#include "tgbeat.h"

class MidiSequence;
class MidiTrack;
class MidiEvent;
class TGMeasureHeader;
class TrackTuningHelper;

class MidiTrackReaderHelper{
public:
	long _ticks = 0;
	long _remainingBytes=0;
	int _runningStatusByte=0;
	
	MidiTrackReaderHelper(long ticks,long remainingBytes,int _runningStatusByte){
		_ticks = ticks;
		_remainingBytes = remainingBytes;
		_runningStatusByte = _runningStatusByte;
	}
};

class MidiSongReader
{
public:
    MidiSongReader();
    ~MidiSongReader();
    
    bool open(const char* filename);
    TGSong* read(int tranps=0);
    
    TempChannel* getTempChannel(int channel);
    void makeNote(long tick,int track,int channel,int value);
    TGMeasure* getMeasure(TGTrack* track,long tick);
    void parseProgramChange(bytes&  data);
private:
    TrackTuningHelper* _getTrackTuningHelper(int track);
    void _checkTracks(TGSongManager* songManager);
    void _checkAll(TGSongManager* songManager);
    void _checkChannels();
    long _readVariableLengthQuantity(MidiTrackReaderHelper& helper);
    MidiEvent* _readEvent(MidiTrackReaderHelper& helper);
    MidiSequence* _getSequence();
    void _readTrack(MidiTrack* track);
    int _read_int(){
        int t;
        _file.read((char*)&t,sizeof(int));
        return __builtin_bswap32(t);
    }
    uint16_t _read_short(){
        uint16_t t;
        _file.read((char*)&t,sizeof(uint16_t));
        return __builtin_bswap16(t);
    }    
    uint8_t _read_byte(){
        uint8_t t;
        _file.read((char*)&t,sizeof(uint8_t));
        return t;
    }
    void _skip(int length){
        while(length--)
            _read_byte();
    }
    int _readUnsignedByte(MidiTrackReaderHelper& helper){
		helper._remainingBytes--;
		return _read_byte();
	}
	int _getType(int statusByte);
	void _initFields(MidiSequence* sequence);
	int _getNextTrackNumber();
	void _parseMessage(int trackNumber,long tick, MidiMessage* message);
	long _parseTick(long tick);
	void _parseTempo(long tick,bytes&  data);
	void _parseTimeSignature(long tick,bytes&  data);
	void _parseControlChange(bytes&  data);
	void _parseProgramChange(bytes&  data);
	void _parseNoteOff(int track,long tick,bytes&  data);
	void _parseNoteOn(int track,long tick,bytes&  data);
	void _makeTempNotesBefore(long tick,int track);
	TGMeasureHeader* _getHeader(long tick);
	TGMeasureHeader* _getLastHeader();
	TempNote* _getTempNote(int track,int channel,int value,bool purge);
	TGDuration _newDuration(int value);
	TGTrack* _getTrack(int number);
	TGBeat* _getBeat(TGMeasure* measure, long start);
	
private:    
	std::ifstream					_file;
	int								_transpose=0;
	int								_resolution;
	std::vector<TGChannel*>			_channels;
	std::vector<TGMeasureHeader*>	_headers;
	std::vector<TGTrack*>			_tracks;
	std::vector<TempNote*>			_tempNotes;
	std::vector<TempChannel*>		_tempChannels;
	std::vector<TrackTuningHelper*>	_trackTuningHelpers;
	GMChannelRouter					_channelRouter;
	TGSong*							_tgSong;// = new TGSong();
		
	constexpr static int	HEADER_LENGTH = 6;
	constexpr static int	HEADER_MAGIC = 0x4d546864;
	constexpr static int	TRACK_MAGIC = 0x4d54726b;
	constexpr static bool   CANCEL_RUNNING_STATUS_ON_META_AND_SYSEX = true;
	constexpr static  int STATUS_NONE = 0;
	constexpr static  int STATUS_ONE_BYTE = 1;
	constexpr static  int STATUS_TWO_BYTES = 2;
	constexpr static  int STATUS_SYSEX = 3;
	constexpr static  int STATUS_META = 4;
	constexpr static int MIN_DURATION_VALUE = TGDuration::SIXTY_FOURTH;
};



#endif // MIDISONGREADER_H
