#ifndef TGNOTEEFFECT_H
#define TGNOTEEFFECT_H

#include "tgeffects.h"

class TGNoteEffect {
public:	
	TGEffectBend* bend;
	TGEffectTremoloBar* tremoloBar;
	TGEffectHarmonic* harmonic;
	TGEffectGrace* grace;
	TGEffectTrill* trill;
	TGEffectTremoloPicking* tremoloPicking;
	bool vibrato;
	bool deadNote;
	bool slide;
	bool hammer;
	bool ghostNote;
	bool accentuatedNote;
	bool heavyAccentuatedNote;
	bool palmMute;
	bool staccato;
	bool tapping;
	bool slapping;
	bool popping;
	bool fadeIn;
	bool letRing;
	
	TGNoteEffect(){
		this->bend = nullptr;
		this->tremoloBar = nullptr;
		this->harmonic = nullptr;
		this->grace = nullptr;
		this->trill = nullptr;
		this->tremoloPicking = nullptr;
		this->vibrato = false;
		this->deadNote = false;
		this->slide = false;
		this->hammer = false;
		this->ghostNote = false;
		this->accentuatedNote = false;
		this->heavyAccentuatedNote = false;
		this->palmMute = false;
		this->staccato = false;
		this->tapping = false;
		this->slapping = false;
		this->popping = false;
		this->fadeIn = false;
		this->letRing = false;
	}
	
	bool isDeadNote() {
		return this->deadNote;
	}
	
	void setDeadNote(bool deadNote) {
		this->deadNote = deadNote;
		//si es true, quito los efectos incompatibles
		if(this->isDeadNote()){
			this->bend = nullptr;
			this->trill = nullptr;
			this->slide = false;
			this->hammer = false;
			this->tremoloBar = nullptr;
			this->tremoloPicking = nullptr;
		}
	}
	
	bool isVibrato() {
		return this->vibrato;
	}
	
	void setVibrato(bool vibrato) {
		this->vibrato = vibrato;
		//si no es nullptr quito los efectos incompatibles
		if(this->isVibrato()){
			this->trill = nullptr;
			this->tremoloPicking = nullptr;
		}
	}
	
	TGEffectBend* getBend() {
		return this->bend;
	}
	
	void setBend(TGEffectBend* bend) {
		this->bend = bend;
		//si no es nullptr quito los efectos incompatibles
		if(this->isBend()){
			this->trill = nullptr;
			this->deadNote = false;
			this->slide = false;
			this->hammer = false;
			this->tremoloBar = nullptr;
			this->tremoloPicking = nullptr;
		}
	}
	
	bool isBend() {
		return (this->bend != nullptr && !this->bend->getPoints().empty());
	}
	
	TGEffectTremoloBar* getTremoloBar() {
		return this->tremoloBar;
	}
	
	void setTremoloBar(TGEffectTremoloBar* tremoloBar) {
		this->tremoloBar = tremoloBar;
		//si no es nullptr quito los efectos incompatibles
		if(this->isTremoloBar()){
			this->bend = nullptr;
			this->trill = nullptr;
			this->deadNote = false;
			this->slide = false;
			this->hammer = false;
			this->tremoloPicking = nullptr;
		}
	}
	
	bool isTremoloBar() {
		return (this->tremoloBar != nullptr);
	}
	
	
	TGEffectTrill* getTrill() {
		return this->trill;
	}
	
	void setTrill(TGEffectTrill* trill) {
		this->trill = trill;
		//si es true, quito los efectos incompatibles
		if(this->isTrill()){
			this->bend = nullptr;
			this->tremoloBar = nullptr;
			this->tremoloPicking = nullptr;
			this->slide = false;
			this->hammer = false;
			this->deadNote = false;
			this->vibrato = false;
		}
	}
	
	bool isTrill() {
		return (this->trill != nullptr);
	}
	
	TGEffectTremoloPicking* getTremoloPicking() {
		return this->tremoloPicking;
	}
	
	void setTremoloPicking(TGEffectTremoloPicking* tremoloPicking) {
		this->tremoloPicking = tremoloPicking;
		//si es true, quito los efectos incompatibles
		if(this->isTremoloPicking()){
			this->trill = nullptr;
			this->bend = nullptr;
			this->tremoloBar = nullptr;
			this->slide = false;
			this->hammer = false;
			this->deadNote = false;
			this->vibrato = false;
		}
	}
	
	bool isTremoloPicking() {
		return (this->tremoloPicking != nullptr);
	}
	
	bool isHammer() {
		return this->hammer;
	}
	
	void setHammer(bool hammer) {
		this->hammer = hammer;
		//si es true, quito los efectos incompatibles
		if(this->isHammer()){
			this->trill = nullptr;
			this->bend = nullptr;
			this->deadNote = false;
			this->slide = false;
			this->tremoloBar = nullptr;
			this->tremoloPicking = nullptr;
		}
	}
	
