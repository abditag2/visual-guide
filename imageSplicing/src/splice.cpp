#include "splice.h"

Splice::Splice()
{
    baseX = 0;
    baseY = 0;
    width = 0;
    height = 0;
}

Splice::Splice(PNG const & image)
{
    width = image.width();
    height = image.height();
    _determineBaseCase();
    std::cout << "Base x: " << baseX << " Base y: " << baseY << std::endl;
    root = _buildTreeHelper(image, 0, 0, width, height);
}

void Splice::_determineBaseCase()
{

    size_t tempWidth = width, tempHeight = height;
    int count = 0;

    while (tempWidth >> 1 > 100) 
    {
        count++;
        tempWidth >>= 1;
    }
    while (count-- != 0) tempHeight >>= 1;

    baseX = tempWidth;
    baseY = tempHeight;

}

void Splice::saveToDisk(std::string const & dirname)
{
    mkdir((string(dirname).append(".splice")).c_str(), 0777);
    _recursiveSaveImage(string(dirname).append(".splice"), root);
}

void Splice::_recursiveSaveImage(std::string const & dirname, quadTreeNode * subroot)
{
    if (subroot != NULL)
    {
        if (isLeaf(subroot))
        {
            subroot->data.writeToFile(string(dirname).append("/image.png"));
        }
        else
        {
            mkdir((string(dirname).append("/NW")).c_str(), 0777);
            mkdir((string(dirname).append("/SW")).c_str(), 0777);
            mkdir((string(dirname).append("/SE")).c_str(), 0777);
            mkdir((string(dirname).append("/NE")).c_str(), 0777);
            _recursiveSaveImage(string(dirname).append("/NW"), subroot->nwChild);
            _recursiveSaveImage(string(dirname).append("/SW"), subroot->swChild);
            _recursiveSaveImage(string(dirname).append("/SE"), subroot->seChild);
            _recursiveSaveImage(string(dirname).append("/NE"), subroot->neChild);
        }
    }
}

Splice::quadTreeNode * Splice::_buildTreeHelper(PNG const & image, int x, int y, int w, int h)
{
    quadTreeNode * newSubroot;

    // std::cout << "Current width: " << w << " Current height: " << h << std::endl;
    
    if (w <= (int) baseX || h <= (int) baseY)
    {
        newSubroot = new quadTreeNode(image, x, y, w, h);
        return newSubroot;
    }

    newSubroot = new quadTreeNode();
    newSubroot->neChild = _buildTreeHelper(image, x + w/2, y, w/2, h/2);
    newSubroot->nwChild = _buildTreeHelper(image, x, y, w/2, h/2);
    newSubroot->swChild = _buildTreeHelper(image, x, y + h/2, w/2, h/2);
    newSubroot->seChild = _buildTreeHelper(image, x + w/2, y + h/2, w/2, h/2);

    return newSubroot;
}

PNG Splice::getImage(spliceRange_t x, spliceRange_t y)
{
    _fitInsideImages(x, y);

    PNG generatedImage;
    generatedImage.resize((int) x.end - x.begin, (int) y.end - y.begin);

    _generateImage(generatedImage, root, 0, 0, x, y, width, height);

    return generatedImage;
}

void Splice::_generateImage(PNG & img, quadTreeNode * subroot, size_t currX, size_t currY, spliceRange_t & x, spliceRange_t & y, size_t resX, size_t resY)
{
    if (isLeaf(subroot))
    {
        if (currX >= x.begin && currX < x.end && currY >= y.begin && currY < y.end)
        {
            // get the valid offset
            int offsetX, offsetY;
            offsetX = currX / baseX - imgSaveOffsetX;
            offsetY = currY /baseY - imgSaveOffsetY;

            for (size_t i = 0; i < baseY; i++)
                for (size_t j = 0; j < baseX; j++)
                    *(img(offsetX * baseX + j, offsetY * baseY + i)) = *(subroot->data(j, i));
        }
        return;
    }

    _generateImage(img, subroot->nwChild, currX, currY, x, y, resX/2, resY/2);
    _generateImage(img, subroot->neChild, currX + resX/2, currY, x, y, resX/2, resY/2);
    _generateImage(img, subroot->swChild, currX, currY + resY/2, x, y, resX/2, resY/2);
    _generateImage(img, subroot->seChild, currX + resX/2, currY + resY/2, x, y, resX/2, resY/2);

}

void Splice::_fitInsideImages(spliceRange_t & x, spliceRange_t & y)
{
    int divisible = x.begin/baseX;
    x.begin = (float) divisible * baseX;
    divisible = y.begin/baseY;
    y.begin = (float) divisible * baseY;

    divisible = x.end/baseX + 1;
    x.end = (float) divisible * baseX;
    divisible = y.end/baseY + 1;
    y.end = (float) divisible * baseY;

    imgSaveOffsetX = x.begin/baseX;
    imgSaveOffsetY = y.begin/baseY;
}