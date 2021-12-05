#include "node.hpp"

#include <cmath>

Coord Coord::operator+(const Coord &other) {
	return Coord(
		this->x + other.x, 
		this->y + other.y, 
		this->coord_type);
}

Coord & Coord::operator+=(const Coord &other) {
	this->x += other.x;
	this->y += other.y;
	return *this;
}

Coord Coord::operator-(const Coord &other) {
	return Coord(
		this->x - other.x, 
		this->y - other.y, 
		this->coord_type - other.coord_type);
}

Coord & Coord::operator-=(const Coord &other) {
	this->x -= other.x;
	this->y -= other.y;
	this->coord_type -= other.coord_type;
	return *this;
}

Coord Coord::operator*(const Coord &other) {
	return Coord(
		this->x * other.x, 
		this->y * other.y, 
		this->coord_type * other.coord_type);
}

Coord & Coord::operator*=(const Coord &other) {
	this->x *= other.x;
	this->y *= other.y;
	this->coord_type *= other.coord_type;
	return *this;
}

Coord Coord::operator*(const double &constant) {
	return Coord(
		this->x * constant, 
		this->y * constant, 
		this->coord_type);
}

Coord & Coord::operator*=(const double &constant) {
	this->x *= constant;
	this->y *= constant;
	return *this;
}

bool operator==(Coord const & cod1, Coord const & cod2) {
	return (cod1.x == cod2.x) && (cod1.y == cod1.y) && (cod1.coord_type == cod2.coord_type);
}

bool operator!=(Coord const & cod1, Coord const & cod2) {
	return !(cod1 == cod2);
}

std::ostream& operator<<(std::ostream& os, const Coord& cod) {
	os << "coordinate: (" << cod.x << ", " << cod.y << ")" << '\n';
	os << "type: " << cod.coord_type << '\n';
    return os;
}

double dist(const Coord &a, const Coord &b) {
	double x = a.x - b.x;
	double y = a.y - b.y;
	return sqrt(x*x + y*y);
}

Coord min_with_scalar(const Coord &cod, double c) {
	return Coord(
		std::min(cod.x, c), 
		std::min(cod.y, c), 
		1
	);
}