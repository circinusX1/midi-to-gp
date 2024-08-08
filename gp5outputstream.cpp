
#include <signal.h>
#include <iostream>
#include <string.h>
#include <ctime>
#include <iostream>
#include <libgen.h>
#include "gp5outputstream.h"


static const char* Instruments[]={"acousticgrandpiano",
                                    "brightacousticpiano",
                                    "electricgrandpiano",
                                    "honkytonkpiano",
                                    "electricpiano1",
                                    "electricpiano2",
                                    "harpsichord",
                                    "clavinet",
                                    "celesta",
                                    "glockenspiel",
                                    "musicbox",
                                    "vibraphone",
                                    "marimba",
                                    "xylophone",
                                    "tubularbells",
                                    "dulcimer",
                                    "drawbarorgan",
                                    "percussiveorgan",
                                    "rockorgan",
                                    "churchorgan",
                                    "reedorgan",
                                    "accordion",
                                    "harmonica",
                                    "tangoaccordion",
                                    "acousticguitarnylon",
                                    "acousticguitarsteel",
                                    "electricguitarjazz",
                                    "electricguitarclean",
                                    "electricguitarmuted",
                                    "overdrivenguitar",
                                    "distortionguitar",
                                    "guitarharmonics",
                                    "acousticbass",
                                    "electricbassfinger",
                                    "electricbasspick",
                                    "fretlessbass",
                                    "slapbass1",
                                    "slapbass2",
                                    "synthbass1",
                                    "synthbass2",
                                    "violin",
                                    "viola",
                                    "cello",
                                    "contrabass",
                                    "tremolostrings",
                                    "pizzicatostrings",
                                    "orchestralharp",
                                    "timpani",
                                    "stringensemble1",
                                    "stringensemble2",
                                    "synthstrings1",
                                    "synthstrings2",
                                    "choiraahs",
                                    "voiceoohs",
                                    "synthvoice",
                                    "orchestrahit",
                                    "trumpet",
                                    "trombone",
                                    "tuba",
                                    "mutedtrumpet",
                                    "frenchhorn",
                                    "brasssection",
                                    "synthbrass1",
                                    "synthbrass2",
                                    "sopranosax",
                                    "altosax",
                                    "tenorsax",
                                    "baritonesax",
                                    "oboe",
                                    "englishhorn",
                                    "bassoon",
                                    "clarinet",
                                    "piccolo",
                                    "flute",
                                    "recorder",
                                    "panflute",
                                    "blownbottle",
                                    "shakuhachi",
                                    "whistle",
                                    "ocarina",
                                    "lead1square",
                                    "lead2sawtooth",
                                    "lead3calliope",
                                    "lead4chiff",
                                    "lead5charang",
                                    "lead6voice",
                                    "lead7fifths",
                                    "lead8bassandlead",
                                    "pad1newage",
                                    "pad2warm",
                                    "pad3polysynth",
                                    "pad4choir",
                                    "pad5bowed",
                                    "pad6metallic",
                                    "pad7halo",
                                    "pad8sweep",
                                    "fx1rain",
                                    "fx2soundtrack",
                                    "fx3crystal",
                                    "fx4atmosphere",
                                    "fx5brightness",
                                    "fx6goblins",
                                    "fx7echoes",
                                    "fx8scifi",
                                    "sitar",
                                    "banjo",
                                    "shamisen",
                                    "koto",
                                    "kalimba",
                                    "bagpipe",
                                    "fiddle",
                                    "shanai",
                                    "tinklebell",
                                    "agogo",
                                    "steeldrums",
                                    "woodblock",
                                    "taikodrum",
                                    "melodictom",
                                    "synthdrum",
                                    "reversecymbal",
                                    "guitarfretnoise",
                                    "breathnoise",
                                    "seashore",
                                    "birdtweet",
                                    "telephonering",
                                    "helicopter",
                                    "applause",
                                    "gunshot","---------"};
                                    



const std::string _sempty="";


const std::string GP5OutputStream::GP5_VERSION = "FICHIER GUITAR PRO v5.00";
const std::vector<std::string> GP5OutputStream::PAGE_SETUP_LINES = {
	"%TITLE%",
	"%SUBTITLE%",
	"%ARTIST%",
	"%ALBUM%",
	"Words by %WORDS%",
	"Music by %MUSIC%",
	"Words & Music by %WORDSMUSIC%",
	"Copyright %COPYRIGHT%",
	"All Rights Reserved - International Copyright Secured",
	"Page %N%/%P%",
	"Moderate",
};

