#ifndef GP5OUTPUTSTREAM_H
#define GP5OUTPUTSTREAM_H

#include <string>
#include <vector>
#include <limits>
#include <stdexcept>
#include "gtpoutputstream.h"
#include "tgnote.h"
#include "tgsong.h"
#include "temps.h"
#include "tgtrack.h"
#include "tglyric.h"
#include "tgmeasure.h"
#include "tgmeasureheader.h"
#include "tgmeasureimpl.h"
#include "tgnoteeffect.h"


class GP5OutputStream : public GTPOutputStream
{
	
private:
	static const std::string GP5_VERSION;
	static constexpr int GP_BEND_SEMITONE = 25;
	static constexpr int GP_BEND_POSITION = 60;
	
	static const std::vector<std::string> PAGE_SETUP_LINES;
	
public:
	GP5OutputStream(const char* file);
	~GP5OutputStream();
	
	void writeSong(TGSong *song);
	
private:
	void writeInfo(TGSong *song);
	void writeLyrics(TGSong *song);
	void writePageSetup();
	void writeChannels(TGSong *song);
	void writeMeasureHeaders(TGSong *song);
	void writeMeasureHeader(TGMeasureHeader *measure, TGTimeSignature *timeSignature);
	void writeTracks(TGSong *song);
	void writeTrack(TGTrack *track);
	void writeMeasures(TGSong *song, TGTempo *tempo);
	void writeMeasure(TGMeasure *measure, bool changeTempo);
	void writeBeat(TGVoice *voice, TGBeat *beat, TGMeasure *measure, bool changeTempo);
	void writeNote(TGNote *note);
	signed char parseDuration(TGDuration *duration);
	void writeChord(TGChord *chord);
	void writeBeatEffects(TGBeat *beat, TGNoteEffect *effect);
	void writeNoteEffects(TGNoteEffect *effect);
	void writeBend(TGEffectBend *bend);
	void writeTremoloBar(TGEffectTremoloBar *tremoloBar);
	void writeGrace(TGEffectGrace *grace);
	void writeTrill(TGEffectTrill *trill);
	void writeTremoloPicking(TGEffectTremoloPicking *tremoloPicking);
	void writeText(TGText *text);
	void writeMixChange(TGTempo *tempo);
	void writeMarker(const TGMarker *marker);
	void writeColor(TGColor *color);
	std::vector<TGChannel*> makeChannels(TGSong *song);
	bytes makeBeamEighthNoteBytes(TGTimeSignature& ts);
	int toStrokeValue(TGStroke *stroke);
	signed char toChannelByte(short s);
	std::vector<std::string> toCommentLines(const std::string &comments);
};

#endif // GP5OUTPUTSTREAM_H
