#ifndef MIDIEVENT_H
#define MIDIEVENT_H

#include <inttypes.h>
#include <vector>

typedef std::vector<char>	bytes;


class MidiMessage
{
	
public:
	static constexpr int TYPE_SHORT = 1;
	static constexpr int TYPE_META = 2;
	
	static constexpr int NOTE_OFF = 0x80;
	static constexpr int NOTE_ON = 0x90;
	static constexpr int CONTROL_CHANGE = 0xB0;
	static constexpr int PROGRAM_CHANGE = 0xC0;
	static constexpr int PITCH_BEND = 0xE0;
	static constexpr int SYSTEM_RESET = 0xFF;
	static constexpr int TEMPO_CHANGE = 0x51;
	static constexpr int TIME_SIGNATURE_CHANGE = 0x58;
	
private:
	int message = 0;
	int command = 0;
	bytes data;
	
public:
	MidiMessage(int message, int command);
	
	void setData(bytes &data);
	
	bytes& getData();
	
	int getType();
	
	int getCommand();
	
	static MidiMessage *shortMessage(int command, int channel, int data1, int data2);
	
	static MidiMessage *shortMessage(int command, int channel, int data);
	
	static MidiMessage *shortMessage(int command);
	
	static MidiMessage *metaMessage(int command, bytes &data);
};


class MidiEvent
{
public:
    MidiEvent(){};
    ~MidiEvent(){};
    
    MidiEvent(MidiMessage* message, long tick){
        this->_message = message;
        this->_tick = tick;
    }	
    MidiMessage* getMessage()const {
        return this->_message;
    }
    
    long getTick()const {
        return this->_tick;
    }    
    
private:
    long _tick;
    MidiMessage* _message;
    
};

#endif // MIDIEVENT_H


