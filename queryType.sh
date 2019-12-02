
if [ $1 -gt 0 ] ;
then 
    echo "Including twitter"
else
    echo "Excluding"
fi
./a.out ../gplus/edges.txt ../gplus/labels.txt ../gplus/attributes.txt ../gplus/querymix.txt ../gplus/querymix.log 1 4 > ../gplus/querymix.csv
./a.out ../gplus/edges.txt ../gplus/labels.txt ../gplus/attributes.txt ../gplus/query2.txt ../gplus/query2.log 1 4 > ../gplus/query2.csv
./a.out ../gplus/edges.txt ../gplus/labels.txt ../gplus/attributes.txt ../gplus/query3.txt ../gplus/query3.log 1 4 > ../gplus/query3.csv
./a.out ../gplus/edges.txt ../gplus/labels.txt ../gplus/attributes.txt ../gplus/query4.txt ../gplus/query4.log 1 4 > ../gplus/query4.csv

cd ../BBFS
clang++ -O3 bbfs.cpp
./a.out gplusqmix ../gplus/edges.txt ../gplus/labels.txt 1 ../gplus/oldquerymix.txt > ../gplus/querymixBBFS.csv&
./a.out gplusq2 ../gplus/edges.txt ../gplus/labels.txt 1 ../gplus/oldquery2.txt > ../gplus/query2BBFS.csv&
./a.out gplusq3 ../gplus/edges.txt ../gplus/labels.txt 1 ../gplus/oldquery3.txt > ../gplus/query3BBFS.csv&
./a.out gplusq4 ../gplus/edges.txt ../gplus/labels.txt 1 ../gplus/oldquery4.txt > ../gplus/query4BBFS.csv

cd ../ARRIVAL
./a.out ../dblp/edges.txt ../dblp/labels.txt ../dblp/attributes.txt ../dblp/querymix.txt ../dblp/querymix.log 0 4 > ../dblp/querymix.csv
./a.out ../dblp/edges.txt ../dblp/labels.txt ../dblp/attributes.txt ../dblp/query2.txt ../dblp/query2.log 0 4 > ../dblp/query2.csv
./a.out ../dblp/edges.txt ../dblp/labels.txt ../dblp/attributes.txt ../dblp/query3.txt ../dblp/query3.log 0 4 > ../dblp/query3.csv
./a.out ../dblp/edges.txt ../dblp/labels.txt ../dblp/attributes.txt ../dblp/query4.txt ../dblp/query4.log 0 4 > ../dblp/query4.csv

cd ../BBFS
./a.out dblpqmix ../dblp/edges.txt ../dblp/labels.txt 0 ../dblp/oldquerymix.txt > ../dblp/querymixBBFS.csv&
./a.out dblpq2 ../dblp/edges.txt ../dblp/labels.txt 0 ../dblp/oldquery2.txt > ../dblp/query2BBFS.csv&
./a.out dblpq3 ../dblp/edges.txt ../dblp/labels.txt 0 ../dblp/oldquery3.txt > ../dblp/query3BBFS.csv&
./a.out dblpq4 ../dblp/edges.txt ../dblp/labels.txt 0 ../dblp/oldquery4.txt > ../dblp/query4BBFS.csv

cd ../ARRIVAL

./a.out ../freebase/edges.txt ../freebase/labels.txt ../freebase/attributes.txt ../freebase/querymix.txt ../freebase/querymix.log 1 4 > ../freebase/querymix.csv
./a.out ../freebase/edges.txt ../freebase/labels.txt ../freebase/attributes.txt ../freebase/query2.txt ../freebase/query2.log 1 4 > ../freebase/query2.csv
./a.out ../freebase/edges.txt ../freebase/labels.txt ../freebase/attributes.txt ../freebase/query3.txt ../freebase/query3.log 1 4 > ../freebase/query3.csv
./a.out ../freebase/edges.txt ../freebase/labels.txt ../freebase/attributes.txt ../freebase/query4.txt ../freebase/query4.log 1 4 > ../freebase/query4.csv

cd ../BBFS
./a.out freebaseqmix ../freebase/edges.txt ../freebase/labels.txt 1 ../freebase/oldquerymix.txt > ../freebase/querymixBBFS.csv&
./a.out freebaseq2 ../freebase/edges.txt ../freebase/labels.txt 1 ../freebase/oldquery2.txt > ../freebase/query2BBFS.csv&
./a.out freebaseq3 ../freebase/edges.txt ../freebase/labels.txt 1 ../freebase/oldquery3.txt > ../freebase/query3BBFS.csv&
./a.out freebaseq4 ../freebase/edges.txt ../freebase/labels.txt 1 ../freebase/oldquery4.txt > ../freebase/query4BBFS.csv

cd ../ARRIVAL

if [ $1 -gt 0 ];
then 
    ./a.out ../twitter/edges.txt ../twitter/labels.txt ../twitter/attributes.txt ../twitter/querymix.txt ../twitter/querymix.log 1 4 > ../twitter/querymix.csv
    ./a.out ../twitter/edges.txt ../twitter/labels.txt ../twitter/attributes.txt ../twitter/query2.txt ../twitter/query2.log 1 4 > ../twitter/query2.csv
    ./a.out ../twitter/edges.txt ../twitter/labels.txt ../twitter/attributes.txt ../twitter/query3.txt ../twitter/query3.log 1 4 > ../twitter/query3.csv
    ./a.out ../twitter/edges.txt ../twitter/labels.txt ../twitter/attributes.txt ../twitter/query4.txt ../twitter/query4.log 1 4 > ../twitter/query4.csv

    cd ../BBFS
    clang++ -O3 bbfs.cpp
    ./a.out twitterqmix ../twitter/edges.txt ../twitter/labels.txt 1 ../twitter/oldquerymix.txt > ../twitter/querymixBBFS.csv&
    ./a.out twitterq2 ../twitter/edges.txt ../twitter/labels.txt 1 ../twitter/oldquery2.txt > ../twitter/query2BBFS.csv&
    ./a.out twitterq3 ../twitter/edges.txt ../twitter/labels.txt 1 ../twitter/oldquery3.txt > ../twitter/query3BBFS.csv&
    ./a.out twitterq4 ../twitter/edges.txt ../twitter/labels.txt 1 ../twitter/oldquery4.txt > ../twitter/query4BBFS.csv
    cd ../ARRIVAL
fi


