//--------------------------------------------------------------------------------- //
//		AVR e Arduino: T�cnicas de Projeto, 2a ed. - 2012.							//	
//--------------------------------------------------------------------------------- //

//---------------------------------------------------------------------------------

#include <avr/fuse.h>
#include <avr/lock.h>

//gerando os dados para gravar o valor dos fus�veis no arquivo *.elf
FUSES = 
    	{
        .low = 0xFF,
        .high = 0xDA,
        .extended = 0xFD,
    	};

//gerando os dados para gravar os bits de travamento no arquivo *.elf
LOCKBITS = 0xCF;

int main()
{}
//---------------------------------------------------------------------------------
