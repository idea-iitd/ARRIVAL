gsed -i 's/rr_node/rr_comb/g' experiments/runExperiment.cpp

./run.sh gplus querymix1 1 > results/gplus_mixed.csv
./run.sh dblp querymix1 0 > results/dblp_mixed.csv
./run.sh freebase querymix1 1 > results/freebase_mixed.csv

gsed -i 's/=2/=4/g' experiments/runExperiment.cpp

./run.sh gplus querymix1 1 > results/gplus_mixed_pen4.csv
./run.sh dblp querymix1 0 > results/dblp_mixed_pen4.csv
./run.sh freebase querymix1 1 > results/freebase_mixed_pen4.csv

gsed -i 's/rr_comb/rr_node/g' experiments/runExperiment.cpp

./run.sh gplus querymix1 1 > results/gplus_node_pen4.csv
./run.sh dblp querymix1 0 > results/dblp_node_pen4.csv
./run.sh freebase querymix1 1 > results/freebase_node_pen4.csv

gsed -i 's/=4/=2/g' experiments/runExperiment.cpp

./run.sh gplus querymix1 1 > results/gplus_node.csv
./run.sh dblp querymix1 0 > results/dblp_node.csv
./run.sh freebase querymix1 1 > results/freebase_node.csv

gsed -i 's/rr_node/rr_comb/g' experiments/runExperiment.cpp
