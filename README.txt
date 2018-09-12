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

1. GyPsum_S