	bool isSlide() {
		return this->slide;
	}
	
	void setSlide(bool slide) {
		this->slide = slide;
		//si es true, quito los efectos incompatibles
		if(this->isSlide()){
			this->trill = nullptr;
			this->bend = nullptr;
			this->deadNote = false;
			this->hammer = false;
			this->tremoloBar = nullptr;
			this->tremoloPicking = nullptr;
		}
	}
	
	bool isGhostNote() {
		return this->ghostNote;
	}
	
	void setGhostNote(bool ghostNote) {
		this->ghostNote = ghostNote;
		//si es true, quito los efectos incompatibles
		if(this->isGhostNote()){
			this->accentuatedNote = false;
			this->heavyAccentuatedNote = false;
		}
	}
	
	bool isAccentuatedNote() {
		return this->accentuatedNote;
	}
	
	void setAccentuatedNote(bool accentuatedNote) {
		this->accentuatedNote = accentuatedNote;
		//si es true, quito los efectos incompatibles
		if(this->isAccentuatedNote()){
			this->ghostNote = false;
			this->heavyAccentuatedNote = false;
		}
	}
	
	bool isHeavyAccentuatedNote() {
		return this->heavyAccentuatedNote;
	}
	
	void setHeavyAccentuatedNote(bool heavyAccentuatedNote) {
		this->heavyAccentuatedNote = heavyAccentuatedNote;
		//si es true, quito los efectos incompatibles
		if(this->isHeavyAccentuatedNote()){
			this->ghostNote = false;
			this->accentuatedNote = false;
		}
	}
	
	void setHarmonic(TGEffectHarmonic* harmonic) {
		this->harmonic = harmonic;
	}
	
	TGEffectHarmonic* getHarmonic() {
		return this->harmonic;
	}
	
	bool isHarmonic() {
		return (this->harmonic != nullptr);
	}
	
	TGEffectGrace* getGrace() {
		return this->grace;
	}
	
	void setGrace(TGEffectGrace* grace) {
		this->grace = grace;
	}
	
	bool isGrace() {
		return (this->grace != nullptr);
	}
	
	bool isPalmMute() {
		return this->palmMute;
	}
	
	void setPalmMute(bool palmMute) {
		this->palmMute = palmMute;
		//si es true, quito los efectos incompatibles
		if(this->isPalmMute()){
			this->staccato = false;
			this->letRing = false;
		}
	}
	
	bool isStaccato() {
		return this->staccato;
	}
	
	void setStaccato(bool staccato) {
		this->staccato = staccato;
		//si es true, quito los efectos incompatibles
		if(this->isStaccato()){
			this->palmMute = false;
			this->letRing = false;
		}
	}
	
	bool isLetRing() {
		return this->letRing;
	}
	
	void setLetRing(bool letRing) {
		this->letRing = letRing;
		//si es true, quito los efectos incompatibles
		if(this->isLetRing()){
			this->staccato = false;
			this->palmMute = false;
		}
	}
	
	bool isPopping() {
		return this->popping;
	}
	
	void setPopping(bool popping) {
		this->popping = popping;
		//si es true, quito los efectos incompatibles
		if(this->isPopping()){
			this->tapping = false;
			this->slapping = false;
		}
	}
	
	bool isSlapping() {
		return this->slapping;
	}
	
	void setSlapping(bool slapping) {
		this->slapping = slapping;
		//si es true, quito los efectos incompatibles
		if(this->isSlapping()){
			this->tapping = false;
			this->popping = false;
		}
	}
	
	bool isTapping() {
		return this->tapping;
	}
	
	void setTapping(bool tapping) {
		this->tapping = tapping;
		//si es true, quito los efectos incompatibles
		if(this->isTapping()){
			this->slapping = false;
			this->popping = false;
		}
	}
	
	bool isFadeIn() {
		return this->fadeIn;
	}
	
	void setFadeIn(bool fadeIn) {
		this->fadeIn = fadeIn;
	}
	
	bool hasAnyEffect(){
		return (isBend() ||
				isTremoloBar() ||
				isHarmonic() ||
				isGrace() ||
				isTrill() ||
				isTremoloPicking() ||
				isVibrato() ||
				isDeadNote() ||
				isSlide() ||
				isHammer() ||
				isGhostNote() ||
				isAccentuatedNote() ||
				isHeavyAccentuatedNote() ||
				isPalmMute() ||
				isLetRing() ||
				isStaccato() ||
				isTapping() ||
				isSlapping() ||
				isPopping() ||
				isFadeIn());
	}
	
};

#endif // TGNOTEEFFECT_H
