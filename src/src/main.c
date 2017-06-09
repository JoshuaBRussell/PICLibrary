#include <xc.h>
#include <stdint.h>

#include "IO_Functions.h"

#define NUM_PORTS 2



void simple_delay(){
    uint16_t i, j;
    for(i = 0; i < 200; i++){
        for(j = 0; j < 200; j++){
            //Do nothing
        }
    }
}


int main(void) {

    setB15Out();//*(TRIS_ARRY[1]) = 0x7FFF;
    B15Off();//*(LAT_ARRY[1])  = 0x7FFF;

    while(1){
    simple_delay();
    B15On();//*(LAT_ARRY[1]) = 0xFFFF;
    simple_delay();
    B15Off();//*(LAT_ARRY[1]) = 0x7FFF;


    }

    return 0;
}
