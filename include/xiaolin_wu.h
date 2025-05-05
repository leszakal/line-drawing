#pragma once

#include <vector>
#include "point.h"

class XiaolinWuLine {
public:
	void plotLine(std::vector<Point>& points, int x0, int y0, int x1, int y1);

private:
	int intPart(float x);
	float roundNum(float x);
	float fracPart(float x);
	float rFracPart(float x);

	void plotLineGradual(std::vector<Point>& points, int x0, int y0, int x1, int y1);
	void plotLineSteep(std::vector<Point>& points, int x0, int y0, int x1, int y1);
};
