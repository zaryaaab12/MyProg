#ifndef JEANS_H
#define JEANS_H

#include <iostream>
#include "Collection.h"

using namespace std;

enum class Jeans_colors {white, black, blue, grey, brown};
enum class Jeans_sizes {small, medium, large, xlarge};

class Jeans{
private: 
  Jeans_colors color;
  Jeans_sizes size;

public:
  Jeans();
  Jeans(Jeans_colors c, Jeans_sizes s);
  Jeans_colors get_color() const; 
  Jeans_sizes get_size() const;
  bool operator==(const Jeans& sb);
};

using CollectionJN = Collection<Jeans, Jeans_colors, Jeans_sizes>;

istream& operator>>(istream& is, CollectionJN& c);
ostream& operator<<(ostream& o, const Jeans& sb);

#endif
