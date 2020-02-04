#include<iostream>
#include<vector>

#include<CreateGlobeGrid.hpp>
#include<Tomography.hpp>

// #include<GMT.hpp>
// #include<ShellExec.hpp>

using namespace std;

int main(){

    // INPUTs.  -----------------
    string tomoFile="/home/shule/Research/t062.WholeMantleTomographyModels.180912/S40RTS_dvs.nc";
    double tomoDepth=2800,contourValue=-0.27; // target contour value.

    double lonGridInc=0.1,latGridInc=0.1; //these 2 parameters control how accurate the ans is.
    // --------------------------


    // Calculate.
    auto tomo=Tomography(tomoFile);
    auto globeGrid=CreateGlobeGrid(lonGridInc,latGridInc);

    // get grid value.
    for (auto &item:globeGrid.first)
        item[2]=tomo.GetValueAt(tomoDepth,item[0],item[1]);
    size_t M=globeGrid.second[1],N=globeGrid.second[0];
    const auto &grid=globeGrid.first;

    // for each longitude, scan latitude point, find intersection.
    vector<double> ansLon,ansLat;
    for (size_t j=0;j<N;++j) {
        for (size_t i=1;i<M;++i) {
            size_t k=M*j+i;
            if ((grid[k-1][2]>contourValue) ^ (grid[k][2]>contourValue)) {
                ansLon.push_back(grid[k][0]);
                ansLat.push_back(grid[k-1][1]+(contourValue-grid[k-1][1])/(grid[k][2]-grid[k-1][1])*globeGrid.second[3]);
            }
        }
    }

    // OUTPUTs.
//     for (size_t i=0;i<ansLon.size();++i) 
//         cout << ansLon[i] << " " << ansLat[i] << '\n';

    // Plot.
//     string outfile=GMT::BeginEasyPlot();
//     GMT::MoveReferencePoint(outfile,"-Xf1i -Yf1i");
//     GMT::pscoast(outfile,"-JR180/10i -Rg -Bxa60g60 -Bya60g60 -BWSne -W0.5p -A10000 -O -K");
//     GMT::psxy(outfile,ansLon,ansLat,"-J -R -W0p -Gred -Sc0.03i -O -K");
//     GMT::SealPlot(outfile);
// 
//     string pdffile=__FILE__;
//     pdffile=pdffile.substr(0,pdffile.find(".cpp"))+".pdf";
//     ShellExec("ps2pdf "+outfile+" "+pdffile);
//     remove(outfile.c_str());
}
