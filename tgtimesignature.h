#ifndef TGTIMESIGNATURE_H
#define TGTIMESIGNATURE_H

#include "tgduration.h"

class TGTimeSignature {
public:	
	TGDuration _denominator;
	int _numerator;
	
	TGTimeSignature(){
		this->_numerator = 4;
	}
	
	int getNumerator()const {
		return this->_numerator;
	}
	
	void setNumerator(int _numerator) {
		this->_numerator = _numerator;
	}
	
	
	void setDenominator(TGDuration& _denominator) {
		this->_denominator = _denominator;
	}
	
	TGDuration& getDenominator() {
		return _denominator;
	}

	
	bool operator==(TGTimeSignature& ts){
		return (_numerator == ts._numerator && 
				_denominator == ts._denominator);
	}
};

#endif // TGTIMESIGNATURE_H
