# seismic-tomography-models

In this database, I collected several whole mantle tomography results, and
converted them into nc files. Each nc files contain 4 variables: depth,
longitude, latitude and "v". The "v"alues could represent either S or P wave
speed (in km/s), density (in g/cm^3), Q or anisotropic parameters, etc. The
details(comments) are within each nc files, but the file name roughly
indicate which value it represent.

Most of the model are downloaded from IRIS SPUD Service:\
http://ds.iris.edu/spud/earthmodel\
Others are downloaded from links in papers or from authors' websites and etc.\

The c++ tool to read and linear interpolate between values are provided in this file:\
https://github.com/shuleyu/CPP-Library/blob/master/Tomography.hpp\
Example program is:\
https://github.com/shuleyu/CPP-Library/blob/master/Examples/Tomography.cpp\

Here are details about download sources and convertions to these nc files:

1. GyPSum_S.nc\
Paper        : doi:10.1029/2010JB007631\
Download link: http://ds.iris.edu/spud/earthmodel/10131119 (netCDF binary of S velocity expressed as km/s)\
Changes      : rename variable "vs" to "v".\

2. GyPSum_P.nc\
Paper        : doi:10.1029/2010JB007631\
Download link: http://ds.iris.edu/spud/earthmodel/10131119 (netCDF binary of P velocity expressed as km/s)\
Changes      : rename variable "vp" to "v".\

3. SEMum_S.nc\
Paper        : doi:10.1111/j.1365-246X.2011.04969.x\
Download link: http://ds.iris.edu/spud/earthmodel/10131263 (the netCDF binary for the above model expressed as absolute velocity)\
Changes      : lose variable "xi", rename variable "vs" to "v".\

4. SEMum_XI.nc\
Paper        : doi:10.1111/j.1365-246X.2011.04969.x\
Download link: http://ds.iris.edu/spud/earthmodel/10131263 (the netCDF binary for the above model expressed as absolute velocity)\
Changes      : lose variable "vs", rename variable "xi" to "v".\
