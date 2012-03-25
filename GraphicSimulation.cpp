#include "GraphicSimulation.h"
#include "Object.h"
#include "Vector3D.h"
#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include <fstream>
using namespace std;
#define Height .3

GraphicsSimulation::GraphicsSimulation(const char* fileName) {
    ctr = 0;
    FILE *bmpInput;
    if ((bmpInput = fopen(fileName, "rb")) == NULL) {
        cerr << "Can not read BMP file";
    } /* Read BMP input file */

    fseek(bmpInput, 0L, SEEK_SET); /* File pointer at byte #0 */
    unsigned char signature[2];
    /* Signature of the File BM = BMP at byte # 0*/
    for (int i = 0; i < 2; i++) {
        signature[i] = (char) getImageInfo(bmpInput, i, 1);
    }

    if (!((signature[0] == 'B') && (signature[1] == 'M'))) {
        cerr << "The image is not a bitmap format, quitting....\n";
        //	 exit(0);
    }

    /* Position of First Raster Data at byte # 10*/


    /* Read BMP file size at byte # 2 */
    long fileSize = getImageInfo(bmpInput, 2, 4);

    /* Read BMP width at byte #18 */
    columns = (int) getImageInfo(bmpInput, 18, 4);

    /* Read BMP height at byte #22 */
    rows = (int) getImageInfo(bmpInput, 22, 4);

    long vectorSize = (long) ((long) columns * (long) rows);

    texArray = (unsigned char*) malloc(vectorSize);

    for (long i = 0; i < vectorSize; i++) {
        texArray[i] = (char) getImageInfo(bmpInput, 1078 + i, 1);
    }

    loadTriangles();
    fclose(bmpInput);
    ofstream out1("nice.dat");

    for (long i = 0; i < 400; i++) {
        for (long j = 0; j < 400; j++) {
            out1 << i << "\t" << j << "\t" << (long) texArray[i + j * 400] << endl;
            texArray2D[i][j] = (long) texArray[i + j * 400];
        }
    }

    for (long i = 0; i < 399; i++) {
        for (long j = 0; j < 400; j++) {
            texArrayi[i][j] = texArray2D[i + 1][j] - texArray2D[i][j];
        }
    }

    for (long i = 0; i < 400; i++) {
        for (long j = 0; j < 399; j++) {
            texArrayi[i][j] = texArray2D[i][j + 1] - texArray2D[i][j];
        }
    }


    out1.close();

}

void GraphicsSimulation::loadTriangles() {

    Vector3D a(1, 0, 0);
    Vector3D b(-1, 0, 0);
    Vector3D c(0, 1, 0);
    Vector3D d(0, -1, 0);
    Vector3D e(0, 0, 1);
    Vector3D f(0, 0, -1);
    Vertex one(a, a, 200, 200);
    Vertex two(b, b, 0, 200);

    Vertex three(e, e, 100, 200);
    Vertex four(f, f, 300, 200);

    Vertex five(c, c, 50, 0);
    Vertex five1(c, c, 150, 0);
    Vertex five2(c, c, 250, 0);
    Vertex five3(c, c, 350, 0);

    Vertex six(d, d, 50, 399);
    Vertex six1(d, d, 150, 399);
    Vertex six2(d, d, 250, 399);
    Vertex six3(d, d, 350, 399);
    obj.memberTriangles.push_back(*(new Triangle(three, one, five1)));
    obj.memberTriangles.push_back(*(new Triangle(three, two, six)));
    obj.memberTriangles.push_back(*(new Triangle(three, six1, one)));
    obj.memberTriangles.push_back(*(new Triangle(three, five, two)));
    obj.memberTriangles.push_back(*(new Triangle(four, five2, one)));
    obj.memberTriangles.push_back(*(new Triangle(four, six3, two)));
    obj.memberTriangles.push_back(*(new Triangle(four, one, six2)));
    obj.memberTriangles.push_back(*(new Triangle(four, two, five3)));
    /*
    for (int i = 0; i < obj.memberTriangles.size(); i++) {
         cout<<obj.memberTriangles[i].a.textureCoordinates[0]<<" "<<obj.memberTriangles[i].a.textureCoordinates[1]<<endl;
         cout<<obj.memberTriangles[i].b.textureCoordinates[0]<<" "<<obj.memberTriangles[i].b.textureCoordinates[1]<<endl;
         cout<<obj.memberTriangles[i].c.textureCoordinates[0]<<" "<<obj.memberTriangles[i].c.textureCoordinates[1]<<endl<<endl;
     }
     */
}

long GraphicsSimulation::getImageInfo(FILE* inputFile, long offset, int numberOfChars) {

    unsigned char *ptrC;
    long value = 0L;
    unsigned char dummy;
    int i;

    dummy = '0';
    ptrC = &dummy;

    fseek(inputFile, offset, SEEK_SET);

    for (i = 1; i <= numberOfChars; i++) {
        fread(ptrC, sizeof (char), 1, inputFile);

        value = (long) (value + (*ptrC)*(pow(256, (i - 1))));
    }

    return (value);

}

GraphicsSimulation::GraphicsSimulation() {

    loadTriangles();
}

GraphicsSimulation::~GraphicsSimulation() {
}

