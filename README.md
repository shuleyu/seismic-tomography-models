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
https://github.com/shuleyu/CPP-Library/blob/master/Tomography.hpp \
Example program is:\
https://github.com/shuleyu/CPP-Library/blob/master/Examples/Tomography.cpp

Here are details about download sources and convertions to these nc files:

1. GyPSum\_vs.nc\
Paper        : doi:10.1029/2010JB007631\
Download link: http://ds.iris.edu/spud/earthmodel/10131119 (netCDF binary of S velocity expressed as km/s)\
Changes      : rename variable "vs" to "v".

2. GyPSum\_vp.nc\
Paper        : doi:10.1029/2010JB007631\
Download link: http://ds.iris.edu/spud/earthmodel/10131119 (netCDF binary of P velocity expressed as km/s)\
Changes      : rename variable "vp" to "v".

3. SEMum\_vs.nc\
Paper        : doi:10.1111/j.1365-246X.2011.04969.x\
Download link: http://ds.iris.edu/spud/earthmodel/10131263 (the netCDF binary for the above model expressed as absolute velocity)\
Changes      : lose variable "xi", rename variable "vs" to "v".

4. SEMum\_xi.nc\
Paper        : doi:10.1111/j.1365-246X.2011.04969.x\
Download link: http://ds.iris.edu/spud/earthmodel/10131263 (the netCDF binary for the above model expressed as absolute velocity)\
Changes      : lose variable "vs", rename variable "xi" to "v".

5. MITP08\_dvp.nc\
Paper        : doi:10.1029/2007GC001806\
Download link: https://agupubs.onlinelibrary.wiley.com/action/downloadSupplement?doi=10.1029%2F2007GC001806&file=ggge1202-sup-0002-ds01.txt.gz
Changes      : convert the ascii file into nc file, rename variable "dvp" to "v", see https://github.com/shuleyu/seismic-tomography-models/blob/master/Processing/Create_MITP08_dvp.cpp

6. MITP08\_vp.nc\
Paper        : doi:10.1029/2007GC001806\
Download link: https://agupubs.onlinelibrary.wiley.com/action/downloadSupplement?doi=10.1029%2F2007GC001806&file=ggge1202-sup-0002-ds01.txt.gz
Changes      : convert dvp into vp using ak135 reference model and create this nc file in which "v" representing "vp, km/s", see https://github.com/shuleyu/seismic-tomography-models/blob/master/Processing/Create_MITP08_vp.cpp

7. SAW642AN\_vs.nc\
Paper        : doi:10.1111/j.1365-246X.2006.03100.x\
Download link: http://ds.iris.edu/spud/earthmodel/10131202 (the netCDF binary for the above model expressed in km/s)\
Changes      : lose variables "vp", "rho", "Qs", rename variable "vs" to "v".

8. SAW642AN\_vp.nc\
Paper        : doi:10.1111/j.1365-246X.2006.03100.x\
Download link: http://ds.iris.edu/spud/earthmodel/10131202 (the netCDF binary for the above model expressed in km/s)\
Changes      : lose variables "vs", "rho", "Qs", rename variable "vp" to "v".

9. SAW642AN\_rho.nc\
Paper        : doi:10.1111/j.1365-246X.2006.03100.x\
Download link: http://ds.iris.edu/spud/earthmodel/10131202 (the netCDF binary for the above model expressed in km/s)\
Changes      : lose variables "vs", "vp", "Qs", rename variable "rho" to "v".

10. SAW642AN\_qs.nc\
Paper        : doi:10.1111/j.1365-246X.2006.03100.x\
Download link: http://ds.iris.edu/spud/earthmodel/10131202 (the netCDF binary for the above model expressed in km/s)\
Changes      : lose variables "vs", "vp", "rho", rename variable "Qs" to "v".

11. SAW642ANb\_vs.nc\
Paper        : doi:10.1029/2010JB007520\
Download link: http://ds.iris.edu/spud/earthmodel/10131193 (the netCDF binary for the above model expressed in km/s)\
Changes      : lose variables "vp", "rho", "Qs", rename variable "vs" to "v".

