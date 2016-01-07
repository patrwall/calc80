/* Calc80 by Patrik Wallander */
/* License GPL2.  See COPYING for details of GPL2 License */
#include "Definitions.h"
#include "Calculator.h"
#include <cstdio>
#include <cerrno>

Calculator::Calculator() {
  _brackets = 0;
  m_active = false;
  _tmod = MT_DEG;
}

bool Calculator::binary(const size_t &o, long double &v1, const long double &v2) {
  int n;
  long double fpart, ipart;
  
  errno = 0;
  
  switch(o){
  case(OP_PLUS):
    v1 = (v1 + v2); 
    break;

  case(OP_MINUS):
    v1 = v1 - v2;
    break;

  case(OP_MULT):
    v1 = v1 * v2;
    break;

  case(OP_DIVIDE):
    v1 = v1 / v2;
    break;

  case(OP_POWER):
       if(is_zero(v1))
	 v1 = 0;
       else if(v2 == 0) {
	 if(v1 < 0)
	   v1 = -1;
	 else
	   v1 = 1;
       }
       else
	 v1 = pow(v1, v2);  
       break;
   
  case(OP_IPOW):
    fpart = modf(v2, &ipart);
    
    n = ipart;
    
    if(is_zero(fpart) && v1 < 0 && n%2 != 0)
      v1 = -pow(abs(v1), 1 / v2);
    else
      v1 = pow(v1, 1 / v2);
    break;
  }

  if(errno != 0 || isnan(v1))
    return false;
  return true;
}

void Calculator::calc(const size_t &o) {
  Operation op = Operation(o);
  long double v = _varea.value; //_varea.get_value();
  
  if(op.prio == HIGHEST_PRIO) {
    if(!unary(op.op, v)) {
      _varea.locked = true;
      return;
    }
  }
  
  else if(op.op == OP_LBRACKET) {
    if(_brackets < 99) {
      _ostack.push(op);
      _brackets++;
    }
    else {
      _varea.locked = true;
      return;
    }
  }
    
  else {
    if(_varea.preset
       && !_ostack.empty()
       && _preop.op != OP_RBRACKET
       && _preop.op != OP_LBRACKET
       && _preop.prio != HIGHEST_PRIO) {
      _ostack.pop();
      if(op.op != OP_RBRACKET)
	_ostack.push(op);
    }
  
    while( !_ostack.empty()
	   && (_ostack.top().prio >= op.prio)) {
      if(_ostack.top().op == OP_LBRACKET)
	_brackets--;
      else {
	if(!binary(_ostack.top().op, _vstack.top(), v)) {
	  _varea.locked = true;
	  return;
	}
      v = _vstack.top();
      _vstack.pop();
      }
      _ostack.pop();
    }

  if(op.op == OP_RBRACKET) {
    if((_brackets > 0 )&&
       (_ostack.top().op == OP_LBRACKET)) {
      _brackets--;
      _ostack.pop();
      } 
  }
  
  else if(op.op != OP_EQUAL) {
    _ostack.push(op);
    _vstack.push(v);
    }
  }
  _preop = op;
  _varea.set_value(v);
}

string Calculator::cmd(const int &o, const string &s) {
  if(_askprec && o <= 9) {
    _varea.prec = o;
    _askprec = false;
  }
  
  else {
    _varea.set_content(s, false);

    switch(o) {
    case KP_0:
    case KP_1:
    case KP_2:
    case KP_3:
    case KP_4:
    case KP_5:
    case KP_6:
    case KP_7:
    case KP_8:
    case KP_9:
      char digit[2]; 
      sprintf(digit, "%i", o);
      _varea.enter_digit(digit[0]);
      break;
    case KP_DOT:
      _varea.enter_digit(_varea.dot);
      break;
    case KP_EXP:
      _varea.enter_digit('E');
      break;
    case KP_SIGN:
      _varea.enter_digit('-');
      break;
    case KP_BS:
      _varea.back_space();
      break;
    case KP_C:
      if(!_varea.locked)
	_varea.clear();
      break;
    case KP_AC:
      _varea.clear();
      while(!_vstack.empty())
 	_vstack.pop();
      while(!_ostack.empty())
	_ostack.pop();
      _brackets = 0;
      break;
    case MM_STORE:
      if(!_varea.locked) {
	_mem = _varea.get_value();
	if(is_zero(_mem))
	  m_active = false;
	else
	  m_active = true;
      }     
      break;
    case MM_RECALL:
      if(!_varea.locked && m_active)
	_varea.set_value(_mem);
      break;
    case MM_SUM:
      if(!_varea.locked) {
	m_active = true;
	_mem += _varea.get_value();
      }
      break;
    case C_PI:
      if(!_varea.locked)
	_varea.set_value(PI);
      break;

    case MT_DEG:
    case MT_RAD:
    case MT_GRAD:
      _tmod = o;
      break;
      
    case MD_FIX:
      _askprec = true;
    case MD_NORM:
    case MD_SCI:
    case MD_ENG:
      _varea.f_mod = o;
      break;
      
    default:
      if(!_varea.locked) {
	try {
	  calc(o);
	}
	catch (char* m) {
	  _varea.locked = true;
	}
      }
    }
  }
  if(_askprec == true) {
    _varea.set_content(_varea.get_content(), true);
    return "?";
  }
  return _varea.get_content();  
}

