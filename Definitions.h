/* Calc80 by Patrik Wallander */
/* License GPL2.  See COPYING for details of GPL2 License */
#include <cstddef> 

using namespace std;

//
//Keypad
//
const size_t KP_0 = 0;
const size_t KP_1 = 1;
const size_t KP_2 = 2;
const size_t KP_3 = 3;
const size_t KP_4 = 4;
const size_t KP_5 = 5;
const size_t KP_6 = 6;
const size_t KP_7 = 7;
const size_t KP_8 = 8;
const size_t KP_9 = 9;
const size_t KP_DOT = 10;
const size_t KP_EXP = 11;
const size_t KP_SIGN = 12;
const size_t KP_BS = 13;
const size_t KP_C = 14;
const size_t KP_AC = 15;

//
//Memory & constants
//
const size_t MM_STORE = 16;
const size_t MM_RECALL = 17;
const size_t MM_SUM = 18;
const size_t C_PI = 19;

//
//Modes
//
const size_t MT_DEG = 32;
const size_t MT_RAD = 33;
const size_t MT_GRAD = 34;
const size_t MD_NORM = 35;
const size_t MD_FIX = 36;
const size_t MD_SCI = 37;
const size_t MD_ENG = 38;

//
//Operations
//
const size_t OP_EQUAL = 64;	//LOWEST PRIO
const size_t OP_LBRACKET = 65;	//LOWER PRIO
const size_t OP_RBRACKET = 66;	//LOW PRIO
const size_t OP_PLUS = 67;	//MID PRIO
const size_t OP_MINUS = 68;

const size_t OP_MULT = 80;	//HIGH PRIO
const size_t OP_DIVIDE = 81;

const size_t OP_POWER =96;	//HIGHER PRIO
const size_t OP_IPOW = 97;
const size_t OP_XROOT = 98;

const size_t OP_TENPOW = 112;  //HIGHEST PRIO
const size_t OP_EPOW = 113;
const size_t OP_PERCENT = 114;	
const size_t OP_SQUARE = 115;
const size_t OP_ROOT = 116;
const size_t OP_REC = 117;
const size_t OP_FACT = 118;
const size_t OP_SIN = 119;
const size_t OP_COS = 120;
const size_t OP_TAN = 121;
const size_t OP_ASIN = 122;
const size_t OP_ACOS = 123;
const size_t OP_ATAN = 124;
const size_t OP_SINH = 125;
const size_t OP_COSH = 126;
const size_t OP_TANH = 127;
const size_t OP_ASINH = 128;
const size_t OP_ACOSH = 129;
const size_t OP_ATANH = 130;
const size_t OP_LOG = 131;
const size_t OP_NLOG = 132;
const size_t OP_QROOT = 133;

//
//Operation Prio
//

const size_t LOWEST_PRIO = 0;
const size_t LOWER_PRIO = 1;
const size_t LOW_PRIO = 2;
const size_t MID_PRIO = 3;
const size_t HIGH_PRIO = 4;
const size_t HIGHER_PRIO = 5;
const size_t HIGHEST_PRIO = 6;

//
//Special
//
const size_t S_SELECT_MODE = 128;
const size_t S_TOGGLE_DRG = 129;

//
//Ignore
//
//const size_t IGNORE = 245;

//
//Constants
//
const long double PI = 3.141592653589793238L;
