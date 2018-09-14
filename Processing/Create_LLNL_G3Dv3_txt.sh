#!/bin/bash

rm -f tmpfile_$$
for lat in `seq -90 90`
do
    for lon in `seq -180 180`
    do
        echo ${lat} ${lon} >> tmpfile_$$
    done
done

rm -f LLNL-G3Dv3_vp.txt LLNL-G3Dv3_dvp.txt
Cnt=2
while read file
do
    Depth=`awk -v C=${Cnt} '{if (NR==C) print $3}' LLNL_G3Dv3.LayerAverages.txt`
    awk -v D=${Depth} '{print D,$2}' ${file} > tmpfile2_$$
    paste tmpfile_$$ tmpfile2_$$ | awk '{print $3,$1,$2,$4}' >> LLNL-G3Dv3_vp.txt
    awk -v D=${Depth} '{print D,$3}' ${file} > tmpfile3_$$
    paste tmpfile_$$ tmpfile3_$$ | awk '{print $3,$1,$2,$4}' >> LLNL-G3Dv3_dvp.txt

    Cnt=$((Cnt+1))
done << EOF
LLNL_G3Dv3.Interpolated.Layer01_Water_top.txt
LLNL_G3Dv3.Interpolated.Layer02_Water_bottom.txt
LLNL_G3Dv3.Interpolated.Layer03_Sediment_1_top.txt
LLNL_G3Dv3.Interpolated.Layer04_Sediment_1_bottom.txt
LLNL_G3Dv3.Interpolated.Layer05_Sediment_2_top.txt
LLNL_G3Dv3.Interpolated.Layer06_Sediment_2_bottom.txt
LLNL_G3Dv3.Interpolated.Layer07_Sediment_3_top.txt
LLNL_G3Dv3.Interpolated.Layer08_Sediment_3_bottom.txt
LLNL_G3Dv3.Interpolated.Layer09_Upper_Crust_top.txt
LLNL_G3Dv3.Interpolated.Layer10_Upper_Crust_bottom.txt
LLNL_G3Dv3.Interpolated.Layer11_Middle_Crust_top.txt
LLNL_G3Dv3.Interpolated.Layer12_Middle_Crust_bottom.txt
LLNL_G3Dv3.Interpolated.Layer13_Lower_Crust_top.txt
LLNL_G3Dv3.Interpolated.Layer14_Lower_Crust_bottom.txt
LLNL_G3Dv3.Interpolated.Layer15_Top_of_mantle_Moho.txt
LLNL_G3Dv3.Interpolated.Layer16_Upper_Mantle_a80km.txt
LLNL_G3Dv3.Interpolated.Layer17_Upper_Mantle_115km.txt
LLNL_G3Dv3.Interpolated.Layer18_Upper_Mantle_150km.txt
LLNL_G3Dv3.Interpolated.Layer19_Upper_Mantle_185km.txt
LLNL_G3Dv3.Interpolated.Layer20_Upper_Mantle_220km.txt
LLNL_G3Dv3.Interpolated.Layer21_Upper_Mantle_265km.txt
LLNL_G3Dv3.Interpolated.Layer22_Upper_Mantle_310km.txt
LLNL_G3Dv3.Interpolated.Layer23_Upper_Mantle_355km.txt
LLNL_G3Dv3.Interpolated.Layer24_Transition_Zone_a410_topside.txt
LLNL_G3Dv3.Interpolated.Layer25_Transition_Zone_a410_underside.txt
LLNL_G3Dv3.Interpolated.Layer26_Transition_Zone_a450km.txt
LLNL_G3Dv3.Interpolated.Layer27_Transition_Zone_a500km.txt
LLNL_G3Dv3.Interpolated.Layer28_Transition_Zone_a550km.txt
LLNL_G3Dv3.Interpolated.Layer29_Transition_Zone_a600km.txt
LLNL_G3Dv3.Interpolated.Layer30_Transition_Zone_a635km.txt
LLNL_G3Dv3.Interpolated.Layer31_Transition_Zone_a660km_topside.txt
LLNL_G3Dv3.Interpolated.Layer32_Transition_Zone_a660km_underside.txt
LLNL_G3Dv3.Interpolated.Layer33_Lower_Mantle_721km.txt
LLNL_G3Dv3.Interpolated.Layer34_Lower_Mantle_771km.txt
LLNL_G3Dv3.Interpolated.Layer35_Lower_Mantle_871km.txt
LLNL_G3Dv3.Interpolated.Layer36_Lower_Mantle_971km.txt
LLNL_G3Dv3.Interpolated.Layer37_Lower_Mantle_1071km.txt
LLNL_G3Dv3.Interpolated.Layer38_Lower_Mantle_1171km.txt
LLNL_G3Dv3.Interpolated.Layer39_Lower_Mantle_1271km.txt
LLNL_G3Dv3.Interpolated.Layer40_Lower_Mantle_1371km.txt
LLNL_G3Dv3.Interpolated.Layer41_Lower_Mantle_1471km.txt
LLNL_G3Dv3.Interpolated.Layer42_Lower_Mantle_1571km.txt
LLNL_G3Dv3.Interpolated.Layer43_Lower_Mantle_1671km.txt
LLNL_G3Dv3.Interpolated.Layer44_Lower_Mantle_1771km.txt
LLNL_G3Dv3.Interpolated.Layer45_Lower_Mantle_1871km.txt
LLNL_G3Dv3.Interpolated.Layer46_Lower_Mantle_1971km.txt
LLNL_G3Dv3.Interpolated.Layer47_Lower_Mantle_2071km.txt
LLNL_G3Dv3.Interpolated.Layer48_Lower_Mantle_2171km.txt
LLNL_G3Dv3.Interpolated.Layer49_Lower_Mantle_2271km.txt
LLNL_G3Dv3.Interpolated.Layer50_Lower_Mantle_2371km.txt
LLNL_G3Dv3.Interpolated.Layer51_Lower_Mantle_2471km.txt
LLNL_G3Dv3.Interpolated.Layer52_Lower_Mantle_2571km.txt
LLNL_G3Dv3.Interpolated.Layer53_Lower_Mantle_2671km.txt
LLNL_G3Dv3.Interpolated.Layer54_Lower_Mantle_2741km.txt
LLNL_G3Dv3.Interpolated.Layer55_Lower_Mantle_2771km.txt
LLNL_G3Dv3.Interpolated.Layer56_Lower_Mantle_2871km.txt
LLNL_G3Dv3.Interpolated.Layer57_Lower_Mantle_2891km.txt
EOF

rm tmpfile*$$

exit 0
