#ifndef ASU_TOMOGRAPHY
#define ASU_TOMOGRAPHY

#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>

#include<Lon2180.hpp>
#include<Lon2360.hpp>
#include<LinearInterp.hpp>

extern "C" {
// Current version: netcdf-4.6.1
#include<netcdf.h>
}

/*************************************************
 * This tool provides an interface to use the
 * tomography nc files.
 *
 * Shule Yu
 * Sept 12 2018
 *
 * Key words: whole mantle, tomography.
*************************************************/

class Tomography {

    std::vector<double> depth,lat,lon,v; // depth in km. lon between [-180,180].
    bool range_is_360;

public:
    Tomography()=default;

    Tomography(const std::vector<double> &d, const std::vector<double> &lo,
          const std::vector<double> &la, const std::vector<double> &data) {
        if (data.size()!=d.size()*lo.size()*la.size())
            throw std::runtime_error("In "+std::string(__func__)+", input sizes don't match.");
        depth=d;lat=la;lon=lo;v=data;range_is_360=(!lon.empty() && lon[0]>=0);
        if (!la.empty() && la[0]>0) ReverseLatitude();
    }

    Tomography(const std::string &nc_filename){

        // tmp data.
        float *data;

        // open the nc file.
        int retval,ncid;
        retval=nc_open(nc_filename.c_str(),NC_NOWRITE,&ncid);
        if (retval!=0) throw std::runtime_error(nc_strerror(retval));


        // get depth length and data.
        int depth_id;
        size_t depth_len;
        retval=nc_inq_dimid(ncid,"depth",&depth_id);
        if (retval!=0) throw std::runtime_error(nc_strerror(retval));
        retval=nc_inq_dimlen(ncid,depth_id,&depth_len);
        if (retval!=0) throw std::runtime_error(nc_strerror(retval));
        depth.resize(depth_len);

        int depth_varid;
        retval=nc_inq_varid(ncid,"depth",&depth_varid);
        if (retval!=0) throw std::runtime_error(nc_strerror(retval));

        data=new float [depth_len];
        retval=nc_get_var_float(ncid,depth_varid,data);
        if (retval!=0) throw std::runtime_error(nc_strerror(retval));
        for (size_t i=0;i<depth_len;++i) depth[i]=data[i];
        delete [] data;


        // get latitude length and data.
        int lat_id;
        size_t lat_len;
        retval=nc_inq_dimid(ncid,"latitude",&lat_id);
        if (retval!=0) throw std::runtime_error(nc_strerror(retval));
        retval=nc_inq_dimlen(ncid,lat_id,&lat_len);
        if (retval!=0) throw std::runtime_error(nc_strerror(retval));
        lat.resize(lat_len);

        int lat_varid;
        retval=nc_inq_varid(ncid,"latitude",&lat_varid);
        if (retval!=0) throw std::runtime_error(nc_strerror(retval));

        data=new float [lat_len];
        retval=nc_get_var_float(ncid,lat_varid,data);
        if (retval!=0) throw std::runtime_error(nc_strerror(retval));
        for (size_t i=0;i<lat_len;++i) lat[i]=data[i];
        delete [] data;

        // get longitude length and data.
        int lon_id;
        size_t lon_len;
        retval=nc_inq_dimid(ncid,"longitude",&lon_id);
        if (retval!=0) throw std::runtime_error(nc_strerror(retval));
        retval=nc_inq_dimlen(ncid,lon_id,&lon_len);
        if (retval!=0) throw std::runtime_error(nc_strerror(retval));
        lon.resize(lon_len);

        int lon_varid;
        retval=nc_inq_varid(ncid,"longitude",&lon_varid);
        if (retval!=0) throw std::runtime_error(nc_strerror(retval));

        data=new float [lon_len];
        retval=nc_get_var_float(ncid,lon_varid,data);
        if (retval!=0) throw std::runtime_error(nc_strerror(retval));
        for (size_t i=0;i<lon_len;++i) lon[i]=data[i];
        delete [] data;

        range_is_360=(!lon.empty() && lon[0]>=0);

        // get velocity length and data.
        size_t v_len=depth_len*lat_len*lon_len;
        v.resize(v_len);

        int v_varid;
        retval=nc_inq_varid(ncid,"v",&v_varid);
        if (retval!=0) throw std::runtime_error(nc_strerror(retval));

        data=new float [v_len];
        retval=nc_get_var_float(ncid,v_varid,data);
        if (retval!=0) throw std::runtime_error(nc_strerror(retval));
        for (size_t i=0;i<v_len;++i) v[i]=data[i];
        delete [] data;


        // close the nc file.
        retval=nc_close(ncid);
        if (retval!=0) throw std::runtime_error(nc_strerror(retval));

        // check latitude direction.
        if (!lat.empty() && lat[0]>0) ReverseLatitude();
    }