GP5OutputStream::GP5OutputStream(const char* file) : GTPOutputStream(file)
{
}

GP5OutputStream::~GP5OutputStream()
{
	
}
/*
const char* *GP5OutputStream::getFileFormat()
{
	return ("Guitar Pro 5", "audio/x-gtp", std::vector<std::string>{"gp5"});
}
*/
static std::string ltime()
{
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];
    
    time (&rawtime);
    timeinfo = localtime(&rawtime);
    
    strftime(buffer,sizeof(buffer),"%d-%m-%Y",timeinfo);
    std::string str(buffer);
    return str;
}

void GP5OutputStream::writeSong(TGSong *song)
{
	char dir[256];
	char file[256];
	char path[256];
	
	if (song == nullptr)
	{
		return;
	}
	gpout.open(_filename.c_str());
	if(gpout.is_open())
	{
		strcpy(path,_filename.c_str());
		strcpy(dir,dirname(path));
	
		std::string sp = _filename;
		size_t ls = sp.find_last_of("/");
		size_t dp = sp.find_last_of(".");
		sp = sp.substr(ls+1,dp-ls-1);
		strcpy(file,sp.c_str());
		
		sp = dir;
		ls = sp.find_last_of("/");
		sp = sp.substr(ls+1);
		strcpy(dir,sp.c_str());
		
		
		std::cout << "Name: " << file << "\n";
        std::cout << "Author: " << dir << "\n";
        std::cout << "Copyright: " << "converted by ghitara.com" << "\n";

		
		song->setName(file);
		song->setAlbum(file);
		song->setAuthor(dir);
		song->setArtist(dir);
		song->setDate(ltime().c_str());
		song->setCopyright("converted by ghitara.com");
		song->setWriter("gmidigp v.1.0");
		song->setTranscriber("unknown");
		song->setComments("converted from midi at ghitara.com");
		
		
		configureChannelRouter(song);
		TGMeasureHeader *header = song->getMeasureHeader(0);
		writeStringByte(GP5_VERSION, 30);
		writeInfo(song);
		writeLyrics(song);
		writePageSetup();
		writeInt(header->getTempo().getValue());
		writeInt(0);
		writeByte((0));
		
		writeChannels(song);
		for (int i = 0; i < 42; i++)
		{
			writeByte((0xff));
		}
		
		writeInt(song->countMeasureHeaders());
		int trcks = song->countTracks();
		std::cout << "Writing " << trcks << " tracks\n";
		writeInt(song->countTracks());
		writeMeasureHeaders(song);
		writeTracks(song);
		skipBytes(2);
		writeMeasures(song, &header->getTempo());
		close();
	}
}

void GP5OutputStream::writeInfo(TGSong *song)
{
	_reopen();
	writeStringByteSizeOfInteger(song->getName());
	writeStringByteSizeOfInteger(_sempty);
	writeStringByteSizeOfInteger(song->getArtist());
	writeStringByteSizeOfInteger(song->getAlbum());
	writeStringByteSizeOfInteger(song->getAuthor());
	writeStringByteSizeOfInteger(_sempty);
	writeStringByteSizeOfInteger(song->getCopyright());
	writeStringByteSizeOfInteger(song->getWriter());
	writeStringByteSizeOfInteger(_sempty);
	
	std::vector<std::string> comments = toCommentLines(song->getComments());
	
	writeInt(comments.size());
	
	for (int i = 0; i < comments.size(); i++)
	{
		writeStringByteSizeOfInteger(comments[i]);
	}
}

void GP5OutputStream::writeLyrics(TGSong *song)
{
	TGTrack *lyricTrack = nullptr;
	for(auto& track : song->getTracks())
	{
		if (track->getLyrics() && !track->getLyrics()->isEmpty())
		{
			lyricTrack = track;
			break;
		}
	}
	writeInt((lyricTrack == nullptr)?0:lyricTrack->getNumber());
	writeInt((lyricTrack == nullptr)?0:lyricTrack->
									 getLyrics()->getFrom());
	writeStringInteger((lyricTrack == nullptr)?
						   _sempty:
						   lyricTrack->getLyrics()->getLyrics());
	
	for (int i = 0; i < 4; i++) // TODO was 4
	{
		writeInt((lyricTrack == nullptr)?0:1);
		//writeStringInteger(_sempty);
	}
	writeStringInteger(_sempty);
	writeStringInteger(_sempty);
	writeStringInteger(_sempty);
	
}


