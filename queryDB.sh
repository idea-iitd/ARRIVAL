
clang++ -std=c++11 -O3 experiments/runExperiment.cpp
./a.out ../$1/edges.txt ../$1/labels.txt ../$1/attributes.txt ../$1/querydb1.txt ../$1/querydb1.log 1 4 > ../$1/querydb1.csv
./a.out ../$1/edges.txt ../$1/labels.txt ../$1/attributes.txt ../$1/querydb2.txt ../$1/querydb2.log 1 4 > ../$1/querydb2.csv
./a.out ../$1/edges.txt ../$1/labels.txt ../$1/attributes.txt ../$1/querydb3.txt ../$1/querydb3.log 1 4 > ../$1/querydb3.csv
./a.out ../$1/edges.txt ../$1/labels.txt ../$1/attributes.txt ../$1/querydb4.txt ../$1/querydb4.log 1 4 > ../$1/querydb4.csv
./a.out ../$1/edges.txt ../$1/labels.txt ../$1/attributes.txt ../$1/querydb5.txt ../$1/querydb5.log 1 4 > ../$1/querydb5.csv

cd ../BBFS
clang++ -std=c++11 -O3 bbfs.cpp
./a.out $1qdb1 ../$1/edges.txt ../$1/labels.txt 1 ../$1/oldquerydb1.txt > ../$1/querydb1BBFS.csv&
./a.out $1qdb2 ../$1/edges.txt ../$1/labels.txt 1 ../$1/oldquerydb2.txt > ../$1/querydb2BBFS.csv&
./a.out $1qdb3 ../$1/edges.txt ../$1/labels.txt 1 ../$1/oldquerydb3.txt > ../$1/querydb3BBFS.csv&
./a.out $1qdb4 ../$1/edges.txt ../$1/labels.txt 1 ../$1/oldquerydb4.txt > ../$1/querydb4BBFS.csv&
./a.out $1qdb5 ../$1/edges.txt ../$1/labels.txt 1 ../$1/oldquerydb5.txt > ../$1/querydb5BBFS.csv

cd ../ARRIVAL
