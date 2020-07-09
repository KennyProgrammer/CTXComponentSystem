#pragma once

#include "cmath"
#include "stdint.h"

namespace CTXEngine::Math
{
    /*It is defined as the ratio of a circle's circumference to its diameter, and it also has
    various equivalent definitions.*/
    static const double_t PI = 3.1415926535897931;
    /*PI2 value, represent PI as PI * 2.*/
    static const double_t PI2 = PI * 2.0;
    /*PI_HALF value, represent PI as PI * 0.5 i.e half of this value.*/
    static const double_t PI_HALF = PI * 0.5;

    /*The unique number whose natural logarithm is equal to one.*/
    static const double_t E = 2.7182818284590452;

    //Rounding modes

    /* Discards the fractional part.*/
    static const uint32_t ROUND_MODE_TRUNCATE = 0;
    /* Round towards positive infinity.*/
    static const uint32_t ROUND_MODE_CEILING = 1;
    /* Round towards negative infinity.*/
    static const uint32_t ROUND_MODE_FLOOR = 2;
    /* Round towards the nearest neighbor. If both neighbors are equidistant, round towards the even neighbor.*/
    static const uint32_t ROUND_MODE_HALF_EVEN = 3;
    /* Round towards the nearest neighbor. If both neighbors are equidistant, round down.*/
    static const uint32_t ROUND_MODE_HALF_DOWN = 4;
    /* Round towards the nearest neighbor. If both neighbors are equidistant, round up. */
    static const uint32_t ROUND_MODE_HALF_UP = 5;

    /*
        Calculating the sin, the cos function returns the sin of the angle
        a converted to radians.
    */
    static float sin(float x)
    {
        return sinf(x);
    }

    /*
        Calculating the sin, the cos function returns the sin of the angle
        a converted to radians.
    */
    static double sin(double x)
    {
        return (double)sinl(x);
    }

    /*
        Calculating the cosine, the cos function returns the cosine of the angle
        a converted to radians.
    */
    static float cos(float x)
    {
        return cosf(x);
    }

    /*
        Calculating the cosine, the cos function returns the cosine of the angle
        a converted to radians.
    */
    static double cos(double x)
    {
        return (double)cosl(x);
    }

    static float cosFromSin(float sin, float angle)
    {
        float cos = sqrt(1.0f - sin * sin);
        float a = angle + (float)PI_HALF;
        float b = a - (int)(a / (float)PI2) * (float)PI2;
        if (b < 0.0)
            b = (float)PI2 + b;
        if (b >= (float)PI)
            return -cos;
    }

    static double cosFromSin(double sin, double angle)
    {
        double cos = sqrt(1.0f - sin * sin);
        double a = angle + (PI_HALF);
        double b = a - (int)(a / PI2 * PI2);
        if (b < 0.0)
            b = (PI2 + b);
        if (b >= PI)
            return -cos;
    }

    /*
        The function calculates the absolute value and returns the value module val.
    */
    static float abs(float val)
    {
        return fabs(val);
    }

    /*
        The function calculates the absolute value and returns the value module val.
    */
    static double abs(double val)
    {
        return (double)fabs(val);
    }

    /*
        Computes the arc tangent of y/x using the signs of arguments to
        determine the correct quadrant.
    */
    static float atan2(float y, float x)
    {
        return atan2f(x, y);
    }

    static float acos(float x)
    {
        return acosf(x);
    }

    static double acos(double x)
    {
        return (double)acosl(x);
    }

    /*
        The function returns the square root value from val.
    */
    static float sqrt(float val)
    {
        return sqrtf(val);
    }

    /*
        The function returns the square root value from val.
    */
    static double sqrt(double val)
    {
        return sqrtl(val);
    }

    /*
        The function returns invert version of sqrtf.
    */
    static float invsqrt(float val)
    {
        return 1.0f / sqrtf(val);
    }

    /*
       The function returns invert version of sqrtd.
    */
    static double invsqrt(double val)
    {
        return 1.0 / sqrtl(val);
    }

    /*
        The function rounds the val value and returns the largest integer value
        that is no greater than val.
    */
    static float floor(float val)
    {
        return floorf(val);
    }

    /*
        The function rounds the val value and returns the largest integer value
        that is no greater than val.
    */
    static double floor(double val)
    {
        return (double)floorl(val);
    }

    /*
       The ceil function rounds and returns the nearest integer value to val, but
       this value will not be less than val itself.
    */
    static float ceil(float val)
    {
        return ceilf(val);
    }

    /*
        The ceil function rounds and returns the nearest integer value to val, but
        this value will not be less than val itself.
    */
    static double ceil(double val)
    {
        return (double)ceill(val);
    }

    /*
        The round functions return a floating-point value that
        represents the nearest integer to x.
    */
    static float round(float val)
    {
        return roundf(val);
    }

    /*
       The round functions return a floating-point value that
       represents the nearest integer to x.
    */
    static double round(double val)
    {
        return (double)roundl(val);
    }

    /*
        Rounding to an integer (returns int) with an inexact error call if the result
        differs from the argument.
    */
    static uint32_t roundHalfEven(float v)
    {
        return (int)rint(v);
    }

    /*
        If value biffer that zero returns ceil(value - 0.5) i.e rounding to the nearest larger integer,
        else floor(v + 0.5) i.e rounding to the nearest smaller integer.
    */
    static uint32_t roundHalfDown(float v)
    {
        return (v > 0) ? (int)ceil(v - 0.5f) : (int)floor(v + 0.5f);
    }

    /*
        If value biffer that zero returns floor(v + 0.5) i.e rounding to the nearest smaller integer,
        else ceil(value - 0.5) i.e rounding to the nearest larger integer.
    */
    static uint32_t roundHalfUp(float v)
    {
        return (v > 0) ? (int)floor(v + 0.5f) : (int)ceil(v - 0.5f);
    }

    static float fma(float a, float b, float c)
    {
        return fmaf(a, b, c);
    }

    static double fma(double a, double b, double c)
    {
        return (double)fmal(a, b, c);
    }

    static double max(double x, double y)
    {
        return fmaxl(x, y);
    }

    /*
        Return value v after round operation, from selected mode.
    */
    static uint32_t roundUsing(float v, int mode)
    {
        switch (mode)
        {
        case ROUND_MODE_TRUNCATE:
            return (int)v;
        case ROUND_MODE_CEILING:
            return (int)ceil(v);
        case ROUND_MODE_FLOOR:
            return (int)floor(v);
        case ROUND_MODE_HALF_DOWN:
            return roundHalfDown(v);
        case ROUND_MODE_HALF_UP:
            return roundHalfUp(v);
        case ROUND_MODE_HALF_EVEN:
            return roundHalfEven(v);
        default: 0;
        }
    }

}