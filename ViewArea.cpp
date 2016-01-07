/* Calc80 by Patrik Wallander */
/* License GPL2.  See COPYING for details of GPL2 License */
#include "Definitions.h"
#include "ViewArea.h"
#include <iomanip>
#include <locale>
#include <cstdlib>
#include <cmath>
#include <cstring>

using namespace std;


ViewArea::ViewArea(){
	clear();
	f_mod = MD_NORM;
	width = 12;
	_neg = false;
}

ViewArea::ViewArea(const int& w){
	clear();
	f_mod = MD_NORM;
	width = w;
	_neg = false;
}

void ViewArea::back_space() {
  if(_init || locked || preset)
     return;

  if(_exp_mode) { 
    if(_exp.size() > 1)
      _exp.erase(_exp.size()-1);
   
    else{
      _exp_mode = false;
      _neg_exp = false;
      _exp.clear();
    }
    return;
  }
  
  if(_num.length() == 1) {
    clear();
    return;
  }
  
  else if(_num.at(_num.size()-1) == dot)
    _has_dot = false;
    
  _num.erase(_num.size()-1);
}

void ViewArea::clear(){
  _num.clear();
  _num.append(1, '0');

  _exp.clear();

  _init = true;
  _has_dot = false;
  _exp_mode = false;
  locked = false;
  _neg = false;
  _neg_exp = false;
  preset = false;
  
  dot = '.'; //Needs more work later
}

void ViewArea::enter_digit(const char& digit){
  
  if(locked)
    return;
  
  if(digit == '-'){    //Take care of sign
    
    if(_exp_mode)
      _neg_exp = !_neg_exp;
    else
      _neg = !_neg;
    return;
  }
  
  if(preset){	//Previous value is set
    preset = false;
    clear();
  }
  
  if(digit == dot){    //Take care of dot
    if(not (_has_dot || _exp_mode)){
      if(_num.size() < width - 7) {
	_num.append(1, digit);
	_has_dot = true;
	_init = false;
      }
    }
    return;
  }	
  
  if(_init){					//Remove zero
    if(digit == 'e' || digit == 'E' || digit == '0')
      return;
    
    _num.clear();
    _init = false;
  }
  
  if(digit == 'e' || digit == 'E'){						//Set exp mode
    _exp_mode = true;
    return;
  }
  
  if(_exp_mode){										//Add digit
    
    if(_exp.size() == 1 && _exp.at(0) == '0')
      _exp.clear();
    
    if(_exp.size() < 2)
      _exp.append(1, digit);
  }
  
  else if(_num.size() < width - 5)
    _num.append(1, digit);
}

string ViewArea::get_content(){
  string s;

  if(locked)
    s.append(1, 'E');
  
  else if(preset) {               //Set value
    if(!to_string(s, f_mod, value)) {
      locked = true;
      s.append(1, 'E');
    }
  }
  
  else {
    s.append(_num);		//Number
    
    if(_exp_mode){			//Exponent
      if(s[s.size() - 1] == dot)	//0 after dot
	s.append(1, '0');
      
      s.append(1, 'E');
      
      if(_neg_exp)
	s.append(1, '-');
      else
	s.append(1, '+');
      
      s.append(_exp);
      
      for(unsigned char n = 0; n < 2 - _exp.size(); n++)
	s.append(1, ' '); 
    }
    else
      s.append("    ");
    
    if(_neg == true)
      s.insert(0, 1, '-');
  }

  l_justify(s);
  
  return s;
}

void ViewArea::l_justify(string &s) {
  int m;
  
  if(s[0] == '-')
    m = 1;
  else
    m = 0;
  
  while(s.length() < width)
      s.insert(m, 1, ' ');
}

bool ViewArea::move_dot(string &s, const int &d) {
  bool neg, ready;	
  int exp;
  string t, u = string(s);	
  stringstream *ss;
  size_t i = s.find('E');
  
  if(i == string::npos)
    exp = 0;
  
  else {
    // = s.substr(i + 1, string::npos);
    exp = atoi(s.substr(i + 1, string::npos).c_str());
    u = u.erase(i, string::npos);
  }
  
  //remove sign
  i = u.find('-');
  if(i == 0) {
    neg = true;
    u.erase(i);
  }
  
  else
    neg = false;
  
  i = s.find('.');
  u.erase(i,1);
  
  if(abs((int)i + d) <= width - 5) {

  //Move dot to left
    if(((int)i + d) <= 0) {
      for(int n = abs((int)i + d); n > -1; n--) {
	u.insert(0, "0");
	u.erase(s.end()-1);
      }
      u.insert(1, ".");
    }
    
    else 
      u.insert(abs((int)i + d), ".");
    
    exp = exp - d;
    ss = new stringstream(stringstream::in | stringstream::out);
    *ss << showpos << exp;
    u.append("E");
    u.append(ss->str());
    if(neg)
      u.insert(0, 1, '-');
    delete ss;
    ready = true;
    s = u;
  }

  else
    ready = false;

  return ready;
}

