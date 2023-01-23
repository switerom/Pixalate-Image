#ifndef _RGBAPIXEL_H_
#define _RGBAPIXEL_H_

#include <iostream>
#include <sstream>

namespace util {
  class RGBAPixel {
  public:
    unsigned char r; 
    unsigned char g; 
    unsigned char b; 
    double a; 

    RGBAPixel();

    RGBAPixel(int red, int green, int blue);

    RGBAPixel(int red, int green, int blue, double alpha);

    RGBAPixel & operator=(RGBAPixel const & other);
    bool operator== (RGBAPixel const & other) const ;
    bool operator!= (RGBAPixel const & other) const ;
    bool operator<  (RGBAPixel const & other) const ;
  };

  std::ostream & operator<<(std::ostream & out, RGBAPixel const & pixel);
  std::stringstream & operator<<(std::stringstream & out, RGBAPixel const & pixel);
}

#endif