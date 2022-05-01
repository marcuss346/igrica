//
// Created by Mark Ilovar on 14/02/2022.
//
#pragma once

#include <iostream>

class Vector2D{
public:
    float x, y;

    Vector2D(){}
    Vector2D(float x,float y){
        this->x=x;
        this->y=y;
    }


    Vector2D& Add(const Vector2D vec);
    Vector2D& Subtract(const Vector2D vec);
    Vector2D& Multiply(const Vector2D vec);
    Vector2D& Divide(const Vector2D vec);

    friend Vector2D& operator+(Vector2D vecA, const Vector2D vecB);
    friend Vector2D& operator-(Vector2D vecA, const Vector2D vecB);
    friend Vector2D& operator*(Vector2D vecA, const Vector2D vecB);
    friend Vector2D& operator/(Vector2D vecA, const Vector2D vecB);
    Vector2D& operator= (const Vector2D vec);
    Vector2D& operator= (Vector2D *vec);

    Vector2D& operator+=(const Vector2D vec);
    Vector2D& operator-=(const Vector2D vec);
    Vector2D& operator*=(const Vector2D vec);
    Vector2D& operator/=(const Vector2D vec);
    Vector2D& Zero();

};