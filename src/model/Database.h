#include <iostream>
#include <map>

#include "../util/Color.h"
#include "./BarChart.h"

using namespace std;
using charts_type = map<string, BarChart *>;
using categories_type = map<string, short>;

class Database {
 private:
  charts_type charts;
  categories_type categories;
  string title;
  string label;
  string source;
  bool single_colored{false};

 public:
  string getTitle() {
    return this->title;
  }
  string getLabel() {
    return this->label;
  }
  string getSource() {
    return this->source;
  }
  bool isSingleColored() {
    return this->single_colored;
  }
  void setTitle(const string title) {
    this->title = title;
  }
  void setLabel(const string label) {
    this->label = label;
  }
  void setSource(const string source) {
    this->source = source;
  }
  charts_type getBarCharts() {
    return this->charts;
  }
  void addBarChart(BarChart *chart) {
    chart->sort();
    this->charts.insert(make_pair(chart->getTimestamp(), chart));

    auto items{chart->getItems()};
    for (auto item = items.begin(); item != items.end(); item++)
      this->categories.insert(make_pair(item->category, (Color::RED + this->categories.size())));

    if (this->categories.size() > 14)
      this->single_colored = true;
  }
  short getColor(const string category) {
    if (this->single_colored)
      return Color::CYAN;

    return this->categories.at(category);
  }
};
