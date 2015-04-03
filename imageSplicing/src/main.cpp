#include "splice.h"
#include <iostream>
#include "png.h"

int main()
{
    PNG inImg;
    inImg.readFromFile("test.png");

    Splice test(inImg);
    test.saveToDisk(string("random"));
    spliceRange_t x, y;
    x.begin = 300;
    x.end = 600;
    y.begin = 300;
    y.end = 600;
    PNG imgout = test.getImage(x, y);
    imgout.writeToFile("test2.png");
    return 0;

}
