#ifndef _STATS_H
#define _STATS_H

#include "PNG.h"
#include "RGBAPixel.h"
#include <utility>
#include <vector>

using namespace std;
using namespace util;

class stats {
private:
	vector< vector< long >> sumRed;
	vector< vector< long >> sumGreen;
	vector< vector< long >> sumBlue;
	vector< vector< long >> sumsqRed;
	vector< vector< long >> sumsqGreen;
	vector< vector< long >> sumsqBlue;

	long getSum(char channel, pair<int,int> ul, pair<int,int> lr);

	long getSumSq(char channel, pair<int,int> ul, pair<int,int> lr);

public:

	stats(PNG & im); 

	long getScore(pair<int,int> ul, pair<int,int> lr);

	RGBAPixel getAvg(pair<int,int> ul, pair<int,int> lr);

	long rectArea(pair<int,int> ul, pair<int,int> lr);
};

#endif