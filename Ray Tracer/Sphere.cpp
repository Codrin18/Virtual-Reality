#include "Sphere.h"

using namespace rt;

Intersection Sphere::getIntersection(const Line& line, float minDist, float maxDist) {
	Intersection in;

	// ADD CODE HERE
	const auto A = line.dx() * line.dx();
	const auto B = (line.dx() + line.dx()) * (line.x0() - this->center());
	const auto C = (line.x0() - this->center()) * (line.x0() - this->center()) - this->radius() * this->radius();

	const auto discriminant = B * B - 4 * A * C;

	if (discriminant >= 0)
	{
		auto x = ((-1) * B + sqrt(discriminant)) / (2 * A);
		in._valid = true;
		in._geometry = this;
		in._t = x;
	}
	else
	{
		in._valid = false;
	}


    return in;
}


const Vector Sphere::normal(const Vector& vec) const {
    Vector n = vec - _center;
    n.normalize();
    return n;
}
