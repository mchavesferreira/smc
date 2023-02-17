//--------------------------------------------------------------------------------- //
//		AVR e Arduino: Técnicas de Projeto, 2a ed. - 2012.							//	
//--------------------------------------------------------------------------------- //

//---------------------------------------------------------------------------------

#include <avr/fuse.h>
#include <avr/lock.h>

//gerando os dados para gravar o valor dos fusíveis no arquivo *.elf
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
