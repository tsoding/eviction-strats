set datafile separator ','
set title 'Eviction strats'
set xlabel 'max\_procs' textcolor 'white'
set ylabel 'avg\_secs' textcolor 'white'
set grid
set term x11 background rgb '#181818'
set border lc rgb 'white'
set grid lc rgb 'white'
set key textcolor rgb 'white'

     #'result-looper1-20-wait-for-all-bad.csv' using 1:2 with lines lw 4 title 'wait-for-all-bad', \
     #'result-looper1-20-wait-for-last.csv' using 1:2 with lines lw 4 title 'wait-for-last', \
     #'result-looper1-20-wait-for-rand.csv' using 1:2 with lines lw 4 title 'wait-for-rand', \
     #'result-looper1-20-wait-for-all.csv' using 1:2 with lines lw 4 title 'wait-for-all', \

     #'result-looper1-20-wait-for-any.csv' using 1:2 with lines lw 4 title 'wait-for-any', \

plot \
     'result-looper1-20-wait-for-any-child-nofan.csv' using 1:2 with lines lw 4 title 'wait-for-any-child-nofan', \
     'result-looper1-20-wait-for-any-child-fan.csv' using 1:2 with lines lw 4 title 'wait-for-any-child-fan', \
     'result-looper1-20-wait-for-any-group-nofan.csv' using 1:2 with lines lw 4 title 'wait-for-any-group-nofan', \
     'result-looper1-20-wait-for-any-group-fan.csv' using 1:2 with lines lw 4 title 'wait-for-any-group-fan', \
     'result-looper1-20-wait-for-any-busy-fan.csv' using 1:2 with lines lw 4 title 'wait-for-any-busy-fan', \
     'result-looper1-20-wait-for-any-busy-sleep-fan.csv' using 1:2 with lines lw 4 title 'wait-for-any-busy-sleep-fan', \
     'result-looper1-20-wait-for-any-busy-yield-fan.csv' using 1:2 with lines lw 4 title 'wait-for-any-busy-yield-fan', \

#plot \
#     'result-sleeper1-20-wait-for-all-bad.csv' using 1:2 with lines lw 4 title 'wait-for-all-bad', \
#     'result-sleeper1-20-wait-for-last.csv' using 1:2 with lines lw 4 title 'wait-for-last', \
#     'result-sleeper1-20-wait-for-rand.csv' using 1:2 with lines lw 4 title 'wait-for-rand', \
#     'result-sleeper1-20-wait-for-all.csv' using 1:2 with lines lw 4 title 'wait-for-all', \
#     'result-sleeper1-20-wait-for-any.csv' using 1:2 with lines lw 4 title 'wait-for-any', \
#     'result-sleeper1-20-wait-for-any-group.csv' using 1:2 with lines lw 4 title 'wait-for-any-group', \

pause -1
