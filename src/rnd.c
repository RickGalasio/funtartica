#include "rnd.h"

void msrand(int zseed){
   mseed=zseed;
}
// simple mersenne twister pseudo random generator
unsigned int mrand(void){
        mseed ^= mseed << 13;
        mseed ^= mseed >> 7;
        mseed ^= mseed << 17;
 return mseed;
}
