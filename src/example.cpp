#include<iostream>

#include<GMT.hpp>
#include<Tomography.hpp>

using namespace std;

int main(){

    auto tomo=Tomography("/home/shule/Research/t062.WholeMantleTomographyModels.180912/SP12RTS_dvs.nc");


    // Example 1. One value at request location (depth, lon, lat).
    cout << tomo.GetValueAt(2343.5,253.03,-43.4) << endl;


    /*

    // Example 2. Plot a depth slice.

    double depth=2850;

    vector<vector<double>> grid;
    double dlon=1,dlat=1,minval=numeric_limits<double>::max(),maxval=-minval;
    for (double lon=-180;lon<180; lon+=dlon)
        for (double lat=-90; lat<=90; lat+=dlat) {
            grid.push_back({lon,lat,tomo.GetValueAt(depth,lon,lat)});
            minval=min(minval,grid.back().back());
            maxval=max(maxval,grid.back().back());
        }
    maxval=max(fabs(minval),fabs(maxval));

    // Plot.
    string outfile="Tomography.ps";
    GMT::set("PS_MEDIA 10ix10i");
    GMT::BeginPlot(outfile);

    GMT::MoveReferencePoint(outfile,"-Xf1i -Yf4i");
    GMT::makecpt("-Cpolar -T-"+to_string(maxval)+"/"+to_string(maxval)+" -I -D > tmp.cpt");
    GMT::grdimage(outfile,grid,dlon,dlat,"-JR140/8i -Rg -Ctmp.cpt -O -K");
    GMT::psscale(outfile,"-Ctmp.cpt -D4i/-0.5i/2i/0.1ih -B1:dV(%): -O -K");
    GMT::pscoast(outfile,"-J -R -W0.5p,black -A10000 -O -K");
    GMT::psbasemap(outfile,"-J -R -Bxa1000 -Bya1000 -Bnews -O -K");

    GMT::SealPlot(outfile);
    remove("tmp.cpt");

    */

    return 0;
}
