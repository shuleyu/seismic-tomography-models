#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>
#include<set>
#include<algorithm>

#include<PREM.hpp>

extern "C" {
// Current version: netcdf-4.6.1
#include<netcdf.h>
}

// the downloaded data is named GAP_P4.01 ~ GAP_P4.29
// each file is lon/lat/dvp within a depth shell, whose range in a README file.
// for example, values in GAP_P4.01 is for depth shell 29 - 51 km
// 
// This database, however, have values at certain depth, for depth between layers, use interpolation.
// 
// Therefore, the preprocessing here re-create depth layers such that
//
// Both depths 29 and 50.9999 km use values in GAP_P4.01
// Both depths 51 and 77.9999 km use values in GAP_P4.02
// ...
// Both depths 2407 and 2565.9999 km use values in GAP_P4.28
// Both depths 2566 and 2891     km use values in GAP_P4.29

using namespace std;

int main(){

    vector<double> Depth={29, 51, 78, 110, 148, 190, 238, 290, 348, 410, 478, 551, 629, 712, 800, 893, 991, 1095, 1203, 1317, 1435, 1559, 1688, 1821, 1960, 2104, 2253, 2407, 2566};

    const string dataDIR="./";


    vector<vector<float>> raw_data;
    float lat,lon,dvp;
    set<float> s_lat,s_lon,s_depth;

    for (size_t i=0; i<29; ++i) {
        const string fileName=dataDIR+"GAP_P4."+(i<9?"0":"")+to_string(i+1);

        float curDepth=Depth[i];
        float nextDepth=(i<28 ? Depth[i+1]-0.001 : 2891);

        s_depth.insert(curDepth);
        s_depth.insert(nextDepth);
        
        ifstream fpin(fileName);

        while (fpin >> lon >> lat >> dvp){
            raw_data.push_back({curDepth, lat,lon,dvp});
            raw_data.push_back({nextDepth, lat,lon,dvp});
            s_lat.insert(lat);
            s_lon.insert(lon);
        }
        fpin.close();
    }

    auto cmp=[](const vector<float> &v1, const vector<float> &v2){
        if (v1[0]==v2[0]) {
            if (v1[1]==v2[1]) return v1[2]<v2[2];
            else return v1[1]<v2[1];
        }
        else return v1[0]<v2[0];
    };
    sort(raw_data.begin(),raw_data.end(),cmp);

    // write nc file.
    int retval,ncid;
    string outfile="GAP_P4_dvp.nc";

    retval=nc_create(outfile.c_str(),NC_CLOBBER,&ncid);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));


    // define dimension id.
    int depth_dimid,lat_dimid,lon_dimid;
    retval=nc_def_dim(ncid,"depth",s_depth.size(),&depth_dimid);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));
    retval=nc_def_dim(ncid,"latitude",s_lat.size(),&lat_dimid);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));
    retval=nc_def_dim(ncid,"longitude",s_lon.size(),&lon_dimid);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));

    // v is not a dimension, just a variable,
    // we will generate a variable id from the dimension ids from dimensions.
    int dimids[3];
    dimids[0]=depth_dimid;
    dimids[1]=lat_dimid;
    dimids[2]=lon_dimid;


    // define variable id.
    int depth_varid,lat_varid,lon_varid;
    retval=nc_def_var(ncid,"depth",NC_FLOAT,1,&depth_dimid,&depth_varid);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));
    retval=nc_def_var(ncid,"latitude",NC_FLOAT,1,&lat_dimid,&lat_varid);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));
    retval=nc_def_var(ncid,"longitude",NC_FLOAT,1,&lon_dimid,&lon_varid);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));

    int v_varid;
    retval=nc_def_var(ncid,"v",NC_FLOAT,3,dimids,&v_varid);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));

    // define units.
    string unit_depth="km_downward",unit_lat="degrees_north",unit_lon="degrees_east";
    retval=nc_put_att_text(ncid,depth_varid,"units",unit_depth.size(),unit_depth.c_str());
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));
    retval=nc_put_att_text(ncid,lat_varid,"units",unit_lat.size(),unit_lat.c_str());
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));
    retval=nc_put_att_text(ncid,lon_varid,"units",unit_lon.size(),unit_lon.c_str());
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));

    string unit_v="dvp, (%), input unit";
    retval=nc_put_att_text(ncid,v_varid,"units",unit_v.size(),unit_v.c_str());
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));

    // End of variable definition.
    retval=nc_enddef(ncid);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));

    // load data.

    float *data;
    size_t i;

    /// depth.
    data=new float [s_depth.size()];
    i=0;
    for (auto &item:s_depth) data[i++]=item;
    retval=nc_put_var_float(ncid,depth_varid,data);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));
    delete [] data;

    /// lat.
    data=new float [s_lat.size()];
    i=0;
    for (auto &item:s_lat) data[i++]=item;
    retval=nc_put_var_float(ncid,lat_varid,data);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));
    delete [] data;

    /// lon.
    data=new float [s_lon.size()];
    i=0;
    for (auto &item:s_lon) data[i++]=item;
    retval=nc_put_var_float(ncid,lon_varid,data);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));
    delete [] data;

    /// v.
    data=new float [raw_data.size()];
    i=0;
    for (auto &item:raw_data) data[i++]=item[3];
    retval=nc_put_var_float(ncid,v_varid,data);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));
    delete [] data;

    // close the nc file.
    retval=nc_close(ncid);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));
    
    return 0;

}
