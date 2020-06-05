set term png 
set title "Cieplo"
set xlabel "x"
set ylabel "y"
set xrange [0:100]
set yrange [0:100]

set output "cieplo.png"
plot 'dane.txt' matrix with image
