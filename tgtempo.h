#ifndef TGTEMPO_H
#define TGTEMPO_H

class TGTempo {
public:	
	constexpr static int SECOND_IN_MILLIS = 1000;
	
	int value;
	
	TGTempo(){
		this->value = 120;
	}
	
	int getValue()const {
		return this->value;
	}
	
	void setValue(int value) {
		this->value = value;
	}
	
	long getInMillis()const{
		double millis = (60.00 / getValue() * SECOND_IN_MILLIS);
		return (long)millis;
	}
	
	long getInUSQ()const{
		double usq = ((60.00 / getValue() * SECOND_IN_MILLIS) * 1000.00);
		return (long)usq;
	}
	
	static TGTempo fromUSQ(int usq){
		double value = ((60.00 * SECOND_IN_MILLIS) / (usq / 1000.00));
		TGTempo tempo;
		tempo.setValue((int)value);
		return tempo;
	}
	
};


#endif // TGTEMPO_H
