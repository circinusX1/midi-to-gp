
#include "tgstring.h"
#include "temps.h"
#include "tgsong.h"

TGSong::TGSong()
{
}

std::string& TGSong::getName()
{
	return this->name;
}

void TGSong::setName(const char* name)
{
	this->name = name;
}

std::string& TGSong::getAlbum()
{
	return this->album;
}

void TGSong::setAlbum(const  char* album)
{
	this->album = album;
}

std::string& TGSong::getAuthor()
{
	return this->author;
}

void TGSong::setAuthor(const  char*  author)
{
	this->author = author;
}

std::string& TGSong::getArtist()
{
	return this->artist;
}

void TGSong::setArtist(const  char* artist)
{
	this->artist = artist;
}

std::string& TGSong::getDate()
{
	return this->date;
}

void TGSong::setDate(const  char* date)
{
	this->date = date;
}

std::string& TGSong::getCopyright()
{
	return this->copyright;
}

void TGSong::setCopyright(const  char* copyright)
{
	this->copyright = copyright;
}

std::string& TGSong::getWriter()
{
	return this->writer;
}

void TGSong::setWriter(const  char* writer)
{
	this->writer = writer;
}

std::string& TGSong::getTranscriber()
{
	return this->transcriber;
}

void TGSong::setTranscriber(const  char* transcriber)
{
	this->transcriber = transcriber;
}

std::string& TGSong::getComments()
{
	return this->comments;
}

void TGSong::setComments(const  char* comments)
{
	this->comments = comments;
}

int TGSong::countMeasureHeaders()
{
	return this->measureHeaders.size();
}

void TGSong::addMeasureHeader(TGMeasureHeader *measureHeader)
{
	this->measureHeaders.push_back(measureHeader);
}

void TGSong::addMeasureHeader(int index, TGMeasureHeader *measureHeader)
{
	measureHeader->setSong(this);
	if(index >=measureHeaders.size())
		this->measureHeaders.resize(index+1);
	else
		delete measureHeaders[index];
	this->measureHeaders[index]=measureHeader;
}

void TGSong::removeMeasureHeader(int index)
{
	this->measureHeaders.erase(this->measureHeaders.begin() + index);
}

void TGSong::removeMeasureHeader(TGMeasureHeader *measureHeader)
{
	this->measureHeaders.erase(ITER(measureHeaders,measureHeader));
}

TGMeasureHeader *TGSong::getMeasureHeader(int index)
{
	return this->measureHeaders[index];
}

std::vector<TGMeasureHeader*>& TGSong::getMeasureHeaders()
{
	return this->measureHeaders;
}

int TGSong::countTracks()
{
	return this->tracks.size();
}

void TGSong::addTrack(TGTrack *track)
{
	track->song = this;
	this->tracks.push_back(track);
}

void TGSong::addTrack(int index, TGTrack *track)
{
	track->setSong(this);
	if(index >= tracks.size())
		tracks.resize(index+1);
	else
		delete tracks[index];
	this->tracks[index]=track;
}

void TGSong::moveTrack(int index, TGTrack *track)
{
	this->tracks.erase(ITER(tracks,track));
	delete track;
	addTrack(index,track);
}

void TGSong::removeTrack(TGTrack *track)
{
	this->tracks.erase(ITER(tracks,track));
	delete track;
}

TGTrack *TGSong::getTrack(int index)
{
	return this->tracks[index];
}

std::vector<TGTrack*>& TGSong::getTracks()
{
	return this->tracks;
}

int TGSong::countChannels()
{
	return this->channels.size();
}

void TGSong::addChannel(TGChannel *channel)
{
	this->channels.push_back(channel);
}

void TGSong::addChannel(int index, TGChannel *channel)
{
	if(index >= this->channels.size())
		this->channels.resize(index+1);
	else
		delete this->channels[index];
	this->channels[index] = channel;
}

void TGSong::moveChannel(int index, TGChannel *channel)
{
	this->channels.erase(ITER(channels,channel));
	delete channel;
	addChannel(index,channel);
}

void TGSong::removeChannel(TGChannel *channel)
{
	this->channels.erase(ITER(channels,channel));
}

TGChannel *TGSong::getChannel(int index)
{
	return this->channels[index];
}

std::vector<TGChannel*>& TGSong::getChannels()
{
	return this->channels;
}

bool TGSong::isEmpty()
{
	return (countMeasureHeaders() == 0 || countTracks() == 0);
}

void TGSong::clear()
{
	for(auto& a : tracks)
	{
		delete a;
	}
	this->tracks.clear();
	
	for(auto& a : channels)
	{
		delete a;
	}
	this->channels.clear();
	
	for(auto& a : measureHeaders)
	{
		delete a;
	}
	this->measureHeaders.clear();
}

