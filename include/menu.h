#pragma once
#include "bresenham.h"
#include "xiaolin_wu.h"

void showMainMenu();
void showRenderPresetsMenu(BresenhamLine bresenham, XiaolinWuLine wu);
void showCustomRenderMenu(BresenhamLine bresenham, XiaolinWuLine wu);
void showTimeTestsHelp();
void showTimeTestsMenu(BresenhamLine bresenham, XiaolinWuLine wu);