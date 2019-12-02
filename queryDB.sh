
./a.out ../gplus/edges.txt ../gplus/labels.txt ../gplus/attributes.txt ../gplus/querydb1.txt ../gplus/querydb1.log 1 4 > ../gplus/querydb1.csv
./a.out ../gplus/edges.txt ../gplus/labels.txt ../gplus/attributes.txt ../gplus/querydb2.txt ../gplus/querydb2.log 1 4 > ../gplus/querydb2.csv
./a.out ../gplus/edges.txt ../gplus/labels.txt ../gplus/attributes.txt ../gplus/querydb3.txt ../gplus/querydb3.log 1 4 > ../gplus/querydb3.csv
./a.out ../gplus/edges.txt ../gplus/labels.txt ../gplus/attributes.txt ../gplus/querydb4.txt ../gplus/querydb4.log 1 4 > ../gplus/querydb4.csv
./a.out ../gplus/edges.txt ../gplus/labels.txt ../gplus/attributes.txt ../gplus/querydb5.txt ../gplus/querydb5.log 1 4 > ../gplus/querydb5.csv

cd ../BBFS
clang++ -O3 bbfs.cpp
./a.out gplusqdb1 ../gplus/edges.txt ../gplus/labels.txt 1 ../gplus/oldquerydb1.txt > ../gplus/querydb1BBFS.csv&
./a.out gplusqdb2 ../gplus/edges.txt ../gplus/labels.txt 1 ../gplus/oldquerydb2.txt > ../gplus/querydb2BBFS.csv&
./a.out gplusqdb3 ../gplus/edges.txt ../gplus/labels.txt 1 ../gplus/oldquerydb3.txt > ../gplus/querydb3BBFS.csv&
./a.out gplusqdb4 ../gplus/edges.txt ../gplus/labels.txt 1 ../gplus/oldquerydb4.txt > ../gplus/querydb4BBFS.csv&
./a.out gplusqdb5 ../gplus/edges.txt ../gplus/labels.txt 1 ../gplus/oldquerydb5.txt > ../gplus/querydb5BBFS.csv

cd ../ARRIVAL
./a.out ../dblp/edges.txt ../dblp/labels.txt ../dblp/attributes.txt ../dblp/querydb1.txt ../dblp/querydb1.log 0 4 > ../dblp/querydb1.csv
./a.out ../dblp/edges.txt ../dblp/labels.txt ../dblp/attributes.txt ../dblp/querydb2.txt ../dblp/querydb2.log 0 4 > ../dblp/querydb2.csv
./a.out ../dblp/edges.txt ../dblp/labels.txt ../dblp/attributes.txt ../dblp/querydb3.txt ../dblp/querydb3.log 0 4 > ../dblp/querydb3.csv
./a.out ../dblp/edges.txt ../dblp/labels.txt ../dblp/attributes.txt ../dblp/querydb4.txt ../dblp/querydb4.log 0 4 > ../dblp/querydb4.csv
./a.out ../dblp/edges.txt ../dblp/labels.txt ../dblp/attributes.txt ../dblp/querydb5.txt ../dblp/querydb5.log 0 4 > ../dblp/querydb5.csv

cd ../BBFS
./a.out dblpqdb1 ../dblp/edges.txt ../dblp/labels.txt 0 ../dblp/oldquerydb1.txt > ../dblp/querydb1BBFS.csv&
./a.out dblpqdb2 ../dblp/edges.txt ../dblp/labels.txt 0 ../dblp/oldquerydb2.txt > ../dblp/querydb2BBFS.csv&
./a.out dblpqdb3 ../dblp/edges.txt ../dblp/labels.txt 0 ../dblp/oldquerydb3.txt > ../dblp/querydb3BBFS.csv&
./a.out dblpqdb4 ../dblp/edges.txt ../dblp/labels.txt 0 ../dblp/oldquerydb4.txt > ../dblp/querydb4BBFS.csv&
./a.out dblpqdb5 ../dblp/edges.txt ../dblp/labels.txt 0 ../dblp/oldquerydb5.txt > ../dblp/querydb5BBFS.csv

cd ../ARRIVAL

./a.out ../freebase/edges.txt ../freebase/labels.txt ../freebase/attributes.txt ../freebase/querydb1.txt ../freebase/querydb1.log 1 4 > ../freebase/querydb1.csv
./a.out ../freebase/edges.txt ../freebase/labels.txt ../freebase/attributes.txt ../freebase/querydb2.txt ../freebase/querydb2.log 1 4 > ../freebase/querydb2.csv
./a.out ../freebase/edges.txt ../freebase/labels.txt ../freebase/attributes.txt ../freebase/querydb3.txt ../freebase/querydb3.log 1 4 > ../freebase/querydb3.csv
./a.out ../freebase/edges.txt ../freebase/labels.txt ../freebase/attributes.txt ../freebase/querydb4.txt ../freebase/querydb4.log 1 4 > ../freebase/querydb4.csv
./a.out ../freebase/edges.txt ../freebase/labels.txt ../freebase/attributes.txt ../freebase/querydb5.txt ../freebase/querydb5.log 1 4 > ../freebase/querydb5.csv

cd ../BBFS
./a.out freebaseqdb1 ../freebase/edges.txt ../freebase/labels.txt 1 ../freebase/oldquerydb1.txt > ../freebase/querydb1BBFS.csv&
./a.out freebaseqdb2 ../freebase/edges.txt ../freebase/labels.txt 1 ../freebase/oldquerydb2.txt > ../freebase/querydb2BBFS.csv&
./a.out freebaseqdb3 ../freebase/edges.txt ../freebase/labels.txt 1 ../freebase/oldquerydb3.txt > ../freebase/querydb3BBFS.csv&
./a.out freebaseqdb4 ../freebase/edges.txt ../freebase/labels.txt 1 ../freebase/oldquerydb4.txt > ../freebase/querydb4BBFS.csv&
./a.out freebaseqdb5 ../freebase/edges.txt ../freebase/labels.txt 1 ../freebase/oldquerydb5.txt > ../freebase/querydb5BBFS.csv



