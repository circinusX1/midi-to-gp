
#include <assert.h>
#include <iostream>
#include "midisongreader.h"
#include "tgtempo.h"
#include "tgmarker.h"
#include "tgmeasure.h"
#include "midisequence.h"
#include "tgnote.h"
#include "tgtext.h"
#include "tgtrack.h"
#include "tgtimesignature.h"
#include "tgmarker.h"
#include "tgnoteeffect.h"
#include "tgsongmanager.h"
#include "gmchannelroute.h"
#include "gmchannelrouter.h"
#include "songadjuster.h"


MidiSongReader::MidiSongReader()
{
    
}

MidiSongReader::~MidiSongReader()
{
    if(_file.is_open())
        _file.close();
}

bool MidiSongReader::open(const char* filename)
{
    _file.open(filename, std::ifstream::binary);
    return _file.is_open();
}

TGSong* MidiSongReader::read(int tranps)
{
	MidiSequence* sequence = _getSequence();
	_tgSong = new TGSong();
	_transpose = tranps;
	_initFields(sequence);
	
	for(int i = 0; i < sequence->countTracks(); i++){
		MidiTrack* track = sequence->getTrack(i);
		int trackNumber = _getNextTrackNumber();
		int events = track->size();
		for(int j = 0;j < events;j ++){
			MidiEvent* event = track->get(j);
			_parseMessage(trackNumber,
						  event->getTick(),
						  event->getMessage());
		}
	}
	std::cout << "making gp\n";
	
	TGSongManager* tgSongManager = new TGSongManager();
	
	this->_checkAll(tgSongManager);
	
	for(auto& channel : this->_channels)
	{
		_tgSong->addChannel(channel);
	}
	
	for(auto& header : this->_headers){
		_tgSong->addMeasureHeader(header);
	}
	
	for(auto& track : _tracks)
	{
		_tgSong->addTrack(track);
	}
	
	SongAdjuster sa(_tgSong);
	sa.adjustSong();
	
	return _tgSong;
}

int MidiSongReader::_getNextTrackNumber()
{
	return (_tracks.size() + 1);
}

void MidiSongReader::_initFields(MidiSequence* sequence)
{
	_resolution = sequence->getResolution();
}

MidiSequence* MidiSongReader::_getSequence()
{
	int headerLength=HEADER_MAGIC;
	int magic = _read_int();
	if(magic != (int)HEADER_MAGIC)
		return nullptr;
	
	headerLength=_read_int();
	if (headerLength != (int)HEADER_LENGTH){
		return nullptr;
	}
	short typ = _read_short();
	if (typ < 0 || typ > 2){
		return nullptr;
	}
	if (typ == 2){
		return nullptr;
	}
	
	int trackCount = _read_short();
	
	if (trackCount <= 0){
		return nullptr;
	}
	
	if (typ == 0 && trackCount != 1){
		return nullptr;
	}
	float _divisionType = -1.0F;
	int _resolution = -1;
	int division = _read_short();
	if ((division & 0x8000) != 0){
		int frameType = -((division >> 8) & 0xFF);
		if(frameType == 24){
			_divisionType = MidiSequence::SMPTE_24;
		}else if(frameType == 25){
			_divisionType = MidiSequence::SMPTE_25;
		}else if(frameType == 29){
			_divisionType = MidiSequence::SMPTE_30DROP;
		}else if(frameType == 30){
			_divisionType = MidiSequence::SMPTE_30;
		}else{
			return nullptr;
		}
		_resolution = division & 0xff;
	}else{
		_divisionType = MidiSequence::PPQ;
		_resolution = division & 0x7fff;
	}
	_skip(headerLength - HEADER_LENGTH);
	
	MidiSequence* sequence = new MidiSequence(_divisionType,_resolution);
	for (int i = 0; i < trackCount; i++){
		MidiTrack* track = new MidiTrack();
		_readTrack( track);
		sequence->addTrack(track);
	}
	return sequence;
}

