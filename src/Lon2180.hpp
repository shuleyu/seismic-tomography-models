#ifndef ASU_LON2180
#define ASU_LON2180

/*******************************************************
 * This C++ template convert input longitude (in deg) to
 * [-180,180] deg.
 *
 * input(s):
 * const T &lon  ----  Longitude.
 *
 * return(s):
 * double ans  ----  Longitude in -180 ~ 180.
 *
 * Shule Yu
 * Dec 29 2017
 *
 * Key words: coordinates, longitude.
*******************************************************/

template<class T>
inline double Lon2180(const T &lon){

    double ans=lon;
    if (ans>=0) ans-=360*((int)(ans/360));
    else ans+=360*(1+(int)(-ans/360));

    if (ans>180) ans-=360;
    return ans;
}

#endif