void GP5OutputStream::writePageSetup()
{
	writeInt(210); // Page width
	writeInt(297); // Page height
	writeInt(10); // Margin left
	writeInt(10); // Margin right
	writeInt(15); // Margin top
	writeInt(10); // Margin bottom
	writeInt(100); // Score size percent
	//gpout.close();
	
	writeByte((0xff)); // View flags
	writeByte((0x01)); // View flags
	
	for (int i = 0; i < PAGE_SETUP_LINES.size(); i++)
	{
		writeInt((PAGE_SETUP_LINES[i].length() + 1));
		_reopen();
		writeStringByte(PAGE_SETUP_LINES[i],0);
		_reopen();
	}
}

void GP5OutputStream::writeChannels(TGSong *song)
{
	std::vector<TGChannel*> channels = makeChannels(song);
	for (int i = 0; i < channels.size(); i++)
	{
		int ip = channels[i]->getProgram();
		writeInt(ip);
		writeByte(toChannelByte(channels[i]->getVolume()));
		writeByte(toChannelByte(channels[i]->getBalance()));
		writeByte(toChannelByte(channels[i]->getChorus()));
		writeByte(toChannelByte(channels[i]->getReverb()));
		writeByte(toChannelByte(channels[i]->getPhaser()));
		writeByte(toChannelByte(channels[i]->getTremolo()));
		writeByte(0);writeByte(0);
	}
}

void GP5OutputStream::writeMeasureHeaders(TGSong *song)
{
	TGTimeSignature *timeSignature =  new TGTimeSignature();
	if (song->countMeasureHeaders() > 0)
	{
		for (int i = 0; i < song->countMeasureHeaders(); i++)
		{
			if (i > 0)
			{
				skipBytes(1);
			}
			TGMeasureHeader *measure = song->getMeasureHeader(i);
			writeMeasureHeader(measure, timeSignature);
			
			timeSignature->
					setNumerator(measure->getTimeSignature().
								 getNumerator());
			timeSignature->getDenominator().
					setValue(measure->getTimeSignature().
							 getDenominator().getValue());
		}
	}
}

void GP5OutputStream::writeMeasureHeader(TGMeasureHeader *measure, 
										 TGTimeSignature *timeSignature)
{
	int flags = 0;
	if (measure->getNumber() == 1)
	{
		flags |= 0x40;
	}
	if (measure->getNumber() == 1 || 
			!(measure->getTimeSignature()==(*timeSignature)))
	{
		flags |= 0x01;
		flags |= 0x02;
	}
	if (measure->isRepeatOpen())
	{
		flags |= 0x04;
	}
	if (measure->getRepeatClose() > 0)
	{
		flags |= 0x08;
	}
	if (measure->getRepeatAlternative() > 0)
	{
		flags |= 0x10;
	}
	if (measure->hasMarker())
	{
		flags |= 0x20;
	}
	writeUnsignedByte(flags);
	
	if ((flags & 0x01) != 0)
	{
		writeByte(
					(measure->getTimeSignature().getNumerator()));
	}
	if ((flags & 0x02) != 0)
	{
		writeByte(
					(measure->getTimeSignature().getDenominator().getValue()));
	}
	if ((flags & 0x08) != 0)
	{
		writeByte((measure->getRepeatClose() + 1));
	}
	if ((flags & 0x20) != 0)
	{
		writeMarker(&measure->getMarker());
	}
	if ((flags & 0x10) != 0)
	{
		writeByte((measure->getRepeatAlternative()));
	}
	if ((flags & 0x40) != 0)
	{
		skipBytes(2);
	}
	if ((flags & 0x01) != 0)
	{
		TGTimeSignature tgs =measure->getTimeSignature();
		bytes lv = makeBeamEighthNoteBytes(tgs);
		writeBytes(lv);
	}
	if ((flags & 0x10) == 0)
	{
		writeByte((0));
	}
	if (measure->getTripletFeel() == TGMeasureHeader::TRIPLET_FEEL_NONE)
	{
		writeByte((0));
	}
	else if (measure->getTripletFeel() == TGMeasureHeader::TRIPLET_FEEL_EIGHTH)
	{
		writeByte((1));
	}
	else if (measure->getTripletFeel() == TGMeasureHeader::TRIPLET_FEEL_SIXTEENTH)
	{
		writeByte((2));
	}
}

