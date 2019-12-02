cd ../Baselines/GraphRegExp
javac *.java
java -Xmx40960 Graphregexp -nogui -Xmx2048m -e ../../gplus/subgraphs/edgeLabel.txt -create ../../gplus/subgraphs/queryedgeLabel.txt >> log.txt&
java -Xmx40960 Graphregexp -nogui -Xmx -e ../../dblp/subgraphs/edgeLabel.txt -create ../../dblp/subgraphs/queryedgeLabel.txt >> log.txt&
sleep 3000
search_terms='Graphregexp' 
kill $(ps aux | grep "$search_terms" | grep -v 'grep' | awk '{print $2}')

cd ../../ARRIVAL
python distributeQueries2.py
chmod +x runRandom.sh
./runRandom.sh