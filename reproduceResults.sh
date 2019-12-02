if [ $1 -gt 0 ]
then 
    echo "Including Twitter"
else
    echo "Excluding Twitter"
fi

unzip gplus.zip
unzip dblp.zip
unzip freebase.zip
unzip twitter.zip
unzip stack.zip

rm *.zip
rm -r __*

git clone https://github.com/idea-iitd/ARRIVAL.git
git clone https://github.com/sarisht/BBFS.git
git clone https://github.com/sarisht/Baselines.git

cd ARRIVAL

# Generate all subgraphs of all graphs
./makeDirectories.sh gplus dblp freebase twitter
python generateSubGraphs.py gplus dblp freebase

# Generate all queries for all graphs (and subgraphs) - For BFS, LI, RL and ARRIVAL
python genQuery.py gplus dblp freebase
python genQueryTime.py
python generateEdgeBaseline.py
python addDynamo.py

# Experiment 1: % of twitter (labels and nodes) vs memory/time
./baselines.sh
python parseRare.py > rareOutput.txt
python parseLCR.py > LCROutput.txt
python parseArrivalBase.py > ArrivalOutput.txt

# Experiment 2: Query type vs recall/speedup 
./queryType.sh $1
sleep(1000) #Wait for thread to end
python parseArrivalType.py > TypeOutput.txt

# Running Rare for table
python generateEdgeGraphs.py
./runRare.sh
python generateTable.py

# Experiment 3: label set size vs recall/speedup
./queryLS.sh
sleep(1000) #Wait for thread to end
python parseArrivalSize.py > LsizeOutput.txt

# Experiment 4: Label frequency density bin vs recall/speedup 
./queryDB.sh
sleep(1000) #Wait for thread to end
python parseDB.py > DBOutput.txt

# Experiment 5: network size vs time
./queryNS.sh
sleep(1000)
python parseNS.py > NSizeOutput.txt

# Experiment 6: Recall and speedup in queries with query-time labels
./queryQT.sh
sleep(1000) #Wait for thread to end
python parseQT.py > QTimeOutput.txt

# Experiment 7: negation/distance vs recall/speedup ----Not going to do-------
./queryNEG.sh
sleep(1000)
./queryDist.sh
sleep(1000)
python parseNeg.py > NegOutput.txt
python parseDist.py > DistanceOutput.txt

# Experiment 8: numwalks, walklength
./queryParams.sh
python parseParams.py > paramsOuput.txt

# Generate Plots
mkdir figures
python plotScript.py