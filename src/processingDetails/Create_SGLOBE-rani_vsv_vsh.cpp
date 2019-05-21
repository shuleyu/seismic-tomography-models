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

// the downloaded data are named "SGLOBE-rani-voigt_percent.nc" and "SGLOBE-rani-true-xi.nc"
// will create two nc files: "SGLOBE-rani_vsv.nc" and "SGLOBE-rani_vsh.nc"

using namespace std;

int main(){

    string infile_dvs="SGLOBE-rani-voigt_percent.nc",infile_xi="SGLOBE-rani-true-xi.nc";
    string outfile_vsv="SGLOBE-rani_vsv.nc",outfile_vsh="SGLOBE-rani_vsh.nc";

    // read nc file.
    int retval,ncid;
    retval=nc_open(infile_dvs.c_str(),NC_NOWRITE,&ncid);
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

    float *lon=new float [lon_len];
    retval=nc_get_var_float(ncid,lon_varid,lon);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));

    // get dvs.

    size_t dvs_len=depth_len*lat_len*lon_len;

    int dvs_varid;
    retval=nc_inq_varid(ncid,"dvs",&dvs_varid);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));

    float *dvs=new float [dvs_len];
    float *vs=new float [dvs_len];
    retval=nc_get_var_float(ncid,dvs_varid,dvs);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));


    // convert dvs to vs (Voigt) using PREM.
    for (size_t i=0;i<dvs_len;++i)
        vs[i]=(1+dvs[i]/100)*Dvs(depth[i/(lon_len*lat_len)]);

    retval=nc_close(ncid);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));

    // get xi.

    retval=nc_open(infile_xi.c_str(),NC_NOWRITE,&ncid);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));

    int xi_varid;
    retval=nc_inq_varid(ncid,"xi",&xi_varid);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));

    float *xi=new float [dvs_len];
    retval=nc_get_var_float(ncid,xi_varid,xi);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));


    // convert vs (Voigt) and xi to vsv and vsh.
    float *vsv=new float [dvs_len];
    float *vsh=new float [dvs_len];
    for (size_t i=0;i<dvs_len;++i) {
        vsv[i]=vs[i]*sqrt(3.0/(2+xi[i]));
        vsh[i]=vsv[i]*sqrt(xi[i]);
    }

    retval=nc_close(ncid);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));


    // write vsv nc file.
    retval=nc_create(outfile_vsv.c_str(),NC_CLOBBER,&ncid);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));


    // define dimension id.
    int depth_dimid,lat_dimid,lon_dimid;
    retval=nc_def_dim(ncid,"depth",depth_len,&depth_dimid);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));
    retval=nc_def_dim(ncid,"latitude",lat_len,&lat_dimid);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));
    retval=nc_def_dim(ncid,"longitude",lon_len,&lon_dimid);
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
    string unit_depth="km_downward",unit_lat="degrees_north",unit_lon="degrees_east";
    retval=nc_put_att_text(ncid,depth_varid,"units",unit_depth.size(),unit_depth.c_str());
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));
    retval=nc_put_att_text(ncid,lat_varid,"units",unit_lat.size(),unit_lat.c_str());
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));
    retval=nc_put_att_text(ncid,lon_varid,"units",unit_lon.size(),unit_lon.c_str());
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));

    string unit_v="vsv, km/s";
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
    retval=nc_put_var_float(ncid,lat_varid,lat);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));

    /// lon.
    retval=nc_put_var_float(ncid,lon_varid,lon);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));

    /// v.
    retval=nc_put_var_float(ncid,v_varid,vsv);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));

    // close the nc file.
    retval=nc_close(ncid);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));


    // write vsh nc file.
    retval=nc_create(outfile_vsh.c_str(),NC_CLOBBER,&ncid);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));


    // define dimension id.
    retval=nc_def_dim(ncid,"depth",depth_len,&depth_dimid);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));
    retval=nc_def_dim(ncid,"latitude",lat_len,&lat_dimid);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));
    retval=nc_def_dim(ncid,"longitude",lon_len,&lon_dimid);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));

    // v is not a dimension, just a variable,
    // we will generate a variable id from the dimension ids from dimensions.
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

    retval=nc_def_var(ncid,"v",NC_FLOAT,3,dimids,&v_varid);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));

    // define units.
    retval=nc_put_att_text(ncid,depth_varid,"units",unit_depth.size(),unit_depth.c_str());
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));
    retval=nc_put_att_text(ncid,lat_varid,"units",unit_lat.size(),unit_lat.c_str());
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));
    retval=nc_put_att_text(ncid,lon_varid,"units",unit_lon.size(),unit_lon.c_str());
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));

    unit_v="vsh, km/s";
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
    retval=nc_put_var_float(ncid,lat_varid,lat);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));

    /// lon.
    retval=nc_put_var_float(ncid,lon_varid,lon);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));

    /// v.
    retval=nc_put_var_float(ncid,v_varid,vsh);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));

    // close the nc file.
    retval=nc_close(ncid);
    if (retval!=0) throw std::runtime_error(nc_strerror(retval));

    return 0;
}
