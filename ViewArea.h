/* Calc80 by Patrik Wallander */
/* License GPL2.  See COPYING for details of GPL2 License */
#include <sstream>
#include <string>

using namespace std;

class ViewArea{
public:
	void back_space();
	void clear();
	ViewArea();
	ViewArea(const int &p);
	void enter_digit(const char &d);
	string get_content();
	long double get_value(){return to_double(get_content());};
	void set_content(const string &s, const bool &ps);
	void set_value(const long double &v);
	long double to_double(const string &s);
	bool to_string(string &s, const size_t &m, const long double &v);
	char dot;
	int f_mod;
	bool locked;
	size_t prec;
	bool preset;
	long double value;
	size_t width;
	
private:
	void l_justify(string &s);
	bool move_dot(string &s, const int &d);
	string parse(const string &s);
	void toggle_sign();
	
	string _num;
	string _exp;
	bool _neg;
	bool _has_dot;
	bool _exp_mode;
	bool _init; 	
	bool _neg_exp;	
	bool _value_is_set;
};