12. SAW642ANb\_vp.nc\
Paper        : doi:10.1029/2010JB007520\
Download link: http://ds.iris.edu/spud/earthmodel/10131193 (the netCDF binary for the above model expressed in km/s)\
Changes      : lose variables "vs", "rho", "Qs", rename variable "vp" to "v".

13. SAW642ANb\_rho.nc\
Paper        : doi:10.1029/2010JB007520\
Download link: http://ds.iris.edu/spud/earthmodel/10131193 (the netCDF binary for the above model expressed in km/s)\
Changes      : lose variables "vs", "vp", "Qs", rename variable "rho" to "v".

14. SAW642ANb\_qs.nc\
Paper        : doi:10.1029/2010JB007520\
Download link: http://ds.iris.edu/spud/earthmodel/10131193 (the netCDF binary for the above model expressed in km/s)\
Changes      : lose variables "vs", "vp", "rho", rename variable "Qs" to "v".

15. SAW24B16\_vs.nc\
Paper        : doi:10.17611/DP/10131184\
Download link: http://ds.iris.edu/spud/earthmodel/10131184 (The netCDF binary for the above 2°x2° model expressed as S-velocity in km/s)\
Changes      : rename variable "vsh" to "v".

16. S362ANI\_vs.nc\
Paper        : doi:10.1029/2007JB005169\
Download link: http://ds.iris.edu/spud/earthmodel/10131231 (the netCDF binary for the above model expressed in km/s)\
Changes      : lose variables "vsv", "vsh", rename variable "vs" to "v".

17. S362ANI\_vsv.nc\
Paper        : doi:10.1029/2007JB005169\
Download link: http://ds.iris.edu/spud/earthmodel/10131231 (the netCDF binary for the above model expressed in km/s)\
Changes      : lose variables "vs", "vsh", rename variable "vsv" to "v".

18. S362ANI\_vsh.nc\
Paper        : doi:10.1029/2007JB005169\
Download link: http://ds.iris.edu/spud/earthmodel/10131231 (the netCDF binary for the above model expressed in km/s)\
Changes      : lose variables "vs", "vsv", rename variable "vsh" to "v".

19. S362ANI+M\_vs.nc\
Paper        : doi:10.1093/gji/ggu356\
Download link: http://ds.iris.edu/spud/earthmodel/10131294 (the netCDF binary for the above model expressed in km/s)\
Changes      : lose variables "vsv", "vsh", rename variable "vs" to "v".

20. S362ANI+M\_vsv.nc\
Paper        : doi:10.1093/gji/ggu356\
Download link: http://ds.iris.edu/spud/earthmodel/10131294 (the netCDF binary for the above model expressed in km/s)\
Changes      : lose variables "vs", "vsh", rename variable "vsv" to "v".

21. S362ANI+M\_vsh.nc\
Paper        : doi:10.1093/gji/ggu356\
Download link: http://ds.iris.edu/spud/earthmodel/10131294 (the netCDF binary for the above model expressed in km/s)\
Changes      : lose variables "vs", "vsv", rename variable "vsh" to "v".

22. S362WMANI\_vs.nc\
Paper        : doi:10.1029/2007JB005169\
Download link: http://ds.iris.edu/spud/earthmodel/10131240 (the netCDF binary for the above model expressed in km/s)\
Changes      : lose variables "vsv", "vsh", rename variable "vs" to "v".

23. S362WMANI\_vsv.nc\
Paper        : doi:10.1029/2007JB005169\
Download link: http://ds.iris.edu/spud/earthmodel/10131240 (the netCDF binary for the above model expressed in km/s)\
Changes      : lose variables "vs", "vsh", rename variable "vsv" to "v".

24. S362WMANI\_vsh.nc\
Paper        : doi:10.1029/2007JB005169\
Download link: http://ds.iris.edu/spud/earthmodel/10131240 (the netCDF binary for the above model expressed in km/s)\
Changes      : lose variables "vs", "vsv", rename variable "vsh" to "v".

