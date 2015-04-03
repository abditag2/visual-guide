/*
 *   @author  Jeffrey Huang
 *            04/03/2015
 *   @class   Splice
 *   
 *   @implementation  Stores a image inside a large image inside a quadtree structure and
 *                    allows you to store it inside a folder hierarchy on disk and grabs a
 *                    subset of the whole image
 *
 *
*/

#ifndef _SPLICE_H_
#define _SPLICE_H_

#include <iostream>
#include <string>
#include "rgbapixel.h"
#include "PNG.h"
#include <sys/stat.h>


#define isLeaf(subroot) subroot->nwChild == NULL && \
                        subroot->neChild == NULL && \
                        subroot->swChild == NULL && \
                        subroot->seChild == NULL

typedef struct 
{
    float begin;
    float end;
} spliceRange_t;

typedef struct 
{
    int locx;
    int locy;
    int width;
    int height;
} imageLocation_t;

typedef struct
{
    size_t xres;
    size_t yres;
    PNG image;
} splicedImage_t;

// spliceRange_t makeSpliceRange(float start, float end)
// {
//     spliceRange_t newSplice;
//     newSplice.begin = start;
//     newSplice.end = end;
//     return newSplice;
// }

class Splice {

public:

    Splice();
    Splice(PNG const & image);
    void saveToDisk(std::string const & dirname);
    PNG getImage(std::string const & fname, spliceRange_t x, spliceRange_t y);
    PNG getImage(spliceRange_t x, spliceRange_t y);

private:

    class quadTreeNode {

    public:

        quadTreeNode() : nwChild(NULL), neChild(NULL), swChild(NULL), seChild(NULL) { /* */ };
        quadTreeNode(quadTreeNode const & other) : data(other.data), nwChild(other.nwChild), neChild(other.neChild), swChild(other.swChild), seChild(other.seChild) { /* */ };
        quadTreeNode(PNG const & image, int x, int y, int width, int height) : nwChild(NULL), neChild(NULL), swChild(NULL), seChild(NULL)
        {
            data.resize(width, height);
            for (int i = 0; i < width; i++)
            {
                for (int j = 0; j < height; j++)
                {
                    // Copy the data from the image into the quadTreeNode
                    *(data(i, j)) = *(image(x + i, y + j));
                }
            }

        }

        PNG data;

        quadTreeNode * nwChild;
        quadTreeNode * neChild;
        quadTreeNode * swChild;
        quadTreeNode * seChild;

    };

    Splice::quadTreeNode * root;


    void _saveToDisk(quadTreeNode const * subroot, string const filename);
    void _deleteRoots(quadTreeNode *& subroot);
    Splice::quadTreeNode * _buildTreeHelper(PNG const & image, int x, int y, int w, int h);
    void _loadData(std::string const & filename);
    void _determineBaseCase();
    void _generateImage(PNG & img, quadTreeNode * subroot, size_t currX, size_t currY, spliceRange_t & x, spliceRange_t & y, size_t resX, size_t resY);
    void _recursiveSaveImage(std::string const & dirname, quadTreeNode * subroot);
    void _fitInsideImages(spliceRange_t & x, spliceRange_t & y);

    size_t width;
    size_t height;

    size_t baseX;
    size_t baseY;

    size_t imgSaveOffsetX;
    size_t imgSaveOffsetY;
    size_t offsetsX;
    size_t offsetsY;

};


#endif