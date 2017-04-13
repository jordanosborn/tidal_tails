set terminal pngcairo size 900,900 enhanced font 'Verdana,10'
set output 'Radius.png'
set title "Radius of Circular orbit with time, Time Period T = 2 pi sqrt(r^3/(GM))"
set xlabel "Time (s)"
set ylabel "Radius (arbitrary units)"
set grid
set datafile separator ","
plot 'radius_data.txt' using 1:2 smooth bezier