string ViewArea::parse(const string &s) {
  bool has_exp = false, neg = false, neg_exp = false, dot = false;
  char other[] = ",.Ee-";
  size_t m, exp_pos = 0;
  string t;
  
  //remove unwanted characters
  for(size_t n = 0; n < s.length(); n++) { 
    m = 0;
    if(isdigit(s[n]))
      t.append(s.substr(n, 1));
    
    else{
      for(; m < strlen(other); m++) {
	if(other[m] == s[n]) {
	  if(other[m] == 'e' || other[m] == 'E') {
	    if(has_exp == false) {
	      has_exp = true;
	      exp_pos = t.length();
	      if(exp_pos == 0)
		t.append("0");
	      t.append("E");
	    }
	  }
	  else if(other[m] == '-') {
	    if(neg == false && has_exp == false && t.length() == 0) {
	      neg = true;
	      t.append("-");
	    }
	    else if(neg_exp == false && t.length() == exp_pos + 1) {
	      neg_exp = true;
	      t.append("-");
	    }
	  }
	  else if(other[m] == '.' || other[m] == ',') {
	    if(dot == false && has_exp == false) {
	      dot = true;
	      t.append(".");
	    }
	  }
	}
      }
    }
  } 
  return t;
}

void ViewArea::set_content(const string &s, const bool &ps) {
  size_t i;
  string t = parse(s);
  value = to_double(t);
  
  if(ps)
    preset = true;

  else {
    if(t[0] == '-') {
      _neg = true;
      t.erase(0, 1);
    }
    else
      _neg = false;
    
    i = t.find('E');
    if(i != string::npos) {
      _exp_mode = true;
      _num = t.substr(0, i);
      if(i + 1 <= t.length()) {
        if(t[i + 1] == '-') {
	  _neg_exp = true;
	  t.erase(i + 1, 1);
	}
	else
	  _neg_exp = false;
	
	if(i + 1 <= t.length())
	  _exp = t.substr(i + 1, string::npos);
      }	
    }

    else {
      _exp_mode = false;
      _num = t;
    }
  }
}

void ViewArea::set_value(const long double &v){
  value = v; 	
  preset = true;
}

long double ViewArea::to_double(const string &s) {
  long double v;
  stringstream ss(stringstream::in | stringstream::out);
  ss << s;
  ss >> v;
  return(v);
}

bool ViewArea::to_string(string &s, const size_t &m, const long double &v) {
  bool ready;
  size_t i;
  int j, k;
  char cs[] = "-+E";
  string t;
  stringstream *ss = new stringstream(stringstream::in | stringstream::out);
  
  switch(m) {
  case MD_FIX:
    ss->precision(prec);
    *ss << uppercase << fixed << v;
    s = ss->str();
    t = s;
    
    //remove +-E
    for(i = 0; i < strlen(cs); ++i) {
      j = t.find(cs[i]);
      if(j != string::npos)
	t.erase(j);
    }
    
     //count overflow digits
    k = (width - 5) - t.length();
    
    //if too much digits
    if(k < 0) {
      //find .
      j = t.find('.');    
      delete ss;
      ss = new stringstream(stringstream::in | stringstream::out);
      
      //if enough decimals printed, remove overflow
      if(j != string::npos &&
	 t.length() - (t.length() - j) <= width) {
	if(prec + k < 0)
	  ss->precision(0);
	else
	  ss->precision(prec + k);
	
	*ss << uppercase << fixed << v;
	s = ss->str();
      }

      else {
	if(prec > width - 6)
	  ss->precision(width - 6);
	else
	  ss->precision(prec);
	
	*ss << uppercase << scientific << v;
	s = ss->str();
      }
    } 
    break;
      
  case MD_NORM:
    ss->precision(width - 5);
    *ss << uppercase << v;
    s = ss->str(); 
    break;
    
  case MD_SCI:
      ss->precision(width - 6);
      *ss << uppercase << scientific << v;
      s = ss->str();
      break;
  }
  delete ss;

  i = s.find('E');
  if(i != s.string::npos) {
    ss = new stringstream(stringstream::in | stringstream::out);
    t = s.substr(i + 1, string::npos);
    *ss << t;
    *ss >> j;

    if(j > 99)
      ready = move_dot(s, j - 99);

    else if(j < -99)
      ready = move_dot(s, j + 99);

    else
      ready = true;

    delete ss;
  }
  
  else
    ready = true;

  return ready;
}
