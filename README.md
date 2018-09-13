# seismic-tomography-models

In this database, I collected several whole mantle tomography results, and
converted them into nc files. Each nc files contain 4 variables: depth,
longitude, latitude and "v". The "v"alues could represent S wave or P wave
speed (in km/s), velocity purturbation (%), density (in kg/m^3), Q or
anisotropic parameters, etc. The details(comments) are within each nc files,
but the nc file names roughly indicate which value it contains.

Most of the model are downloaded from IRIS SPUD Service:\
http://ds.iris.edu/spud/earthmodel \
Others are downloaded from links in papers or from authors' websites and etc.

The c++ tool to read and linear interpolate between values are provided in this file:\
https://github.com/shuleyu/CPP-Library/blob/master/Tomography.hpp
Example program is:\
https://github.com/shuleyu/CPP-Library/blob/master/Examples/Tomography.cpp

Here are details about download sources and convertions to these nc files:

1. GyPSum_vs.nc\
Paper        : doi:10.1029/2010JB007631\
Download link: http://ds.iris.edu/spud/earthmodel/10131119 (netCDF binary of S velocity expressed as km/s)\
Changes      : rename variable "vs" to "v".

2. GyPSum_vp.nc\
Paper        : doi:10.1029/2010JB007631\
Download link: http://ds.iris.edu/spud/earthmodel/10131119 (netCDF binary of P velocity expressed as km/s)\
Changes      : rename variable "vp" to "v".

3. SEMum_vs.nc\
Paper        : doi:10.1111/j.1365-246X.2011.04969.x\
Download link: http://ds.iris.edu/spud/earthmodel/10131263 (the netCDF binary for the above model expressed as absolute velocity)\
Changes      : lose variable "xi", rename variable "vs" to "v".

4. SEMum_xi.nc\
Paper        : doi:10.1111/j.1365-246X.2011.04969.x\
Download link: http://ds.iris.edu/spud/earthmodel/10131263 (the netCDF binary for the above model expressed as absolute velocity)\
Changes      : lose variable "vs", rename variable "xi" to "v".

5. MITP08_dvp.nc\
Paper        : doi:10.1029/2007GC001806\
Download link: https://agupubs.onlinelibrary.wiley.com/action/downloadSupplement?doi=10.1029%2F2007GC001806&file=ggge1202-sup-0002-ds01.txt.gz
Changes      : convert the ascii file into nc file, rename variable "dvp" to "v", see https://github.com/shuleyu/seismic-tomography-models/blob/master/Processing/Create_MITP08_dvp.cpp

6. MITP08_vp.nc\
Paper        : doi:10.1029/2007GC001806\
Download link: https://agupubs.onlinelibrary.wiley.com/action/downloadSupplement?doi=10.1029%2F2007GC001806&file=ggge1202-sup-0002-ds01.txt.gz
Changes      : convert dvp into vp using ak135 reference model and create this nc file in which "v" representing "vp, km/s", see https://github.com/shuleyu/seismic-tomography-models/blob/master/Processing/Create_MITP08_vp.cpp

7. SAW642AN_vs.nc\
Paper        : doi:10.1111/j.1365-246X.2006.03100.x\
Download link: http://ds.iris.edu/spud/earthmodel/10131202 (the netCDF binary for the above model expressed in km/s)\
Changes      : lose variables "vp", "rho", "Qs", rename variable "vs" to "v".

8. SAW642AN_vp.nc\
Paper        : doi:10.1111/j.1365-246X.2006.03100.x\
Download link: http://ds.iris.edu/spud/earthmodel/10131202 (the netCDF binary for the above model expressed in km/s)\
Changes      : lose variables "vs", "rho", "Qs", rename variable "vp" to "v".

9. SAW642AN_rho.nc\
Paper        : doi:10.1111/j.1365-246X.2006.03100.x\
Download link: http://ds.iris.edu/spud/earthmodel/10131202 (the netCDF binary for the above model expressed in km/s)\
Changes      : lose variables "vs", "vp", "Qs", rename variable "rho" to "v".

10. SAW642AN_qs.nc\
Paper        : doi:10.1111/j.1365-246X.2006.03100.x\
Download link: http://ds.iris.edu/spud/earthmodel/10131202 (the netCDF binary for the above model expressed in km/s)\
Changes      : lose variables "vs", "vp", "rho", rename variable "Qs" to "v".

