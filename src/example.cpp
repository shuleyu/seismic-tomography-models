#include<iostream>
#include<sstream>
#include<iomanip>

#include<ShellExec.hpp>
#include<Tomography.hpp>

using namespace std;

int main(){

    // get current directory.
    string pwd=ShellExec("pwd");
    pwd.pop_back(); 

    // designate an *.nc file to use.
    auto tomo=Tomography(pwd+"/../SP12RTS_dvs.nc");

    // get dvs value at location (depth, lon, lat).
    cout << tomo.GetValueAt(2343.5,253.03,-43.4) << endl;
    
    return 0;
}
