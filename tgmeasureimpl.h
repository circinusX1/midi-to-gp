#ifndef TGMEASUREIMPL_H
#define TGMEASUREIMPL_H

#include <vector>
#include "tgbeat.h"
#include "tgmeasure.h"
#include "tgmeasurebuffer.h"

class TGMeasureImpl :  TGMeasure{
public:
	constexpr static  int NATURAL = 1;
	constexpr static  int SHARP = 2;
	constexpr static  int FLAT = 3;
	
	static const vvector KEY_SIGNATURES;
	
	constexpr static  int ACCIDENTAL_SHARP_NOTES[] = {0,0,1,1,2,3,3,4,4,5,5,6};
	constexpr static  int ACCIDENTAL_FLAT_NOTES [] = {0,1,1,2,2,3,4,4,5,5,6,6};
	constexpr static  bool ACCIDENTAL_NOTES[] = {false,true,false,true,
												false,false,true,
												false,true,false,true,false};
	
	static const std::vector<std::vector<int>> SCORE_KEY_SHARP_POSITIONS;
	static const std::vector<std::vector<int>> SCORE_KEY_FLAT_POSITIONS;	
	/**
	 * Espacio por defecto de la clave
	 */
	constexpr static int DEFAULT_CLEF_WIDTH = 16;
	
	/**
	 * Posicion X
	 */
	 float posX;
	/** 
	 * Posicion Y
	 */
	 float posY;
	/**
	 * Espacio entre negras
	 */
	 float quarterSpacing;
	/**
	 * Espacio entre pulsos
	 */
	 long divisionLength;
	/**
	 * Boolean para saber si hay que pintar la clave
	 */
	 bool paintClef = true;
	/**
	 * Boolean para saber si hay que pintar el KeySignature
	 */
	 bool paintKeySignature = true;
	/**
	 * Compas anterior
	 */
	 TGMeasureImpl* previousMeasure;
	/**
	 * Boolean para saber si el compas esta en el area de pantalla
	 */
	 bool outOfBounds;
	/**
	 * Boolean para saber si el compas es el primero de la linea
	 */
	 bool firstOfLine;
	
	 bool compactMode;
	
	 float spacing;
	
	 float maxY;
	
	 float minY;
	
	 int notEmptyVoices;
	
	 int notEmptyBeats;
	
	 float widthBeats = 0;
	
	 //std::vector<TGBeatGroup*> voiceGroups[TGBeat::MAX_VOICES];
	
	 TGMeasureBuffer* buffer;
	
	 bool bufferCreated;
	
	 int lyricBeatIndex;
	 float width;
	
	 float beatEffectSpacing;
	 bool text;
	 bool chord;
	 bool division1;
	 bool division2;
	
	 bool registeredAccidentals[11][7];
	
	 bool readyToPaint;
	
	 TGMeasureImpl(TGMeasureHeader* header):TGMeasure(header) {
 	 }

};

#endif // TGMEASUREIMPL_H
