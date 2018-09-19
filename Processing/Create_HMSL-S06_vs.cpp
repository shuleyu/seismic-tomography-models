#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>
#include<set>
#include<algorithm>

#include<AK135.hpp>
#include<Tomography.hpp>

using namespace std;

int main(){

    auto tomo=Tomography("HMSL-S06_dvs.nc");

    // write nc file.
    int retval,ncid;
    string outfile="HMSL-S06_vs.nc";

    retval=nc_create(outfile.c_str(),NC_CLOBBER,&ncid);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));


    // define dimension id.
    int depth_dimid,lat_dimid,lon_dimid;
    retval=nc_def_dim(ncid,"depth",tomo.GetDepths().size(),&depth_dimid);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));
    retval=nc_def_dim(ncid,"latitude",tomo.GetLatitudes().size(),&lat_dimid);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));
    retval=nc_def_dim(ncid,"longitude",tomo.GetLongitudes().size(),&lon_dimid);
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

    string unit_v="vs, km/s, converted form dvs and ak135, however, it might be meaningless, use with care";
    retval=nc_put_att_text(ncid,v_varid,"units",unit_v.size(),unit_v.c_str());
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));

    // End of variable definition.
    retval=nc_enddef(ncid);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));

    // load data.

    float *data;
    size_t i;

    /// depth.
    data=new float [tomo.GetDepths().size()];
    i=0;
    for (auto &item:tomo.GetDepths()) data[i++]=item;
    retval=nc_put_var_float(ncid,depth_varid,data);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));
    delete [] data;

    /// lat.
    data=new float [tomo.GetLatitudes().size()];
    i=0;
    for (auto &item:tomo.GetLatitudes()) data[i++]=item;
    retval=nc_put_var_float(ncid,lat_varid,data);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));
    delete [] data;

    /// lon.
    data=new float [tomo.GetLongitudes().size()];
    i=0;
    for (auto &item:tomo.GetLongitudes()) data[i++]=item;
    retval=nc_put_var_float(ncid,lon_varid,data);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));
    delete [] data;

    /// v.

    data=new float [tomo.GetDepths().size()*tomo.GetLatitudes().size()*tomo.GetLongitudes().size()];
    size_t index=0;
    for (size_t i=0;i<tomo.GetDepths().size();++i) {
        for (size_t j=0;j<tomo.GetLatitudes().size();++j) {
            for (size_t k=0;k<tomo.GetLongitudes().size();++k) {
                data[index]=Dvs_ak135(tomo.GetDepths()[i])*(1+tomo.GetValues()[index]/100.0);
                ++index;
            }
        }
    }
    retval=nc_put_var_float(ncid,v_varid,data);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));
    delete [] data;

    // close the nc file.
    retval=nc_close(ncid);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));
    
    return 0;
}
