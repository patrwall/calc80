/* Calc80 by Patrik Wallander */
/* License GPL2.  See COPYING for details of GPL2 License */
class Operation {
public:
  Operation();
  Operation(const unsigned char &o);

  unsigned char index;
  unsigned char prio;
  unsigned char op;
};

	
	
