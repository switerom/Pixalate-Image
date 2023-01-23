all:
	g++ -o pixelate.exe src/RGBAPixel.cpp src/lodepng.cpp src/PNG.cpp main.cpp src/twoDtree.cpp src/stats.cpp