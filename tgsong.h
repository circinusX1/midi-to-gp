#ifndef TGSONG_H
#define TGSONG_H

#include <string>
#include "tgtrack.h"
#include "tgmeasureheader.h"
#include "tgchannel.h"

class TGSong
{
	
private:
	std::string name;
	std::string artist;
	std::string album;
	std::string author;
	std::string date;
	std::string copyright;
	std::string writer;
	std::string transcriber;
	std::string comments;
	std::vector<TGTrack*> tracks;
	std::vector<TGMeasureHeader*> measureHeaders;
	std::vector<TGChannel*> channels;
	
public:
	TGSong();
	virtual ~TGSong(){};
	
	std::string& getName();
	void setName(const  char* name);
	std::string& getAlbum();
	void setAlbum(const  char* album);
	std::string& getAuthor();
	void setAuthor(const  char* author);
	std::string& getArtist();
	void setArtist(const  char* artist);
	std::string& getDate();
	void setDate(const  char* date);
	std::string& getCopyright();
	void setCopyright(const  char* copyright);
	std::string& getWriter();
	void setWriter(const  char* writer);
	std::string& getTranscriber();
	void setTranscriber(const  char* transcriber);
	std::string& getComments();
	void setComments(const char* comments);
	int countMeasureHeaders();
	void addMeasureHeader(TGMeasureHeader *measureHeader);
	void addMeasureHeader(int index, TGMeasureHeader *measureHeader);
	void removeMeasureHeader(int index);
	void removeMeasureHeader(TGMeasureHeader *measureHeader);
	TGMeasureHeader *getMeasureHeader(int index);
	std::vector<TGMeasureHeader*>& getMeasureHeaders();
	int countTracks();
	void addTrack(TGTrack *track);
	void addTrack(int index, TGTrack *track);
	void moveTrack(int index, TGTrack *track);
	void removeTrack(TGTrack *track);
	TGTrack *getTrack(int index);
	std::vector<TGTrack*>& getTracks();
	int countChannels();
	void addChannel(TGChannel *channel);
	void addChannel(int index, TGChannel *channel);
	void moveChannel(int index, TGChannel *channel);
	void removeChannel(TGChannel *channel);
	TGChannel *getChannel(int index);
	std::vector<TGChannel*>& getChannels();
	bool isEmpty();
	void clear();
};


#endif // TGSONG_H