string Calculator::fmod_ind()
{
  string s;
  switch(_varea.f_mod) {
  case MD_FIX:
    s.append("FIX");
    break;
  case MD_SCI:
    s.append("SCI");
    break;
  }
  return s;
}

void Calculator::from_rad(long double &a) {
    if(_tmod == MT_DEG)
        a = a * 180 / M_PI;

    else if(_tmod == MT_GRAD)
        a = a * 200 / M_PI;
}

bool Calculator::is_zero(const long double &v)
{
	int length;
	char temp[20];

	length = sprintf(temp, "%.15LG", v);

	if( length == 1 && temp[0] == '0' )
		return( true );

	return( false );
}

string Calculator::mem_ind()
{
  string s;
  if(m_active)
    s.append("M");
  
  return s;
}

string Calculator::nr_of_brackets() {
  string s;
  stringstream ss;

  if(_brackets != 0) {   
    s.append("()x");
    ss << _brackets;
    s.append(ss.str());
  }
  return s;
}

string Calculator::set_content(const string &s) {
  _varea.set_content(s, true);
  return _varea.get_content();
}

string Calculator::tmod_ind()
{
  string s;
  switch(_tmod) {
  case MT_DEG:
    s.append("DEG");
    break;
  case MT_RAD:
    s.append("RAD");
    break;
  case MT_GRAD:
    s.append("GRAD");
    break;
  }
  return s;
}


void Calculator::to_rad(long double &a){
  if(_tmod == MT_DEG)
    a = a * M_PI / 180;
  
  if(_tmod == MT_GRAD)
    a = a * M_PI / 200;
}

void Calculator::to_zero(long double &v) {
  if(v < 1E-30)
    v = 0;
}

bool Calculator::unary(const size_t &o, long double &v){
  long double t1, t2;
  
  errno = 0;
  
  switch(o) {
  case(OP_PERCENT):
    (v = v * 0.01);
    break;
    
  case(OP_ROOT):
    v = sqrt(v);
    break;
    
  case(OP_SQUARE):
    v = pow(v, 2);
    break;
    
  case(OP_REC):
      v = 1/v;
    break;
      
  case(OP_LOG):
      v = log10(v);
    break;
      
  case(OP_NLOG):
      v = log(v);
    break;
    
  case(OP_TENPOW):
    v = pow(10, v);
    break;
      
  case(OP_EPOW):
    v = pow(M_E, v);
  break;
      
  case(OP_FACT):
    t2 = modf(v, &t1);
    if(t2 != 0)
      return false;
    
    t2 = 1;
    for(int n = 1; n < t1; n++)
      t2 *= n;
    v = t2;
  break;
  
  case(OP_SIN):
    to_rad(v);
    v = sin(v);
    break;
    
  case(OP_COS):
    to_rad(v);
    v = cos(v);
    to_zero(v);
    break;
    
  case(OP_TAN):
    to_rad(v);
    v = tan(v);
    to_zero(v);
    break;
    
  case(OP_ASIN):
    v = asin(v);
    from_rad(v);
    break;
    
  case(OP_ACOS):
    v = acos(v);
    from_rad(v);
    break;
    
  case(OP_ATAN):
    v = atan(v);
    from_rad(v);
    break;
    
  case(OP_SINH):
    v = sinh(v);
    break;
    
  case(OP_COSH):
    v = cosh(v);
    break;
    
  case(OP_TANH):
    v = tanh(v);
    break;
    
  case(OP_ASINH):
    v = asinh(v);
    break;
    
  case(OP_ACOSH):
      v = acosh(v);
    break;
    
  case(OP_ATANH):
      v = atanh(v);
    break;

  case(OP_QROOT):
    if(v < 0)
      v = - pow(abs(v), 1 / (long double)3);
    else
      v = pow(v, 1 / (long double)3);
    break;
  }

  if (errno != 0)
    return false;
  return true;
}

string Calculator::width(const size_t &w) {
  _varea.width = w;
  return _varea.get_content();
}