void MidiSongReader::_readTrack(MidiTrack* track)
{
	while (true){
		if (_read_int() == TRACK_MAGIC){
			break;
		}
		int chunkLength = _read_int();
		if (chunkLength % 2 != 0){
			chunkLength++;
		}
		_skip(chunkLength);
	}
	
	int bytes =_read_int();
	MidiTrackReaderHelper helper(0,bytes,-1);
	while (helper._remainingBytes > 0){
		helper._ticks += _readVariableLengthQuantity(helper);
		MidiEvent* event = _readEvent(helper);
		if(event != nullptr){
			track->add(event);
		}
	}
}

long MidiSongReader::_readVariableLengthQuantity(MidiTrackReaderHelper& helper)
{
	int	count = 0;
	long value = 0;
	while (count < 4){
		int	data = (int)_readUnsignedByte(helper);
		count++;
		value <<= 7;
		value |= (data & 0x7f);
		if (data < 128){
			return value;
		}
	}
	assert(0);
}

MidiEvent* MidiSongReader::_readEvent( MidiTrackReaderHelper& helper)
{
	int statusByte = _readUnsignedByte(helper);
	int savedByte = 0;
	bool runningStatusApplies = false;
	
	if (statusByte < 0x80){
		if (helper._runningStatusByte != -1){
			runningStatusApplies = true;
			savedByte = statusByte;
			statusByte = helper._runningStatusByte;
		}else{
			assert(0);
			return nullptr;
		}
	}
	
	int type = _getType(statusByte);
	if(type == STATUS_ONE_BYTE){
		int data = 0;
		if (runningStatusApplies){
			data = savedByte;
		}else{
			data = _readUnsignedByte(helper);
			helper._runningStatusByte = statusByte;
		}
		MidiMessage *pm = MidiMessage::shortMessage((statusByte & 0xF0),(statusByte & 0x0F), data);
		return new MidiEvent(pm, helper._ticks);
	}
	else if(type == STATUS_TWO_BYTES)
	{
		int	data1 = 0;
		if (runningStatusApplies)
		{
			data1 = savedByte;
		}
		else
		{
			data1 = _readUnsignedByte(helper);
			helper._runningStatusByte = statusByte;
		}
		uint8_t byte2  = _readUnsignedByte(helper);
		MidiMessage *pm = MidiMessage::shortMessage((statusByte & 0xF0),
													(statusByte & 0x0F), 
													data1, 
													byte2);
		return new MidiEvent(pm, helper._ticks);
	}
	else if(type == STATUS_SYSEX)
	{
		if (CANCEL_RUNNING_STATUS_ON_META_AND_SYSEX){
			helper._runningStatusByte = -1;
		}
		int dataLength = (int) _readVariableLengthQuantity(helper);
		bytes data;
		for (int i = 0; i < dataLength; i++){
			data.push_back((uint8_t)_readUnsignedByte(helper));
		}
	}
	else if(type == STATUS_META)
	{
		if (CANCEL_RUNNING_STATUS_ON_META_AND_SYSEX){
			helper._runningStatusByte = -1;
		}
		int typeByte = _readUnsignedByte(helper);
		int dataLength = (int) _readVariableLengthQuantity(helper);
		bytes data;
		for (int i = 0; i < dataLength; i++){
			data.push_back((uint8_t)_readUnsignedByte(helper));
		}
		
		MidiMessage * pmm = MidiMessage::metaMessage(typeByte, data);
		return new MidiEvent(pmm, helper._ticks);
	}
	
	return nullptr;
}


int MidiSongReader::_getType(int statusByte)
{
	if (statusByte < 0xf0) {
		int command = statusByte & 0xf0;
		if(command == 0x80 || command == 0x90 || 
				command == 0xa0 || command == 0xb0 || 
				command == 0xe0)
		{
			return STATUS_TWO_BYTES;
		}
		else if(command == 0xc0 || command == 0xd0){
			return STATUS_ONE_BYTE;
		}
		return STATUS_NONE;
	}
	else if (statusByte == 0xf0 || statusByte == 0xf7){
		return STATUS_SYSEX;
	}
	else if (statusByte == 0xff){
		return STATUS_META;
	}
	else{
		return STATUS_NONE;
	}
}


