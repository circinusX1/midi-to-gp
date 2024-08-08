#include "songadjuster.h"
#include "tgnote.h"
#include "tgbeat.h"

SongAdjuster::SongAdjuster(TGSong *song)
{
	this->song = song;
	this->minDurationTime = 40;
}

TGSong *SongAdjuster::adjustSong()
{
	for(auto& track: this->song->getTracks())
	{
		adjustTrack(track);
	}
	return this->song;
}

void SongAdjuster::adjustTrack(TGTrack *track)
{
	for(auto& measure : track->measures)
	{
		process(measure);
	}
}

void SongAdjuster::process(TGMeasure *measure)
{
	orderBeats(measure);
	joinBeats(measure);
	adjustStrings(measure);
}

void SongAdjuster::joinBeats(TGMeasure *measure)
{
	TGBeat *previous = nullptr;
	bool finish = true;

	long long measureStart = measure->getStart();
	long long measureEnd = (measureStart + measure->getLength());
	for (int i = 0;i < measure->countBeats();i++)
	{
		TGBeat *beat = measure->getBeat(i);
		long long beatStart = beat->getStart();
		long long beatLength = beat->getVoice(0)->duration.getTime();
		if (previous != nullptr)
		{
			long long previousStart = previous->getStart();
			long long previousLength = previous->getVoice(0)->duration.getTime();

			//if(previousStart == beatStart){
			if (beatStart >= previousStart && (previousStart + this->minDurationTime) > beatStart)
			{
				// add beat notes to previous
				for (int n = 0;n < beat->getVoice(0)->countNotes();n++)
				{
					TGNote *note = beat->getVoice(0)->getNote(n);
					previous->getVoice(0)->addNote(note);
				}

				// add beat chord to previous
				if (!previous->isChordBeat() && beat->isChordBeat())
				{
					previous->setChord(beat->getChord());
				}

				// add beat text to previous
				if (!previous->isTextBeat() && beat->isTextBeat())
				{
					previous->setText(beat->getText());
				}

				// set the best duration
				if (beatLength > previousLength && (beatStart + beatLength) <= measureEnd)
				{
					previous->getVoice(0)->duration = (beat->getVoice(0)->duration);
				}

				measure->removeBeat(beat);
				finish = false;
				break;
			}

			else if (previousStart < beatStart && (previousStart + previousLength) > beatStart)
			{
				if (beat->getVoice(0)->isRestVoice())
				{
					measure->removeBeat(beat);
					finish = false;
					break;
				}
				TGDuration duration = TGDuration::fromTime((long)(beatStart - previousStart));
				previous->getVoice(0)->duration = duration;
			}
		}
		if ((beatStart + beatLength) > measureEnd)
		{
			if (beat->getVoice(0)->isRestVoice())
			{
				measure->removeBeat(beat);
				finish = false;
				break;
			}
			TGDuration duration = TGDuration::fromTime((measureEnd - beatStart));
			beat->getVoice(0)->duration=(duration);
		}

		previous = beat;
	}
	if (!finish)
	{
		joinBeats(measure);
	}
}

void SongAdjuster::orderBeats(TGMeasure *measure)
{
	for (int i = 0;i < measure->countBeats();i++)
	{
		TGBeat *minBeat = nullptr;
		for (int j = i;j < measure->countBeats();j++)
		{
			TGBeat *beat = measure->getBeat(j);
			if (minBeat == nullptr || beat->getStart() < minBeat->getStart())
			{
				minBeat = beat;
			}
		}
		measure->moveBeat(i, minBeat);
	}
}

void SongAdjuster::adjustStrings(TGMeasure *measure)
{
	for (int i = 0;i < measure->countBeats();i++)
	{
		TGBeat *beat = measure->getBeat(i);
		adjustStrings(beat);
	}
}

void SongAdjuster::adjustStrings(TGBeat *beat)
{
	TGTrack *track = beat->getMeasure()->getTrack();
	std::vector<TGString*> freeStrings(track->getStrings());
	std::vector<TGNote*> notesToRemove;

	//ajusto las cuerdas
	for(auto& note: beat->getVoice(0)->getNotes())
	{
		int string = getStringForValue(freeStrings,note->value);
		for (int j = 0;j < freeStrings.size();j++)
		{
			TGString *tempString = static_cast<TGString*>(freeStrings[j]);
			if (tempString->number == string)
			{
				note->setValue(note->value - tempString->value);
				note->setString(tempString->number);
				freeStrings.erase(freeStrings.begin() + j);
				break;
			}
		}

		//Cannot have more notes on same string 
		if (note->getString() < 1)
		{
			notesToRemove.push_back(note);
		}
	}

	// Remove notes
	while (notesToRemove.size() > 0)
	{
		beat->getVoice(0)->removeNote(static_cast<TGNote*>(notesToRemove[0]));
		notesToRemove.erase(notesToRemove.begin());
	}
}

int SongAdjuster::getStringForValue(std::vector<TGString*> &strings, int value)
{
	int minFret = -1;
	int stringForValue = 0;
	for (int i = 0;i < strings.size();i++)
	{
		TGString *string = static_cast<TGString*>(strings[i]);
		int fret = value - string->value;
		if (minFret < 0 || (fret >= 0 && fret < minFret))
		{
			stringForValue = string->number;
			minFret = fret;
		}
	}
	return stringForValue;
}
