#include "splice.h"
#include <iostream>
#include "png.h"

int main()
{
    PNG inImg;
    inImg.readFromFile("test.png");

    Splice test(inImg);
    test.saveToDisk("Super");
    spliceRange_t x, y;
    x.begin = 12;
    x.end = 800;
    y.begin = 2;
    y.end = 989;
    PNG imgout;

    imgout = test.getImage(string("Super"), x, y);
    imgout.writeToFile("test3.png");

    return 0;

}
