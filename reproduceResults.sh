# Generate all subgraphs of all graphs
# Generate all queries (and label frequencies) for all graphs (and subgraphs) - For BFS, LI, RL and ARRIVAL
curl -o gplus.zip -O https://uc617c23a7381db41ab62e6cc953.dl.dropboxusercontent.com/cd/0/get/AsIJCDQHRMSIqzi5N5OFDbcR8DIe1QztzUEsPETZtunBPd0SC81KBiAiKeg_xv7VK7uGaqIBIbBbRqsuSJGHYkgHvolBVOQ4f0PZEgCLbMKW71-eB3mvamFfoJxXN-u6FDg/file
curl -o dblp.zip -O https://uc413e6f8c8b13110b5f2f89ffe0.dl.dropboxusercontent.com/cd/0/get/AsPk_JhVs1py97ulmvcbnhw_ev8cQUlGn7dUhTgcy3B7fsBC1VbRXg4B9AzmskBkMbJ10Qn1f3ioai9vsHXXO5l-vUO1RXs28gnMR70d5nUWnffhFSuzbESfe_TCSnqTpvk/file
curl -o freebase.zip -O https://uca1b8be666551fdcd4a9a163a5e.dl.dropboxusercontent.com/cd/0/get/AsPkvj2dzcHl3kC6RE1NL_vs3XVpwqu6VibvZWIvnNDAzwSF6Z8KgFM988AO188mjOFArWWEV5i5gyl7UqPL0xFNTIPtMeYp-Wr4-4EXUFOCM3WNHYVQHitaPzM1NxTt5bc/file

unzip gplus.zip
unzip dblp.zip
unzip freebase.zip

rm *.zip
rm -r __*

git clone https://github.com/idea-iitd/ARRIVAL.git

python scripts/generateSubGraphs.py gplus freebase dblp

# Experiment 1: % of twitter (labels and nodes) vs memory
# Experiment 2: % of twitter (labels and nodes) vs time

# Experiment 3: Query type vs recall/speedup ---
# Experiment 4: label set size vs recall/speedup ---

# Experiment 5: Label frequency density bin vs recall/speedup ---
# Experiment 6: network size vs time

# Experiment 7: Recall and speedup in queries with query-time labels
# Experiment 8: negation/distance vs recall/speedup

# Experiment 9: numwalks, walklength