long MidiSongReader::_parseTick(long tick)
{
	return std::abs(TGDuration::QUARTER_TIME * tick / this->_resolution);
}


void MidiSongReader::_parseMessage(int trackNumber,long tick,
								   MidiMessage* message)
{
	long parsedTick = _parseTick(tick + this->_resolution);
	
	//NOTE ON
	if(message->getType() == MidiMessage::TYPE_SHORT && 
			message->getCommand() == MidiMessage::NOTE_ON){
		_parseNoteOn(trackNumber,parsedTick,message->getData());
	}
	//NOTE OFF
	else if(message->getType() == MidiMessage::TYPE_SHORT && 
			message->getCommand() == MidiMessage::NOTE_OFF){
		_parseNoteOff(trackNumber,parsedTick,message->getData());
	}
	//PROGRAM CHANGE
	else if(message->getType() == MidiMessage::TYPE_SHORT && 
			message->getCommand() == MidiMessage::PROGRAM_CHANGE){
		_parseProgramChange(message->getData());
	}
	//CONTROL CHANGE
	else if(message->getType() == MidiMessage::TYPE_SHORT && 
			message->getCommand() == MidiMessage::CONTROL_CHANGE){
		_parseControlChange(message->getData());
	}
	//TIME SIGNATURE
	else if(message->getType() == MidiMessage::TYPE_META && 
			message->getCommand() == MidiMessage::TIME_SIGNATURE_CHANGE){
		_parseTimeSignature(parsedTick,message->getData());
	}
	//TEMPO
	else if(message->getType() == MidiMessage::TYPE_META && 
			message->getCommand() == MidiMessage::TEMPO_CHANGE){
		_parseTempo(parsedTick,message->getData());
	}
}

void MidiSongReader::_parseProgramChange(bytes& data){
	int length = data.size();
	int channel = (length > 0)?((data[0] & 0xFF) & 0x0F):-1;
	int instrument = (length > 1)?(data[1] & 0xFF):-1;
	if(channel != -1 && instrument != -1){
		getTempChannel(channel)->setInstrument(instrument);
	}
}

void MidiSongReader::_makeTempNotesBefore(long tick,int track)
{
	long nextTick = tick;
	bool check = true;
	while(check){
		check = false;
		for(int i = 0;i < this->_tempNotes.size();i ++){
			TempNote* note = (TempNote*)this->_tempNotes.at(i);
			if(note->getTick() < nextTick && note->getTrack() == track){
				nextTick = note->getTick() + (TGDuration::QUARTER_TIME * 5); 
				makeNote(nextTick,track,note->getChannel(),note->getValue());
				check = true;
				break;
			}
		}
	}
}

void MidiSongReader::_parseNoteOn(int track,long tick,bytes&  data)
{
	int length = data.size();
	int channel = (length > 0)?((data[0] & 0xFF) & 0x0F):0;
	int value = (length > 1)?(data[1] & 0xFF):0;
	int velocity = (length > 2)?(data[2] & 0xFF):0;
	if(velocity == 0){
		_parseNoteOff(track,tick,data);
	}else if(value > 0){
		_makeTempNotesBefore(tick,track);
		getTempChannel(channel)->setTrack(track);
		_getTrackTuningHelper(track)->checkValue(value);
		this->_tempNotes.push_back(new TempNote(track,channel,value,tick));
	}
}

void MidiSongReader::_parseNoteOff(int track,long tick,bytes&  data)
{
	int length = data.size();
	
	int channel = (length > 0)?((data[0] & 0xFF) & 0x0F):0;
	int value = (length > 1)?(data[1] & 0xFF):0;
	
	makeNote(tick,track,channel,value);
}

void MidiSongReader::_parseControlChange(bytes&  data)
{
	int length = data.size();
	int channel = (length > 0)?((data[0] & 0xFF) & 0x0F):-1;
	int control = (length > 1)?(data[1] & 0xFF):-1;
	int value = (length > 2)?(data[2] & 0xFF):-1;
	if(channel != -1 && control != -1 && value != -1){
		getTempChannel(channel)->setVolume(value);
	}
}

