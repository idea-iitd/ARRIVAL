clang++ -Xpreprocessor -flto -march=native -O3 experiments/runExperiment.cpp
./a.out ../$1/edges.txt ../$1/labels.txt ../$1/$2.txt $3 $4
