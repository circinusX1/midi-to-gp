# midi-to-gp
## Converts midi to guitar pro
### Thanks to (https://www.tuxguitar.app/)

* The code was taken from tuxguitar and converted to C++
* It has lots of memory leaks, it was done in one evenning.
* On portions I used java to cpp utilities, then manual fixes until the code compiled and ran.

### Projects using it:
[Free online guitar tabs player GHITARA.COM ](https://ghitara.com)


### ΕΞΙ-COILS GUITAR PICKUP
[ΕΞΙ-COIL, 6 coils guitar pickup](https://exicoil.from-ca.com/)



### Howto
    * Use Ubuntu 20.X 22.X 24.X
    * git clone this repo
    * cd midi-to-gp
    * make
    * run
        *./gmidigp midifile.midi gpfile.gp5 transpose, where transpose 1 means 1 semitone (-14..+14), usually 0

        
