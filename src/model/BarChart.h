#include <algorithm>
#include <vector>

#include "./BarItem.h"

using items_type = vector<BarItem>;

bool comparison(const BarItem &a, const BarItem &b) {
  return a.value > b.value;
}

class BarChart {
 private:
  string timestamp;
  items_type items;

 public:
  string getTimestamp() {
    return this->timestamp;
  }
  items_type getItems() {
    return this->items;
  }
  void setTimestamp(const string timestamp) {
    this->timestamp = timestamp;
  }
  void addItem(const BarItem item) {
    this->items.push_back(item);
  }
  void sort() {
    std::sort(this->items.begin(), this->items.end(), comparison);
  }
};