void GP5OutputStream::writeTracks(TGSong *song)
{
	for (int i = 0; i < song->countTracks(); i++)
	{
		TGTrack *track = song->getTrack(i);
		TGChannel* pc  = song->getChannel(track->channelId);
		if(pc)
		{
			if(pc->program <127)
			{
				std::cout << "Track:" <<
							track->getNumber() << ":" <<
							Instruments[pc->program] <<"\n";
			}
		}
		writeTrack(track);
	}
}

void GP5OutputStream::writeTrack(TGTrack *track)
{
	GMChannelRoute *channel = getChannelRoute(track->getChannelId());
	std::vector<TGString*> strings; 
	this->createWritableStrings(track, strings);
	
	int flags = 0;
	if (isPercussionChannel(track->getSong(),track->getChannelId()))
	{
		flags |= 0x01;
	}
	writeUnsignedByte(flags);
	writeUnsignedByte((8 | flags));
	writeStringByte(track->getName(), 40);
	writeInt(strings.size());
	for (int i = 0; i < 7; i++)
	{
		int value = 0;
		if (strings.size() > i)
		{
			value = strings[i]->value;
		}
		writeInt(value);
	}
	writeInt(1);
	writeInt(channel->getChannel1() + 1);
	writeInt(channel->getChannel2() + 1);
	writeInt(24);
	writeInt(track->getOffset());
	writeColor(&track->color);
	bytes	bys={67, 1, 0, 0, 0, 0, 0, 0, 
				 0, 0, 0, 0, 0, 100, 0, 
				 0, 0, 1, 2, 3, 4, 5, 6, 7, 
				 8, 9, 10, -1, 3, -1, -1, -1, 
				 -1, -1, -1, -1, -1, -1, -1, 
				 -1, -1, -1, -1, -1};
	writeBytes(bys);
}

void GP5OutputStream::writeMeasures(TGSong *song, TGTempo *tempo)
{
	for (int i = 0; i < song->countMeasureHeaders(); i++)
	{
		TGMeasureHeader *header = song->getMeasureHeader(i);
		for (int j = 0; j < song->countTracks(); j++)
		{
			TGTrack *track = song->getTrack(j);
			TGMeasure *measure = track->getMeasure(i);
			writeMeasure(measure, 
						 (header->getTempo().getValue() != tempo->getValue()));
			skipBytes(1);
		}
		*tempo = header->getTempo();
	}
}

void GP5OutputStream::writeMeasure(TGMeasure *measure, 
								   bool changeTempo)
{
	for (int v = 0; v < 2 ; v++)
	{
		std::vector<TGVoice*> voices;
		for (int m = 0; m < measure->countBeats(); m++)
		{
			TGBeat *beat = measure->getBeat(m);
			if (v < beat->countVoices())
			{
				TGVoice *voice = beat->getVoice(v);
				if (!voice->isEmpty())
				{
					voices.push_back(voice);
				}
			}
		}
		if (voices.size() > 0)
		{
			writeInt(voices.size());
			for (int i = 0; i < voices.size() ; i++)
			{
				TGVoice *voice = voices[i];
				assert(voice->getBeat());
				writeBeat(voice, voice->getBeat(), 
						  measure, (changeTempo && i == 0));
			}
		}
		else
		{
			// Fill empty voices.
			int count = measure->getTimeSignature().getNumerator();
			TGBeat *beat = new TGBeat();
			if (v < beat->countVoices())
			{
				TGVoice *voice = beat->getVoice(v);
				voice->getDuration().
						setValue(
							measure->getTimeSignature().
							getDenominator().getValue());
				voice->setEmpty(true);
				writeInt(count);
				for (int i = 0; i < count ; i++)
				{
					assert(voice->getBeat());
					writeBeat(voice, voice->getBeat(), 
							  measure, (changeTempo && i == 0));
				}
			}
		}
	}
}

