
if [ $1 -gt 0 ] ;
then 
    echo "Including twitter"
else
    echo "Excluding"
fi
./a.out ../gplus/edges.txt ../gplus/labels.txt ../gplus/attributes.txt ../gplus/queryls2.txt ../gplus/queryls2.log 1 4 > ../gplus/queryls2.csv
./a.out ../gplus/edges.txt ../gplus/labels.txt ../gplus/attributes.txt ../gplus/queryls4.txt ../gplus/queryls4.log 1 4 > ../gplus/queryls4.csv
./a.out ../gplus/edges.txt ../gplus/labels.txt ../gplus/attributes.txt ../gplus/queryls6.txt ../gplus/queryls6.log 1 4 > ../gplus/queryls6.csv
./a.out ../gplus/edges.txt ../gplus/labels.txt ../gplus/attributes.txt ../gplus/queryls8.txt ../gplus/queryls8.log 1 4 > ../gplus/queryls8.csv

cd ../BBFS
clang++ -O3 bbfs.cpp
./a.out gplusqls2 ../gplus/edges.txt ../gplus/labels.txt 1 ../gplus/oldqueryls2.txt > ../gplus/queryls2BBFS.csv&
./a.out gplusqls4 ../gplus/edges.txt ../gplus/labels.txt 1 ../gplus/oldqueryls4.txt > ../gplus/queryls4BBFS.csv&
./a.out gplusqls6 ../gplus/edges.txt ../gplus/labels.txt 1 ../gplus/oldqueryls6.txt > ../gplus/queryls6BBFS.csv&
./a.out gplusqls8 ../gplus/edges.txt ../gplus/labels.txt 1 ../gplus/oldqueryls8.txt > ../gplus/queryls8BBFS.csv

cd ../ARRIVAL
./a.out ../dblp/edges.txt ../dblp/labels.txt ../dblp/attributes.txt ../dblp/queryls2.txt ../dblp/queryls2.log 0 4 > ../dblp/queryls2.csv
./a.out ../dblp/edges.txt ../dblp/labels.txt ../dblp/attributes.txt ../dblp/queryls4.txt ../dblp/queryls4.log 0 4 > ../dblp/queryls4.csv
./a.out ../dblp/edges.txt ../dblp/labels.txt ../dblp/attributes.txt ../dblp/queryls6.txt ../dblp/queryls6.log 0 4 > ../dblp/queryls6.csv
./a.out ../dblp/edges.txt ../dblp/labels.txt ../dblp/attributes.txt ../dblp/queryls8.txt ../dblp/queryls8.log 0 4 > ../dblp/queryls8.csv

cd ../BBFS
./a.out dblpqls2 ../dblp/edges.txt ../dblp/labels.txt 0 ../dblp/oldqueryls2.txt > ../dblp/queryls2BBFS.csv&
./a.out dblpqls4 ../dblp/edges.txt ../dblp/labels.txt 0 ../dblp/oldqueryls4.txt > ../dblp/queryls4BBFS.csv&
./a.out dblpqls6 ../dblp/edges.txt ../dblp/labels.txt 0 ../dblp/oldqueryls6.txt > ../dblp/queryls6BBFS.csv&
./a.out dblpqls8 ../dblp/edges.txt ../dblp/labels.txt 0 ../dblp/oldqueryls8.txt > ../dblp/queryls8BBFS.csv

cd ../ARRIVAL

./a.out ../freebase/edges.txt ../freebase/labels.txt ../freebase/attributes.txt ../freebase/queryls2.txt ../freebase/queryls2.log 1 4 > ../freebase/queryls2.csv
./a.out ../freebase/edges.txt ../freebase/labels.txt ../freebase/attributes.txt ../freebase/queryls4.txt ../freebase/queryls4.log 1 4 > ../freebase/queryls4.csv
./a.out ../freebase/edges.txt ../freebase/labels.txt ../freebase/attributes.txt ../freebase/queryls6.txt ../freebase/queryls6.log 1 4 > ../freebase/queryls6.csv
./a.out ../freebase/edges.txt ../freebase/labels.txt ../freebase/attributes.txt ../freebase/queryls8.txt ../freebase/queryls8.log 1 4 > ../freebase/queryls8.csv

cd ../BBFS
./a.out freebaseqls2 ../freebase/edges.txt ../freebase/labels.txt 1 ../freebase/oldqueryls2.txt > ../freebase/queryls2BBFS.csv&
./a.out freebaseqls4 ../freebase/edges.txt ../freebase/labels.txt 1 ../freebase/oldqueryls4.txt > ../freebase/queryls4BBFS.csv&
./a.out freebaseqls6 ../freebase/edges.txt ../freebase/labels.txt 1 ../freebase/oldqueryls6.txt > ../freebase/queryls6BBFS.csv&
./a.out freebaseqls8 ../freebase/edges.txt ../freebase/labels.txt 1 ../freebase/oldqueryls8.txt > ../freebase/queryls8BBFS.csv

cd ../ARRIVAL

