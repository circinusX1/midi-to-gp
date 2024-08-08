#include "midievent.h"


MidiMessage::MidiMessage(int message, int command)
{
	this->message = message;
	this->command = command;
}

void MidiMessage::setData(bytes &data)
{
	this->data = data;
}

bytes& MidiMessage::getData()
{
	return this->data;
}

int MidiMessage::getType()
{
	return this->message;
}

int MidiMessage::getCommand()
{
	return this->command;
}

MidiMessage *MidiMessage::shortMessage(int command, int channel, int data1, int data2)
{
	MidiMessage *message = new MidiMessage(TYPE_SHORT,command);
	bytes by{(char)((command & 0xF0) | (channel & 0x0F)), 
								  (char)(data1),
								  (char)(data2)};
	message->setData(by);
	
	return message;
}

MidiMessage *MidiMessage::shortMessage(int command, int channel, int data)
{
	MidiMessage *message = new MidiMessage(TYPE_SHORT,command);
	bytes by{(char)((command & 0xF0) | (channel & 0x0F)), 
						  (char)(data)};
	message->setData(by);
	
	return message;
}

MidiMessage *MidiMessage::shortMessage(int command)
{
	MidiMessage *message = new MidiMessage(TYPE_SHORT,command);
	bytes by{(char)(command)};
	message->setData(by);
	
	return message;
}

MidiMessage *MidiMessage::metaMessage(int command, bytes &data)
{
	MidiMessage *message = new MidiMessage(TYPE_META,command);
	message->setData(data);
	
	return message;
}
