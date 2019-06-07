# ARRIVAL

To run the code, run "run.sh" with three arguments, 1: folder name of the dataset being used, 2: queryfilename inside folder 1
,3: 1 if the graph is directed, 0 if undirected, 4: the maximum times that a node for which successor is not found, is searched

The folder should contain:
1. edgefile (edges.txt) (each line of the form u v l, where there is an edge from u to v with a label l, if l is not present it is assumed to be 1)
2. labelfile (labels.txt) (each line of the form u l, where node u has a label l, multiple labels on a node are allowed with newline) 
3. queryfile (query has to be of the form u v noderegex edgeregex, if no edgeregex is found it will be assumed to be (1)*).
