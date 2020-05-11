# ARRIVAL

## Introduction

We introduce our method ARRIVAL, a random walks based algorithm to answer a traditional graph query: Reachability. We do this, keeping in mind that most networks today are labeled and reachability under certain constraints becomes an interesting problem. These queries nowadays are called Regular Path Queries. These queries are studied among many different semantics: existential, shortest and simple being the primary ones. We restrict ourselves to only Regualar Simple Paths, but our technique can easily be scaled to existential as well. We deal with all kinds of labels, be it on the node or edge or whether it be defined at the time of querying. We are also able to deal with large Dynamic Graphs with incoming flow of nodes, edges as well as labels.

## Running the complete set of experiments (shortScript, which covers most of the results)

Run shortResults.sh (without cloning this repo (clone command present in script)), with datasets in the folder. Datasets can be downloaded here: https://drive.google.com/drive/folders/1rlhBzOuUpzuzdN5MTFBD5gfnMHdiIfoC?usp=sharing

--------------------------------------------

## Individual Results

To compile: g++ -std=c++11 -O3 experiments/runExperiment.cpp

To run: ./a.out path/to/dataset/edges.txt path/to/dataset/labels.txt path/to/dataset/attributes.txt path/to/dataset/query.txt
directed_parameter max_check_at_deadend

The dataset folder should contain:
1. edgefile (edges.txt) (each line of the form u v l, where there is an edge from u to v with a label l, if l is not present it is assumed to be 1)
2. labelfile (labels.txt) (each line of the form u l, where node u has a label l, multiple labels on a node are allowed with newline) 
3. queryfile ("query" u v noderegex edgeregex, to ask a query; "edge" u v, to add an edge from u to v; "label" u l, to add a label l to node u) See EDIT 1
4. attributes (attributes.txt) [For on the fly generation of queries] (each line of the form: node attribute attr_value)

directed_parameter: 1 for directed, 0 for undirected. 

max_check_at_deadend: higher the value, more time taken by random walk, higher accuracy. range between 2-4 for decent accuracy and speedups

### EDIT 1: 
With Dynamic Queries, the queries need to be of the form: "query" u v noderegex edgeregex, to ask a query; "edge" u v, to add an edge from u to v; "label" u l, to add a label l to node u
