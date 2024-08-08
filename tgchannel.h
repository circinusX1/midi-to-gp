#ifndef TGCHANNEL_H
#define TGCHANNEL_H


#include <string>
#include <vector>
#include "tgchannelparameter.h"
#include "tgstring.h"

extern int TracksVolume;

class TGChannel {
public:
	
	constexpr static  short DEFAULT_PERCUSSION_CHANNEL = 9;
	constexpr static  short DEFAULT_PERCUSSION_PROGRAM = 0;
	constexpr static  short DEFAULT_PERCUSSION_BANK = 128;
	
	constexpr static  short DEFAULT_BANK = 0;
	constexpr static  short DEFAULT_PROGRAM = 25;
	constexpr static  short DEFAULT_VOLUME = 127;
	constexpr static  short DEFAULT_BALANCE = 64;
	constexpr static  short DEFAULT_CHORUS = 0;
	constexpr static  short DEFAULT_REVERB = 0;
	constexpr static  short DEFAULT_PHASER = 0;
	constexpr static  short DEFAULT_TREMOLO = 0;
	
	int channelId;
	short bank;
	short program;
	short volume;
	short balance;
	short chorus;
	short reverb;
	short phaser;
	short tremolo;
	std::string name;
	std::vector<TGChannelParameter*> parameters;
	
	TGChannel() {
		this->channelId = 0;
		this->bank = DEFAULT_BANK;
		this->program = DEFAULT_PROGRAM;
		this->volume = DEFAULT_VOLUME;
		this->balance = DEFAULT_BALANCE;
		this->chorus = DEFAULT_CHORUS;
		this->reverb = DEFAULT_REVERB;
		this->phaser = DEFAULT_PHASER;
		this->tremolo = DEFAULT_TREMOLO;
	}
	
	int getChannelId()const {
		return this->channelId;
	}
	
	void setChannelId(int channelId) {
		this->channelId = channelId;
	}
	
	short getBalance()const {
		return this->balance;
	}
	
	void setBalance(short balance) {
		this->balance = balance;
	}
	
	short getChorus()const {
		return this->chorus;
	}
	
	void setChorus(short chorus) {
		this->chorus = chorus;
	}
	
	short getBank()const {
		return this->bank;
	}
	
	void setBank(short bank) {
		this->bank = bank;
	}
	
	short getProgram()const {
		return this->program;
	}
	
	void setProgram(short program) {
		this->program = program;
	}
	
	short getPhaser()const {
		return this->phaser;
	}
	
	void setPhaser(short phaser) {
		this->phaser = phaser;
	}
	
	short getReverb()const {
		return this->reverb;
	}
	
	void setReverb(short reverb) {
		this->reverb = reverb;
	}
	
	short getTremolo()const {
		return this->tremolo;
	}
	
	void setTremolo(short tremolo) {
		this->tremolo = tremolo;
	}
	
	short getVolume()const {
        if(TracksVolume==1){ // scale{
            //scale up from 1/4
            short volume = 32 + ((this->volume/4) * 3) - 1;
            return volume;
        }
        if(TracksVolume>100)
    		return (short)TracksVolume;
		return this->volume;
	}
	
	void setVolume(short volume) {
  		this->volume = volume;
	}
	
	std::string getName()const {
		return this->name;
	}
	
	void setName(const std::string& name) {
		this->name = name;
	}
	
	std::vector<TGChannelParameter*>& getParameters() {
		return this->parameters;
	}
	
	void addParameter(TGChannelParameter *parameter){
		this->parameters.push_back(parameter);
	}
	
	void addParameter(int index, TGChannelParameter* parameter){
		v_insert(parameters,index,parameter);
	}
	
	TGChannelParameter* getParameter(int index){
		if(index >= 0 && index < countParameters()){
			return this->parameters.at(index);
		}
		return nullptr;
	}
	
	void removeParameter(int index){
		this->parameters.erase(this->parameters.begin()+index);
	}
	
	void removeParameters(){
		this->parameters.clear();
	}
	
	int countParameters(){
		return this->parameters.size();
	}
	
	bool isPercussionChannel(){
		return (this->getBank() == DEFAULT_PERCUSSION_BANK);
	}
	
	TGChannel* clone(){
		TGChannel* tgChannel = new TGChannel();
		tgChannel->copyFrom(this);
		return tgChannel; 
	}
	
	void copyFrom(TGChannel* channel){
		this->setChannelId(channel->getChannelId());
		this->setBank(channel->getBank());
		this->setProgram(channel->getProgram());
		this->setVolume(channel->getVolume());
		this->setBalance(channel->getBalance());
		this->setChorus(channel->getChorus());
		this->setReverb(channel->getReverb());
		this->setPhaser(channel->getPhaser());
		this->setTremolo(channel->getTremolo());
		this->setName(channel->getName());
		
		this->removeParameters();
		for(int i = 0; i < channel->countParameters(); i ++){
			this->addParameter(channel->getParameter(i)->clone());
		}
	}
};


#endif // TGCHANNEL_H
