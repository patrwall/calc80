/* Calc80 by Patrik Wallander */
/* License GPL2.  See COPYING for details of GPL2 License */
#include <cmath>
#include <stack>
#include "Operation.h"
#include "ViewArea.h"


class Calculator {
 public:
	Calculator();
	string cmd(const int &o, const string &s);
	string fmod_ind();
	string mem_ind();
	string nr_of_brackets();
	string precision(const size_t &p);	
	string set_content(const string &s);
	string tmod_ind();
	string width(const size_t &w);
	bool m_active;
	
 private:
	bool binary(const size_t &o, long double &v1, const long double &v2);
	void calc(const size_t &o);
	void from_rad(long double &a);
	void to_zero(long double &v);
	bool is_zero(const long double &v);
	void to_rad(long double &a);
	bool unary(const size_t &o, long double &v);
	
	bool _askprec;
	unsigned int _brackets;
	long double _mem;
	stack<Operation> _ostack;
	Operation _preop;
	int _tmod;
	stack<long double> _vstack;
	ViewArea _varea;
};
