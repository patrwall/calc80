/* Calc80 by Patrik Wallander */
/* License GPL2.  See COPYING for details of GPL2 License */
#include "Definitions.h"
#include "Operation.h"
Operation::Operation() {
  op = 0;
  prio = 0;
  index = 0;
}
Operation::Operation(const unsigned char &o) {
  op = o;

  //set prio
  switch(op) {
  case OP_EQUAL:
    prio = LOWEST_PRIO;
    break;
    
  case OP_LBRACKET:
    prio = LOWER_PRIO;
    break;
    
  case OP_RBRACKET:
    prio = LOW_PRIO;
    break;
    
  case OP_PLUS:
  case OP_MINUS:
    prio = MID_PRIO;
    break;
    
  case OP_MULT:
  case OP_DIVIDE:
    prio = HIGH_PRIO;
    break;		
    
  case OP_POWER:
  case OP_IPOW:
    prio = HIGHER_PRIO;
  break;
  
  default:
    prio = HIGHEST_PRIO;
	}
}
