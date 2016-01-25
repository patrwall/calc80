/* Calc80 by Patrik Wallander */
/* License GPL2.  See COPYING for details of GPL2 License */
#include "MyMenuBar.h"
#include <cstdio>

int MyMenuBar::handle(int event) {
const Fl_Menu_Item* v;
  if (menu() && menu()->text) switch (event) {
  case FL_ENTER:
  case FL_LEAVE:
    return 1;
  case FL_PUSH:
    v = 0;
  J1:
    v = menu()->pulldown(x(), y(), w(), h(), v, this, 0, 1);
    picked(v);
    return 1;
  case FL_SHORTCUT:
    if (visible_r()) {
      v = menu()->find_shortcut(0, true);
      if (v && v->submenu()) goto J1;
    }
    if (Fl::event_key() == 65027) {
      v = (Fl_Menu_Item*)this -> menu();
      goto J1;
    }
        
    return test_shortcut() != 0;
  }
  return 0;
}



