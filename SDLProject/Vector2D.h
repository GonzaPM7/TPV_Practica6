#pragma once

#include <iostream>

using namespace std;

class Vector2D {
	double x_;  // first coordinate
	double y_;  // second coordinate
public:
	Vector2D();
	Vector2D(const Vector2D &v);
	Vector2D(double x, double y);
	virtual ~Vector2D();
	double getX() const;
	double getY() const;
	void setX(double x);
	void setY(double y);
	void set(const Vector2D &v);
	void set(double x, double y);
	double magnitude() const;
	Vector2D rotate(double degrees);
	double angle(const Vector2D& v) const;
	Vector2D normalize();

	Vector2D operator-(const Vector2D& v) const;
	Vector2D operator+(const Vector2D& v) const;
	Vector2D operator*(double d) const;
	double operator *(const Vector2D& d) const;
	Vector2D operator/(double d) const;
	friend ostream& operator<<(ostream& os, const Vector2D &v);
};
