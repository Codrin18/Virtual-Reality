#include "Sphere.h"

using namespace rt;

Intersection Sphere::getIntersection(const Line& line, float minDist, float maxDist) {
	//Intersection in;

	// ADD CODE HERE
	const auto A = line.dx() * line.dx();
	const auto B = (line.dx() + line.dx()) * (line.x0() - this->center());
	const auto C = (line.x0() - this->center()) * (line.x0() - this->center()) - this->radius() * this->radius();

	auto discriminant = B * B - 4 * A * C;
	float x;

	if (discriminant < 0)
	{
		return Intersection(false, this, &line, 0);
	}

	discriminant = sqrt(discriminant);

	float x0 = (-B + discriminant) / (2 * A);

	float x1 = (-B - discriminant) / (2 * A);

	if (x0 < x1)
	{
		x = x0;
	}
	else
	{
		x = x1;
	}

	if (x < minDist || x > maxDist)
	{
		return Intersection(false, this, &line, 0);
	}

	

    return Intersection(true,this,&line,x);
}


const Vector Sphere::normal(const Vector& vec) const {
    Vector n = vec - _center;
    n.normalize();
    return n;
}
