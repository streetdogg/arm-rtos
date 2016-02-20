#include "reg_names.h"

int main( void ){

  RCGC2      |= 0x00000020;         
  PORTF_DIR   = 0x0E;         
  PORTF_PUR   = 0x11;          
  PORTF_DEN   = 0x1F; 
	// Turn the red led on!
  PORTF_DATA  = 0x02;
  
  while(1);
}