11. SAW642ANb_vs.nc\
Paper        : doi:10.1029/2010JB007520\
Download link: http://ds.iris.edu/spud/earthmodel/10131193 (the netCDF binary for the above model expressed in km/s)\
Changes      : lose variables "vp", "rho", "Qs", rename variable "vs" to "v".

12. SAW642ANb_vp.nc\
Paper        : doi:10.1029/2010JB007520\
Download link: http://ds.iris.edu/spud/earthmodel/10131193 (the netCDF binary for the above model expressed in km/s)\
Changes      : lose variables "vs", "rho", "Qs", rename variable "vp" to "v".

13. SAW642ANb_rho.nc\
Paper        : doi:10.1029/2010JB007520\
Download link: http://ds.iris.edu/spud/earthmodel/10131193 (the netCDF binary for the above model expressed in km/s)\
Changes      : lose variables "vs", "vp", "Qs", rename variable "rho" to "v".

14. SAW642ANb_qs.nc\
Paper        : doi:10.1029/2010JB007520\
Download link: http://ds.iris.edu/spud/earthmodel/10131193 (the netCDF binary for the above model expressed in km/s)\
Changes      : lose variables "vs", "vp", "rho", rename variable "Qs" to "v".

15. SAW24B16_vs.nc\
Paper        : doi:10.17611/DP/10131184\
Download link: http://ds.iris.edu/spud/earthmodel/10131184 (The netCDF binary for the above 2°x2° model expressed as S-velocity in km/s)\
Changes      : rename variable "vsh" to "v".

16. S362ANI_vs.nc\
Paper        : doi:10.1029/2007JB005169\
Download link: http://ds.iris.edu/spud/earthmodel/10131231 (the netCDF binary for the above model expressed in km/s)\
Changes      : lose variables "vsv", "vsh", rename variable "vs" to "v".

17. S362ANI_vsv.nc\
Paper        : doi:10.1029/2007JB005169\
Download link: http://ds.iris.edu/spud/earthmodel/10131231 (the netCDF binary for the above model expressed in km/s)\
Changes      : lose variables "vs", "vsh", rename variable "vsv" to "v".

18. S362ANI_vsh.nc\
Paper        : doi:10.1029/2007JB005169\
Download link: http://ds.iris.edu/spud/earthmodel/10131231 (the netCDF binary for the above model expressed in km/s)\
Changes      : lose variables "vs", "vsv", rename variable "vsh" to "v".

19. S362ANI+M_vs.nc\
Paper        : doi:10.1093/gji/ggu356\
Download link: http://ds.iris.edu/spud/earthmodel/10131294 (the netCDF binary for the above model expressed in km/s)\
Changes      : lose variables "vsv", "vsh", rename variable "vs" to "v".

20. S362ANI+M_vsv.nc\
Paper        : doi:10.1093/gji/ggu356\
Download link: http://ds.iris.edu/spud/earthmodel/10131294 (the netCDF binary for the above model expressed in km/s)\
Changes      : lose variables "vs", "vsh", rename variable "vsv" to "v".

21. S362ANI+M_vsh.nc\
Paper        : doi:10.1093/gji/ggu356\
Download link: http://ds.iris.edu/spud/earthmodel/10131294 (the netCDF binary for the above model expressed in km/s)\
Changes      : lose variables "vs", "vsv", rename variable "vsh" to "v".

22. S362WMANI_vs.nc\
Paper        : doi:10.1029/2007JB005169\
Download link: http://ds.iris.edu/spud/earthmodel/10131240 (the netCDF binary for the above model expressed in km/s)\
Changes      : lose variables "vsv", "vsh", rename variable "vs" to "v".

23. S362WMANI_vsv.nc\
Paper        : doi:10.1029/2007JB005169\
Download link: http://ds.iris.edu/spud/earthmodel/10131240 (the netCDF binary for the above model expressed in km/s)\
Changes      : lose variables "vs", "vsh", rename variable "vsv" to "v".

24. S362WMANI_vsh.nc\
Paper        : doi:10.1029/2007JB005169\
Download link: http://ds.iris.edu/spud/earthmodel/10131240 (the netCDF binary for the above model expressed in km/s)\
Changes      : lose variables "vs", "vsv", rename variable "vsh" to "v".