void GP5OutputStream::writeBeat(TGVoice *voice, 
								TGBeat *beat, 
								TGMeasure *measure, 
								bool changeTempo)
{
	TGDuration& duration = voice->getDuration();
	TGNoteEffect *effect = new TGNoteEffect();
	for (int i = 0; i < voice->countNotes(); i++)
	{
		TGNote *playedNote = voice->getNote(i);
		
		if(playedNote->getEffect()){	
			if (playedNote->getEffect()->isFadeIn())
			{
				effect->setFadeIn(true);
			}
			if (playedNote->getEffect()->isTremoloBar())
			{
				effect->setTremoloBar(playedNote->getEffect()->getTremoloBar());
			}
			if (playedNote->getEffect()->isTapping())
			{
				effect->setTapping(true);
			}
			if (playedNote->getEffect()->isSlapping())
			{
				effect->setSlapping(true);
			}
			if (playedNote->getEffect()->isPopping())
			{
				effect->setPopping(true);
			}
		}
	}
	
	int flags = 0;
	if (duration.isDotted() || duration.isDoubleDotted())
	{
		flags |= 0x01;
	}
	if (voice->getIndex() == 0 && beat->isChordBeat())
	{
		flags |= 0x02;
	}
	if (voice->getIndex() == 0 && beat->isTextBeat())
	{
		flags |= 0x04;
	}
	if (beat->getStroke().getDirection() != TGStroke::STROKE_NONE)
	{
		flags |= 0x08;
	}
	else if (effect->isTremoloBar() || 
			 effect->isTapping() || 
			 effect->isSlapping() || 
			 effect->isPopping() || 
			 effect->isFadeIn())
	{
		flags |= 0x08;
	}
	if (changeTempo)
	{
		flags |= 0x10;
	}
	if (!(duration.getDivision()==TGDivisionType::NORMAL))
	{
		flags |= 0x20;
	}
	if (voice->isEmpty() || voice->isRestVoice())
	{
		flags |= 0x40;
	}
	writeUnsignedByte(flags);
	
	if ((flags & 0x40) != 0)
	{
		writeUnsignedByte((voice->isEmpty() ? 0x00 : 0x02));
		
	}
	writeByte(parseDuration(&duration));
	if ((flags & 0x20) != 0)
	{
		writeInt(duration.getDivision().getEnters());
	}
	
	if ((flags & 0x02) != 0)
	{
		writeChord(beat->getChord());
	}
	
	if ((flags & 0x04) != 0)
	{
		writeText(beat->getText());
	}
	
	if ((flags & 0x08) != 0)
	{
		writeBeatEffects(beat, effect);
	}
	
	if ((flags & 0x10) != 0)
	{
		writeMixChange(&measure->getTempo());
	}
	int stringFlags = 0;
	if (!voice->isRestVoice())
	{
		for (int i = 0; i < voice->countNotes(); i++)
		{
			TGNote *playedNote = voice->getNote(i);
			int string = (7 - playedNote->getString());
			stringFlags |= (1 << string);
		}
	}
	writeUnsignedByte(stringFlags);
	for (int i = 6; i >= 0; i--)
	{
		if ((stringFlags & (1 << i)) != 0)
		{
			for (int n = 0; n < voice->countNotes(); n++)
			{
				TGNote *playedNote = voice->getNote(n);
				if (playedNote->getString() == (6 - i + 1))
				{
					writeNote(playedNote);
					break;
				}
			}
		}
	}
	
	skipBytes(2);
}

void GP5OutputStream::writeNote(TGNote *note)
{
	//int flags = 0x20;
	int flags = (0x20 | 0x10);
	
	if (note->getEffect()->isVibrato() || 
			note->getEffect()->isBend() || 
			note->getEffect()->isSlide() || 
			note->getEffect()->isHammer() || 
			note->getEffect()->isLetRing() || 
			note->getEffect()->isPalmMute() || 
			note->getEffect()->isStaccato() || 
			note->getEffect()->isTrill() || 
			note->getEffect()->isGrace() || 
			note->getEffect()->isHarmonic() || 
			note->getEffect()->isTremoloPicking())
	{
		flags |= 0x08;
	}
	if (note->getEffect()->isGhostNote())
	{
		flags |= 0x04;
	}
	if (note->getEffect()->isHeavyAccentuatedNote())
	{
		flags |= 0x02;
	}
	if (note->getEffect()->isAccentuatedNote())
	{
		flags |= 0x40;
	}
	writeUnsignedByte(flags);
	
	if ((flags & 0x20) != 0)
	{
		int typeHeader = 0x01;
		if (note->isTiedNote())
		{
			typeHeader = 0x02;
		}
		else if (note->getEffect()->isDeadNote())
		{
			typeHeader = 0x03;
		}
		writeUnsignedByte(typeHeader);
	}
	if ((flags & 0x10) != 0)
	{
		writeByte((((note->getVelocity() - 
					 TGVelocities::MIN_VELOCITY) / 
					TGVelocities::VELOCITY_INCREMENT) + 1));
	}
	if ((flags & 0x20) != 0)
	{
		writeByte((note->getValue()));
	}
	skipBytes(1);
	if ((flags & 0x08) != 0)
	{
		writeNoteEffects(note->getEffect());
	}
}

