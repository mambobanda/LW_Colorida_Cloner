/*
 * The Mailo Today Solutions Software License
 *
 * Copyright 2016 Mailo Today Solutions.
 *
 * This program is free software, distributed under the terms of the
 * GNU General Public License (GPL) 
 * http://www.gnu.org/licenses
 */

#ifndef VECTOR_H
#define	VECTOR_H

#include <string>

using namespace std;



  
class Vector2{
    public:
        float x,y;

        Vector2();
        Vector2(float x, float y);
        Vector2(const Vector2 &);

        void negate();
        float magnitude();
        void normalize();
        bool isZeroVector();
        Vector2 operator *(float );
        Vector2 operator /(float );
        Vector2 operator +(const Vector2 &);
        Vector2 operator -(const Vector2 &);
        void operator =(const Vector2 &);

        //string toString();
};

class Vector3{
    public:
        float x,y,z;

        Vector3();
        Vector3(float x, float y, float z);
        Vector3(const Vector3 &);

        void  negate();
        float magnitude();
        void  normalize();
        bool isZeroVector();
        Vector3 operator *(float );
        Vector3 operator /(float );
        Vector3 operator +(const Vector3 &);
        Vector3 operator -(const Vector3 &);
        void operator =(const Vector3 &);

        //string toString();
};

typedef Vector2 Point2D;
typedef Vector3 Point3D;    

float distance(const Vector2 &, const Vector2 &);
float distance(const Vector3 &, const Vector3 &);

float dot(const Vector2 &, const Vector2 &);
float dot(const Vector3 &, const Vector3 &);

Vector3 cross(const Vector3 &, const Vector3 &);


#endif