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

// the downloaded data is named "TX2000_percent.nc"
// TX2000_percent.nc has longitude range -3 ~ 357.
// Will adjust it to 1 ~ 357 (lose -3 values).

using namespace std;

int main(){

    string infile="TX2000_percent.nc";
    string outfile="TX2000_dvs.nc";

    // read nc file.
    int retval,ncid;
    retval=nc_open(infile.c_str(),NC_NOWRITE,&ncid);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));

    // get depth length and content.
    int depth_id;
    size_t depth_len;
    retval=nc_inq_dimid(ncid,"depth",&depth_id);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));
    retval=nc_inq_dimlen(ncid,depth_id,&depth_len);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));

    int depth_varid;
    retval=nc_inq_varid(ncid,"depth",&depth_varid);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));

    float *depth = new float [depth_len];
    retval=nc_get_var_float(ncid,depth_varid,depth);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));


    // get latitude length and content.
    int lat_id;
    size_t lat_len;
    retval=nc_inq_dimid(ncid,"latitude",&lat_id);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));
    retval=nc_inq_dimlen(ncid,lat_id,&lat_len);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));

    int lat_varid;
    retval=nc_inq_varid(ncid,"latitude",&lat_varid);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));

    float *lat=new float [lat_len];
    retval=nc_get_var_float(ncid,lat_varid,lat);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));
cout << lat[0] << endl;


    // get longitude length and content.
    int lon_id;
    size_t lon_len;
    retval=nc_inq_dimid(ncid,"longitude",&lon_id);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));
    retval=nc_inq_dimlen(ncid,lon_id,&lon_len);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));

    int lon_varid;
    retval=nc_inq_varid(ncid,"longitude",&lon_varid);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));

    float *lon_raw=new float [lon_len];
    retval=nc_get_var_float(ncid,lon_varid,lon_raw);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));

    // get dvs.

    size_t dvs_raw_len=depth_len*lat_len*lon_len;

    int dvs_varid;
    retval=nc_inq_varid(ncid,"dvs",&dvs_varid);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));

    float *dvs_raw=new float [dvs_raw_len];
    retval=nc_get_var_float(ncid,dvs_varid,dvs_raw);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));

    // close infile.
    retval=nc_close(ncid);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));


    // write nc file.
    retval=nc_create(outfile.c_str(),NC_CLOBBER,&ncid);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));


    // define dimension id.
    int depth_dimid,lat_dimid,lon_dimid;
    retval=nc_def_dim(ncid,"depth",depth_len,&depth_dimid);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));
    retval=nc_def_dim(ncid,"latitude",lat_len,&lat_dimid);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));
    retval=nc_def_dim(ncid,"longitude",lon_len-1,&lon_dimid);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));

    // v is not a dimension, just a variable,
    // we will generate a variable id from the dimension ids from dimensions.
    int dimids[3];
    dimids[0]=depth_dimid;
    dimids[1]=lat_dimid;
    dimids[2]=lon_dimid;


    // define variable id.
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
    string unit_depth="km_downward",unit_lat="degrees_south",unit_lon="degrees_east";
    retval=nc_put_att_text(ncid,depth_varid,"units",unit_depth.size(),unit_depth.c_str());
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));
    retval=nc_put_att_text(ncid,lat_varid,"units",unit_lat.size(),unit_lat.c_str());
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));
    retval=nc_put_att_text(ncid,lon_varid,"units",unit_lon.size(),unit_lon.c_str());
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));

    string unit_v="Vs perturbation (\% deviation from layer mean)";
    retval=nc_put_att_text(ncid,v_varid,"units",unit_v.size(),unit_v.c_str());
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));

    // End of variable definition.
    retval=nc_enddef(ncid);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));

    // load data.

    /// depth.
    retval=nc_put_var_float(ncid,depth_varid,depth);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));

    /// lat.
cout << lat[0] << endl;
    retval=nc_put_var_float(ncid,lat_varid,lat);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));

    /// lon.
    
    float *lon=new float [lon_len-1];
    for (size_t i=1;i<lon_len;++i) lon[i-1]=lon_raw[i];
    retval=nc_put_var_float(ncid,lon_varid,lon);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));

    /// v.
    size_t dvs_len=depth_len*lat_len*(lon_len-1);
    float *dvs=new float [dvs_len];
    for (size_t i=0;i<dvs_raw_len;++i) {
        size_t depth_index=i/(lat_len*lon_len);
        size_t lat_index=(i%(lat_len*lon_len))/lon_len;
        size_t lon_index=(i%(lat_len*lon_len))%lon_len;
        if (lon_index==0) continue;
        --lon_index;
        dvs[depth_index*(lat_len*(lon_len-1))+lat_index*(lon_len-1)+lon_index]=dvs_raw[i];
    }
    retval=nc_put_var_float(ncid,v_varid,dvs);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));

    // close the nc file.
    retval=nc_close(ncid);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));

    return 0;
}
