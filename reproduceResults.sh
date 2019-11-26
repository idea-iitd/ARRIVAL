# Generate all subgraphs of all graphs
# Generate all queries (and label frequencies) for all graphs (and subgraphs) - For BFS, LI, RL and ARRIVAL
unzip gplus.zip
unzip dblp.zip
unzip freebase.zip
unzip twitter.zip
unzip stack.zip

rm *.zip
rm -r __*

git clone https://github.com/idea-iitd/ARRIVAL.git

cd ARRIVAL
python genQuery.py gplus dblp freebase
python genQueryTime.py

./makeDirectories.sh gplus dblp freebase twitter
python generateSubGraphs.py gplus dblp freebase

python generateEdgeBaseline.py
./baselines.sh

python parseRare.py > rareOutput.txt
python parseLCR.py > LCROutput.txt
python parseArrivalBase.py > ArrivalOutput.txt





# Experiment 1: % of twitter (labels and nodes) vs memory
# Experiment 2: % of twitter (labels and nodes) vs time

# Experiment 3: Query type vs recall/speedup ---
# Experiment 4: label set size vs recall/speedup ---

# Experiment 5: Label frequency density bin vs recall/speedup ---
# Experiment 6: network size vs time

# Experiment 7: Recall and speedup in queries with query-time labels
# Experiment 8: negation/distance vs recall/speedup----Not going to do-------

# Experiment 9: numwalks, walklength