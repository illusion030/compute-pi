reset
set ylabel 'time(sec)'
set style fill solid
set title 'perfomance comparison'
set term png enhanced font 'Verdana,10'
set output 'runtime.png'

plot [:][:3] 'result_clock_gettime.csv' using 2:xtic(1) with line lw 2 title 'baseline', \
'' using 4:xtic(1) with line lw 2 title 'openmp(2threads)', \
'' using 6:xtic(1) with line lw 2 title 'openmp(4threads)', \
'' using 8:xtic(1) with line lw 2 title 'avx', \
'' using 10:xtic(1) with line lw 2 title 'avx unroll'