25. HMSL-S06\_dvs.nc\
Paper        : doi:10.1111/j.1365-246X.2008.03763.x\
Download link: http://ds.iris.edu/spud/earthmodel/10131133 (The netCDF binary of the model)\
Changes      : rename variable "dvs" to "v".

26. HMSL-S06\_vs.nc\
Paper        : doi:10.1111/j.1365-246X.2008.03763.x\
Download link: http://ds.iris.edu/spud/earthmodel/10131133 (The netCDF binary of the model)\
Changes      : convert dvs into vs using ak135 reference model. However, this doesn't have much meaning. In the model's online discription "While ak135 is the 1D model used for ray tracing in the inversion, the travel time measurements for each phase have the mean removed, so the 3D model is not built with respect to any particular 1D model.", therefore use with care, in this nc file, "v" represents "vs", see https://github.com/shuleyu/seismic-tomography-models/blob/master/Processing/Create_HMSL-S06_vs.cpp

27. HMSL-P06\_dvp.nc\
Paper        : doi:10.1111/j.1365-246X.2008.03763.x\
Download link: http://ds.iris.edu/spud/earthmodel/10131126 (The netCDF binary of the model)\
Changes      : rename variable "dvp" to "v".

28. HMSL-P06\_vp.nc\
Paper        : doi:10.1111/j.1365-246X.2008.03763.x\
Download link: http://ds.iris.edu/spud/earthmodel/10131126 (The netCDF binary of the model)\
Changes      : convert dvp into vp using ak135 reference model. However, this doesn't have much meaning. In the model's online discription "While ak135 is the 1D model used for ray tracing in the inversion, the travel time measurements for each phase have the mean removed, so the 3D model is not built with respect to any particular 1D model.", therefore use with care, in this nc file, "v" represents "vp", see https://github.com/shuleyu/seismic-tomography-models/blob/master/Processing/Create_HMSL-P06_vp.cpp

29. LLNL-G3Dv3\_vp.nc\
Paper        : doi:10.1029/2012JB009525\
Download link: http://ds.iris.edu/spud/earthmodel/10131310 (Complete model package contains LLNL\_G3Dv3\_README.pdf file detailing the contents. Velocity values are expressed as absolute velocity and percentage variations relative to the layer average)\
Changes      : Use the depth (column 3) in "LLNL\_G3Dv3.LayerAverages.txt", latitude ranging from -90 to 90, longitude ranging from -180 to 180, values (column 2) in "LLNL\_G3Dv3.Interpolated.Layer??\_\*km.txt" to creat the vp grid. This ignore a lot details. Use with care. in this nc file, "v" represents "vp". see https://github.com/shuleyu/seismic-tomography-models/blob/master/Processing/Create_LLNL-G3Dv3_vp.cpp

30. LLNL-G3Dv3\_dvp.nc\
Paper        : doi:10.1029/2012JB009525\
Download link: http://ds.iris.edu/spud/earthmodel/10131310 (Complete model package contains LLNL\_G3Dv3\_README.pdf file detailing the contents. Velocity values are expressed as absolute velocity and percentage variations relative to the layer average)\
Changes      : Use the depth (column 3) in "LLNL\_G3Dv3.LayerAverages.txt", latitude ranging from -90 to 90, longitude ranging from -180 to 180, values (column 3) in "LLNL\_G3Dv3.Interpolated.Layer??\_\*km.txt" to creat the dvp grid. This ignore a lot details. Use with care. in this nc file, "v" represents "dvp". see https://github.com/shuleyu/seismic-tomography-models/blob/master/Processing/Create_LLNL-G3Dv3_dvp.cpp

31. TX2000\_dvs.nc\
Paper        : doi:10.1098/rsta.2002.1077\
Download link: http://ds.iris.edu/spud/earthmodel/10131209 (Model on a 4°x4° grid for depths from 60 to 2800 km at non-uniform intervals in netCDF format.)\
Changes      : rename variable "dvs" to "v".