signed char GP5OutputStream::parseDuration(TGDuration *duration)
{
	signed char value = 0;
	switch (duration->getValue())
	{
	case TGDuration::WHOLE:
		value = -2;
		break;
	case TGDuration::HALF:
		value = -1;
		break;
	case TGDuration::QUARTER:
		value = 0;
		break;
	case TGDuration::EIGHTH:
		value = 1;
		break;
	case TGDuration::SIXTEENTH:
		value = 2;
		break;
	case TGDuration::THIRTY_SECOND:
		value = 3;
		break;
	case TGDuration::SIXTY_FOURTH:
		value = 4;
		break;
	}
	return value;
}

void GP5OutputStream::writeChord(TGChord *chord)
{
	bytes sc = {1, 1, 0, 0, 0, 12, 0, 0, -1, -1, -1, -1, 0, 0, 0, 0, 0};
	this->writeBytes(sc);
	writeStringByte(chord->getName(), 21);
	skipBytes(4);
	writeInt(chord->getFirstFret());
	for (int i = 0; i < 7; i++)
	{
		writeInt((i < chord->countStrings() ? chord->getFretValue(i) : -1));
	}
	this->skipBytes(32);
}

void GP5OutputStream::writeBeatEffects(TGBeat *beat, TGNoteEffect *effect)
{
	int flags1 = 0;
	int flags2 = 0;
	
	if (effect->isFadeIn())
	{
		flags1 |= 0x10;
	}
	if (effect->isTapping() || effect->isSlapping() || effect->isPopping())
	{
		flags1 |= 0x20;
	}
	if (effect->isTremoloBar())
	{
		flags2 |= 0x04;
	}
	if (beat->getStroke().getDirection() != TGStroke::STROKE_NONE)
	{
		flags1 |= 0x40;
	}
	writeUnsignedByte(flags1);
	writeUnsignedByte(flags2);
	
	if ((flags1 & 0x20) != 0)
	{
		if (effect->isTapping())
		{
			writeUnsignedByte(1);
		}
		else if (effect->isSlapping())
		{
			writeUnsignedByte(2);
		}
		else if (effect->isPopping())
		{
			writeUnsignedByte(3);
		}
	}
	if ((flags2 & 0x04) != 0)
	{
		writeTremoloBar(effect->getTremoloBar());
	}
	if ((flags1 & 0x40) != 0)
	{
		writeUnsignedByte((beat->getStroke().getDirection() == TGStroke::STROKE_UP ? 
							   toStrokeValue(&beat->getStroke()) : 0));
		writeUnsignedByte((beat->getStroke().getDirection() == TGStroke::STROKE_DOWN ? 
							   toStrokeValue(&beat->getStroke()) : 0));
	}
}

