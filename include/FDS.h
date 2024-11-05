#ifndef FDS_H
#define FDS_H

#include <vector>
#include <iostream>
#include <queue>
#include "FDS.h"
#include "raylib.h"

using namespace std;

vector<pair<int, int>> FDS(int ix, int iy, int fx, int fy, int R, int C, int cellStates[20][20]);
#endif // D_H