void GraphicsSimulation::display(int number,bool type) {
    points.clear();
    double diff = 1.0 / number;
    double t1 = 0, t2 = 0;
    for (int k = 0; k < obj.memberTriangles.size(); k++) {
        for (int i = 0; i <= number; i++) {
            for (int j = 0; j <= (number - i); j++) {
                double h = heightMap(t1, t2, obj.memberTriangles[k]);
                Vector3D backTransformation((t1) * obj.memberTriangles[k].c.position_vector + (t2) * obj.memberTriangles[k].b.position_vector + (1 - t1 - t2) * obj.memberTriangles[k].a.position_vector
                        + h * ((t1) * obj.memberTriangles[k].c.normal + (t2) * obj.memberTriangles[k].b.normal + (1 - t1 - t2) * obj.memberTriangles[k].a.normal));
                points.push_back(backTransformation);
                t2 += diff;
            }
            t1 += diff;
            t2 = 0;
        }
        t1 = 0;
        t2 = 0;

    }
    glPointSize(3);
    ofstream out("hello");
    glEnable(GL_SMOOTH);
    int bigcount = (number + 1)*(number + 2) / 2;
    vector<Vector3D> temp;

    for (int k = 0; k < obj.memberTriangles.size(); k++) {
        temp.clear();
        out << k * bigcount << endl << endl;

        for (int i = (k + 1) * bigcount - 1; i >= k * bigcount; i--)
            temp.push_back(points[i]);
        /*
                for (int i = 0; i < temp.size(); i++) {
                    glBegin(GL_POINTS);
                        glVertex3f(temp[i]._x, temp[i]._y, temp[i]._z);
                    glEnd();
                }
         */

        for (int i = 0; i < number; i++) {
            int count = i * (i + 1) / 2;
            if (!type) {
                for (int j = 0; j <= i; j++) {

                    glBegin(GL_TRIANGLES);
                    glVertex3f(temp[count + j]._x, temp[count + j]._y, temp[count + j]._z);
                    glVertex3f(temp[count + j + i + 1]._x, temp[count + j + i + 1]._y, temp[count + j + i + 1]._z);
                    glVertex3f(temp[count + j + i + 2]._x, temp[count + j + i + 2]._y, temp[count + j + i + 2]._z);
                    glEnd();
                }

                for (int j = 0; j < i; j++) {
                    glBegin(GL_TRIANGLES);
                    glVertex3f(temp[count + j]._x, temp[count + j]._y, temp[count + j]._z);
                    glVertex3f(temp[count + j + i + 2]._x, temp[count + j + i + 2]._y, temp[count + j + i + 2]._z);
                    glVertex3f(temp[count + j + 1]._x, temp[count + j + 1]._y, temp[count + j + 1]._z);
                    glEnd();
                }
            }
            else
            {
                for (int j = 0; j <= i; j++) {

                    glBegin(GL_TRIANGLES);
                    glVertex3f(temp[count + j]._x, temp[count + j]._y, temp[count + j]._z);
                    glVertex3f(temp[count + j + i + 1]._x, temp[count + j + i + 1]._y, temp[count + j + i + 1]._z);
                    glVertex3f(temp[count + j + i + 2]._x, temp[count + j + i + 2]._y, temp[count + j + i + 2]._z);
                    glEnd();
                }

            }
        }

    }

    for (int i = 0; i < obj.memberTriangles.size(); i++) {
        glColor3f(i * .15, i * .30, i * .8);
        glBegin(GL_TRIANGLES);
        glVertex3f(obj.memberTriangles[i].a.position_vector._x, obj.memberTriangles[i].a.position_vector._y, obj.memberTriangles[i].a.position_vector._z);
        glVertex3f(obj.memberTriangles[i].b.position_vector._x, obj.memberTriangles[i].b.position_vector._y, obj.memberTriangles[i].b.position_vector._z);
        glVertex3f(obj.memberTriangles[i].c.position_vector._x, obj.memberTriangles[i].c.position_vector._y, obj.memberTriangles[i].c.position_vector._z);
        glEnd();
    }

}

double myNewFunc(double var) {
    //return var;
    //return (1 - cos(var))/2;
    return (3 * var * var - 2 * var * var * var);
}

double GraphicsSimulation::heightMap(double t0, double t1, Triangle tri) {
    //double H = 1 - ( myNewFunc(t0)*t0 + myNewFunc(t1)*t1 + myNewFunc(1-t0-t1)*(1-t0-t1))/(myNewFunc(t0) + myNewFunc(t1) + myNewFunc(1-t0-t1)) ;
    //    cout<<t0<<"  "<<t1<<"   "<<tri.a.position_vector<<"  " <<tri.a.textureCoordinates[0]<<tri.a.textureCoordinates[1]<<" "
    //            <<tri.b.position_vector<<tri.b.textureCoordinates[0]<<tri.b.textureCoordinates[1]<<"  "
    //            <<tri.c.position_vector<<tri.c.textureCoordinates[0]<<tri.c.textureCoordinates[1]<<endl;
    double H = (1 / sqrt(t0 * t0 + t1 * t1 + (1 - t0 - t1)*(1 - t0 - t1)) - 1);
    /*
        double ax = t0*tri.a.textureCoordinates[0];
        double bx = t1*tri.b.textureCoordinates[0];
        double cx = (1-t0-t1)*tri.c.textureCoordinates[0];

        double ay = t0*tri.a.textureCoordinates[1];
        double by = t1*tri.b.textureCoordinates[1];
        double cy = (1-t0-t1)*tri.c.textureCoordinates[1];

        double x = ax + bx + cx;
        double y = ay + by + cy;

        double s = x - floor(x);
        double t = y - floor(y);

        double ts=texArray2D[ (int)x ][(int)y];;
        ts /= 255;
     */

    //return H;
    return H+((double)(rand()%50)/200.0);
}

