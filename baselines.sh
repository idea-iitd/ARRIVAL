# LI

cd ../Baselines/LCR/LCRIndexing
chmod +x rebuild.sh
./rebuild.sh

./build/default/genQuery ../../../twitter/subgraphs/label30edges100.txt 1 100 4 6
./build/default/genQuery ../../../twitter/subgraphs/label30edges133.txt 1 100 4 6
./build/default/genQuery ../../../twitter/subgraphs/label30edges150.txt 1 100 4 6
./build/default/genQuery ../../../twitter/subgraphs/label30edges166.txt 1 100 4 6
./build/default/genQuery ../../../twitter/subgraphs/label30edges175.txt 1 100 4 6
./build/default/genQuery ../../../twitter/subgraphs/label30edges200.txt 1 100 4 6
./build/default/genQuery ../../../twitter/subgraphs/label25edges200.txt 1 100 4 6
./build/default/genQuery ../../../twitter/subgraphs/label20edges200.txt 1 100 4 6
./build/default/genQuery ../../../twitter/subgraphs/label15edges200.txt 1 100 4 6
./build/default/genQuery ../../../twitter/subgraphs/label10edges200.txt 1 100 4 6
./build/default/genQuery ../../../twitter/subgraphs/label5edges200.txt 1 100 4 6


./build/default/runExperiment ../../../twitter/subgraphs/label30edges100.txt 1 30_100.csv > 30_100.output
./build/default/runExperiment ../../../twitter/subgraphs/label30edges133.txt 1 30_133.csv > 30_133.output
./build/default/runExperiment ../../../twitter/subgraphs/label30edges150.txt 1 30_150.csv > 30_150.output
./build/default/runExperiment ../../../twitter/subgraphs/label30edges166.txt 1 30_166.csv > 30_166.output
./build/default/runExperiment ../../../twitter/subgraphs/label30edges175.txt 1 30_175.csv > 30_175.output
./build/default/runExperiment ../../../twitter/subgraphs/label30edges200.txt 1 30_200.csv > 30_200.output
./build/default/runExperiment ../../../twitter/subgraphs/label25edges200.txt 1 25_200.csv > 25_200.output
./build/default/runExperiment ../../../twitter/subgraphs/label20edges200.txt 1 20_200.csv > 20_200.output
./build/default/runExperiment ../../../twitter/subgraphs/label15edges200.txt 1 15_200.csv > 15_200.output
./build/default/runExperiment ../../../twitter/subgraphs/label10edges200.txt 1 10_200.csv > 10_200.output
./build/default/runExperiment ../../../twitter/subgraphs/label5edges200.txt 1 5_200.csv > 5_200.output

# RARE LABELS


cd ../../GraphRegExp
javac *.java
java Graphregexp -nogui -e ../../twitter/subgraphs/label30edges100.txt -create ../../twitter/subgraphs/label30edges100queries.txt >> log.txt&
sleep 30
search_terms='Graphregexp' 
kill $(ps aux | grep "$search_terms" | grep -v 'grep' | awk '{print $2}')

java Graphregexp -nogui -e ../../twitter/subgraphs/label30edges133.txt -create ../../twitter/subgraphs/label30edges133queries.txt >> log.txt&
java Graphregexp -nogui -e ../../twitter/subgraphs/label30edges150.txt -create ../../twitter/subgraphs/label30edges150queries.txt >> log.txt&
java Graphregexp -nogui -e ../../twitter/subgraphs/label30edges166.txt -create ../../twitter/subgraphs/label30edges166queries.txt >> log.txt&
java Graphregexp -nogui -e ../../twitter/subgraphs/label30edges175.txt -create ../../twitter/subgraphs/label30edges175queries.txt >> log.txt&
java Graphregexp -nogui -e ../../twitter/subgraphs/label30edges200.txt -create ../../twitter/subgraphs/label30edges200queries.txt >> log.txt&

sleep 60
kill $(ps aux | grep "$search_terms" | grep -v 'grep' | awk '{print $2}')

