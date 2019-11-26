

clang++ -Xpreprocessor -flto -march=native -O3 experiments/runExperiment.cpp
./a.out ../twitter/subgraphs/edges100.txt ../twitter/subgraphs/labels100_30.txt ../twitter/attributes.txt ../twitter/subgraphs/query100_30.txt ../twitter/base100_30.log 1 2 >> results.txt
echo "..." >>results.txt
./a.out ../twitter/subgraphs/edges133.txt ../twitter/subgraphs/labels133_30.txt ../twitter/attributes.txt ../twitter/subgraphs/query133_30.txt ../twitter/base133_30.log 1 2 >> results.txt
echo "..." >>results.txt
./a.out ../twitter/subgraphs/edges150.txt ../twitter/subgraphs/labels150_30.txt ../twitter/attributes.txt ../twitter/subgraphs/query150_30.txt ../twitter/base150_30.log 1 2 >> results.txt
echo "..." >>results.txt
./a.out ../twitter/subgraphs/edges166.txt ../twitter/subgraphs/labels166_30.txt ../twitter/attributes.txt ../twitter/subgraphs/query166_30.txt ../twitter/base166_30.log 1 2 >> results.txt
echo "..." >>results.txt
./a.out ../twitter/subgraphs/edges175.txt ../twitter/subgraphs/labels175_30.txt ../twitter/attributes.txt ../twitter/subgraphs/query175_30.txt ../twitter/base175_30.log 1 2 >> results.txt
echo "..." >>results.txt
./a.out ../twitter/subgraphs/edges200.txt ../twitter/subgraphs/labels200_30.txt ../twitter/attributes.txt ../twitter/subgraphs/query200_30.txt ../twitter/base200_30.log 1 2 >> results.txt
echo "..." >>results.txt
./a.out ../twitter/subgraphs/edges200.txt ../twitter/subgraphs/labels200_25.txt ../twitter/attributes.txt ../twitter/subgraphs/query200_25.txt ../twitter/base200_25.log 1 2 >> results.txt
echo "..." >>results.txt
./a.out ../twitter/subgraphs/edges200.txt ../twitter/subgraphs/labels200_20.txt ../twitter/attributes.txt ../twitter/subgraphs/query200_20.txt ../twitter/base200_20.log 1 2 >> results.txt
echo "..." >>results.txt
./a.out ../twitter/subgraphs/edges200.txt ../twitter/subgraphs/labels200_15.txt ../twitter/attributes.txt ../twitter/subgraphs/query200_15.txt ../twitter/base200_15.log 1 2 >> results.txt
echo "..." >>results.txt
./a.out ../twitter/subgraphs/edges200.txt ../twitter/subgraphs/labels200_10.txt ../twitter/attributes.txt ../twitter/subgraphs/query200_10.txt ../twitter/base200_10.log 1 2 >> results.txt
echo "..." >>results.txt
./a.out ../twitter/subgraphs/edges200.txt ../twitter/subgraphs/labels200_5.txt ../twitter/attributes.txt ../twitter/subgraphs/query200_5.txt ../twitter/base200_5.log 1 2 >> results.txt