32. TX2000\_vs.nc\
Paper        : doi:10.1098/rsta.2002.1077\
Download link: http://ds.iris.edu/spud/earthmodel/10131209 (Model on a 4°x4° grid for depths from 60 to 2800 km at non-uniform intervals in netCDF format.)\
Changes      : convert dvs into vs using PREM. The desicription in the dvs reads "(% deviation from layer mean)". Use with care. in this nc file, "v" represents "vs". see https://github.com/shuleyu/seismic-tomography-models/blob/master/Processing/Create_TX2000_vs.cpp

33. TX2011\_dvs.nc\
Paper        : doi:10.1098/rsta.2002.1077\
Download link: http://ds.iris.edu/spud/earthmodel/10131216 (Model on a 2°x2° grid for depths from 0 to 2890 km in netCDF format)\
Changes      : rename variable "dvs" to "v".

34. TX2000\_vs.nc\
Paper        : doi:10.1098/rsta.2002.1077\
Download link: http://ds.iris.edu/spud/earthmodel/10131216 (Model on a 2°x2° grid for depths from 0 to 2890 km in netCDF format)\
Changes      : convert dvs into vs using TX2011_ref downloaded from http://ds.iris.edu/files/products/emc/data/TX2011/TX2011_ref. in this nc file, "v" represents "vs". see https://github.com/shuleyu/seismic-tomography-models/blob/master/Processing/Create_TX2011_vs.cpp

35. SEMUCB-WM1\_dvs.nc\
Paper        : doi:10.1093/gji/ggu334\
Download link: http://www.seismo.berkeley.edu/~barbara/REPRINTS/UCB_a3d_dist.SEMUCB-WM1.r20151019.tar.gz \
Changes      : Use the program provided in the tar file, a 10km depth interval (from 60km to 2890km to avoid "nan"), 1 deg x 1 deg grid is created for dvs. This dvs is "the relative Voigt-average shear velocity perturbation relative to the reference 1D model data/model.ref". in this nc file, "v" represents "dvs". see https://github.com/shuleyu/seismic-tomography-models/blob/master/Processing/Create_SEMUCB-WM1_dvs.cpp

36. SEMUCB-WM1\_vsh.nc\
Paper        : doi:10.1093/gji/ggu334\
Download link: http://www.seismo.berkeley.edu/~barbara/REPRINTS/UCB_a3d_dist.SEMUCB-WM1.r20151019.tar.gz \
Changes      : Use the program provided in the tar file, a 10km depth interval (from 60km to 2890km to avoid "nan"), 1 deg x 1 deg grid is created for vsh. in this nc file, "v" represents "vsh". see https://github.com/shuleyu/seismic-tomography-models/blob/master/Processing/Create_SEMUCB-WM1_vsh.cpp

37. SEMUCB-WM1\_vsv.nc\
Paper        : doi:10.1093/gji/ggu334\
Download link: http://www.seismo.berkeley.edu/~barbara/REPRINTS/UCB_a3d_dist.SEMUCB-WM1.r20151019.tar.gz \
Changes      : Use the program provided in the tar file, a 10km depth interval (from 60km to 2890km to avoid "nan"), 1 deg x 1 deg grid is created for vsv. in this nc file, "v" represents "vsv". see https://github.com/shuleyu/seismic-tomography-models/blob/master/Processing/Create_SEMUCB-WM1_vsv.cpp

38. SEMUCB-WM1\_vs.nc\
Paper        : doi:10.1093/gji/ggu334\
Download link: http://www.seismo.berkeley.edu/~barbara/REPRINTS/UCB_a3d_dist.SEMUCB-WM1.r20151019.tar.gz \
Changes      : This vs is the Voigt-average shear velocity (sqrt((vsh^2+2vsv^2)/3)) in the same grid as before. in this nc file, "v" represents "vs". see https://github.com/shuleyu/seismic-tomography-models/blob/master/Processing/Create_SEMUCB-WM1_vs.cpp
