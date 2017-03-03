reset
set ylabel 'error rate'
set style fill solid
set title 'error rate comparison'
set term png enhanced font 'Verdana,10'
set output 'error_rate.png'

plot [:][:0.001] 'result_clock_gettime.csv' using 3:xtic(1) with line lw 2 title 'baseline', \
'' using 5:xtic(1) with line lw 2 title 'openmp(2threads)', \
'' using 7:xtic(1) with line lw 2 title 'openmp(4threads)', \
'' using 9:xtic(1) with line lw 2 title 'avx', \
'' using 11:xtic(1) with line lw 2 title 'avx unroll', \
'' using 13:xtic(1) with line lw 2 title 'leibniz'
