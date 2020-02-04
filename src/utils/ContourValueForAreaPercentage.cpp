#include<iostream>
#include<vector>

#include<CreateGlobeGrid.hpp>
#include<GlobeGridArea.hpp>
#include<Tomography.hpp>
#include<GetHomeDir.hpp>

using namespace std;

// INPUTs.  -----------------

const string tomoFile="../../S40RTS_dvs.nc";
const double tomoDepth=2800; // shell depth (in km.)
const double percentageValue=30; // 0~100 (in %)

const double lonGridInc=0.5,latGridInc=0.5,ansEps=1e-3; //these 3 parameters control how accurate the ans is.

// --------------------------

int main(){

    // Calculate.
    auto tomo=Tomography(tomoFile);
    auto globeGrid=CreateGlobeGrid(lonGridInc,latGridInc);
    size_t M=globeGrid.second[1];

    // get grid area.
    double targetArea=4*M_PI*percentageValue/100;
    vector<double> areaForEachLat(M,0);
    for (size_t i=0;i<M;++i) areaForEachLat[i]=GlobeGridArea(1,globeGrid.first[i][1],globeGrid.second[2],globeGrid.second[3]);

    // get grid area and grid value.
    for (size_t i=0;i<globeGrid.first.size();++i)
        globeGrid.first[i][2]=tomo.GetValueAt(tomoDepth,globeGrid.first[i][0],globeGrid.first[i][1]);

    // binary search for the result.
    double l=-1e10, r=1e10;
    while (r-l>ansEps){
        double mid=(l+r)/2,area=0;

        for (size_t i=0;i<globeGrid.first.size();++i)
            if (globeGrid.first[i][2]<mid)
                area+=areaForEachLat[i%M];

        if (area>targetArea) r=mid;
        else l=mid;
    }

    cout << l << endl;

    return 0;
}
