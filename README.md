# seismic-tomography-models


![Summary](https://github.com/shuleyu/seismic-tomography-models/blob/master/Summary.txt)
![alt text](https://github.com/shuleyu/seismic-tomography-models/blob/master/src/utils/largePlot.png)

In this database, I collected several whole mantle tomography models.
I converted them into nc files for conformity and easy-access.
Each nc files contain 4 variables: depth, longitude, latitude and "v".
The "v"alues could represent:
- S wave or P wave speed (in km/s)
- S wave or P velocity purturbation (%)
- density (in kg/m^3)
- attenuation factor Q
- anisotropic parameters
- etc.

Please refer to the file name and the comments within each nc files for the
meaning of "v"alue.

The c++ tools to read the nc files and to get value at
certain location are provided in `src`

Dependencies are 
- netcdf-4.6.1
- (optional, for plotting) GMT-5.4.4

Here are details about data sources and preprocessings to make these nc files:

1. GyPSuM\_vs.nc\
Paper        : [Simmons et al., 2010] https://doi.org/10.1029/2010JB007631 \
Download link: http://ds.iris.edu/spud/earthmodel/10131119 (netCDF binary of S velocity expressed as km/s)\
Changes      : rename variable "vs" to "v".

2. GyPSuM\_vp.nc\
Paper        : [Simmons et al., 2010] https://doi.org/10.1029/2010JB007631 \
Download link: http://ds.iris.edu/spud/earthmodel/10131119 (netCDF binary of P velocity expressed as km/s)\
Changes      : rename variable "vp" to "v".

3. SEMum\_vs.nc\
Paper        : [Lekic and Romanowicz, 2011] https://doi.org/10.1111/j.1365-246X.2011.04969.x \
Download link: http://ds.iris.edu/spud/earthmodel/10131263 (the netCDF binary for the above model expressed as absolute velocity)\
Changes      : lose variable "xi", rename variable "vs" to "v".

4. SEMum\_xi.nc\
Paper        : [Lekic and Romanowicz, 2011] https://doi.org/10.1111/j.1365-246X.2011.04969.x \
Download link: http://ds.iris.edu/spud/earthmodel/10131263 (the netCDF binary for the above model expressed as absolute velocity)\
Changes      : lose variable "vs", rename variable "xi" to "v". xi= (vsh^2/vsv^2).

5. MITP08\_dvp.nc\
Paper        : [Li et al., 2008] https://doi.org/10.1029/2007GC001806 \
Download link: https://agupubs.onlinelibrary.wiley.com/action/downloadSupplement?doi=10.1029%2F2007GC001806&file=ggge1202-sup-0002-ds01.txt.gz \
Changes      : convert the ascii file into nc file, rename variable "dvp" to "v", see https://github.com/shuleyu/seismic-tomography-models/blob/master/Processing/Create_MITP08_dvp.cpp

6. MITP08\_vp.nc\
Paper        : [Li et al., 2008] https://doi.org/10.1029/2007GC001806 \
Download link: https://agupubs.onlinelibrary.wiley.com/action/downloadSupplement?doi=10.1029%2F2007GC001806&file=ggge1202-sup-0002-ds01.txt.gz \
Changes      : convert dvp into vp using ak135 reference model and create this nc file in which "v" representing "vp, km/s", see https://github.com/shuleyu/seismic-tomography-models/blob/master/Processing/Create_MITP08_vp.cpp

7. SAW642AN\_vs.nc\
Paper        : [Panning and Romanowicz, 2006] https://doi.org/10.1111/j.1365-246X.2006.03100.x \
Download link: http://ds.iris.edu/spud/earthmodel/10131202 (the netCDF binary for the above model expressed in km/s)\
Changes      : lose variables "vp", "rho", "Qs", rename variable "vs" to "v".

8. SAW642AN\_vp.nc\
Paper        : [Panning and Romanowicz, 2006] https://doi.org/10.1111/j.1365-246X.2006.03100.x \
Download link: http://ds.iris.edu/spud/earthmodel/10131202 (the netCDF binary for the above model expressed in km/s)\
Changes      : lose variables "vs", "rho", "Qs", rename variable "vp" to "v".

9. SAW642AN\_rho.nc\
Paper        : [Panning and Romanowicz, 2006] https://doi.org/10.1111/j.1365-246X.2006.03100.x \
Download link: http://ds.iris.edu/spud/earthmodel/10131202 (the netCDF binary for the above model expressed in km/s)\
Changes      : lose variables "vs", "vp", "Qs", rename variable "rho" to "v".

10. SAW642AN\_qs.nc\
Paper        : [Panning and Romanowicz, 2006] https://doi.org/10.1111/j.1365-246X.2006.03100.x \
Download link: http://ds.iris.edu/spud/earthmodel/10131202 (the netCDF binary for the above model expressed in km/s)\
Changes      : lose variables "vs", "vp", "rho", rename variable "Qs" to "v".

11. SAW642ANb\_vs.nc\
Paper        : [Panning and Romanowicz, 2010] https://doi.org/10.1029/2010JB007520 \
Download link: http://ds.iris.edu/spud/earthmodel/10131193 (the netCDF binary for the above model expressed in km/s)\
Changes      : lose variables "vp", "rho", "Qs", rename variable "vs" to "v".

12. SAW642ANb\_vp.nc\
Paper        : [Panning and Romanowicz, 2010] https://doi.org/10.1029/2010JB007520 \
Download link: http://ds.iris.edu/spud/earthmodel/10131193 (the netCDF binary for the above model expressed in km/s)\
Changes      : lose variables "vs", "rho", "Qs", rename variable "vp" to "v".

13. SAW642ANb\_rho.nc\
Paper        : [Panning and Romanowicz, 2010] https://doi.org/10.1029/2010JB007520 \
Download link: http://ds.iris.edu/spud/earthmodel/10131193 (the netCDF binary for the above model expressed in km/s)\
Changes      : lose variables "vs", "vp", "Qs", rename variable "rho" to "v".

14. SAW642ANb\_qs.nc\
Paper        : [Panning and Romanowicz, 2010] https://doi.org/10.1029/2010JB007520 \
Download link: http://ds.iris.edu/spud/earthmodel/10131193 (the netCDF binary for the above model expressed in km/s)\
Changes      : lose variables "vs", "vp", "rho", rename variable "Qs" to "v".

15. SAW24B16\_vs.nc\
Paper        : [Megnin and Romanowicz, 2000] https://doi.org/10.1046/j.1365-246X.2000.00298.x \
Download link: http://ds.iris.edu/spud/earthmodel/10131184 (The netCDF binary for the above 2°x2° model expressed as S-velocity in km/s)\
Changes      : rename variable "vsh" to "v".

16. S362ANI\_vs.nc\
Paper        : [Kustowski et al., 2008] https://doi.org/10.1029/2007JB005169 \
Download link: http://ds.iris.edu/spud/earthmodel/10131231 (the netCDF binary for the above model expressed in km/s)\
Changes      : lose variables "vsv", "vsh", rename variable "vs" to "v".

17. S362ANI\_vsv.nc\
Paper        : [Kustowski et al., 2008] https://doi.org/10.1029/2007JB005169 \
Download link: http://ds.iris.edu/spud/earthmodel/10131231 (the netCDF binary for the above model expressed in km/s)\
Changes      : lose variables "vs", "vsh", rename variable "vsv" to "v".

18. S362ANI\_vsh.nc\
Paper        : [Kustowski et al., 2008] https://doi.org/10.1029/2007JB005169 \
Download link: http://ds.iris.edu/spud/earthmodel/10131231 (the netCDF binary for the above model expressed in km/s)\
Changes      : lose variables "vs", "vsv", rename variable "vsh" to "v".

19. S362ANI+M\_vs.nc\
Paper        : [Moulik and Ekstrom] https://doi.org/10.1093/gji/ggu356 \
Download link: http://ds.iris.edu/spud/earthmodel/10131294 (the netCDF binary for the above model expressed in km/s)\
Changes      : lose variables "vsv", "vsh", rename variable "vs" to "v".

20. S362ANI+M\_vsv.nc\
Paper        : [Moulik and Ekstrom] https://doi.org/10.1093/gji/ggu356 \
Download link: http://ds.iris.edu/spud/earthmodel/10131294 (the netCDF binary for the above model expressed in km/s)\
Changes      : lose variables "vs", "vsh", rename variable "vsv" to "v".

21. S362ANI+M\_vsh.nc\
Paper        : [Moulik and Ekstrom] https://doi.org/10.1093/gji/ggu356 \
Download link: http://ds.iris.edu/spud/earthmodel/10131294 (the netCDF binary for the above model expressed in km/s)\
Changes      : lose variables "vs", "vsv", rename variable "vsh" to "v".

22. S362WMANI\_vs.nc\
Paper        : [Kustowski et al., 2008] https://doi.org/10.1029/2007JB005169 \
Download link: http://ds.iris.edu/spud/earthmodel/10131240 (the netCDF binary for the above model expressed in km/s)\
Changes      : lose variables "vsv", "vsh", rename variable "vs" to "v".

23. S362WMANI\_vsv.nc\
Paper        : [Kustowski et al., 2008] https://doi.org/10.1029/2007JB005169 \
Download link: http://ds.iris.edu/spud/earthmodel/10131240 (the netCDF binary for the above model expressed in km/s)\
Changes      : lose variables "vs", "vsh", rename variable "vsv" to "v".

24. S362WMANI\_vsh.nc\
Paper        : [Kustowski et al., 2008] https://doi.org/10.1029/2007JB005169 \
Download link: http://ds.iris.edu/spud/earthmodel/10131240 (the netCDF binary for the above model expressed in km/s)\
Changes      : lose variables "vs", "vsv", rename variable "vsh" to "v".

25. HMSL-S06\_dvs.nc\
Paper        : [Houser et al., 2008] https://doi.org/10.1111/j.1365-246X.2008.03763.x \
Download link: http://ds.iris.edu/spud/earthmodel/10131133 (The netCDF binary of the model)\
Changes      : rename variable "dvs" to "v".

26. HMSL-S06\_vs.nc\
Paper        : [Houser et al., 2008] https://doi.org/10.1111/j.1365-246X.2008.03763.x \
Download link: http://ds.iris.edu/spud/earthmodel/10131133 (The netCDF binary of the model)\
Changes      : convert dvs into vs using ak135 reference model. However, this doesn't have much meaning. In the model's online discription "While ak135 is the 1D model used for ray tracing in the inversion, the travel time measurements for each phase have the mean removed, so the 3D model is not built with respect to any particular 1D model.", therefore use with care, in this nc file, "v" represents "vs", see https://github.com/shuleyu/seismic-tomography-models/blob/master/Processing/Create_HMSL-S06_vs.cpp

27. HMSL-P06\_dvp.nc\
Paper        : [Houser et al., 2008] https://doi.org/10.1111/j.1365-246X.2008.03763.x \
Download link: http://ds.iris.edu/spud/earthmodel/10131126 (The netCDF binary of the model)\
Changes      : rename variable "dvp" to "v".

28. HMSL-P06\_vp.nc\
Paper        : [Houser et al., 2008] https://doi.org/10.1111/j.1365-246X.2008.03763.x \
Download link: http://ds.iris.edu/spud/earthmodel/10131126 (The netCDF binary of the model)\
Changes      : convert dvp into vp using ak135 reference model. However, this doesn't have much meaning. In the model's online discription "While ak135 is the 1D model used for ray tracing in the inversion, the travel time measurements for each phase have the mean removed, so the 3D model is not built with respect to any particular 1D model.", therefore use with care, in this nc file, "v" represents "vp", see https://github.com/shuleyu/seismic-tomography-models/blob/master/Processing/Create_HMSL-P06_vp.cpp

29. LLNL-G3Dv3\_vp.nc\
Paper        : [Simmons et al., 2012] https://doi.org/10.1029/2012JB009525 \
Download link: http://ds.iris.edu/spud/earthmodel/10131310 (Complete model package contains LLNL\_G3Dv3\_README.pdf file detailing the contents. Velocity values are expressed as absolute velocity and percentage variations relative to the layer average)\
Changes      : Use the depth (column 3) in "LLNL\_G3Dv3.LayerAverages.txt", latitude ranging from -90 to 90, longitude ranging from -180 to 180, values (column 2) in "LLNL\_G3Dv3.Interpolated.Layer??\_\*km.txt" to creat the vp grid. This ignore a lot details. Use with care. in this nc file, "v" represents "vp". see https://github.com/shuleyu/seismic-tomography-models/blob/master/Processing/Create_LLNL-G3Dv3_vp.cpp

30. LLNL-G3Dv3\_dvp.nc\
Paper        : [Simmons et al., 2012] https://doi.org/10.1029/2012JB009525 \
Download link: http://ds.iris.edu/spud/earthmodel/10131310 (Complete model package contains LLNL\_G3Dv3\_README.pdf file detailing the contents. Velocity values are expressed as absolute velocity and percentage variations relative to the layer average)\
Changes      : Use the depth (column 3) in "LLNL\_G3Dv3.LayerAverages.txt", latitude ranging from -90 to 90, longitude ranging from -180 to 180, values (column 3) in "LLNL\_G3Dv3.Interpolated.Layer??\_\*km.txt" to creat the dvp grid. This ignore a lot details. Use with care. in this nc file, "v" represents "dvp". see https://github.com/shuleyu/seismic-tomography-models/blob/master/Processing/Create_LLNL-G3Dv3_dvp.cpp

31. TX2000\_dvs.nc\
Paper        : [Davies et al., 2002] https://doi.org/10.1098/rsta.2002.1077 \
Download link: http://ds.iris.edu/spud/earthmodel/10131209 (Model on a 4°x4° grid for depths from 60 to 2800 km at non-uniform intervals in netCDF format.)\
Changes      : rename variable "dvs" to "v". The desicription in the dvs reads "(% deviation from layer mean)".

32. TX2011\_dvs.nc\
Paper        : [Davies et al., 2002] https://doi.org/10.1098/rsta.2002.1077 \
Download link: http://ds.iris.edu/spud/earthmodel/10131216 (Model on a 2°x2° grid for depths from 0 to 2890 km in netCDF format)\
Changes      : rename variable "dvs" to "v".

33. TX2011\_vs.nc\
Paper        : [Davies et al., 2002] https://doi.org/10.1098/rsta.2002.1077 \
Download link: http://ds.iris.edu/spud/earthmodel/10131216 (Model on a 2°x2° grid for depths from 0 to 2890 km in netCDF format)\
Changes      : convert dvs into vs using TX2011\_ref downloaded from http://ds.iris.edu/files/products/emc/data/TX2011/TX2011_ref. in this nc file, "v" represents "vs". see https://github.com/shuleyu/seismic-tomography-models/blob/master/Processing/Create_TX2011_vs.cpp

34. SEMUCB-WM1\_dvs.nc\
Paper        : [French and Romanowicz, 2014] https://doi.org/10.1093/gji/ggu334 \
Download link: http://www.seismo.berkeley.edu/~barbara/REPRINTS/UCB_a3d_dist.SEMUCB-WM1.r20151019.tar.gz \
Changes      : Use the program provided in the tar file, a 10km depth interval (from 60km to 2890km to avoid "nan"), 1 deg x 1 deg grid is created for dvs. This dvs is "the relative Voigt-average shear velocity perturbation relative to the reference 1D model data/model.ref". in this nc file, "v" represents "dvs". see https://github.com/shuleyu/seismic-tomography-models/blob/master/Processing/Create_SEMUCB-WM1_dvs.cpp

35. SEMUCB-WM1\_vsh.nc\
Paper        : [French and Romanowicz, 2014] https://doi.org/10.1093/gji/ggu334 \
Download link: http://www.seismo.berkeley.edu/~barbara/REPRINTS/UCB_a3d_dist.SEMUCB-WM1.r20151019.tar.gz \
Changes      : Use the program provided in the tar file, a 10km depth interval (from 60km to 2890km to avoid "nan"), 1 deg x 1 deg grid is created for vsh. in this nc file, "v" represents "vsh". see https://github.com/shuleyu/seismic-tomography-models/blob/master/Processing/Create_SEMUCB-WM1_vsh.cpp

36. SEMUCB-WM1\_vsv.nc\
Paper        : [French and Romanowicz, 2014] https://doi.org/10.1093/gji/ggu334 \
Download link: http://www.seismo.berkeley.edu/~barbara/REPRINTS/UCB_a3d_dist.SEMUCB-WM1.r20151019.tar.gz \
Changes      : Use the program provided in the tar file, a 10km depth interval (from 60km to 2890km to avoid "nan"), 1 deg x 1 deg grid is created for vsv. in this nc file, "v" represents "vsv". see https://github.com/shuleyu/seismic-tomography-models/blob/master/Processing/Create_SEMUCB-WM1_vsv.cpp

37. SEMUCB-WM1\_vs.nc\
Paper        : [French and Romanowicz, 2014] https://doi.org/10.1093/gji/ggu334 \
Download link: http://www.seismo.berkeley.edu/~barbara/REPRINTS/UCB_a3d_dist.SEMUCB-WM1.r20151019.tar.gz \
Changes      : This vs is the Voigt-average shear velocity (sqrt((vsh^2+2vsv^2)/3)) in the same grid. in this nc file, "v" represents "vs". see https://github.com/shuleyu/seismic-tomography-models/blob/master/Processing/Create_SEMUCB-WM1_vs.cpp

38. S20RTS\_dvs.nc\
Paper        : [Ritsema et al., 1999] https://doi.org/10.1126/science.286.5446.1925 \
Download link: https://jritsema.earth.lsa.umich.edu/S20RTS_plotting.tar.gz \
Changes      : Because S40RTS has PREM as reference 1D model, I assume S20RTS is also using PREM as 1D reference model. Use the program provided in the tar fille, a 10km depth interval (24.4km, 25km to 2885km, 2891km), 1 deg x 1 deg grid is created for dvs. in this nc file, "v" represents "dvs". see https://github.com/shuleyu/seismic-tomography-models/blob/master/Processing/Create_S20RTS_dvs.cpp

39. S40RTS\_dvs.nc\
P9per        : [Ritsema et al., 2011] https://doi.org/10.1111/j.1365-246X.2010.04884.x \
Download link: https://jritsema.earth.lsa.umich.edu/S20RTS_plotting.tar.gz \
Changes      : In paper it reads "... S40RTS is a model of 3‐D perturbations of isotropic shear velocity with respect to the PREM model...". The reference 1D model is PREM. Use the program provided in the tar fille, a 10km depth interval (24.4km, 25km to 2885km, 2891km), 1 deg x 1 deg grid is created for dvs. in this nc file, "v" represents "dvs". see https://github.com/shuleyu/seismic-tomography-models/blob/master/Processing/Create_S40RTS_dvs.cpp

40. SP12RTS\_dvs.nc\
Paper        : [Koelemeijer et al., 2015] https://doi.org/10.1093/gji/ggv481 \
Download link: https://www.earth.ox.ac.uk/~univ4152/downloads_sp12rts.html ("SP12RTS\_plotting.tar.gz")\
Changes      : In "SP12RTS.1x1.zip" it reads "... in % from anisotropic PREM ...". The reference 1D model should be PREM. Grid depths are taken from "SP12RTS.1x1.zip", 1 deg x 1 deg. in this nc file, "v" represents "dvs". see https://github.com/shuleyu/seismic-tomography-models/blob/master/Processing/Create_SP12RTS_dvs.cpp

41. SP12RTS\_dvp.nc\
Paper        : [Koelemeijer et al., 2015] https://doi.org/10.1093/gji/ggv481 \
Download link: https://www.earth.ox.ac.uk/~univ4152/downloads_sp12rts.html ("SP12RTS\_plotting.tar.gz")\
Changes      : In "SP12RTS.1x1.zip" it reads "... in % from anisotropic PREM ...". The reference 1D model should be PREM. Grid depths are taken from "SP12RTS.1x1.zip", 1 deg x 1 deg. in this nc file, "v" represents "dvp". see https://github.com/shuleyu/seismic-tomography-models/blob/master/Processing/Create_SP12RTS_dvp.cpp

42. SEISGLOB2\_dvs.nc\
Paper        : [Durand et al., 2017] https://doi.org/10.1093/gji/ggx405 \
Download link: http://ds.iris.edu/spud/earthmodel/16588566 (The netCDF binary for the above model expressed as shear velocity (%))\
Changes      : rename "dvs" to "v". Reference model is PREM.

43. SGLOBE-rani\_dvs.nc\
Paper        : [Chang et al., 2015] https://doi.org/10.1002/2014JB011824 \
Download link: http://ds.iris.edu/spud/earthmodel/13619038 (netCDF binary files for the above model expressed as Voigt isotropy)\
Changes      : rename "dvs" to "v". Reference model is PREM.

44. SGLOBE-rani\_vsv.nc\
Paper        : [Chang et al., 2015] https://doi.org/10.1002/2014JB011824 \
Download link: http://ds.iris.edu/spud/earthmodel/13619038 (netCDF binary files for the above model expressed as Voigt isotropy)\
Changes      : convert dvs in previous nc file to vs (Voigt isotropy) using PREM. Then use the nc file downloaded from (netCDF binary files for the above model expressed as radial anisotropy in (SH/SV)^2 dimensionless scale) to calculate the vsv. in this nc file, "v" represents "vsv". see https://github.com/shuleyu/seismic-tomography-models/blob/master/Processing/Create_SGLOBE-rani_vsv_vsh.cpp

45. SGLOBE-rani\_vsh.nc\
Paper        : [Chang et al., 2015] https://doi.org/10.1002/2014JB011824 \
Download link: http://ds.iris.edu/spud/earthmodel/13619038 (netCDF binary files for the above model expressed as Voigt isotropy)\
Changes      : convert dvs in previous nc file to vs (Voigt isotropy) using PREM. Then use the nc file downloaded from (netCDF binary files for the above model expressed as radial anisotropy in (SH/SV)^2 dimensionless scale) to calculate the vsh. in this nc file, "v" represents "vsh". see https://github.com/shuleyu/seismic-tomography-models/blob/master/Processing/Create_SGLOBE-rani_vsv_vsh.cpp

46. SPani\_dvp.nc\
Paper        : [Tesoniero et al., 2015] https://doi.org/10.1002/2015JB012026 \
Download link: http://ds.iris.edu/spud/earthmodel/10162642 (the netCDF binary for the above model)\
Changes      : lose variables "dlnvs", "vp", "vs", "xi", "phi", rename variable "dlnvp" to "v". Relative to PREM.

47. SPani\_dvs.nc\
Paper        : [Tesoniero et al., 2015] https://doi.org/10.1002/2015JB012026 \
Download link: http://ds.iris.edu/spud/earthmodel/10162642 (the netCDF binary for the above model)\
Changes      : lose variables "dlnvp", "vp", "vs", "xi", "phi", rename variable "dlnvs" to "v". Relative to PREM.

48. SPani\_vp.nc\
Paper        : [Tesoniero et al., 2015] https://doi.org/10.1002/2015JB012026 \
Download link: http://ds.iris.edu/spud/earthmodel/10162642 (the netCDF binary for the above model)\
Changes      : lose variables "dlnvp", "dlnvs", "vs", "xi", "phi", rename variable "vp" to "v". vp=(vpv^2+4vph^2)/5.

49. SPani\_vs.nc\
Paper        : [Tesoniero et al., 2015] https://doi.org/10.1002/2015JB012026 \
Download link: http://ds.iris.edu/spud/earthmodel/10162642 (the netCDF binary for the above model)\
Changes      : lose variables "dlnvp", "dlnvs", "vp", "xi", "phi", rename variable "vs" to "v". vs=(vph^2+2vpv^2)/3;

50. SPani\_xi.nc\
Paper        : [Tesoniero et al., 2015] https://doi.org/10.1002/2015JB012026 \
Download link: http://ds.iris.edu/spud/earthmodel/10162642 (the netCDF binary for the above model)\
Changes      : lose variables "dlnvp", "dlnvs", "vp", "vs", "phi", rename variable "xi" to "v". In paper it reads xi = (vsh^2/vsv^2). In this nc file, the comment reads xi=(vsv^2/vsh^2), which could be a typo.

51. SPani\_phi.nc\
Paper        : [Tesoniero et al., 2015] https://doi.org/10.1002/2015JB012026 \
Download link: http://ds.iris.edu/spud/earthmodel/10162642 (the netCDF binary for the above model)\
Changes      : lose variables "dlnvp", "dlnvs", "vp", "vs", "xi", rename variable "phi" to "v". In paper it reads phi = (vpv^2/vph^2).

52. GAP\_P4\_dvp.nc\
Paper        : [Obayashi et al., 2013] https://doi.org/10.1002/2013GL057401 [Fukao and Obayashi, 2013] https://doi.org/10.1002/2013JB010466 \
Download link: http://www.godac.jamstec.go.jp/catalog/data_catalog/metadataDisp/GAP_P4?lang=en \
Changes      : created GAP_P4.01 ~ GAP_P4.29, then doubled the depth layer. For example: 29 and 50.999 km get values from GAP_P4.01