void MidiSongReader::_parseTimeSignature(long tick,bytes&  data)
{
	if(data.size() >= 2){
		TGTimeSignature timeSignature;
		timeSignature.setNumerator(data[0]);
		timeSignature._denominator.setValue(TGDuration::QUARTER);
		if (data[1] == 0) {
			timeSignature._denominator.setValue(TGDuration::WHOLE);
		} else if (data[1] == 1) {
			timeSignature._denominator.setValue(TGDuration::HALF);
		} else if (data[1] == 2) {
			timeSignature._denominator.setValue(TGDuration::QUARTER);
		} else if (data[1] == 3) {
			timeSignature._denominator.setValue(TGDuration::EIGHTH);
		} else if (data[1] == 4) {
			timeSignature._denominator.setValue(TGDuration::SIXTEENTH);
		} else if (data[1] == 5) {
			timeSignature._denominator.setValue(TGDuration::THIRTY_SECOND);
		}
		_getHeader(tick)->setTimeSignature(timeSignature);
	}
}

void MidiSongReader::_parseTempo(long tick,bytes&  data)
{
	if(data.size() >= 3)
	{
		TGTempo tempo = TGTempo::fromUSQ((data[2] & 0xff) | 
				((data[1] & 0xff) << 8) | 
				((data[0] & 0xff) << 16));
		_getHeader(tick)->setTempo(tempo);
	}
}

TGMeasureHeader* MidiSongReader::_getHeader(long tick)
{
	long realTick = (tick >= TGDuration::QUARTER_TIME)?tick:TGDuration::QUARTER_TIME;
	
	for(auto h :_headers)
	{
		if(realTick >= h->getStart() && 
				realTick < h->getStart() + h->getLength()){
			return (TGMeasureHeader*)h;
		}
	}
	TGMeasureHeader* last = _getLastHeader();
	TGMeasureHeader* header = new TGMeasureHeader;
	header->setNumber((last != nullptr)?last->getNumber() + 1:1);
	header->setStart((last != nullptr)?(last->getStart() + 
										last->getLength()):TGDuration::QUARTER_TIME);
	header->getTempo().setValue(  (last != nullptr)?last->getTempo().getValue():120 );
	if(last != nullptr){
		header->_timeSignature = last->getTimeSignature();
	}else{
		header->getTimeSignature().setNumerator(4);
		header->getTimeSignature()._denominator.setValue(TGDuration::QUARTER);
	}
	this->_headers.push_back(header);
	
	if(realTick >= header->getStart() && realTick < header->getStart() +
			header->getLength()){
		return header;
	}
	return _getHeader(realTick);
}

TGMeasureHeader* MidiSongReader::_getLastHeader()
{
	if(!this->_headers.empty()){
		return (TGMeasureHeader*)this->_headers.back();
	}
	return nullptr;
}

TempChannel* MidiSongReader::getTempChannel(int channel)
{
	for(auto c : _tempChannels)
	{
		if(c->getChannel() == channel){
			return c;
		}
	}
	TempChannel* tempChannel = new TempChannel(channel);
	this->_tempChannels.push_back(tempChannel);
	return tempChannel;
}

void MidiSongReader::makeNote(long tick,int track,int channel,int value)
{
	TempNote* tempNote = _getTempNote(track,channel,value,true);
	if(tempNote != nullptr){
		int nString = 0;
		int nValue = (tempNote->getValue() + this->_transpose);
		int nVelocity = 64;
		long nStart = tempNote->getTick();
		TGDuration minDuration(MIN_DURATION_VALUE);
		TGDuration nDuration = TGDuration::fromTime(tick - 
													tempNote->getTick(),
													minDuration);
		
		TGMeasure* measure = getMeasure(_getTrack(track),tempNote->getTick());
		TGBeat* beat = _getBeat(measure, nStart);
		beat->getVoice(0)->duration = nDuration;
		
		TGNote* note = new TGNote;
		note->setValue(nValue);
		note->setString(nString);
		note->setVelocity(nVelocity);
		beat->getVoice(0)->addNote(note);
	}
}


