./a.out ../dblp/edges.txt ../dblp/labels.txt ../dblp/attributes.txt ../dblp/querymix.txt ../dblp/querynw25.log 0 4 1 0.25> ../dblp/querynw25.csv
./a.out ../dblp/edges.txt ../dblp/labels.txt ../dblp/attributes.txt ../dblp/querymix.txt ../dblp/querynw50.log 0 4 1 0.5 > ../dblp/querynw50.csv
./a.out ../dblp/edges.txt ../dblp/labels.txt ../dblp/attributes.txt ../dblp/querymix.txt ../dblp/querynw75.log 0 4 1 0.75> ../dblp/querynw75.csv
./a.out ../dblp/edges.txt ../dblp/labels.txt ../dblp/attributes.txt ../dblp/querymix.txt ../dblp/querynw100.log 0 4 1 1> ../dblp/querynw100.csv
./a.out ../dblp/edges.txt ../dblp/labels.txt ../dblp/attributes.txt ../dblp/querymix.txt ../dblp/querynw125.log 0 4 1 1.25> ../dblp/querynw125.csv
./a.out ../dblp/edges.txt ../dblp/labels.txt ../dblp/attributes.txt ../dblp/querymix.txt ../dblp/querynw150.log 0 4 1 1.5> ../dblp/querynw150.csv
./a.out ../dblp/edges.txt ../dblp/labels.txt ../dblp/attributes.txt ../dblp/querymix.txt ../dblp/querynw175.log 0 4 1 1.75> ../dblp/querynw175.csv

./a.out ../dblp/edges.txt ../dblp/labels.txt ../dblp/attributes.txt ../dblp/querymix.txt ../dblp/querywl25.log 0 4 0.25 1> ../dblp/querywl25.csv
./a.out ../dblp/edges.txt ../dblp/labels.txt ../dblp/attributes.txt ../dblp/querymix.txt ../dblp/querywl50.log 0 4 0.5 1> ../dblp/querywl50.csv
./a.out ../dblp/edges.txt ../dblp/labels.txt ../dblp/attributes.txt ../dblp/querymix.txt ../dblp/querywl75.log 0 4 0.75 1> ../dblp/querywl75.csv
./a.out ../dblp/edges.txt ../dblp/labels.txt ../dblp/attributes.txt ../dblp/querymix.txt ../dblp/querywl100.log 0 4 1 1> ../dblp/querywl100.csv
./a.out ../dblp/edges.txt ../dblp/labels.txt ../dblp/attributes.txt ../dblp/querymix.txt ../dblp/querywl125.log 0 4 1.25 1> ../dblp/querywl125.csv
./a.out ../dblp/edges.txt ../dblp/labels.txt ../dblp/attributes.txt ../dblp/querymix.txt ../dblp/querywl150.log 0 4 1.5 1> ../dblp/querywl150.csv
./a.out ../dblp/edges.txt ../dblp/labels.txt ../dblp/attributes.txt ../dblp/querymix.txt ../dblp/querywl175.log 0 4 1.75 1> ../dblp/querywl175.csv

cd ../BBFS
./a.out dblpqwl25 ../dblp/edges.txt ../dblp/labels.txt 0 ../dblp/oldquerymix.txt > ../dblp/querymixBBFS.csv&

./a.out ../freebase/edges.txt ../freebase/labels.txt ../freebase/attributes.txt ../freebase/querymix.txt ../freebase/querynw25.log 1 4 1 0.25> ../freebase/querynw25.csv
./a.out ../freebase/edges.txt ../freebase/labels.txt ../freebase/attributes.txt ../freebase/querymix.txt ../freebase/querynw50.log 1 4 1 0.5> ../freebase/querynw50.csv
./a.out ../freebase/edges.txt ../freebase/labels.txt ../freebase/attributes.txt ../freebase/querymix.txt ../freebase/querynw75.log 1 4 1 0.75> ../freebase/querynw75.csv
./a.out ../freebase/edges.txt ../freebase/labels.txt ../freebase/attributes.txt ../freebase/querymix.txt ../freebase/querynw100.log 1 4 1 1> ../freebase/querynw100.csv
./a.out ../freebase/edges.txt ../freebase/labels.txt ../freebase/attributes.txt ../freebase/querymix.txt ../freebase/querynw125.log 1 4 1 1.25> ../freebase/querynw125.csv
./a.out ../freebase/edges.txt ../freebase/labels.txt ../freebase/attributes.txt ../freebase/querymix.txt ../freebase/querynw150.log 1 4 1 1.5> ../freebase/querynw150.csv
./a.out ../freebase/edges.txt ../freebase/labels.txt ../freebase/attributes.txt ../freebase/querymix.txt ../freebase/querynw175.log 1 4 1 1.75> ../freebase/querynw175.csv

./a.out ../freebase/edges.txt ../freebase/labels.txt ../freebase/attributes.txt ../freebase/querymix.txt ../freebase/querywl25.log 1 4 0.25 1> ../freebase/querywl25.csv
./a.out ../freebase/edges.txt ../freebase/labels.txt ../freebase/attributes.txt ../freebase/querymix.txt ../freebase/querywl50.log 1 4 0.5 1> ../freebase/querywl50.csv
./a.out ../freebase/edges.txt ../freebase/labels.txt ../freebase/attributes.txt ../freebase/querymix.txt ../freebase/querywl75.log 1 4 0.75 1> ../freebase/querywl75.csv
./a.out ../freebase/edges.txt ../freebase/labels.txt ../freebase/attributes.txt ../freebase/querymix.txt ../freebase/querywl100.log 1 4 1 1> ../freebase/querywl100.csv
./a.out ../freebase/edges.txt ../freebase/labels.txt ../freebase/attributes.txt ../freebase/querymix.txt ../freebase/querywl125.log 1 4 1.25 1> ../freebase/querywl125.csv
./a.out ../freebase/edges.txt ../freebase/labels.txt ../freebase/attributes.txt ../freebase/querymix.txt ../freebase/querywl150.log 1 4 1.5 1> ../freebase/querywl150.csv
./a.out ../freebase/edges.txt ../freebase/labels.txt ../freebase/attributes.txt ../freebase/querymix.txt ../freebase/querywl175.log 1 4 1.75 1> ../freebase/querywl175.csv

