#pragma once

#include <vector>
#include "point.h"

class BresenhamLine {
public:
	void plotLine(std::vector<Point> &points, int x0, int y0, int x1, int y1);

private:
	void plotLineGradual(std::vector<Point> &points, int x0, int y0, int x1, int y1);
	void plotLineSteep(std::vector<Point> &points, int x0, int y0, int x1, int y1);
};
