
#ifndef ITEM_H
#define ITEM_H
// Item class represents an item with a weight and a value
class Item {
public:
  long long weight;
  long long value;
  Item(long long w, long long v) : weight(w), value(v) {}
};

#endif

