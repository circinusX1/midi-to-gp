#ifndef TGMARKER_H
#define TGMARKER_H

#include <string>

class TGColor {
	
public:
	
	int r;
	int g;
	int b;
	
	TGColor(){
		this->r = 0;
		this->g = 0;
		this->b = 0;
	}
	
	int getB()const {
		return this->b;
	}
	
	void setB(int b) {
		this->b = b;
	}
	
	int getG()const {
		return this->g;
	}
	
	void setG(int g) {
		this->g = g;
	}
	
	int getR()const {
		return this->r;
	}
	
	void setR(int r) {
		this->r = r;
	}
	
	bool operator==(const TGColor& _color){
		return (this->getR() == _color.getR() &&
				this->getG() == _color.getG() && 
				this->getB() == _color.getB());
	}

	static TGColor newColor(int r,int g,int b){
		TGColor _color;
		_color.setR(r);
		_color.setG(g);
		_color.setB(b);
		return _color;
	}
	
	
	const static  TGColor RED  ;// = newColor(255,0,0);
	const static  TGColor GREEN;// = newColor(0,255,0);
	const static  TGColor BLUE ;// = newColor(0,0,255);
	const static  TGColor WHITE;// = newColor(255,255,255);
	const static  TGColor BLACK;// = newColor(0,0,0);
	const static  TGColor DEFAULT_COLOR;
};


class TGMarker {
	
public:
	
	TGMarker() {
		this->_measure = 0;
		this->_title = DEFAULT_TITLE;
		this->_color = DEFAULT_COLOR;
	}
	
	int getMeasure()const {
		return this->_measure;
	}
	
	void setMeasure(int _measure) {
		this->_measure = _measure;
	}
	
	std::string getTitle()const {
		return this->_title;
	}
	
	void setTitle(std::string _title) {
		this->_title = _title;
	}
	
	TGColor getColor()const {
		return this->_color;
	}
	
	void setColor(TGColor _color) {
		this->_color = _color;
	}
	
public:
	const static TGColor DEFAULT_COLOR ;//= TGColor::RED;
	const static std::string DEFAULT_TITLE;// = "Untitled";
	
	int			_measure;
	std::string _title;
	TGColor		_color;	 
};

#endif // TGMARKER_H
