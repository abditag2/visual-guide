/*
 *   @author  Jeffrey Huang
 *   @date    04/03/2015
 *   @file    splice.h
 *   
 *   Definition of the Splice Image Class
 *
*/

#ifndef _SPLICE_H_
#define _SPLICE_H_

#include <iostream>
#include <string>
#include "rgbapixel.h"
#include "PNG.h"
#include <sys/stat.h>
#include <fstream>
#include <vector>

#define error(message) \
 std::cout << message << std::endl;


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

    /*
     *   Constructors and destructors
     *   Valid Inputs: PNG image, a filename that is a .splice and a default constructor
     */

    Splice();
    Splice(PNG const & image);
    Splice(std::string const & filename);
    Splice(Splice const & other);
    ~Splice();
    Splice & operator=(Splice const & other);

    /* Saves the current spliced image onto the disk.  By saving it, it is no longer stored in RAM, instead
     * It is all stored on the HDD and then the filename that it saved as is stored inside the class
     * All operations from that point on are handled on the disk
    */

    void saveToDisk(std::string const & dirname);
    void saveToDisk(char const * dirname);

    /* 
     *  Gets an image inside a range, returns a struct that holds the image, xres, yres
     *
     *  @returns     splicedImage_t 
     *                  \_ size_t xres
     *                  \_ size_t yres
     *                  \_ PNG image
     */

    splicedImage_t getImage(char const * fname, spliceRange_t x, spliceRange_t y);
    splicedImage_t getImage(std::string const & fname, spliceRange_t x, spliceRange_t y);
    splicedImage_t getImage(spliceRange_t x, spliceRange_t y);

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
    void _generateImageOnDisk(PNG & generatedImage, string const & fname, size_t currX, size_t currY, spliceRange_t x, spliceRange_t y, size_t resX, size_t resY);
    void _deleteTree(Splice::quadTreeNode *& subroot);
    Splice::quadTreeNode * _copyTreeRecursive(Splice::quadTreeNode const * subroot);
    void _copy(Splice const & other);

    size_t width;
    size_t height;

    size_t baseX;
    size_t baseY;

    size_t imgSaveOffsetX;
    size_t imgSaveOffsetY;
    size_t offsetsX;
    size_t offsetsY;

    std::string file;
    bool disk;

};


#endif