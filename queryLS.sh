clang++ -std=c++11 -O3 experiments/runExperiment.cpp
./a.out ../$1/edges.txt ../$1/labels.txt ../$1/attributes.txt ../$1/queryls2.txt ../$1/queryls2.log 1 4 > ../$1/queryls2.csv
./a.out ../$1/edges.txt ../$1/labels.txt ../$1/attributes.txt ../$1/queryls4.txt ../$1/queryls4.log 1 4 > ../$1/queryls4.csv
./a.out ../$1/edges.txt ../$1/labels.txt ../$1/attributes.txt ../$1/queryls6.txt ../$1/queryls6.log 1 4 > ../$1/queryls6.csv
./a.out ../$1/edges.txt ../$1/labels.txt ../$1/attributes.txt ../$1/queryls8.txt ../$1/queryls8.log 1 4 > ../$1/queryls8.csv

cd ../BBFS
clang++ -std=c++11 -O3 bbfs.cpp
./a.out $1qls2 ../$1/edges.txt ../$1/labels.txt 1 ../$1/oldqueryls2.txt > ../$1/queryls2BBFS.csv&
./a.out $1qls4 ../$1/edges.txt ../$1/labels.txt 1 ../$1/oldqueryls4.txt > ../$1/queryls4BBFS.csv&
./a.out $1qls6 ../$1/edges.txt ../$1/labels.txt 1 ../$1/oldqueryls6.txt > ../$1/queryls6BBFS.csv&
./a.out $1qls8 ../$1/edges.txt ../$1/labels.txt 1 ../$1/oldqueryls8.txt > ../$1/queryls8BBFS.csv

cd ../ARRIVAL

