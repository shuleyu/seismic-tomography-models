#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>
#include<set>
#include<algorithm>

#include<PREM.hpp>
#include<Tomography.hpp>

using namespace std;

double TX2011_ref(const double &d);

int main(){

    auto tomo=Tomography("TX2011_dvs.nc");

    // write nc file.
    int retval,ncid;
    string outfile="TX2011_vs.nc";

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

    string unit_v="vs, km/s, converted form dvs and TX2011_ref";
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
                data[index]=TX2011_ref(tomo.GetDepths()[i])*(1+tomo.GetValues()[index]/100.0);
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

double TX2011_ref(const double &depth){

    vector<double> d={0.0,3.5,4.0,34.0,36.0,60.0,75.0,100.0,125.0,150.0,175.0,200.0,225.0,250.0,275.0,300.0,325.0,350.0,375.0,395.0,414.0,416.0,425.0,450.0,475.0,500.0,525.0,550.0,575.0,600.0,625.0,645.0,654.0,656.0,675.0,700.0,725.0,750.0,775.0,800.0,825.0,850.0,875.0,900.0,925.0,950.0,975.0,1000.0,1025.0,1050.0,1075.0,1100.0,1125.0,1150.0,1162.5,1175.0,1187.5,1200.0,1212.5,1225.0,1237.5,1250.0,1262.5,1275.0,1287.5,1300.0,1312.5,1325.0,1337.5,1350.0,1362.5,1375.0,1387.5,1400.0,1412.5,1425.0,1437.5,1450.0,1462.5,1475.0,1487.5,1500.0,1512.5,1525.0,1537.5,1550.0,1562.5,1575.0,1587.5,1600.0,1612.5,1625.0,1637.5,1650.0,1662.5,1675.0,1687.5,1700.0,1712.5,1725.0,1737.5,1750.0,1762.5,1775.0,1787.5,1800.0,1812.5,1825.0,1837.5,1850.0,1862.5,1875.0,1887.5,1900.0,1912.5,1925.0,1937.5,1950.0,1962.5,1975.0,1987.5,2000.0,2012.5,2025.0,2037.5,2050.0,2062.5,2075.0,2087.5,2100.0,2112.5,2125.0,2137.5,2150.0,2162.5,2175.0,2187.5,2200.0,2212.5,2225.0,2237.5,2250.0,2262.5,2275.0,2287.5,2300.0,2312.5,2325.0,2337.5,2350.0,2362.5,2375.0,2387.5,2400.0,2412.5,2425.0,2437.5,2450.0,2462.5,2475.0,2487.5,2500.0,2512.5,2525.0,2537.5,2550.0,2562.5,2575.0,2587.5,2600.0,2612.5,2625.0,2637.5,2650.0,2662.5,2675.0,2687.5,2700.0,2712.5,2725.0,2737.5,2750.0,2762.5,2775.0,2787.5,2800.0,2811.4,2822.8,2834.1,2845.5,2856.9,2868.2,2879.6,2891.0,2891.1,2911.0,2931.0,2951.0,2971.0,2996.0,3021.0,3046.0,3071.0,3096.0,3121.0,3146.0,3171.0,3196.0,3221.0,3246.0,3271.0,3296.0,3321.0,3346.0,3371.0,3396.0,3421.0,3446.0,3471.0,3496.0,3521.0,3546.0,3571.0,3596.0,3621.0,3646.0,3671.0,3696.0,3721.0,3746.0,3771.0,3796.0,3821.0,3846.0,3871.0,3896.0,3921.0,3946.0,3971.0,3996.0,4021.0,4046.0,4071.0,4096.0,4121.0,4146.0,4171.0,4196.0,4221.0,4246.0,4271.0,4296.0,4321.0,4346.0,4371.0,4396.0,4421.0,4446.0,4471.0,4496.0,4521.0,4546.0,4571.0,4596.0,4621.0,4646.0,4671.0,4696.0,4721.0,4746.0,4771.0,4796.0,4821.0,4846.0,4871.0,4896.0,4921.0,4946.0,4971.0,4996.0,5021.0,5046.0,5071.0,5110.0,5129.5,5149.0,5150.0,5171.0,5271.0,5371.0,5471.0,5571.0,5671.0,5771.0,5871.0,5971.0,6071.0,6171.0};

    vector<double> vs={3.200,3.200,3.650,3.750,4.600,4.600,4.600,4.600,4.500,4.500,4.500,4.480,4.480,4.480,4.510,4.570,4.630,4.680,4.730,4.770,4.810,5.050,5.070,5.110,5.150,5.190,5.250,5.290,5.330,5.390,5.450,5.520,5.620,5.830,5.950,6.070,6.140,6.190,6.220,6.240,6.260,6.279,6.296,6.313,6.330,6.346,6.363,6.380,6.396,6.411,6.427,6.443,6.458,6.474,6.481,6.489,6.497,6.504,6.511,6.518,6.525,6.532,6.539,6.547,6.554,6.561,6.568,6.575,6.582,6.589,6.596,6.603,6.610,6.617,6.624,6.630,6.637,6.643,6.650,6.657,6.664,6.670,6.677,6.683,6.690,6.696,6.703,6.709,6.716,6.722,6.728,6.734,6.741,6.747,6.753,6.759,6.766,6.772,6.778,6.784,6.790,6.796,6.803,6.809,6.815,6.821,6.827,6.833,6.839,6.845,6.850,6.856,6.862,6.868,6.873,6.879,6.885,6.891,6.896,6.902,6.908,6.914,6.919,6.925,6.931,6.937,6.942,6.948,6.954,6.960,6.965,6.971,6.977,6.983,6.988,6.994,6.999,7.005,7.010,7.016,7.021,7.027,7.032,7.038,7.043,7.049,7.055,7.060,7.065,7.071,7.077,7.083,7.089,7.094,7.099,7.105,7.110,7.116,7.122,7.127,7.132,7.138,7.143,7.149,7.155,7.161,7.166,7.171,7.176,7.182,7.191,7.200,7.222,7.245,7.267,7.290,7.287,7.285,7.283,7.280,7.277,7.275,7.273,7.270,7.267,7.265,7.264,7.263,7.261,7.260,7.259,7.257,7.256,7.255,8.009,8.046,8.082,8.119,8.155,8.199,8.242,8.285,8.328,8.369,8.410,8.451,8.492,8.530,8.569,8.608,8.646,8.682,8.718,8.754,8.790,8.824,8.858,8.892,8.926,8.957,8.988,9.019,9.050,9.080,9.109,9.138,9.168,9.196,9.223,9.251,9.279,9.305,9.331,9.358,9.384,9.409,9.434,9.459,9.484,9.508,9.532,9.555,9.579,9.601,9.624,9.646,9.669,9.690,9.711,9.733,9.754,9.774,9.794,9.815,9.835,9.854,9.873,9.893,9.912,9.930,9.949,9.967,9.986,10.003,10.021,10.038,10.056,10.073,10.090,10.106,10.122,10.139,10.155,10.171,10.187,10.203,10.219,10.234,10.250,10.265,10.280,10.295,10.310,10.333,10.344,10.356,11.028,11.036,11.072,11.105,11.135,11.162,11.185,11.206,11.223,11.237,11.248,11.256};

    // linear interpolate.
    auto it=lower_bound(d.begin(),d.end(),depth);
    size_t index=distance(d.begin(),it);
    if (index==0) return vs[0];
    else if (index==d.size()) return vs.back();
    else return vs[index-1]+(vs[index]-vs[index-1])/(d[index]-d[index-1]);
}
