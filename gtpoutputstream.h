#ifndef GTPOUTPUTSTREAM_H
#define GTPOUTPUTSTREAM_H

#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <iostream>
#include <fstream>
#include <string>
#include "tgsong.h"
#include "midievent.h"
#include "tgstring.h"
#include "tgtrack.h"
#include "tgsongmanager.h"
#include "gmchannelrouter.h"
#include "gmchannelrouterconfigurator.h"

class GTPOutputStream 
{
public:	
	const static  std::string DEFAULT_TG_CHARSET;
	const static  std::string DEFAULT_VERSION_CHARSET;
	
	GMChannelRouter* channelRouter=nullptr;
	std::ofstream	gpout;
	std::string		_filename;
	
	GTPOutputStream(const char* file);
	virtual ~GTPOutputStream();
	
	virtual void writeSong(TGSong* song)=0;
	
	void write(TGSong* song){
		this->writeSong(song);
		_reopen();
	}
	
	void skipBytes(int count) {
		uint8_t by=0;
		for(int i = 0;i < count;i++){
			this->gpout.write((char*)&by,sizeof(uint8_t));
		}
		_reopen();
	}
	
	void writeByte(uint8_t v) {
		this->gpout.write((char*)&v, sizeof(uint8_t));
	}
	
	void writeUnsignedByte(int v) {
		this->gpout.write((char*)&v, sizeof(uint8_t));
		_reopen();
	}
	
	void writeBytes(bytes& v) {
		for(const auto& b : v)
			this->gpout.write((char*)&b, sizeof(uint8_t));
		_reopen();
	}
	
	

	void writeBoolean(bool v) {
		this->gpout.write((char*)&v, sizeof(uint8_t));
	}
	
	void writeInt(int v) 
	{
		this->gpout.write((char*)&v,sizeof(uint32_t));
		_reopen();
	}
	
	void writeString(const std::string& bytes, int maximumLength) 
	{
		int length = (maximumLength == 0 || 
					  maximumLength > (int)bytes.size() ? 
						  bytes.size() : maximumLength );
		for(int i = 0 ; i < length; i ++){
			writeByte(bytes[i]);
		}
		_reopen();
	}
	
	void writeStringInteger(const std::string& tring) {
		this->writeInt( tring.length()==0 ? 0: tring.length());
		if(tring.empty()){
			writeByte(0);
		}else{
			this->writeString( tring , 1 );
		}
		_reopen();
	}
	
	
	void writeStringByte(const std::string& tring, int size) 
	{
		int len = size;
		if(size > (int)tring.length())
		{
			size = tring.length();
		}
		else if(!tring.empty() && size==0)
		{
			size = tring.length();
			if(len==0)
				len=size;
		}
		
		this->writeByte(size);
		if(len==0){
			this->writeByte(0);
		}
		else{
			this->writeString( tring , size );
		}
		_reopen();
		this->skipBytes( len - tring.length() );
		_reopen();
	}
	
	void writeStringByteSizeOfInteger(const std::string& tring, 
									  int adjust=1) 
	{
		size_t sl = tring.length();
		this->writeInt( sl ? sl + adjust : 1);
		if(!tring.empty())
			this->writeStringByte(tring, sl);
		else
			this->writeByte(0);
		_reopen();
	}
	
	void close(){
		this->gpout.flush();
		this->gpout.close();
	}
	
	size_t createWritableStrings(TGTrack* track, 
								 std::vector<TGString*>& writableStrings) 
	{
		int minimum = 4;
		int maximum = 7;
		int count = track->stringCount();
		if( count >= minimum && count <= maximum ) {
			writableStrings = track->strings;
			return track->strings.size();
		}
		int writableCount = count;
		if( writableCount < minimum ) {
			writableCount = minimum;
		}
		if( writableCount > maximum ) {
			writableCount = maximum;
		}
		std::vector<TGString*>& strings = track->strings;
		createDefaultStrings(track, writableCount, writableStrings);
		for(auto& string : strings)
		{
			if( string->number >= minimum && string->number <= maximum ) 
			{
				for(const auto& writableString : writableStrings) 
				{
					if( writableString->number == string->number ) 
					{
						writableString->value = (string->value);
					}
				}
			}
		}
		return writableStrings.size();
	}
	
	size_t createDefaultStrings(TGTrack* track, int count, 
								std::vector<TGString*>& sv) 
	{
		if( this->isPercussionChannel(track->getSong(), track->getChannelId()) ) {
			return TGSongManager::createPercussionStrings(count, sv);
		}
		return TGSongManager::createDefaultInstrumentStrings(count, sv);
	}
	
	void configureChannelRouter( TGSong* song )
	{
		this->channelRouter = new GMChannelRouter();
		
		GMChannelRouterConfigurator* gmChannelRouterConfigurator = 
				new GMChannelRouterConfigurator(this->channelRouter);
		gmChannelRouterConfigurator->configureRouter(song->getChannels());
	}
	
	GMChannelRoute* getChannelRoute(int channelId)
	{
		GMChannelRoute* gmChannelRoute = this->channelRouter->getRoute(channelId);
		if( gmChannelRoute == nullptr || 
				gmChannelRoute->getChannel1() < 0  || 
				gmChannelRoute->getChannel2() < 0 )
		{
			int defaultChannel = (gmChannelRoute != nullptr &&
					gmChannelRoute->getChannel1() >= 0 ? 
						gmChannelRoute->getChannel1() : 15);
			
			gmChannelRoute = new GMChannelRoute(channelId);
			gmChannelRoute->setChannel1(defaultChannel);
			gmChannelRoute->setChannel2(defaultChannel);
		}
		
		return gmChannelRoute;
	}
	
	bool isPercussionChannel( TGSong* song, int channelId )
	{
		for(auto& channel : song->getChannels())
		{
			if( channel->getChannelId() == channelId ){
				return channel->isPercussionChannel();
			}
		}
		return false;
	}
	
	void _reopen();
};

#endif // GTPOUTPUTSTREAM_H
