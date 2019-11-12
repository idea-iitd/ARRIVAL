clang++ -Xpreprocessor -flto -march=native -O3 experiments/runExperiment.cpp
if [ ! -d "log" ]; then
  mkdir log
fi
if [ ! -d "log/$1" ]; then
  mkdir log/$1
fi
./a.out ../$1/edges.txt ../$1/labels.txt ../$1/attributes.txt ../$1/$2.txt log/$1/$2$4.log $3 $4
