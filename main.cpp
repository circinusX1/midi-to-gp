#include <iostream>
#include "midisongreader.h"
#include "gtpoutputstream.h"
#include "gp5outputstream.h"

int TracksVolume = 0;

int main(int argc, char *argv[])
{
    (void)argv;
    (void)argc;
    MidiSongReader m;
    std::cout << "By marius.c \n";

    if(argc==5){ // program midi gp trans vol
        TracksVolume = atoi(argv[4]);
        if(TracksVolume>127)
            TracksVolume=127;
    }
    std::cout << "Using tracks volume = " << TracksVolume << "\n";
    if(argc > 2 && m.open(argv[1]))
    {
        TGSong* song = m.read(argc==4 ? atoi(argv[3]) : 0);
        if(song)
        {
            GP5OutputStream gp5(argv[2]);
            gp5.write(song);
        }
    }
    else
        std::cout <<"usage: "<< argv[0] << " midifile.midi gpfile.gp5 transpose\n";
    return 0;
}
