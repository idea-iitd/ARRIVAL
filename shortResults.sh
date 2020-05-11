anywait(){
    for pid in "$@"; do
        while kill -0 "$pid"; do
            sleep 0.5
        done
    done
}

unzip gplus.zip
unzip dblp.zip

rm *.zip
rm -r __*

git clone https://github.com/idea-iitd/ARRIVAL.git
git clone https://github.com/sarisht/BBFS.git
git clone https://github.com/sarisht/Baselines.git

cd ARRIVAL

# Generate all subgraphs of all graphs
./makeDirectories.sh gplus
python generateSubGraphs.py gplus

# Generate all queries for all graphs (and subgraphs) - For BFS, LI, RL and ARRIVAL
python genQuery.py gplus
python genQuery.py dblp

# Experiment 2: Query type vs recall/speedup 
./queryType.sh gplus
search_terms='a.out' 
anywait $(ps aux | grep "$search_terms" | grep -v 'grep' | awk '{print $2}')
python parseArrivalType2.py gplus> TypeOutput.txt

# Experiment 3: label set size vs recall/speedup
./queryLS.sh gplus
anywait $(ps aux | grep "$search_terms" | grep -v 'grep' | awk '{print $2}')
python parseArrivalSize2.py gplus > LsizeOutput.txt

# Experiment 4: Label frequency density bin vs recall/speedup 
./queryDB.sh gplus
anywait $(ps aux | grep "$search_terms" | grep -v 'grep' | awk '{print $2}')
python parseDB2.py gplus> DBOutput.txt

# Experiment 5: network size vs time
./queryNS.sh gplus
anywait $(ps aux | grep "$search_terms" | grep -v 'grep' | awk '{print $2}')
python parseNS2.py gplus> NSizeOutput.txt

# Experiment 6: numwalks, walklength
./queryParams.sh dblp
anywait $(ps aux | grep "$search_terms" | grep -v 'grep' | awk '{print $2}')
python parseParams2.py dblp> paramsOuput.txt