void GP5OutputStream::writeNoteEffects(TGNoteEffect *effect)
{
	int flags1 = 0;
	int flags2 = 0;
	if (effect->isBend())
	{
		flags1 |= 0x01;
	}
	if (effect->isHammer())
	{
		flags1 |= 0x02;
	}
	if (effect->isLetRing())
	{
		flags1 |= 0x08;
	}
	if (effect->isGrace())
	{
		flags1 |= 0x10;
	}
	if (effect->isStaccato())
	{
		flags2 |= 0x01;
	}
	if (effect->isPalmMute())
	{
		flags2 |= 0x02;
	}
	if (effect->isTremoloPicking())
	{
		flags2 |= 0x04;
	}
	if (effect->isSlide())
	{
		flags2 |= 0x08;
	}
	if (effect->isHarmonic())
	{
		flags2 |= 0x10;
	}
	if (effect->isTrill())
	{
		flags2 |= 0x20;
	}
	if (effect->isVibrato())
	{
		flags2 |= 0x40;
	}
	writeUnsignedByte(flags1);
	writeUnsignedByte(flags2);
	if ((flags1 & 0x01) != 0)
	{
		writeBend(effect->getBend());
	}
	
	if ((flags1 & 0x10) != 0)
	{
		writeGrace(effect->getGrace());
	}
	
	if ((flags2 & 0x04) != 0)
	{
		writeTremoloPicking(effect->getTremoloPicking());
	}
	
	if ((flags2 & 0x08) != 0)
	{
		writeByte((1));
	}
	
	if ((flags2 & 0x10) != 0)
	{
		writeByte((1));
	}
	
	if ((flags2 & 0x20) != 0)
	{
		writeTrill(effect->getTrill());
	}
	
}

void GP5OutputStream::writeBend(TGEffectBend *bend)
{
	int points = bend->getPoints().size();
	writeByte((1));
	writeInt(0);
	writeInt(points);
	for (int i = 0; i < points; i++)
	{
		BendPoint& point = bend->getPoints()[i];
		writeInt((point.getPosition() * GP_BEND_POSITION / MAX_POSITION_LENGTH));
		writeInt((point.getValue() * GP_BEND_SEMITONE / TGEffectBend::SEMITONE_LENGTH));
		writeByte((0));
	}
}

void GP5OutputStream::writeTremoloBar(TGEffectTremoloBar *tremoloBar)
{
	int points = tremoloBar->getPoints().size();
	writeByte((1));
	writeInt(0);
	writeInt(points);
	for (int i = 0; i < points; i++)
	{
		TremoloBarPoint& point = tremoloBar->getPoints()[i];
		writeInt((point.getPosition() * GP_BEND_POSITION / MAX_POSITION_LENGTH));
		writeInt((point.getValue() * (GP_BEND_SEMITONE * 2)));
		writeByte((0));
	}
}

void GP5OutputStream::writeGrace(TGEffectGrace *grace)
{
	writeUnsignedByte(grace->getFret());
	writeUnsignedByte(((grace->getDynamic() - 
						TGVelocities::MIN_VELOCITY) / TGVelocities::VELOCITY_INCREMENT) + 1);
	if (grace->getTransition() == TGEffectGrace::TRANSITION_NONE)
	{
		writeUnsignedByte(0);
	}
	else if (grace->getTransition() == TGEffectGrace::TRANSITION_SLIDE)
	{
		writeUnsignedByte(1);
	}
	else if (grace->getTransition() == TGEffectGrace::TRANSITION_BEND)
	{
		writeUnsignedByte(2);
	}
	else if (grace->getTransition() == TGEffectGrace::TRANSITION_HAMMER)
	{
		writeUnsignedByte(3);
	}
	writeUnsignedByte(grace->getDuration());
	writeUnsignedByte((grace->isDead() ? 0x01 : 0) | (grace->isOnBeat() ? 0x02 : 0));
}

void GP5OutputStream::writeTrill(TGEffectTrill *trill)
{
	writeByte((trill->getFret()));
	
	if (trill->getDuration().getValue() == TGDuration::SIXTEENTH)
	{
		writeByte((1));
	}
	else if (trill->getDuration().getValue() == TGDuration::THIRTY_SECOND)
	{
		writeByte((2));
	}
	else if (trill->getDuration().getValue() == TGDuration::SIXTY_FOURTH)
	{
		writeByte((3));
	}
}

void GP5OutputStream::writeTremoloPicking(TGEffectTremoloPicking *tremoloPicking)
{
	if (tremoloPicking->getDuration().getValue() == TGDuration::EIGHTH)
	{
		writeByte((1));
	}
	else if (tremoloPicking->getDuration().getValue() == TGDuration::SIXTEENTH)
	{
		writeByte((2));
	}
	else if (tremoloPicking->getDuration().getValue() == TGDuration::THIRTY_SECOND)
	{
		writeByte((3));
	}
}

void GP5OutputStream::writeText(TGText *text)
{
	writeStringByteSizeOfInteger(text->getValue());
}

