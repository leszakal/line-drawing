#include <iostream>
#include <vector>
#include <cmath>
#include "xiaolin_wu.h"

// integer part of x
int XiaolinWuLine::intPart(float x) {
	return floor(x);
}

float XiaolinWuLine::roundNum(float x) {
	return intPart(x + 0.5);
}

// fractional part of x
float XiaolinWuLine::fracPart(float x) {
	return (x - intPart(x));
}

float XiaolinWuLine::rFracPart(float x) {
	return 1 - fracPart(x);
}

void XiaolinWuLine::plotLineGradual(std::vector<Point>& points, int x0, int y0, int x1, int y1) {
	float intensity;
	float dx = x1 - x0;
	float dy = y1 - y0;

	if (dx == 0.0) {
		intensity = 1.0;
	}
	else {
		intensity = dy / dx;
	}

	float xend = roundNum(x0);
	float yend = y0 + intensity * (xend - x0);
	float xgap = rFracPart(x0 + 0.5);

	int xpxl_1 = xend;
	int ypxl_1 = intPart(yend);

	// Add points for plotting
	points.push_back(Point{ xpxl_1, ypxl_1, rFracPart(yend) * xgap });
	points.push_back(Point{ xpxl_1, ypxl_1 + 1, fracPart(yend) * xgap });

	float intersect_y = yend + intensity;

	xend = roundNum(x1);
	yend = y1 + intensity * (xend - x1);
	xgap = fracPart(x1 + 0.5);
	int xpxl_2 = xend;
	int ypxl_2 = intPart(yend);

	points.push_back(Point{ xpxl_2, ypxl_2, rFracPart(yend) * xgap });
	points.push_back(Point{ xpxl_2, ypxl_2 + 1, fracPart(yend) * xgap });

	for (int x = xpxl_1; x < xpxl_2; x++) {
		points.push_back(Point{ x, intPart(intersect_y), rFracPart(intersect_y) });
		points.push_back(Point{ x, intPart(intersect_y) + 1, fracPart(intersect_y) });
		intersect_y += intensity;
	}
}

void XiaolinWuLine::plotLineSteep(std::vector<Point>& points, int x0, int y0, int x1, int y1) {
	float intensity;
	float dx = x1 - x0;
	float dy = y1 - y0;

	if (dy == 0.0) {
		intensity = 1.0;
	}
	else {
		intensity = dx / dy;
	}

	float yend = roundNum(y0);
	float xend = x0 + intensity * (yend - y0);
	float ygap = rFracPart(y0 + 0.5);

	int ypxl_1 = yend;
	int xpxl_1 = intPart(xend);

	// Add points for plotting
	points.push_back(Point{ xpxl_1, ypxl_1, rFracPart(xend) * ygap });
	points.push_back(Point{ xpxl_1 + 1, ypxl_1, fracPart(xend) * ygap });

	float intersect_x = xend + intensity;

	yend = roundNum(y1);
	xend = x1 + intensity * (yend - y1);
	ygap = fracPart(y1 + 0.5);
	int ypxl_2 = yend;
	int xpxl_2 = intPart(xend);

	points.push_back(Point{ xpxl_2, ypxl_2, rFracPart(xend) * ygap });
	points.push_back(Point{ xpxl_2 + 1, ypxl_2, fracPart(xend) * ygap });

	for (int y = ypxl_1; y < ypxl_2; y++) {
		points.push_back(Point{ intPart(intersect_x), y, rFracPart(intersect_x) });
		points.push_back(Point{ intPart(intersect_x) + 1, y, fracPart(intersect_x) });
		intersect_x += intensity;
	}
}

// (x0, y0) start, (x1, y1) end
void XiaolinWuLine::plotLine(std::vector<Point>& points, int x0, int y0, int x1, int y1) {
	if (abs(y1 - y0) < abs(x1 - x0)) {
		if (x0 < x1) {
			plotLineGradual(points, x0, y0, x1, y1);
		}
		else {
			plotLineGradual(points, x1, y1, x0, y0);
		}
	}
	else {
		if (y0 < y1) {
			plotLineSteep(points, x0, y0, x1, y1);
		}
		else {
			plotLineSteep(points, x1, y1, x0, y0);
		}
	}
}