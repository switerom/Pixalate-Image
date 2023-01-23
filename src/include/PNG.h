#ifndef _PNG_H_
#define _PNG_H_

#include <string>
#include <vector>
#include "RGBAPixel.h"

using namespace std;

namespace util {
  class PNG {
  public:

    PNG();

    PNG(unsigned int width, unsigned int height);

    PNG(PNG const & other);

    ~PNG();

    PNG const & operator= (PNG const & other);

    bool operator== (PNG const & other) const;

    bool operator!= (PNG const & other) const;

    bool readFromFile(string const & fileName);

    bool writeToFile(string const & fileName);

    RGBAPixel * getPixel(unsigned int x, unsigned int y) const;

    unsigned int width() const;

    unsigned int height() const;

    void resize(unsigned int newWidth, unsigned int newHeight);

    std::size_t computeHash() const;

  private:
    unsigned int width_;          
    unsigned int height_;          
    RGBAPixel *imageData_;          
    RGBAPixel defaultPixel_;        

    /*
     * Copies the contents of `other` to self
     */
     void _copy(PNG const & other);
  };

  std::ostream & operator<<(std::ostream & out, PNG const & pixel);
  std::stringstream & operator<<(std::stringstream & out, PNG const & pixel);
}

#endif