void GP5OutputStream::writeMixChange(TGTempo *tempo)
{
	writeByte((0xff));
	for (int i = 0; i < 16; i++)
	{
		writeByte((0xff));
	}
	writeByte((0xff)); //volume
	writeByte((0xff)); //int pan
	writeByte((0xff)); //int chorus
	writeByte((0xff)); //int reverb
	writeByte((0xff)); //int phaser
	writeByte((0xff)); //int tremolo
	writeStringByteSizeOfInteger(_sempty); //tempo name
	writeInt((tempo != nullptr)?tempo->getValue():-1); //tempo value
	if ((tempo != nullptr))
	{
		skipBytes(1);
	}
	writeByte((1));
	writeByte((0xff));
}

void GP5OutputStream::writeMarker(const TGMarker *marker)
{
	writeStringByteSizeOfInteger(marker->getTitle());
	writeColor((TGColor*)&marker->_color);
}

void GP5OutputStream::writeColor(TGColor *color)
{
	writeUnsignedByte(color->getR());
	writeUnsignedByte(color->getG());
	writeUnsignedByte(color->getB());
	writeByte((0));
}

std::vector<TGChannel*> GP5OutputStream::makeChannels(TGSong *song)
{
	std::vector<TGChannel*> channels(64);
	for (int i = 0; i < channels.size(); i++)
	{
		channels[i] =  new TGChannel();
		channels[i]->setProgram(static_cast<short>(24));
		channels[i]->setVolume(static_cast<short>(13));
		channels[i]->setBalance(static_cast<short>(8));
		channels[i]->setChorus(static_cast<short>(0));
		channels[i]->setReverb(static_cast<short>(0));
		channels[i]->setPhaser(static_cast<short>(0));
		channels[i]->setTremolo(static_cast<short>(0));
	}
	
	for(auto& tgChannel : song->getChannels())
	{
		GMChannelRoute *gmChannelRoute = getChannelRoute(tgChannel->getChannelId());
		int ch1 = gmChannelRoute->getChannel1();
		int ch2 = gmChannelRoute->getChannel2();
		
		channels[ch1]->setProgram(tgChannel->getProgram());
		channels[ch1]->setVolume(tgChannel->getVolume());
		channels[ch1]->setBalance(tgChannel->getBalance());
		channels[ch2]->setProgram(tgChannel->getProgram());
		channels[ch2]->setVolume(tgChannel->getVolume());
		channels[ch2]->setBalance(tgChannel->getBalance());
	}
	return channels;
}

bytes GP5OutputStream::makeBeamEighthNoteBytes(TGTimeSignature& ts)
{
	bytes bytes = {0, 0, 0, 0};
	if (ts.getDenominator().getValue() <= TGDuration::EIGHTH)
	{
		int eighthsInDenominator = (TGDuration::EIGHTH / ts.getDenominator().getValue());
		int total = (eighthsInDenominator * ts.getNumerator());
		int byteValue = (total / 4);
		int missingValue = (total - (4 * byteValue));
		for (int i = 0 ; i < bytes.size(); i++)
		{
			bytes[i] = (byteValue);
		}
		if (missingValue > 0)
		{
			bytes[0] += missingValue;
		}
	}
	return bytes;
}

int GP5OutputStream::toStrokeValue(TGStroke *stroke)
{
	if (stroke->getValue() == TGDuration::SIXTY_FOURTH)
	{
		return 2;
	}
	if (stroke->getValue() == TGDuration::THIRTY_SECOND)
	{
		return 3;
	}
	if (stroke->getValue() == TGDuration::SIXTEENTH)
	{
		return 4;
	}
	if (stroke->getValue() == TGDuration::EIGHTH)
	{
		return 5;
	}
	if (stroke->getValue() == TGDuration::QUARTER)
	{
		return 6;
	}
	return 2;
}

signed char GP5OutputStream::toChannelByte(short s)
{
	return ((s + 1) / 8);
}

std::vector<std::string> GP5OutputStream::toCommentLines(const std::string &comments)
{
	std::vector<std::string> lines;
	
	std::string line = comments;
	while (line.length() > std::numeric_limits<signed char>::max())
	{
		std::string subline = line.substr(0, std::numeric_limits<signed char>::max());
		lines.push_back(subline);
		line = line.substr(std::numeric_limits<signed char>::max());
	}
	lines.push_back(line);
	
	return lines;
}



