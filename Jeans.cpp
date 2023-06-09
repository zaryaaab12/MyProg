#include "Jeans.h"

// implementation of class Jeans
//...

// default constructor
Jeans::Jeans()
{
    // random
    color = (Jeans_colors)(rand() % 4);
    size = (Jeans_sizes)(rand() % 3);
}

// constructor
Jeans::Jeans(Jeans_colors c, Jeans_sizes s)
{
    color = c;
    size = s;
}

// method functions
Jeans_colors Jeans::get_color( ) const
{
    return color;
}

Jeans_sizes Jeans::get_size() const
{
    return size;
}

bool Jeans::operator==(const Jeans& sb)
{
    return (this->color == sb.color && this->size == sb.size);
}

ostream& operator<<(ostream& os, const Jeans& sb)
{
    os << "(";
    Jeans_colors color = sb.get_color();
    Jeans_sizes size = sb.get_size();
    if (color == Jeans_colors::white)
        os << "white, ";
    else if (color == Jeans_colors::black)
        os << "black, ";
    else if (color == Jeans_colors::blue)
        os << "blue, ";
    else if (color == Jeans_colors::grey)
        os << "grey, ";
    else if (color == Jeans_colors::brown)
        os << "brown, ";
    
    if (size == Jeans_sizes::xlarge) 
        os << "xlarge)";
    else if (size == Jeans_sizes::large)
        os << "large)";
    else if (size == Jeans_sizes::medium)
        os << "medium)";
    else if (size == Jeans_sizes::small)
        os << "small)";

    return os;
}

istream& operator>>(istream& is, CollectionJN& c) 
{
    string color, size;
    is >> color >> size;
    Jeans_colors c_color;
    Jeans_sizes c_size;
    if (color == "white")
        c_color = Jeans_colors::white;
    else if (color == "black")
        c_color = Jeans_colors::black;
    else if (color == "blue")
        c_color = Jeans_colors::blue;
    else if (color == "grey")
        c_color = Jeans_colors::grey;

    if (size == "xlarge")
        c_size = Jeans_sizes::xlarge;
    else if (size == "large")
        c_size = Jeans_sizes::large;
    else if (size == "medium")
        c_size = Jeans_sizes::medium;
    else if (size == "small")
        c_size = Jeans_sizes::small;

    Jeans j(c_color, c_size);
    c.insert_item(j);
    return is;
}
