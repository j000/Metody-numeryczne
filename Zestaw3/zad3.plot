set term pngcairo background "#171111" size 1920,1080 font 'Input Mono'

########################################
# Ethan A Merritt - my preference for gnuplot colors
# 2 3 4 5 6 8 are borrowed from the colors_podo set
#
set linetype  1 lc rgb "dark-violet" lw 2
set linetype  2 lc rgb "#009e73" lw 2
set linetype  3 lc rgb "#e69f00" lw 2
set linetype  4 lc rgb "#56b4e9" lw 2
set linetype  5 lc rgb "#f0e442" lw 2
set linetype  6 lc rgb "#0072b2" lw 2
set linetype  7 lc rgb "#e51e10" lw 2
set linetype  8 lc rgb "white"   lw 2
set linetype  9 lc rgb "gray50"  lw 2
set linetype cycle  9
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

max(x,y) = (x > y) ? x : y

# stats
stats filename name 'ALL' nooutput
array maxs[ALL_columns + 1]

do for [i=2:ALL_columns] {
	stats filename using i nooutput
	maxs[i] = STATS_max
}

# drugi wykres:
max = 1e-2 # 1.05 * max(maxs[3], maxs[4])
# ile zajmuje drugi wykres
split = 0.3

if (exists("my_title")) set title my_title textcolor linestyle 11

set lmargin 8

set multiplot
set origin 0,split
set size 1,(1-split)
set logscale x 2
set format x "1+2^{%L}"
set xtics 4
set xtics 1./(2**14),4

plot for [i=2:ALL_columns] filename using 1:i title sprintf("%s (max: %7.4f)",columnhead(i),maxs[i]) lc i-1

unset title
set origin 0,0
set size 1,split
set yrange [0:max]
set ytics add ("" maxs[4] 1)
set ytics add ("" maxs[5] 1)
set format x ""
set key off

plot for [i=4:ALL_columns] filename using 1:i lc i-1

unset multiplot
