
#include <string.h>

#include <fstream>
#include <iomanip>
#include <ios>
#include <iostream>
#include <thread>

#include "./model/Database.h"
#include "./util/message.h"

#define MAX 50

using namespace std;
using std::cout;

using namespace Color;

void read_file_and_fill_database(ifstream *file, Database *database, const int &max_bars) {
  BarChart *chart = nullptr;
  string line;

  for (unsigned short i{0}; i < 3; i++) {
    getline(*file, line);

    if (i == 0)
      database->setTitle(line);
    else if (i == 1)
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

    if (chart->getItems().size() >= max_bars) {
      step--;
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

string build_header(const string title, const string timestamp) {
  stringstream header;

  string label{"Time stamp: " + timestamp};

  header << "" << setw(MAX - (title.length() / 2)) << "" << title << endl;
  header << "" << setw(MAX - (label.length() / 2)) << ""
         << label << endl;

  return message::inline_info(header.str());
}

string build_footer(Database *database) {
  stringstream footer;
  footer << tcolor(database->getLabel(), YELLOW, BOLD) << endl
         << endl;

  footer << tcolor(database->getSource(), WHITE, BOLD) << endl;

  if (database->isSingleColored())
    return footer.str();

  auto categories{database->getCategories()};
  for (auto item = categories.begin(); item != categories.end(); item++) {
    auto color{item->second};
    footer << tcolor(" ", color, REVERSE) << ": " << tcolor(item->first, color, BOLD) << " ";
  }
  footer << endl;

  return footer.str();
}

void print_charts(const int &fps, Database *database) {
  auto title{database->getTitle()};
  auto charts{database->getBarCharts()};

  stringstream string_stream;
  stringstream string_chart;

  for (auto entry = charts.begin(); entry != charts.end(); entry++) {
    string_chart.str(string());

    auto chart{entry->second};
    auto items{chart->getItems()};

    auto first_value{items.begin()->value};
    for (auto item = items.begin(); item != items.end(); item++) {
      auto length{(item->value * MAX) / first_value};
      auto color{database->getColor(item->category)};

      // prints the bar
      string_stream.str(string());
      string_stream << " " << setfill('.') << setw(length) << "";
      string_chart << tcolor(string_stream.str(), color, REVERSE);

      // prints the label and value
      string_chart << " " << tcolor(item->label, color);
      string_chart << " (" << item->value << ")" << endl
                   << endl;
    }

    cout << build_header(title, chart->getTimestamp()) << endl;
    cout << string_chart.str() << endl;
    cout << build_footer(database) << endl;

    chrono::milliseconds duration{1000 / fps};
    this_thread::sleep_for(duration);
  }
}

int main(int argc, char **argv) {
  if (argc % 2 != 0) {
    message::danger("Invalid arguments");
    return 1;
  }

  if (argc <= 1) {
    message::danger("No filename was provided");
    return 1;
  }

  int fps{24}, max_bars{15};
  for (int i{1}; i < argc - 1; i++)
    if (i % 2 != 0)
      if (strcmp(argv[i], "-b") == 0) {
        auto arg_max_bars = atoi(argv[i + 1]);
        if (arg_max_bars > 0 && arg_max_bars < 15)
          max_bars = arg_max_bars;
      } else if (strcmp(argv[i], "-f") == 0) {
        auto arg_fps = atoi(argv[i + 1]);
        if (arg_fps > 0 && arg_fps < 24)
          fps = arg_fps;
      }

  string filename{argv[argc - 1]};
  cout << "The provided filename was: " << filename << endl;

  ifstream file(filename);
  if (!file.good()) {
    message::danger("No file was not found with the provided filename");
    file.close();
    return 1;
  }

  message::success("The provided file was found");
  message::info("Reading file...");

  Database *database = new Database();
  read_file_and_fill_database(&file, database, max_bars);
  file.close();

  message::success("File successfully read");

  cout << endl
       << "File info: " << endl
       << tcolor(database->getTitle(), WHITE, BOLD) << endl
       << tcolor(to_string(database->getBarCharts().size()) + " bar charts", WHITE, BOLD) << endl
       << tcolor(database->getSource(), WHITE, BOLD) << endl
       << endl;

  message::info("Press any key to proceed to the animation...");
  cin.get();

  print_charts(fps, database);
  return 0;
}
