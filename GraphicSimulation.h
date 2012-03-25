/* 
 * File:   GraphicSimulation.h
 * Author: nero
 *
 * Created on October 19, 2010, 8:43 PM
 */

#ifndef GRAPHICSIMULATION_H
#define	GRAPHICSIMULATION_H

#include <vector>
#include "Object.h"

class GraphicsSimulation {
public:
    std::vector<Vector3D> points;
    Object obj;
    unsigned long ctr;
    unsigned char *texArray;//the mesh object consisting of triangles
    unsigned long texArray2D[400][400];				//filename of the texture to be used
    unsigned long texArrayi[400][400];				//filename of the texture to be used
    unsigned long texArrayj[400][400];				//filename of the texture to be used

    int rows;
    int columns;

    void display(int ,bool);
    void print(Vector3D point);
    double heightMap(double t0, double t1, Triangle tri);
    long getImageInfo(FILE* inputFile, long offset, int numberOfChars);
    void loadTriangles();

    GraphicsSimulation(const char* );
    GraphicsSimulation();
    GraphicsSimulation(int n);
    ~GraphicsSimulation();


};

#endif	/* GRAPHICSIMULATION_H */