TempNote* MidiSongReader::_getTempNote(int track,int channel,int value,bool purge)
{
	for(int i = 0;i < this->_tempNotes.size();i ++)
	{
		TempNote* note = _tempNotes[i];
		if(note->getTrack() == track && 
				note->getChannel() == channel && 
				note->getValue() == value){
			if(purge){
				_tempNotes.erase(_tempNotes.begin()+i);
			}
			return note;
		}
	}
	return nullptr;
}

TGDuration MidiSongReader::_newDuration(int value)
{
	TGDuration duration;
	duration.setValue(value);
	return duration;
}

TGTrack* MidiSongReader::_getTrack(int number)
{
	for(auto& a : _tracks){
		if(a->getNumber() == number){
			return a;
		}
	}
	
	TGTrack* track = new TGTrack();
	
	track->setNumber(number);
	track->setChannelId(-1);
	track->color = TGColor::RED;
	this->_tracks.push_back(track);
	return track;
}

TGMeasure* MidiSongReader::getMeasure(TGTrack* track,long tick)
{
	long realTick = (tick >= TGDuration::QUARTER_TIME)?tick:TGDuration::QUARTER_TIME;
	for(auto &m : track->measures)
	{
		if(realTick >= m->getStart() && realTick < m->getStart() + m->getLength()){
			return m;
		}
	}
	_getHeader(realTick);
	for(int i = 0;i < this->_headers.size();i++){
		bool exist = false;
		TGMeasureHeader* header = this->_headers.at(i);
		int measureCount = track->countMeasures();
		for(int j = 0;j < measureCount;j++){
			TGMeasure* measure = track->getMeasure(j);
			if(measure->header == header){
				exist = true;
			}
		}
		if(!exist){
			TGMeasure* measure = new TGMeasure(header);
			track->addMeasure(measure);
		}
	}
	return getMeasure(track,realTick);
}

TGBeat* MidiSongReader::_getBeat(TGMeasure* measure, long start){
	int beatCount = measure->countBeats();
	for( int i = 0 ; i < beatCount ; i ++){
		TGBeat* beat = measure->getBeat( i );
		if( beat->getStart() == start){
			return beat;
		}
	}
	TGBeat* beat = new TGBeat;
	beat->setStart(start);
	measure->addBeat(beat);
	return beat;
}

void MidiSongReader::_checkAll(TGSongManager* songManager)
{
	_checkChannels();
	_checkTracks(songManager);
	
	int headerCount = this->_headers.size();
	for(int i = 0;i < this->_tracks.size();i ++){
		TGTrack* track = (TGTrack*)this->_tracks.at(i);
		
		while(track->countMeasures() < headerCount){
			long start = TGDuration::QUARTER_TIME;
			TGMeasure* lastMeasure = ((track->countMeasures() > 0)?
										 track->getMeasure(track->countMeasures() - 1) :
										  nullptr);
			if(lastMeasure != nullptr){
				start = (lastMeasure->getStart() + lastMeasure->getLength());
			}
			track->addMeasure(new TGMeasure(_getHeader(start)));
		}
	}
	
	if(this->_headers.empty() || this->_tracks.empty()){
		assert(0);
	}
}