    double GetValueAt(const double &d, double lo, const double &la) const;
    const std::vector<double> &GetDepths() const {return depth;}
    const std::vector<double> &GetLatitudes() const {return lat;}
    const std::vector<double> &GetLongitudes() const {return lon;}
    const std::vector<double> &GetValues() const {return v;}
    void ReverseLatitude();

};

double Tomography::GetValueAt(const double &d, double lo, const double &la) const {

    if (v.empty())
        throw std::runtime_error("In "+std::string(__func__)+", model is empty.");

    if (d<depth[0] || d>depth.back() || la<lat[0] || la>lat.back()) return 0.0/0.0;

    size_t lat_len=GetLatitudes().size(),lon_len=GetLongitudes().size();

    lo=(range_is_360?Lon2360(lo):Lon2180(lo));
    size_t index_depth=std::distance(depth.begin(),
                                     std::lower_bound(depth.begin(),depth.end(),d));
    size_t index_lat=std::distance(lat.begin(),std::lower_bound(lat.begin(),lat.end(),la));
    size_t index_lon=std::distance(lon.begin(),std::lower_bound(lon.begin(),lon.end(),lo));

    size_t index_prev_depth=(index_depth==0?0:index_depth-1);
    size_t index_prev_lat=(index_lat==0?0:index_lat-1);
    size_t index_prev_lon=(index_lon==0?lon_len-1:index_lon-1);
    if (index_lon==lon_len) index_lon=0;


    std::vector<double> p(8),pp(3);
    p[0]=v[index_prev_depth*lat_len*lon_len+index_prev_lat*lon_len+index_prev_lon];
    p[1]=v[index_prev_depth*lat_len*lon_len+index_prev_lat*lon_len+index_lon];
    p[2]=v[index_prev_depth*lat_len*lon_len+index_lat*lon_len+index_prev_lon];
    p[3]=v[index_prev_depth*lat_len*lon_len+index_lat*lon_len+index_lon];
    p[4]=v[index_depth*lat_len*lon_len+index_prev_lat*lon_len+index_prev_lon];
    p[5]=v[index_depth*lat_len*lon_len+index_prev_lat*lon_len+index_lon];
    p[6]=v[index_depth*lat_len*lon_len+index_lat*lon_len+index_prev_lon];
    p[7]=v[index_depth*lat_len*lon_len+index_lat*lon_len+index_lon];
    if (index_prev_lon>index_lon)
        pp[0]=((lo<lon[index_prev_lon]?lo+360:lo)-lon[index_prev_lon])
              /(lon[index_lon]+360-lon[index_prev_lon]);
    else
        pp[0]=(lo-lon[index_prev_lon])/(lon[index_lon]-lon[index_prev_lon]);
    pp[1]=(la-lat[index_prev_lat])/(lat[index_lat]-lat[index_prev_lat]);
    pp[2]=(d-depth[index_prev_depth])/(depth[index_depth]-depth[index_prev_depth]);
    return LinearInterp(p,pp);
}

void Tomography::ReverseLatitude(){
    auto old_data=GetValues();
    size_t lat_len=GetLatitudes().size(),lon_len=GetLongitudes().size();

    for (size_t i=0;i<GetValues().size();++i){
        size_t depth_index=i/(lat_len*lon_len);
        size_t lat_index=lat_len-1-(i%(lat_len*lon_len))/lon_len;
        size_t lon_index=(i%(lat_len*lon_len))%lon_len;
        v[i]=old_data[depth_index*(lat_len*lon_len)+lat_index*lon_len+lon_index];
    }
    std::reverse(lat.begin(),lat.end());
    return;
}

#endif
