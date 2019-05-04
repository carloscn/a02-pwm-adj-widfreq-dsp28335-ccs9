#include "../include/DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "../include/DSP2833x_Examples.h"   // DSP2833x Examples Include File

void MemCopy(Uint16 *SourceAddr, Uint16* SourceEndAddr, Uint16* DestAddr)
{
    while(SourceAddr < SourceEndAddr)
    { 
       *DestAddr++ = *SourceAddr++;
    }
    return;
}

//===========================================================================
// End of file.
//===========================================================================
