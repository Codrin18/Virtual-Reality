#include <cmath>
#include <iostream>
#include <string>

#include "Vector.h"
#include "Line.h"
#include "Geometry.h"
#include "Sphere.h"
#include "Image.h"
#include "Color.h"
#include "Intersection.h"
#include "Material.h"

#include "Scene.h"

using namespace std;
using namespace rt;

float imageToViewPlane(int n, int imgSize, float viewPlaneSize) {
    float u = (float)n*viewPlaneSize / (float)imgSize;
    u -= viewPlaneSize / 2;
    return u;
}

const Intersection findFirstIntersection(const Line& ray,
    float minDist, float maxDist) {
    Intersection intersection;

    for (int i = 0; i < geometryCount; i++) {
        Intersection in = scene[i]->getIntersection(ray, minDist, maxDist);
        if (in.valid()) {
            if (!intersection.valid()) {
                intersection = in;
            }
            else if (in.t() < intersection.t()) {
                intersection = in;
            }
        }
    }

    return intersection;
}

int main() {
    Vector viewPoint(-50, 10, 0);
    Vector viewDirection(50, -10, 100);
    Vector viewUp(0, -1, 0);

	viewDirection.normalize();
	viewUp.normalize();

    float frontPlaneDist = 0;
    float backPlaneDist = 1000;

    float viewPlaneDist = 65;
    float viewPlaneWidth = 160;
    float viewPlaneHeight = 120;

    int imageWidth = 1024;
    int imageHeight = 768;

    Vector viewParallel = viewUp^viewDirection;
    viewParallel.normalize();

    Image image(imageWidth, imageHeight);

	// ADD CODE HERE
	for (auto i = 0; i < imageWidth; i++)
	{
		for (auto j = 0; j < imageHeight; j++)
		{
			auto realW = imageToViewPlane(i, imageWidth, viewPlaneWidth);
			auto realH = imageToViewPlane(j, imageHeight, viewPlaneHeight);
			Vector onPlaneHVector = viewUp * realH;
			Vector onPlaneWVector = viewParallel * realW;
			Vector viewVector = viewDirection * viewPlaneDist;
			Vector pointVector = viewPoint + viewVector + onPlaneHVector + onPlaneWVector;
			Line line = Line(viewPoint, pointVector, false);

			Intersection in = findFirstIntersection(line, frontPlaneDist, backPlaneDist);

			if (in.valid())
			{
				image.setPixel(i, j, in.geometry()->color());
			}
			else
			{
				image.setPixel(i, j, Color{ 0,0,0 });
			}
		}
	}

	

    image.store("scene.png");

    for (int i = 0; i < geometryCount; i++) {
        delete scene[i];
    }

	for (int i = 0; i < lightCount; i++) {
		delete lights[i];
	}

    return 0;
}
