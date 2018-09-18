#ifndef ASU_LINEARINTERP
#define ASU_LINEARINTERP

#include<iostream>
#include<vector>
#include<cmath>

/****************************************************************
 * This C++ template is designed for finding values inside a unit
 * cubic when the values at the corners are known, using
 * linear interpolation recursively.
 *
 * The variation is that when input vector is of size 2, 4 or 8,
 * corresponding to finding value within a line segment, a square
 * or a cubic.
 *
 * For convenience, the order of the vector is fixed:
 *
 * 1D:
 *
 * p[0] represents value at piont (0)
 * p[1] represents value at piont (1)
 *
 * 2D:
 *
 * p[0] represents value at piont (0,0)      |
 * p[1] represents value at piont (1,0)      |  ------ copied, add 1's at back --|
 * p[2] represents value at piont (0,1)      |  ------ copied, add 0's at back   |
 * p[3] represents value at piont (1,1)      |                                   |
 *                                                            |                  |
 *                                                            |                  |
 * 3D:                                                        |                  |
 *                                                            |                  |
 * p[0] represents value at piont (0,0,0)                     |                  |
 * p[1] represents value at piont (1,0,0)                     |                  |
 * p[2] represents value at piont (0,1,0)       < ----------- |                  |
 * p[3] represents value at piont (1,1,0)                                        |
 * p[4] represents value at piont (0,0,1)                                        |
 * p[5] represents value at piont (1,0,1)       < ------------------------------ |
 * p[6] represents value at piont (0,1,1)
 * p[7] represents value at piont (1,1,1)
 *
 * ...
 *
 * input(s):
 * const vector<T1> &p   ----  Values at unit cubic corners.
 *                             1D: pp.size()=2.
 *                             2D: pp.size()=4.
 *                             3D: pp.size()=8.
 *                             ...
 *
 * const vector<T2> &pp  ----  Point location (value of pp is 0~1).
 *                             1D: pp.size()=1.
 *                             2D: pp.size()=2.
 *                             3D: pp.size()=3.
 *                             ...
 * return(s):
 * double val            ----  value at piont pp.
 *
 *
 * Shule Yu
 * Jan 23 2018
 *
 * Reference:
 *     http://en.wikipedia.org/wiki/Bilinear_interpolation
 *     http://en.wikipedia.org/wiki/Trilinear_interpolation
 *
 * Key words: interpolation, linear.
***************************************************************/

template<class T1, class T2>
double LinearInterp_Recur(const std::vector<T1> &p, const std::vector<T2> &pp, const int &l, const int &r, const int &P) {
    if (P==0) return p[l]*(1-pp[P])+p[r]*pp[P];
    else {
        double a=LinearInterp_Recur(p,pp,l,l+(r-l)/2,P-1);
        double b=LinearInterp_Recur(p,pp,l+(r-l)/2+1,r,P-1);
        return a*(1-pp[P])+b*pp[P];
    }
}

template<class T1, class T2>
double LinearInterp(const std::vector<T1> &p, const std::vector<T2> &pp){

    int m=p.size(),n=pp.size();

    // check array size.
    if (n==0) {
        std::cerr <<  "Error in " << __func__ << ": input point dimension error ..." << std::endl;
        return 0.0/0.0;
    }

    if (m!=pow(2,n)) {
        std::cerr <<  "Error in " << __func__ << ": input cubic dimension error ..." << std::endl;
        return 0.0/0.0;
    }

    return LinearInterp_Recur(p,pp,0,m-1,n-1);
}

#endif
