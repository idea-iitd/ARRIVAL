clang++ -std=c++11 -O3 experiments/runExperiment.cpp
./a.out ../$1/edges.txt ../$1/labels.txt ../$1/attributes.txt ../$1/querymix.txt ../$1/querymix.log 1 4 > ../$1/querymix.csv
./a.out ../$1/edges.txt ../$1/labels.txt ../$1/attributes.txt ../$1/query2.txt ../$1/query2.log 1 4 > ../$1/query2.csv
./a.out ../$1/edges.txt ../$1/labels.txt ../$1/attributes.txt ../$1/query3.txt ../$1/query3.log 1 4 > ../$1/query3.csv
./a.out ../$1/edges.txt ../$1/labels.txt ../$1/attributes.txt ../$1/query4.txt ../$1/query4.log 1 4 > ../$1/query4.csv

cd ../BBFS

clang++ -std=c++11 -O3 bbfs.cpp
./a.out $1qmix ../$1/edges.txt ../$1/labels.txt 1 ../$1/oldquerymix.txt > ../$1/querymixBBFS.csv&
./a.out $1q2 ../$1/edges.txt ../$1/labels.txt 1 ../$1/oldquery2.txt > ../$1/query2BBFS.csv&
./a.out $1q3 ../$1/edges.txt ../$1/labels.txt 1 ../$1/oldquery3.txt > ../$1/query3BBFS.csv&
./a.out $1q4 ../$1/edges.txt ../$1/labels.txt 1 ../$1/oldquery4.txt > ../$1/query4BBFS.csv

cd ../ARRIVAL
