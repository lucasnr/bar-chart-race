
#include <fstream>
#include <iomanip>
#include <ios>
#include <iostream>
#include <thread>

#include "./model/Database.h"
#include "./util/message.h"

#define MAX 50

using namespace std;
using namespace Color;

void readFileAndFillDatabase(ifstream *file, Database *database) {
  BarChart *chart = nullptr;
  string line;

  for (unsigned short i{0}; i < 3; i++) {
    getline(*file, line);

    if (i == 1)
      database->setTitle(line);
    else if (i == 2)
      database->setLabel(line);
    else
      database->setSource(line);
  }

  unsigned short step{0};
  while (getline(*file, line)) {
    if (line.empty())
      continue;

    if (step == 0) {  // line with the amount of following items
      if (chart != nullptr)
        database->addBarChart(chart);

      step = atoi(line.c_str());
      chart = new BarChart();
      continue;
    }

    BarItem item;
    size_t position{0};
    string delimiter{","};
    string token;

    unsigned short token_count{0};
    while ((position = line.find(delimiter)) != string::npos) {
      token = line.substr(0, position);
      line.erase(0, position + delimiter.length());

      switch (token_count++) {
        case 0:
          chart->setTimestamp(token);
          break;
        case 1:
          item.label = token;
          break;
        case 2:
          item.related = token;
          break;
        case 3:
          item.value = atof(token.c_str());
          break;
        default:
          break;
      }
    }
    item.category = line;

    chart->addItem(item);
    step--;
  }
}

int main() {
  string filename{"../data/cities.txt"};
  cout << "The filename is: " << filename << endl;

  ifstream file(filename);
  if (!file.good()) {
    file.close();
    return 1;
  }

  Database *database = new Database();
  readFileAndFillDatabase(&file, database);
  file.close();

  int fps{12};
  stringstream string_stream;
  auto charts{database->getBarCharts()};

  for (auto entry = charts.begin(); entry != charts.end(); entry++) {
    auto chart{entry->second};
    auto items{chart->getItems()};

    auto first_value{items.begin()->value};
    for (auto item = items.begin(); item != items.end(); item++) {
      auto length{(item->value * MAX) / first_value};
      auto color{database->getColor(item->category)};

      string_stream.str(string());
      string_stream << " " << setfill('.') << setw(length) << " ";
      cout << tcolor(string_stream.str(), color, REVERSE);

      string_stream.str(string());
      string_stream << " " << item->label << " (" << item->value << ")";
      cout << tcolor(string_stream.str(), color) << endl
           << endl;
    }

    cout << endl
         << endl;

    chrono::milliseconds duration{1000 / fps};
    this_thread::sleep_for(duration);
  }

  message::success("Normal shutoff");
  return 0;
}
