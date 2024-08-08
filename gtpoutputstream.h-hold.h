#ifndef GTPOUTPUTSTREAM_H
#define GTPOUTPUTSTREAM_H

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "tgsong.h"
#include "midievent.h"
#include "tgstring.h"
#include "tgtrack.h"
#include "tgsongmanager.h"
#include "gmchannelrouter.h"

class GTPOutputStream 
{
public:	
	constexpr static   char* DEFAULT_TG_CHARSET = "UTF-8";
	constexpr static   char* DEFAULT_VERSION_CHARSET = "UTF-8";
	
	//GMChannelRouter channelRouter;
	std::ofstream	outputStream;
	std::string		_filename;
	
	GTPOutputStream(const char* file):_filename(file){
	}
	virtual ~GTPOutputStream(){};
	
	virtual void writeSong(const TGSong* song);
	
	
	void write(const TGSong* song){
		this->writeSong(song);
	}
	
	void skipBytes(int count) {
		uint8_t by=0;
		for(int i = 0;i < count;i++){
			this->outputStream.write((char*)&by,sizeof(uint8_t));
		}
	}
	
	void writeByte(uint8_t v) {
		this->outputStream.write((char*)&v, sizeof(uint8_t));
	}
	
	void writeUnsignedByte(int v) {
		this->outputStream.write((char*)&v, sizeof(uint8_t));
	}
	
	void writeBytes(bytes& v) {
		for(const auto& b : v)
			this->outputStream.write((char*)&b, sizeof(uint8_t));
	}
	
	void writeBoolean(bool v) {
		this->outputStream.write((char*)&v, sizeof(uint8_t));
	}
	
	void writeInt(int v) 
	{
		this->outputStream.write(__builtin_bswap32(v));
	}
	
	void writeString(std::string& bytes, int maximumLength) 
	{
		int length = (maximumLength == 0 || maximumLength > bytes.size() ? 
						  bytes.size() : maximumLength );
		for(int i = 0 ; i < length; i ++){
			writeByte(bytes[i]);
		}
	}
	
	void writeStringInteger(std::string& tring) {
		this->writeInt( tring.length() );
		this->writeString( tring , 0 );
	}
	
	void writeStringByte(std::string& tring, int size) 
	{
		this->writeByte( (uint8_t)( size == 0 || size > tring.length() ? 
										tring.length() : size ));
		this->writeString( tring , size );
		this->skipBytes( size - tring.length() );
	}
	
	void writeStringByteSizeOfInteger(std::string& tring) 
	{
		this->writeInt( (tring.length() + 1) );
		this->writeStringByte(tring, tring.length());
	}
	
	void close(){
		this->outputStream.flush();
		this->outputStream.close();
	}
	
	size_t createWritableStrings(TGTrack* track, 
								 std::vector<TGString*>& writableStrings) 
	{
		int minimum = 4;
		int maximum = 7;
		int count = track->stringCount();
		if( count >= minimum && count <= maximum ) {
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
		for(auto& string : strings) {
			if( string->number >= minimum && string->number <= maximum ) {
				for(const auto& writableString : writableStrings) {
					if( writableString->number == string->number ) {
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
		
		GMChannelRouterConfigurator gmChannelRouterConfigurator = new GMChannelRouterConfigurator(this->channelRouter);
		gmChannelRouterConfigurator.configureRouter(song.getChannels());
	}
	
	GMChannelRoute getChannelRoute(int channelId){
		GMChannelRoute gmChannelRoute = this->channelRouter.getRoute(channelId);
		if( gmChannelRoute == null || gmChannelRoute.getChannel1() < 0  || gmChannelRoute.getChannel2() < 0 ){
			Integer defaultChannel = (gmChannelRoute != null && gmChannelRoute.getChannel1() >= 0 ? gmChannelRoute.getChannel1() : 15);
			
			gmChannelRoute = new GMChannelRoute(channelId);
			gmChannelRoute.setChannel1(defaultChannel);
			gmChannelRoute.setChannel2(defaultChannel);
		}
		
		return gmChannelRoute;
	}
	
	bool isPercussionChannel( TGSong* song, int channelId )
	{
		for(auto& channel :song.getChannels())
		{
			if( channel->getChannelId() == channelId ){
				return channel->isPercussionChannel();
			}
		}
		return false;
	}
};

#endif // GTPOUTPUTSTREAM_H
