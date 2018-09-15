#!/bin/bash

# prompt> export TOMO_S20RTS=`pwd`
# prompt> export PATH=${PATH}:.
# SP12RTS, dvp (EP), the first argument to mkmap is 3. 
# This will create SP12RTS_dvp.txt. Noitice it's not sorted.

rm -f SP12RTS_dvp.txt *xyz *ps
while read depth
do
    ./mkmap 3 1 ${depth}
    Line=`tail -n 2 map.${depth}km.xyz`
    NorthVal=`echo ${Line} | awk '{print $3}'`
    SouthVal=`echo ${Line} | awk '{print $6}'`

    for lon in `seq -180 179`
    do
        printf "%.2lf %.2lf %.2lf %.5e\n" ${depth} ${lon} -90 ${SouthVal} >> SP12RTS_dvp.txt
        printf "%.2lf %.2lf %.2lf %.5e\n" ${depth} ${lon} 90 ${NorthVal} >> SP12RTS_dvp.txt
    done
    awk -v d=${depth} 'NR<=64440 {printf "%.2lf %.2lf %.2lf %.5e\n",d,$1,$2,$3}' map.${depth}km.xyz >> SP12RTS_dvp.txt

done << EOF
25
50
70
75
100
120
125
150
170
175
200
220
225
250
270
275
300
320
325
350
370
375
400
420
425
450
470
475
500
520
525
550
575
580
600
620
625
650
670
675
700
720
725
750
775
780
800
825
850
875
900
925
950
975
1000
1025
1050
1075
1100
1125
1150
1175
1200
1225
1250
1275
1300
1325
1350
1375
1400
1425
1450
1475
1500
1525
1550
1575
1600
1625
1650
1675
1700
1725
1750
1775
1800
1825
1850
1875
1900
1925
1950
1975
2000
2025
2050
2075
2100
2125
2150
2175
2200
2225
2250
2275
2300
2325
2350
2375
2400
2425
2450
2475
2500
2525
2550
2575
2600
2625
2650
2675
2700
2725
2750
2775
2800
2825
2850
2875
2891
EOF

rm -f *xyz *ps

exit 0
