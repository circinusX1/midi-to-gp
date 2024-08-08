#ifndef TGSTROKE_H
#define TGSTROKE_H

class TGBeat;
class TGStroke {
public:
    
    constexpr static  int STROKE_NONE = 0;
    constexpr static  int STROKE_UP = 1;
    constexpr static  int STROKE_DOWN = -1;
    
    int direction;
    int value;
    
    TGStroke(){
        this->direction = STROKE_NONE;
    }
    
    int getDirection() {
        return this->direction;
    }
    
    void setDirection(int direction) {
        this->direction = direction;
    }
    
    int getValue() {
        return this->value;
    }
    
    void setValue(int value) {
        this->value = value;
    }
    
    int getIncrementTime( TGBeat* beat );
    
};


#endif // TGSTROKE_H
