#include<iostream>
#include<vector>

#include<CreateGlobeGrid.hpp>
#include<GlobeGridArea.hpp>
#include<Tomography.hpp>

using namespace std;

int main(){

    // INPUTs.  -----------------
    string tomoFile="/home/shule/Research/t062.WholeMantleTomographyModels.180912/S40RTS_dvs.nc";
    double tomoDepth=2800; // shell depth (in km.)
    double percentageValue=70; // 0~100 (in %)

    double lonGridInc=0.5,latGridInc=0.5,ansEps=1e-3; //these 3 parameters control how accurate the ans is.
    // --------------------------


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
    double r=1e10,l=-r;
    while (r-l>ansEps){

        double mid=(l+r)/2,area=0;
        for (size_t i=0;i<globeGrid.first.size();++i)
            if (globeGrid.first[i][2]>mid)
                area+=areaForEachLat[i%M];

        if (area>targetArea)
            l=mid;
        else r=mid;
    }

    // OUTPUTs.

    cout << l << endl;
}