void MidiSongReader::_checkChannels()
{
	for(int tc = 0 ; tc < this->_tempChannels.size() ; tc ++ ){
		TempChannel* tempChannel = this->_tempChannels.at( tc );
		if( tempChannel->getTrack() > 0 ){
			bool channelExists = false;
			for(int c = 0 ; c < this->_channels.size() ; c ++ ){
				TGChannel* tgChannel = this->_channels[c];
				GMChannelRoute* gmChannelRoute = 
						this->_channelRouter.getRoute(tgChannel->getChannelId());
				if( gmChannelRoute != nullptr ){
					if( gmChannelRoute->getChannel1() == tempChannel->getChannel() ||
						gmChannelRoute->getChannel2() == tempChannel->getChannel() )
					{
						channelExists = true;
					}
				}
			}
			
			if(!channelExists){
				TGChannel* tgChannel = new TGChannel();
				tgChannel->setChannelId(this->_channels.size() + 1);
				tgChannel->setProgram((short)tempChannel->getInstrument());
				tgChannel->setVolume((short)tempChannel->getVolume());
				tgChannel->setBalance((short)tempChannel->getBalance());
				tgChannel->setName((std::string("#") + 
									std::to_string(tgChannel->getChannelId())));
				tgChannel->setBank(tempChannel->getChannel() == 9 ? 
									  TGChannel::DEFAULT_PERCUSSION_BANK : 
									  TGChannel::DEFAULT_BANK);
				
				GMChannelRoute* gmChannelRoute = 
						new GMChannelRoute(tgChannel->getChannelId());
				gmChannelRoute->setChannel1(tempChannel->getChannel());
				gmChannelRoute->setChannel2(tempChannel->getChannel());
				
				for(int tcAux = (tc + 1) ; 
					tcAux < this->_tempChannels.size() ; 
					tcAux ++ ){
					TempChannel* tempChannelAux =this->_tempChannels.at( tcAux );
					if( tempChannel->getTrack() == tempChannelAux->getTrack() ){
						if( gmChannelRoute->getChannel2() == 
								gmChannelRoute->getChannel1() ){
							gmChannelRoute->setChannel2( tempChannelAux->getChannel() );
						}else{
							tempChannelAux->setTrack(-1);
						}
					}
				}
				
				this->_channelRouter.configureRoutes(gmChannelRoute, 
													 (tempChannel->getChannel() == 9));
				
				TGChannelParameter* gmChannel1Param = new TGChannelParameter();
				TGChannelParameter* gmChannel2Param = new TGChannelParameter();
				
				gmChannel1Param->setKey(GMChannelRoute::PARAMETER_GM_CHANNEL_1);
				gmChannel1Param->setValue(std::to_string(gmChannelRoute->getChannel1()));
				
				gmChannel2Param->setKey(GMChannelRoute::PARAMETER_GM_CHANNEL_2);
				gmChannel2Param->setValue(std::to_string(gmChannelRoute->getChannel2()));
				
				tgChannel->addParameter(gmChannel1Param);
				tgChannel->addParameter(gmChannel2Param);
				
				this->_channels.push_back( tgChannel );
			}
		}
	}
}

void MidiSongReader::_checkTracks(TGSongManager* songManager)
{
	for(auto& track : this->_tracks)
	{
		TGChannel* trackChannel = nullptr;
		for( auto& tempChannel: _tempChannels)
		{
			if( tempChannel->getTrack() == track->getNumber() ){
				for(auto& tgChannel : _channels)
				{
					GMChannelRoute* gmChannelRoute = 
							this->_channelRouter.getRoute(tgChannel->getChannelId());
					if( gmChannelRoute != nullptr && 
							tempChannel->getChannel() == gmChannelRoute->getChannel1() )
					{
						trackChannel = tgChannel;
					}
				}
			}
		}
		if( trackChannel != nullptr ){
			track->setChannelId( trackChannel->getChannelId() );
		}
		if( trackChannel != nullptr && trackChannel->isPercussionChannel() ){
			std::vector<TGString*> sv;
			songManager->createPercussionStrings(6, sv);
			track->setStrings(sv);
		}else{
			TrackTuningHelper* th = _getTrackTuningHelper(track->getNumber());
			std::vector<TGString*> s;
			th->getStrings(s);
			track->setStrings(s);
		}
	}
}

TrackTuningHelper* MidiSongReader::_getTrackTuningHelper(int track)
{
	for(auto& helper : _trackTuningHelpers)
	{
		if(helper->getTrack() == track){
			return helper;
		}
	}
	TrackTuningHelper* helper = new TrackTuningHelper(track);
	this->_trackTuningHelpers.push_back(helper);
	return helper;
}

