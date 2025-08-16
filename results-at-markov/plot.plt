set datafile separator ','
set title 'Eviction strats'
set xlabel 'max\_procs' textcolor 'white'
set ylabel 'avg\_secs' textcolor 'white'
set grid
set term x11 background rgb '#181818'
set border lc rgb 'white'
set grid lc rgb 'white'
set key textcolor rgb 'white'

plot \
     'result-looper1-20-wait-for-all-bad.csv' using 1:2 with lines lw 4 title 'wait-for-all-bad', \
     'result-looper1-20-wait-for-last.csv' using 1:2 with lines lw 4 title 'wait-for-last', \
     'result-looper1-20-wait-for-rand.csv' using 1:2 with lines lw 4 title 'wait-for-rand', \
     'result-looper1-20-wait-for-all.csv' using 1:2 with lines lw 4 title 'wait-for-all', \
     'result-looper1-20-wait-for-any.csv' using 1:2 with lines lw 4 title 'wait-for-any', \

#plot \
#     'result-sleeper1-20-wait-for-all-bad.csv' using 1:2 with lines lw 4 title 'wait-for-all-bad', \
#     'result-sleeper1-20-wait-for-last.csv' using 1:2 with lines lw 4 title 'wait-for-last', \
#     'result-sleeper1-20-wait-for-rand.csv' using 1:2 with lines lw 4 title 'wait-for-rand', \
#     'result-sleeper1-20-wait-for-all.csv' using 1:2 with lines lw 4 title 'wait-for-all', \
#     'result-sleeper1-20-wait-for-any.csv' using 1:2 with lines lw 4 title 'wait-for-any', \

pause -1
