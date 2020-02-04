#include<iostream>
#include<sstream>
#include<iomanip>

#include<ShellExec.hpp>
#include<Tomography.hpp>

using namespace std;

int main(){

    // which *.nc file to use.
    auto tomo=Tomography("/Volumes/Homes/shuleyu/Documents/Research/t062.WholeMantleTomographyModels.180912/GAP_P4_dvp.nc");

    // get dvs value at location (depth, lon, lat).
    cout << tomo.GetValueAt(2343.5,253.03,-87.5) << endl;


    // Other APIs.
    cout << tomo.GetDepths()[0] << " " << tomo.GetDepths().back() << endl;
    cout << tomo.GetLongitudes()[0] << " " << tomo.GetLongitudes().back() << endl;
    cout << tomo.GetLatitudes()[0] << " " << tomo.GetLatitudes().back() << endl;
    
    return 0;
}
