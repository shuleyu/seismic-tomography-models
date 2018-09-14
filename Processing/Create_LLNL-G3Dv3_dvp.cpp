#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>
#include<set>
#include<algorithm>

extern "C" {
// Current version: netcdf-4.6.1
#include<netcdf.h>
}

// the downloaded files are converted into "LLNL-G3Dv3_dvp.txt";

using namespace std;

int main(){

    vector<vector<float>> raw_data;
    float lat,lon,depth,dvp;
    set<float> s_lat,s_lon;
    vector<float> s_depth={0.0000,2.3800,2.3800,2.6200,2.6200,3.1500,3.1500,3.4300,3.4300,9.3400,9.3400,15.7200,15.7200,21.6200,21.6200,68.3100,115.0000,150.0000,185.0000,220.0000,265.0000,310.0000,355.0000,412.2700,412.2700,457.1500,502.0200,546.9000,591.7700,623.1900,654.6000,654.6000,721.0000,771.0000,871.0000,971.0000,1071.0000,1171.0000,1271.0000,1371.0000,1471.0000,1571.0000,1671.0000,1771.0000,1871.0000,1971.0000,2071.0000,2170.9900,2271.0000,2371.0000,2471.0000,2571.0000,2671.0000,2741.0000,2771.0000,2871.0000,2891.0000};
    string tmpstr;
    ifstream fpin("LLNL-G3Dv3_dvp.txt");

    while (fpin >> depth >> lat >> lon >> dvp){
        raw_data.push_back({depth,lat,lon,dvp});
        s_lat.insert(lat);
        s_lon.insert(lon);
    }
    fpin.close();

    // write nc file.
    int retval,ncid;
    string outfile="LLNL-G3Dv3_dvp.nc";

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

    string unit_v="dvp, (%)";
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
