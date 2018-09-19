#include<iostream>
#include<sstream>
#include<iomanip>

#include<GMT.hpp>
#include<Tomography.hpp>

using namespace std;

int main(){

    /*

    // Example 1. One value at request location (depth, lon, lat).

    auto tomo=Tomography("/home/shule/Research/t062.WholeMantleTomographyModels.180912/SP12RTS_dvs.nc");
    cout << tomo.GetValueAt(2343.5,253.03,-43.4) << endl;

    */


    /*


    // Example 2. Plot depth slices.
    vector<string> ModelNames={"TX2011_dvs.nc"};
//     vector<string> ModelNames={"GyPSuM_vp.nc","GyPSuM_vs.nc","HMSL-P06_dvp.nc","HMSL-P06_vp.nc","HMSL-S06_dvs.nc","HMSL-S06_vs.nc","LLNL-G3Dv3_dvp.nc","LLNL-G3Dv3_vp.nc","MITP08_dvp.nc","MITP08_vp.nc","S20RTS_dvs.nc","S362ANI+M_vsh.nc","S362ANI+M_vs.nc","S362ANI+M_vsv.nc","S362ANI_vsh.nc","S362ANI_vs.nc","S362ANI_vsv.nc","S362WMANI_vsh.nc","S362WMANI_vs.nc","S362WMANI_vsv.nc","S40RTS_dvs.nc","SAW24B16_vs.nc","SAW642ANb_qs.nc","SAW642ANb_rho.nc","SAW642ANb_vp.nc","SAW642ANb_vs.nc","SAW642AN_qs.nc","SAW642AN_rho.nc","SAW642AN_vp.nc","SAW642AN_vs.nc","SEISGLOB2_dvs.nc","SEMUCB-WM1_dvs.nc","SEMUCB-WM1_vsh.nc","SEMUCB-WM1_vs.nc","SEMUCB-WM1_vsv.nc","SEMum_vs.nc","SEMum_xi.nc","SGLOBE-rani_dvs.nc","SGLOBE-rani_vsh.nc","SGLOBE-rani_vsv.nc","SP12RTS_dvp.nc","SP12RTS_dvs.nc","SPani_dvp.nc","SPani_dvs.nc","SPani_phi.nc","SPani_vp.nc","SPani_vs.nc","SPani_xi.nc","TX2000_dvs.nc","TX2011_dvs.nc","TX2011_vs.nc"};

    vector<double> Depths={100,220,300,410,500,600,660,700,800,1000,1200,1400,1600,1800,2000,2200,2400,2600,2800};

    string outfile="TomographyModels.ps";
    size_t XSIZE=ModelNames.size()*9+1,YSIZE=Depths.size()*7+1;
    GMT::set("PS_MEDIA "+to_string(XSIZE)+"ix"+to_string(YSIZE)+"i");
    GMT::set("FONT_ANNOT 4p");
    GMT::BeginPlot(outfile);

    for (size_t i=0;i<ModelNames.size();++i) {

        // Read in tomograph model.
        auto tomo=Tomography("/home/shule/Research/t062.WholeMantleTomographyModels.180912/"+ModelNames[i]);
        cout << "Plotting model: " << ModelNames[i] << " ..." << endl;

        size_t p=ModelNames[i].find_last_of("_")+1;

        for (size_t j=0;j<Depths.size();++j) {
            cout << "    At " << Depths[j] << " km ..." << endl;

            stringstream ss;
            ss << fixed << setprecision(0) << Depths[j];
            string label=(ModelNames[i][p]=='d'?"0.5:\"":"0.1:\"");
            label+=ModelNames[i]+" ";
            label+=(ModelNames[i][p]=='d'?"(%) - ":" - ");
            label+=ss.str()+" km\":";

            vector<vector<double>> grid;
            double dlon=1,dlat=1,minval=numeric_limits<double>::max(),maxval=-minval;
            for (double lon=-180;lon<180; lon+=dlon)
                for (double lat=-90; lat<=90; lat+=dlat) {
                    grid.push_back({lon,lat,tomo.GetValueAt(Depths[j],lon,lat)});
                    minval=min(minval,grid.back().back());
                    maxval=max(maxval,grid.back().back());
                }
            maxval=max(fabs(minval),fabs(maxval));

            GMT::MoveReferencePoint(outfile,"-Xf"+to_string(1+9*i)+"i -Yf"+to_string(YSIZE-7*(j+1)+0.5)+"i");
            GMT::makecpt("-Cpolar -T"+to_string(ModelNames[i][p]=='d'?-maxval:minval)+"/"+to_string(maxval)+" -I -D > tmp.cpt");
            GMT::grdimage(outfile,grid,dlon,dlat,"-JR0/8i -Rg -Ctmp.cpt -O -K");
            GMT::psscale(outfile,"-Ctmp.cpt -D4i/-0.5i/2i/0.1ih -B"+label+" -O -K");
            GMT::pscoast(outfile,"-J -R -W0.5p,black -A10000 -O -K");
            GMT::psbasemap(outfile,"-J -R -Bxa1000 -Bya1000 -Bnews -O -K");
        }
    }

    GMT::SealPlot(outfile);
    remove("tmp.cpt");
    
    */

    return 0;
}
