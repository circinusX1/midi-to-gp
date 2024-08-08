#ifndef TGDURATION_H
#define TGDURATION_H

#include <algorithm>
#include <assert.h>
#include "tgdivisiontype.h"

#define MAX_POSITION_LENGTH		12

class TGDuration {
public:
	TGDuration(const TGDuration& d)
	{
		_value = d._value;
		_dotted = d._dotted;
		_doubleDotted = d._doubleDotted;
		_divisionType = d._divisionType;
	}
	
	TGDuration(int value=QUARTER){
		this->_value = value;
		this->_dotted = false;
		this->_doubleDotted = false;
	}
	
	int getValue() {
		return this->_value;
	}
	
	void setValue(int _value) {
		this->_value = _value;
	}
	
	bool isDotted() {
		return this->_dotted;
	}
	
	void setDotted(bool _dotted) {
		this->_dotted = _dotted;
	}
	
	bool isDoubleDotted() {
		return this->_doubleDotted;
	}
	
	void setDoubleDotted(bool _doubleDotted) {
		this->_doubleDotted = _doubleDotted;
	}
	
	TGDivisionType& getDivision(){
		return this->_divisionType;
	}
	
	long getTime(){
		assert(this->_value);
		long time = (long)( QUARTER_TIME * 
							( 4.0f / this->_value ) ) ;
		if(this->_dotted){
			time += time / 2;
		}else if(this->_doubleDotted){
			time += ((time / 4) * 3);
		}
		return this->_divisionType.convertTime(time);
	}
	
	static TGDuration fromTime(long time){
		TGDuration duration;
		duration.setValue(TGDuration::SIXTY_FOURTH);
		duration.setDotted(false);
		duration.setDoubleDotted(false);
		duration.getDivision().setEnters(3);
		duration.getDivision().setTimes(2);
		return TGDuration::fromTime(time,duration);
	}
	
	static TGDuration fromTime(long time,TGDuration& minDuration){
		return TGDuration::fromTime(time, minDuration, 10);
	}
	
	static TGDuration fromTime(long time,TGDuration& minimum, int diff){
		
		TGDuration duration = minimum;
		TGDuration tmpDuration;
		
		tmpDuration.setValue(TGDuration::WHOLE);
		tmpDuration.setDotted(true);
		bool finish = false;
		while(!finish){
			long tmpTime = tmpDuration.getTime();
			if(tmpTime - diff <= time){
				if( std::abs( tmpTime - time ) < 
						std::abs( duration.getTime() - time ) )
				{
					duration = tmpDuration;
				}
			}
			if(tmpDuration.isDotted()){
				tmpDuration.setDotted(false);
			}else if(tmpDuration.getDivision()==(TGDivisionType::NORMAL)){
				tmpDuration.getDivision().setEnters(3);
				tmpDuration.getDivision().setTimes(2);
			}else{
				tmpDuration.setValue(tmpDuration.getValue() * 2);
				tmpDuration.setDotted(true);
				tmpDuration.getDivision().setEnters(1);
				tmpDuration.getDivision().setTimes(1);
			}
			if(tmpDuration.getValue() > TGDuration::SIXTY_FOURTH){
				finish = true;
			}
		}
		return duration;
	}
	
	int getIndex(){
		int index = 0;
		int _value = this->_value;
		while( ( _value = ( _value >> 1 ) ) > 0 ){
			index ++;
		}
		return index;
	}
	
	bool operator==(TGDuration& d)
	{
		return (getValue() == d.getValue() && 
				isDotted() == d.isDotted() && 
				isDoubleDotted() == d.isDoubleDotted() && 
				_divisionType==d._divisionType);
	}
	
	TGDuration operator=(TGDuration& d)
	{
		_value = d._value;
		_dotted = d._dotted;
		_doubleDotted = d._doubleDotted;
		_divisionType = d._divisionType;
		return *this;
	}
	
public:
	constexpr static  long QUARTER_TIME = 960;
	constexpr static  int WHOLE = 1;
	constexpr static  int HALF = 2;
	constexpr static  int QUARTER = 4;
	constexpr static  int EIGHTH = 8;
	constexpr static  int SIXTEENTH = 16;
	constexpr static  int THIRTY_SECOND = 32;
	constexpr static  int SIXTY_FOURTH = 64;
	int				_value;
	bool			_dotted;
	bool			_doubleDotted;
	TGDivisionType  _divisionType;
};

#endif // TGDURATION_H
