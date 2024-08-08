#ifndef TGNOTEIMPL_H
#define TGNOTEIMPL_H

#include "tgnote.h"
#include "tglayout.h"

class TGNoteImpl : public TGNote {
public:
	
	float tabPosY;
	float scorePosY;
	int accidental;
	
	TGNoteImpl() {
	}
	
	
};

#endif // TGNOTEIMPL_H
