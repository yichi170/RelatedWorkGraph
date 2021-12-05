#include <cstdint>
#include <algorithm>
#include <utility>
#include <iostream>
#include <random>

class Coord {
public:
	Coord(double x, double y, int coord_type, int mass = 1)		// default constructor
	: x(x), y(y), coord_type(coord_type), mass(mass) {}

	Coord(Coord const & other)					// copy constructor
	: x(other.x), 
	  y(other.y), 
	  coord_type(other.coord_type) {}

	Coord & operator=(Coord const & other) {	// copy assignment
		if (this == &other)	{ return *this; }
		x = other.x;
		y = other.y;
		coord_type = other.coord_type;
		return *this;
	}

	Coord(Coord && other) {						// move constructor
		std::swap(other.x, x);
		std::swap(other.y, y);
		std::swap(other.coord_type, coord_type);
	}

	Coord & operator=(Coord && other) {			// move assignment
		if (this == &other)	{ return *this; }
		std::swap(other.x, x);
		std::swap(other.y, y);
		std::swap(other.coord_type, coord_type);
		return *this;
	}

	~Coord() {}									// destructor

	Coord operator+(const Coord &);
	Coord & operator+=(const Coord &);
	Coord operator-(const Coord &);
	Coord & operator-=(const Coord &);
	Coord operator*(const Coord &);
	Coord & operator*=(const Coord &);
	Coord operator*(const double &);
	Coord & operator*=(const double &);
	double dist(const Coord &, const Coord &);
	friend std::ostream& operator<<(std::ostream& os, const Coord& cod);

public:
	double x, y;
	int coord_type; // 1 for node, 0 for vector
	int mass;
};

bool operator==(Coord const &, Coord const &);
bool operator!=(Coord const &, Coord const &);
double dist(const Coord &, const Coord &);
Coord min_with_scalar(const Coord &, double);