java Graphregexp -nogui -e ../../twitter/subgraphs/label5edges200.txt -create ../../twitter/subgraphs/label5edges200queries.txt >> log.txt&
java Graphregexp -nogui -e ../../twitter/subgraphs/label10edges200.txt -create ../../twitter/subgraphs/label10edges200queries.txt >> log.txt&
java Graphregexp -nogui -e ../../twitter/subgraphs/label15edges200.txt -create ../../twitter/subgraphs/label15edges200queries.txt >> log.txt&
java Graphregexp -nogui -e ../../twitter/subgraphs/label20edges200.txt -create ../../twitter/subgraphs/label20edges200queries.txt >> log.txt&
java Graphregexp -nogui -e ../../twitter/subgraphs/label25edges200.txt -create ../../twitter/subgraphs/label25edges200queries.txt >> log.txt&

sleep 60
kill $(ps aux | grep "$search_terms" | grep -v 'grep' | awk '{print $2}')

python distributeQueries.py
chmod +x runRandom.sh
./runRandom.sh

cd ../../ARRIVAL

# ARRIVAL

clang++ -Xpreprocessor -flto -march=native -O3 experiments/genQuery.cpp
echo "100_30" > results.txt
./a.out ../twitter/subgraphs/edges100.txt ../twitter/subgraphs/labels100_30.txt ../twitter/attributes.txt ../twitter/subgraphs/query100_30.txt ../twitter/base100_30.log 1 2 >> results.txt
echo "133_30" >>results.txt
./a.out ../twitter/subgraphs/edges133.txt ../twitter/subgraphs/labels133_30.txt ../twitter/attributes.txt ../twitter/subgraphs/query133_30.txt ../twitter/base133_30.log 1 2 >> results.txt
echo "150_30" >>results.txt
./a.out ../twitter/subgraphs/edges150.txt ../twitter/subgraphs/labels150_30.txt ../twitter/attributes.txt ../twitter/subgraphs/query150_30.txt ../twitter/base150_30.log 1 2 >> results.txt
echo "166_30" >>results.txt
./a.out ../twitter/subgraphs/edges166.txt ../twitter/subgraphs/labels166_30.txt ../twitter/attributes.txt ../twitter/subgraphs/query166_30.txt ../twitter/base166_30.log 1 2 >> results.txt
echo "175_30" >>results.txt
./a.out ../twitter/subgraphs/edges175.txt ../twitter/subgraphs/labels175_30.txt ../twitter/attributes.txt ../twitter/subgraphs/query175_30.txt ../twitter/base175_30.log 1 2 >> results.txt
echo "200_30" >>results.txt
./a.out ../twitter/subgraphs/edges200.txt ../twitter/subgraphs/labels200_30.txt ../twitter/attributes.txt ../twitter/subgraphs/query200_30.txt ../twitter/base200_30.log 1 2 >> results.txt
echo "200_25" >>results.txt
./a.out ../twitter/subgraphs/edges200.txt ../twitter/subgraphs/labels200_25.txt ../twitter/attributes.txt ../twitter/subgraphs/query200_25.txt ../twitter/base200_25.log 1 2 >> results.txt
echo "200_20" >>results.txt
./a.out ../twitter/subgraphs/edges200.txt ../twitter/subgraphs/labels200_20.txt ../twitter/attributes.txt ../twitter/subgraphs/query200_20.txt ../twitter/base200_20.log 1 2 >> results.txt
echo "200_15" >>results.txt
./a.out ../twitter/subgraphs/edges200.txt ../twitter/subgraphs/labels200_15.txt ../twitter/attributes.txt ../twitter/subgraphs/query200_15.txt ../twitter/base200_15.log 1 2 >> results.txt
echo "200_10" >>results.txt
./a.out ../twitter/subgraphs/edges200.txt ../twitter/subgraphs/labels200_10.txt ../twitter/attributes.txt ../twitter/subgraphs/query200_10.txt ../twitter/base200_10.log 1 2 >> results.txt
echo "200_5" >>results.txt
./a.out ../twitter/subgraphs/edges200.txt ../twitter/subgraphs/labels200_5.txt ../twitter/attributes.txt ../twitter/subgraphs/query200_5.txt ../twitter/base200_5.log 1 2 >> results.txt
