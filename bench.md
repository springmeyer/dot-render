## basics

$ du -h us-west.csv 
1.2G    us-west.csv

$ time wc -l us-west.csv  
40690230 us-west.csv

real    0m1.647s
user    0m1.441s
sys     0m0.206s

time cat us-west.csv > copy.csv

real    0m40.410s
user    0m0.012s
sys     0m26.004s

# render with 8 core 15in mbpro - OS X 10.7 / clang version 3.3 (trunk 176187)
time cat us-west.csv | ./stdin-render; open test.png                             

real    0m30.312s
user    0m29.763s
sys     0m1.070s
