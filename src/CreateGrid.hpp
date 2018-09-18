#ifndef ASU_CREATEGRID
#define ASU_CREATEGRID

#include<iostream>
#include<vector>
#include<cmath>

/***********************************************************
 * This C++ template returns the 1D grid meshing results.
 *
 * input(s):
 * const T1  &lowerbound   ----  Grid lower bound.
 * const T2  &upperbound   ----  Grid upper bound.
 * const T3  &Para         ----  meaning-changing parameter.
 *                               it's meaning depends on which mode:
 *
 * const int &mode         ----  select mode.
 *                               Define the meaning of Para and return vector.
 *
 *                               0: Para means number of gird points.
 *                                  Return a vector (ans) of size Para:
 *
 *                                  ans.size()=Para;
 *                                  ans[0]=lowerbound;
 *                                  ans[Para-1]=upperbound;
 *
 *                               1: Para means grid increment.
 *                                  Last grid point is less equal to higherbound.
 *                                  Return a vector (ans) of calculated size:
 *
 *                                  ans[0]=lowerbound;
 *                                  ans[1]-ans[0]=Para;
 *                                  upperbound-Para<ans.back();
 *                                  ans.back()<=upperbound;
 *
 *                              -1: Same as 1. Will only return the grid property:
 *
 *                                  ans.size()=2;
 *                                  ans[0] = calculated grid size.
 *                                  ans[1] = adjusted upperbound.
 *
 *
 *                               2: Para means an estimation of grid increment.
 *                                  The calculated grid increment (Para*) is (possibly)
 *                                  sightly decreased such that the higherbound is meet.
 *                                  Return a vector (ans) of calculated size:
 *
 *                                  ans[0]=lowerbound;
 *                                  ans[1]-ans[0]=Para* (<=Para);
 *                                  ans.back()=upperbound;
 *
 *                              -2: Same as 2. Will only return the grid property:
 *
 *                                  ans.size()=2;
 *                                  ans[0] = calculated grid size.
 *                                  ans[1] = adjusted Para (Para*).
 *
 * return(s):
 * vector<double> ans  ----  Created grid or grid properties, depending on mode.
 *
 * Shule Yu
 * Jan 23 2018
 *
 * Key words: creating grid.
***********************************************************/

template<class T1, class T2, class T3>
std::vector<double> CreateGrid(const T1 &lowerbound, const T2 &upperbound, const T3 &Para, const int mode){

    // check lower and upper bound.
    if (upperbound<lowerbound) {
        std::cerr <<  "Error in " << __func__ << ": lower bound > upper bound ..." << std::endl;
        return {};
    }

    if (mode==0){

        int N=Para;
        double Inc=1.0*(upperbound-lowerbound)/(N-1);

        std::vector<double> ans(N,lowerbound);
        for (int i=1;i<N;++i) ans[i]=ans[i-1]+Inc;
        return ans;
    }
    if (mode==1 || mode==-1){

        double Inc=Para;

        if (mode==-1) {
            double N=1+floor(1.0*(upperbound-lowerbound)/Inc);
            if (fabs((upperbound-lowerbound-N*Inc))<Inc*1e-6) // float number rounding error?
                N+=1;
            return {N,lowerbound+(N-1)*Inc};
        }

        std::vector<double> ans;

        double Cur=lowerbound;

        while (Cur<=upperbound || Cur-upperbound<Inc*1e-6) {
            ans.push_back(Cur);
            Cur+=Inc;
        }
        return ans;
    }
    if (mode==2 || mode==-2){

        double Inc=Para;
        int N=1+(int)ceil((upperbound-lowerbound)/Inc);
        Inc=1.0*(upperbound-lowerbound)/(N-1);

        if (mode==-2) {
            return {1.0*N,Inc};
        }

        std::vector<double> ans;
        double Cur=lowerbound;

        for (int i=0;i<N;++i) {
            ans.push_back(Cur);
            Cur+=Inc;
        }
        return ans;
    }

    std::cerr <<  "Error in " << __func__ << ": mode error ..." << std::endl;
    return {};
}

#endif
