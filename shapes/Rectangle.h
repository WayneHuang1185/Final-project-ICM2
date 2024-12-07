#ifndef RECTANGLE_H_INCLUDED
#define RECTANGLE_H_INCLUDED

#include "Shape.h"

/**
 * @see Shape.cpp
 */
class Rectangle : public Shape
{
public:
	bool overlap(const Shape &s) const;
	double center_x() const { return (x1 + x2) / 2; }
	double center_y() const { return (y1 + y2) / 2; }
	void update_center_x(const double &x) {
		double dx = x - center_x();
		x1 += dx, x2 += dx;
	}
	void update_center_y(const double &y) {
		double dy = y - center_y();
		y1 += dy, y2 += dy;
	}
	const ShapeType getType() const { return ShapeType::RECTANGLE; }
public:
	Rectangle() : type(0) {}
	Rectangle(double x1, double y1, double x2, double y2, int type, bool can_move = false, double dx = 0, double dy = 0) 
		: x1{x1}, y1{y1}, x2{x2}, y2{y2}, type{type}, can_move{can_move}, dx(dx), dy{dy} {}
	Rectangle(int x1, int y1, int x2, int y2, int type) :
		x1{static_cast<double>(x1)},
		y1{static_cast<double>(y1)},
		x2{static_cast<double>(x2)},
		y2{static_cast<double>(y2)}, 
		type{type} {}
	double x1, y1, x2, y2;
	int type;
	bool can_move;
	double dx, dy;
};

#endif
