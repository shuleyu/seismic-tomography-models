#include<iostream>
#include<vector>

#include<FindAz.hpp>
#include<MeshGrid.hpp>
#include<Tomography.hpp>
#include<GcpDistance.hpp>
#include<GMT.hpp>
#include<WayPoint.hpp>

using namespace std;

// INPUTs.  -----------------

const string tomoFile="/Volumes/Homes/shuleyu/Research/t062.WholeMantleTomographyModels.180912/S40RTS_dvs.nc";
const double minDepth=0, maxDepth=2900; // in km.
const double lonA=195, latA=70, lonB=195, latB=-70; // in deg. point A and point B longitude and latitude.

const double thetaInc=0.5; // in deg. theta direction increment.
const double depthInc=10; // in km. depth increment.
const double RE=6371.0;

// --------------------------

int main() {

    // Get the azimuth from point A to point B.
    double az=FindAz(lonA, latA, lonB, latB);
    double dist=GcpDistance(lonA, latA, lonB, latB);

    // Calculate.
    auto tomo=Tomography(tomoFile);

    // create a grid.
    auto thetaGrid=CreateGrid(0, dist, thetaInc, 1);
    auto depthGrid=CreateGrid(minDepth, maxDepth, depthInc, 1);

    // create the value grid.
    vector<vector<double>> plotGrid;
    double centerLon=lonA;
    for (size_t i=0; i<thetaGrid.size(); ++i) {
        auto p=WayPoint(lonA, latA, az, thetaGrid[i]);
        if (i==thetaGrid.size()/2) centerLon=p.first;
        for (size_t j=0; j<depthGrid.size(); ++j) {
            double val=tomo.GetValueAt(depthGrid[j], p.first, p.second);
            cout << thetaGrid[i] << " " << depthGrid[j] << " " << val << endl;
            plotGrid.push_back({thetaGrid[i], RE-depthGrid[j], val});
        }
    }

    // plot.
    string outfile=GMT::BeginEasyPlot(10,10);

    GMT::MoveReferencePoint(outfile, "-Xf1i -Yf6i");
    GMT::pscoast(outfile, "-JR"+to_string(centerLon)+"/5i -A100000 -Rg -W0.5p,black -O -K");
    GMT::psbasemap(outfile, "-J -R -Bxa30 -Bya30 -Bwsne -O -K");
    GMT::psxy(outfile, vector<double> {lonA, lonB}, vector<double> {latA, latB}, "-J -R -W1p,red -O -K");

    GMT::MoveReferencePoint(outfile, "-Xf1i -Yf1.5i");
    GMT::makecpt("-Cpolar -T-1/0/0.5 -D -I -Z > tmp.cpt");
    GMT::grdimage(outfile, plotGrid, thetaGrid[1]-thetaGrid[0], depthGrid[1]-depthGrid[0],
                "-JPa8i/"+to_string(dist/2.0)+"z -R0/"+to_string(dist)+"/"+to_string(RE-maxDepth)+"/"+to_string(RE-minDepth)+" -Ctmp.cpt -O -K");
    GMT::psbasemap(outfile, "-J -R -Bxa"+to_string(dist/10)+" -Bya"+to_string((maxDepth-minDepth)/10)+" -O -K");
    GMT::psscale(outfile,"-Ctmp.cpt -D4i/-0.5i/4i/0.1ih -O -K -B0.5:dVs(%):");
    GMT::SealPlot(outfile);
    GMT::ps2pdf(outfile, __FILE__);

    remove("tmp.cpt");

    return 0;
}
