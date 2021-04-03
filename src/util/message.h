#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>
#include <sstream>
#include <string>
using namespace std;

namespace Color {

//=== Color attribute
static constexpr short RED{31};
static constexpr short GREEN{32};
static constexpr short YELLOW{33};
static constexpr short BLUE{34};
static constexpr short MAGENTA{35};
static constexpr short CYAN{36};
static constexpr short WHITE{37};
static constexpr short BRIGHT_RED{91};
static constexpr short BRIGHT_GREEN{92};
static constexpr short BRIGHT_YELLOW{93};
static constexpr short BRIGHT_BLUE{94};
static constexpr short BRIGHT_MAGENTA{95};
static constexpr short BRIGHT_CYAN{96};
static constexpr short BRIGHT_WHITE{97};
//=== Modificators.
static constexpr short REGULAR{0};
static constexpr short BOLD{1};
static constexpr short UNDERLINE{4};
static constexpr short BLINK{5};
static constexpr short REVERSE{7};

inline string tcolor(const string& msg, short color = Color::WHITE,
                     short modifier = Color::REGULAR) {
  ostringstream oss;
  oss << "\e[" << modifier << ";" << color << "m" << msg << "\e[0m";
  return oss.str();
}
}  // namespace Color

namespace message {

using namespace Color;

void print(const string& msg, short color) {
  std::cout << tcolor(msg, color) << endl;
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
