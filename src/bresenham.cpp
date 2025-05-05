#include <iostream>
#include <stdlib.h>
#include "bresenham.h"

// (x0, y0) start, (x1, y1) end
void BresenhamLine::plotLine(std::vector<Point> &points, int x0, int y0, int x1, int y1) {
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

void BresenhamLine::plotLineGradual(std::vector<Point> &points, int x0, int y0, int x1, int y1) {
	int dx = x1 - x0;
	int dy = y1 - y0;
	int yi = 1;
	if (dy < 0) {
		yi = -1;
		dy = -dy;
	}
	int D = (2 * dy) - dx;
	int y = y0;

	for (int x = x0; x < x1; x++) {
		// Add point for plotting
		Point point{ x, y };
		points.push_back(point);
		if (D > 0) {
			y = y + yi;
			D = D + (2 * (dy - dx));
		}
		else {
			D = D + (2 * dy);
		}
	}
}

void BresenhamLine::plotLineSteep(std::vector<Point> &points, int x0, int y0, int x1, int y1) {
	int dx = x1 - x0;
	int dy = y1 - y0;
	int xi = 1;
	if (dx < 0) {
		xi = -1;
		dx = -dx;
	}
	int D = (2 * dx) - dy;
	int x = x0;

	for (int y = y0; y < y1; y++) {
		Point point{ x, y };
		points.push_back(point);
		if (D > 0) {
			x = x + xi;
			D = D + (2 * (dx - dy));
		}
		else {
			D = D + (2 * dx);
		}
	}
}