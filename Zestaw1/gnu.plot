set term pngcairo background "#171111" size 1920,1080 font 'Input Mono'

########################################
# line styles for ColorBrewer Set3
# author: Anna Schneider
set linetype 1 lc rgb '#8DD3C7' pt 0 # teal
set linetype 2 lc rgb '#FFFFB3' pt 5 # banana
set linetype 3 lc rgb '#BEBADA' pt 7 # lilac
set linetype 4 lc rgb '#FB8072' pt 9 # red
set linetype 5 lc rgb '#80B1D3' pt 11 # steel blue
set linetype 6 lc rgb '#FDB462' pt 13 # adobe orange
set linetype 7 lc rgb '#B3DE69' pt 15 # lime green
set linetype 8 lc rgb '#FCCDE5' pt 3 # mauve
set linetype cycle 8
########################################

set style line 11 lw 1 lt 1 lc rgbcolor "#AA9999"
set style line 12 lw 1 lt 1 lc rgbcolor "#443333"
set style line 13 lw 2 lt 0 lc rgbcolor "#443333"

set key top left textcolor linestyle 11
set grid xtics mxtics ls 12, ls 13
set grid ytics mytics ls 12, ls 13

set border linewidth 0 ls 12
set ytics textcolor linestyle 11
set xtics textcolor linestyle 11 rotate
set xlabel tc ls 11 offset 0,-3
unset xzeroaxis

set style data lines
set datafile separator ","
set key autotitle columnhead

set xtics pi/4
set format x '%.2Pπ'
set xtics('0' 0, 'π/6' pi/6, 'π/4' pi/4, 'π/3' pi/3, 'π/2' pi/2)

max(x,y) = (x > y) ? x : y

# stats
stats filename name 'ALL' nooutput
array maxs[ALL_columns + 1]

do for [i=2:ALL_columns] {
	stats filename using i nooutput
	maxs[i] = STATS_max
}

# drugi wykres: max y = błąd względny
max = 1.05 * max(maxs[4], maxs[5])
# ile zajmuje drugi wykres
split = 0.3

set lmargin 8
set multiplot
set origin 0,split
set size 1,(1-split)
set yrange [0:1]

plot for [i=2:ALL_columns] filename using 1:i title sprintf("%s (max: %7.4f)",columnhead(i),maxs[i])

set origin 0,0
set size 1,split
set yrange [0:max]
set ytics add ("" maxs[4] 1)
set ytics add ("" maxs[5] 1)
set xtics scale 0
set key off

plot for [i=4:ALL_columns] filename using 1:i

unset multiplot
