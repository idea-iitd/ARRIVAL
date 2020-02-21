./a.out ../$1/edges.txt ../$1/labels.txt ../$1/attributes.txt ../$1/querymix.txt ../$1/querynw25.log 0 4 1 0.25 > ../$1/querynw25.csv
./a.out ../$1/edges.txt ../$1/labels.txt ../$1/attributes.txt ../$1/querymix.txt ../$1/querynw50.log 0 4 1 0.5 > ../$1/querynw50.csv
./a.out ../$1/edges.txt ../$1/labels.txt ../$1/attributes.txt ../$1/querymix.txt ../$1/querynw75.log 0 4 1 0.75 > ../$1/querynw75.csv
./a.out ../$1/edges.txt ../$1/labels.txt ../$1/attributes.txt ../$1/querymix.txt ../$1/querynw100.log 0 4 1 1 > ../$1/querynw100.csv
./a.out ../$1/edges.txt ../$1/labels.txt ../$1/attributes.txt ../$1/querymix.txt ../$1/querynw125.log 0 4 1 1.25 > ../$1/querynw125.csv
./a.out ../$1/edges.txt ../$1/labels.txt ../$1/attributes.txt ../$1/querymix.txt ../$1/querynw150.log 0 4 1 1.5 > ../$1/querynw150.csv
./a.out ../$1/edges.txt ../$1/labels.txt ../$1/attributes.txt ../$1/querymix.txt ../$1/querynw175.log 0 4 1 1.75 > ../$1/querynw175.csv

./a.out ../$1/edges.txt ../$1/labels.txt ../$1/attributes.txt ../$1/querymix.txt ../$1/querywl25.log 0 4 0.25 1 > ../$1/querywl25.csv
./a.out ../$1/edges.txt ../$1/labels.txt ../$1/attributes.txt ../$1/querymix.txt ../$1/querywl50.log 0 4 0.5 1 > ../$1/querywl50.csv
./a.out ../$1/edges.txt ../$1/labels.txt ../$1/attributes.txt ../$1/querymix.txt ../$1/querywl75.log 0 4 0.75 1 > ../$1/querywl75.csv
./a.out ../$1/edges.txt ../$1/labels.txt ../$1/attributes.txt ../$1/querymix.txt ../$1/querywl100.log 0 4 1 1 > ../$1/querywl100.csv
./a.out ../$1/edges.txt ../$1/labels.txt ../$1/attributes.txt ../$1/querymix.txt ../$1/querywl125.log 0 4 1.25 1 > ../$1/querywl125.csv
./a.out ../$1/edges.txt ../$1/labels.txt ../$1/attributes.txt ../$1/querymix.txt ../$1/querywl150.log 0 4 1.5 1 > ../$1/querywl150.csv
./a.out ../$1/edges.txt ../$1/labels.txt ../$1/attributes.txt ../$1/querymix.txt ../$1/querywl175.log 0 4 1.75 1 > ../$1/querywl175.csv

cd ../BBFS
./a.out $1qmix ../$1/edges.txt ../$1/labels.txt 1 ../$1/oldquerymix.txt > ../$1/querymixBBFS.csv

cd ../ARRIVAL