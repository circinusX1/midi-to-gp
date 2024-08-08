#include "tgstroke.h"
#include "tgbeat.h"
#include "tgduration.h"

int TGStroke::getIncrementTime( TGBeat* beat )
{
    long duration = 0;
    if( this->value > 0 ){
        for(int v = 0; v < beat->countVoices(); v ++){
            TGVoice* voice = beat->getVoice( v );
            if( !voice->isEmpty() )
            {
                long currentDuration = voice->getDuration().getTime();
                if(duration == 0 || currentDuration < duration)
                {
                    duration = ( currentDuration <= TGDuration::QUARTER_TIME ? 
                                     currentDuration : TGDuration::QUARTER_TIME );
                }
            }
        }
        if( duration > 0 )
        {
            return (int)( ( ( duration / 8.0f ) * ( 4.0f / this->value ) ) );
        }
    }
    return 0;
}
