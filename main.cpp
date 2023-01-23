#include "src/include/twoDtree.h"
#include "src/include/RGBAPixel.h"
#include "src/include/PNG.h"

using namespace util;
using namespace std;

int main() {

	PNG origImg1;

	//choose file to process
	origImg1.readFromFile("images/starry-night.png");

	twoDtree t1(origImg1);

	//modify paramters to get different effects
	t1.prune(0.99, 8500);

	PNG pic1 = t1.render();

	//write to file
	pic1.writeToFile("images/output-starry-night.png");
	
	return 0;
}