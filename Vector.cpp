/*
 * The Mailo Today Solutions Software License
 *
 * Copyright 2016 Mailo Today Solutions.
 *
 * This program is free software, distributed under the terms of the
 * GNU General Public License (GPL) 
 * http://www.gnu.org/licenses
 */

#include <math.h>
#include "Vector.h"



Vector2::Vector2(){
    x = 0.0f;
    y = 0.0f;
}

Vector2::Vector2(const Vector2 &vec2){
    this->x = vec2.x;
    this->y = vec2.y;
}

Vector2::Vector2(float x, float y){
    this->x = x;
    this->y = y;
}

void Vector2::operator =(Vector2 const &vec2){
    this->x = vec2.x;
    this->y = vec2.y;
}

Vector2 Vector2::operator *(float scalar){
    return Vector2(x * scalar,y * scalar);
}

Vector2 Vector2::operator /(float scalar){
    return Vector2(x / scalar,y / scalar);
}

Vector2 Vector2::operator +(const Vector2 &vec2){
    return Vector2(x + vec2.x, y + vec2.y);
}

    Vector2 Vector2::operator -(const Vector2 &vec2){
    return Vector2(x - vec2.x, y - vec2.y);
}

void Vector2::negate(){
    x = x * -1.0f;
    y = y * -1.0f;
}

float Vector2::magnitude(){
    return sqrtf(powf(x,2.0f) + powf(y, 2.0f));
}

void Vector2::normalize(){
    if(isZeroVector())
        return;
    else{

        Vector2 temp_vec = Vector2(*this);
        temp_vec = temp_vec / temp_vec.magnitude();
        this->x = temp_vec.x;
        this->y = temp_vec.y; 
    }
}

bool Vector2::isZeroVector(){
    return (x == 0.0 && y == 0.0)? true: false; 
}

//string Vector2::toString(){
//    string str = "[" + util::toString(x) + ", " + util::toString(y) + "]";
//
//    return str;
//}

    /*3D Vector*/
Vector3::Vector3(){
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
}

Vector3::Vector3(const Vector3 &vec3){
    this->x = vec3.x;
    this->y = vec3.y;
    this->z = vec3.z;
}

Vector3::Vector3(float x, float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
}

void Vector3::operator =(Vector3 const &vec3){
    this->x = vec3.x;
    this->y = vec3.y;
    this->z = vec3.z;
}

Vector3 Vector3::operator *(float scalar){
    return Vector3(x * scalar,y * scalar, z * scalar);
}

Vector3 Vector3::operator /(float scalar){
    return Vector3(x / scalar,y / scalar, z / scalar);
}

Vector3 Vector3::operator +(const Vector3 &vec3){
    return Vector3(x + vec3.x, y + vec3.y, z + vec3.z);
}

    Vector3 Vector3::operator -(const Vector3 &vec3){
    return Vector3(x - vec3.x, y - vec3.y, z - vec3.z);
}

void Vector3::negate(){
    x = x * -1.0f;
    y = y * -1.0f;
    z = z * -1.0f;
}

float Vector3::magnitude(){
    return sqrtf(powf(x,2.0f) + powf(y, 2.0f) + powf(z, 2.0f));
}

void Vector3::normalize(){
    if(isZeroVector())
        return;
    else{

        Vector3 temp_vec = Vector3(*this);
        temp_vec = temp_vec / temp_vec.magnitude();
        this->x = temp_vec.x;
        this->y = temp_vec.y; 
        this->z = temp_vec.z;
    }
}

bool Vector3::isZeroVector(){
    return (x == 0.0 && y == 0.0 && z == 0.0)? true: false; 
}

/* string Vector3::toString(){
    string str = "[" + util::toString(x) + ", " + util::toString(y) + ", " + util::toString(z) + "]";

    return str;
}*/

////////////////////////////////
//Function Definitions
////////////////////////////////

float distance(const Vector2 &vec1, const Vector2 &vec2){
    return sqrt(pow(vec2.x - vec1.x, 2) + pow(vec2.y - vec1.y, 2));
}

float distance(const Vector3 &vec1, const Vector3 &vec2){
    return sqrt(pow(vec2.x - vec1.x, 2) + pow(vec2.y - vec1.y, 2) + pow(vec2.z - vec1.z, 2));
}

float dot(const Vector2 &vec1, const Vector2 &vec2){
    return (vec1.x * vec2.x) + (vec1.y * vec2.y);
}

    float dot(const Vector3 &vec1, const Vector3 &vec2){
    return (vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z);
}

Vector3 cross(const Vector3 &vec1, const Vector3 &vec2){
    return Vector3(((vec1.y*vec2.z) - (vec1.z*vec2.y)), 
                    ((vec1.z*vec2.x) - (vec1.x*vec2.z)), 
                    ((vec1.x*vec2.y) - (vec1.y*vec2.x)));
}

 