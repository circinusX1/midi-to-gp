#ifndef TGDIVISIONTYPE_H
#define TGDIVISIONTYPE_H

#include <assert.h>

class TGDivisionType {
public:
	
	TGDivisionType(){
		this->enters = 1;
		this->times = 1;
	}
	
	int getEnters()const {
		return this->enters;
	}
	
	void setEnters(int enters) {
		this->enters = enters;
	}
	
	int getTimes()const {
		return this->times;
	}
	
	void setTimes(int times) {
		this->times = times;
	}
	
	long convertTime(long time)const{
		assert(this->enters!=0);
		return time * this->times / this->enters;
	}
	
	bool operator==(const TGDivisionType& divisionType){
		return (divisionType.getEnters() == getEnters() &&
				divisionType.getTimes() == getTimes());
	}
	
	static TGDivisionType newDivisionType(int enters,int times){
		TGDivisionType divisionType;
		divisionType.setEnters(enters);
		divisionType.setTimes(times);
		return divisionType;
	}
	
	int enters;
	int times;
	
	static TGDivisionType NORMAL;
	static TGDivisionType TRIPLET;
	static  TGDivisionType ALTERED_DIVISION_TYPES[];
	
};

#endif // TGDIVISIONTYPE_H
