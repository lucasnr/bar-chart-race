#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

namespace message {

using namespace Color;

void print(const string& msg, short color) {
  cout << tcolor(msg, color) << endl;
}

void danger(const string& msg) { print(msg, RED); }
void info(const string& msg) { print(msg, BLUE); }
void success(const string& msg) { print(msg, GREEN); }
void warning(const string& msg) { print(msg, YELLOW); }

inline string inline_danger(const string& msg) {
  return tcolor(msg, RED, BOLD);
}
inline string inline_info(const string& msg) {
  return tcolor(msg, BLUE, BOLD);
}
inline string inline_success(const string& msg) {
  return tcolor(msg, GREEN, BOLD);
}
inline string inline_warning(const string& msg) {
  return tcolor(msg, YELLOW, BOLD);
}

}  // namespace message

#endif
