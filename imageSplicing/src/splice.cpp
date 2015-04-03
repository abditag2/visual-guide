/*
 *   @author  Jeffrey Huang
 *   @date    04/03/2015
 *   @file    splice.cpp
 *   
 *   @implementation  Stores a image inside a large image inside a quadtree structure and
 *                    allows you to store it inside a folder hierarchy on disk and grabs a
 *                    subset of the whole image for PURE research
 *
*/

#include "splice.h"

Splice::Splice()
{
    baseX = 0;
    baseY = 0;
    width = 0;
    height = 0;
    disk = 0;
}

Splice::Splice(PNG const & image)
{
    width = image.width();
    height = image.height();
    _determineBaseCase();
    disk = 0;
    std::cout << "Base x: " << baseX << " Base y: " << baseY << std::endl;
    root = _buildTreeHelper(image, 0, 0, width, height);
}

Splice::Splice(std::string const & filename)
{
    file = string(filename);
    disk = 1;
}

Splice::Splice(Splice const & other)
{
    _copy(other);
}

Splice & Splice::operator=(Splice const & other)
{
    if (this != &other)
    {
        _deleteTree(root);
        _copy(other);
    }

    return *this;
    
}

void Splice::_copy(Splice const & other)
{
    width = other.width;
    height = other.height;
    baseX = other.baseX;
    baseY = other.baseY;
    imgSaveOffsetX = other.imgSaveOffsetX;
    imgSaveOffsetY = other.imgSaveOffsetY;
    disk = other.disk;
    root = _copyTreeRecursive(other.root);
}

Splice::quadTreeNode * Splice::_copyTreeRecursive(Splice::quadTreeNode const * subroot)
{
    if (subroot != NULL)
    {
        quadTreeNode * newSubroot = new quadTreeNode(*subroot);

        if (isLeaf(subroot))
        {
            return newSubroot;
        }

        newSubroot->nwChild = _copyTreeRecursive(subroot->nwChild);
        newSubroot->neChild = _copyTreeRecursive(subroot->neChild);
        newSubroot->swChild = _copyTreeRecursive(subroot->swChild);
        newSubroot->seChild = _copyTreeRecursive(subroot->seChild);
        return newSubroot;
    }
    return NULL;
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
    std::ofstream metadata;
    metadata.open(string(dirname).append(".splice").append("/").append(".metadata"));

    // Save the meta data to use when we don't have it in ram
    metadata << width << std::endl << 
                height << std::endl << 
                baseX << std::endl << 
                baseY << std::endl << 
                imgSaveOffsetX << std::endl << 
                imgSaveOffsetY << std::endl;

    _deleteTree(root);
    file = dirname;
    disk = 1;
}

void Splice::saveToDisk(char const * dirname)
{
    if (dirname == NULL)
    {
        std::cout << "Please enter a valid filename" << std::endl;
    }
    saveToDisk(string(dirname));
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

splicedImage_t Splice::getImage(char const * fname, spliceRange_t x, spliceRange_t y)
{
    if (fname == NULL)
    {
        error("Please enter a valid filename");
    }
    return getImage(std::string(fname), x, y);
}

splicedImage_t Splice::getImage(std::string const & fname, spliceRange_t x, spliceRange_t y)
{

    std::ifstream metadata;
    metadata.open(string(fname).append(".splice").append("/").append(".metadata"));
    std::string line;
    std::vector<int> meta;
    if (!metadata.is_open())
    {
        error("Error File does not exist");
        splicedImage_t newPNG;
        return newPNG;
    }

    while (getline(metadata, line))
    {
        meta.push_back(stol(line));
    }

    width = meta[0];
    height = meta[1];
    baseX = meta[2];
    baseY = meta[3];
    imgSaveOffsetX = meta[4];
    imgSaveOffsetY = meta[5];

    std::cout << "Width: " << width << " Height: " << height << std::endl;
    std::cout << "BaseX: " << baseX << " BaseY: " << baseY << std::endl;


    _fitInsideImages(x, y);

    splicedImage_t splicedImg;
    splicedImg.image.resize((int) x.end - x.begin, (int) y.end - y.begin);
    splicedImg.xres = (int) x.end - x.begin;
    splicedImg.yres = (int) y.end - y.begin;

    _generateImageOnDisk(splicedImg.image, string(fname).append(".splice"), 0, 0, x, y, width, height);

    return splicedImg;
}

void Splice::_generateImageOnDisk(PNG & generatedImage, string const & fname, size_t currX, size_t currY, spliceRange_t x, spliceRange_t y, size_t resX, size_t resY)
{
    std::ifstream img;
    img.open(string(fname).append("/image.png"));

    if (img.is_open())
    {
        if (currX >= x.begin && currX < x.end && currY >= y.begin && currY < y.end)
        {
            int offsetX, offsetY;
            PNG data(string(fname).append("/image.png"));
            offsetX = currX / baseX - imgSaveOffsetX;
            offsetY = currY /baseY - imgSaveOffsetY;

            for (size_t i = 0; i < baseY; i++)
                for (size_t j = 0; j < baseX; j++)
                    *(generatedImage(offsetX * baseX + j, offsetY * baseY + i)) = *(data(j, i));
        }
        img.close();
        return;
    }

    _generateImageOnDisk(generatedImage, string(fname).append("/NW"), currX, currY, x, y, resX/2, resY/2);
    _generateImageOnDisk(generatedImage, string(fname).append("/NE"), currX + resX/2, currY, x, y, resX/2, resY/2);
    _generateImageOnDisk(generatedImage, string(fname).append("/SW"), currX, currY + resY/2, x, y, resX/2, resY/2);
    _generateImageOnDisk(generatedImage, string(fname).append("/SE"), currX + resX/2, currY + resY/2, x, y, resX/2, resY/2);

}

splicedImage_t Splice::getImage(spliceRange_t x, spliceRange_t y)
{
    if (disk == 1)
    {
        return getImage(file, x, y);
    }
    _fitInsideImages(x, y);

    splicedImage_t splicedImg;
    splicedImg.image.resize((int) x.end - x.begin, (int) y.end - y.begin);
    splicedImg.xres = (int) x.end - x.begin;
    splicedImg.yres = (int) y.end - y.begin;

    _generateImage(splicedImg.image, root, 0, 0, x, y, width, height);

    return splicedImg;
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

Splice::~Splice()
{
    _deleteTree(root);
}

void Splice::_deleteTree(Splice::quadTreeNode *& subroot)
{
    if (subroot != NULL)
    {
        if (isLeaf(subroot))
        {
            delete subroot;
            subroot = NULL;
            return;
        }
        _deleteTree(subroot->neChild);
        _deleteTree(subroot->nwChild);
        _deleteTree(subroot->swChild);
        _deleteTree(subroot->seChild);
        return;
    }
}