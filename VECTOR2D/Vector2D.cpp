#include "Vector2D.h"

Vector2D & Vector2D::Add(const Vector2D vec){
    this->x += vec.x;
    this->y += vec.y;

    return *this;
}

Vector2D & Vector2D::Subtract(const Vector2D vec){
    this->x -= vec.x;
    this->y -= vec.y;

    return *this;
}

Vector2D & Vector2D::Multiply(const Vector2D vec){
    this->x *= vec.x;
    this->y *= vec.y;

    return *this;
}

Vector2D & Vector2D::Divide(const Vector2D vec){
    this->x /= vec.x;
    this->y /= vec.y;

    return *this;
}

Vector2D& operator+(Vector2D vecA, const Vector2D vecB){
    return vecA.Add(vecB);
}

Vector2D& operator-(Vector2D vecA, const Vector2D vecB){
    return vecA.Subtract(vecB);
}

Vector2D& operator*(Vector2D vecA, const Vector2D vecB){
    return vecA.Multiply(vecB);
}

Vector2D& operator/(Vector2D vecA, const Vector2D vecB){
    return vecA.Divide(vecB);
}

Vector2D & Vector2D::operator=(const Vector2D vec){
    x = vec.x;
    y = vec.y;

    return *this;
}

Vector2D & Vector2D::operator=(Vector2D *vec){
    x = vec->x;
    y = vec->y;

    delete vec;

    return *this;
}

Vector2D& Vector2D::operator+=(const Vector2D vecB){
    return this->Add(vecB);
}

Vector2D& Vector2D::operator-=(const Vector2D vecB){
    return this->Subtract(vecB);
}

Vector2D& Vector2D::operator*=(const Vector2D vecB){
    return this->Multiply(vecB);
}

Vector2D& Vector2D::operator/=(const Vector2D vecB){
    return this->Divide(vecB);
}


Vector2D& Vector2D::Zero(){
    this->x = 0;
    this->y = 0;

    return *this;
}
