# seismic-tomography-models

In this database, I collected several whole mantle tomography results, and
converted them into nc files. Each nc files contain 4 values: depth,
longitude, latitude and wave speed (in km/s). The speed could be either S or
P, indicated in the file names.

Most of the model are downloaded from IRIS SPUD Service:
http://ds.iris.edu/spud/earthmodel
Others are downloaded from links in papers/authors' websites and etc.

The c++ tool to read the values are provided in this file:
https://github.com/shuleyu/CPP-Library/blob/master/Tomography.hpp
Example program is:
https://github.com/shuleyu/CPP-Library/blob/master/Examples/Tomography.cpp

Here are details about download sources and convertions to these nc files:

1. GyPSum_S.nc
Paper        : doi:10.1029/2010JB007631
Download link: http://ds.iris.edu/spud/earthmodel/10131119 (netCDF binary of S velocity expressed as km/s)
Changes      : rename variable "vs" to "v".

2. GyPSum_P.nc
Paper        : doi:10.1029/2010JB007631
Download link: http://ds.iris.edu/spud/earthmodel/10131119 (netCDF binary of P velocity expressed as km/s)
Changes      : rename variable "vp" to "v".
