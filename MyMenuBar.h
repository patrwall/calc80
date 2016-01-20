/* Calc80 by Patrik Wallander */
/* License GPL2.  See COPYING for details of GPL2 License */
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Menu_Bar.H>

class MyMenuBar : public Fl_Menu_Bar {
 public:
 MyMenuBar(int X,int Y,int W,int H,const char*L=0) : Fl_Menu_Bar(X,Y,W,H,L) {
  }
  
 private:
  int handle(int event);	
};
