#include "../parseRegEx/regexToAutomata.cc"

#ifndef random_H
#define random_H
#include "../random/random.cc"
#endif

#ifndef Graph_H
#define Graph_H
#include "../Graph/Graph.cc"
#endif

#include "../Methods/rr_node.cc"

void runQueries(Graph *newG, Random *rand, char *queryFile, int max_penalty)
{
    string line;
    double negtime = 0, postime = 0;
    int negn = 0, posn = 0;
    ifstream myfile3(queryFile);
    struct timespec start, finish;
    double inter;
    int querynum = 0;
    inter = 0;
    for (int inter_c = 0; inter_c < 50; inter_c++)
    {
        clock_gettime(CLOCK_MONOTONIC, &start);
        clock_gettime(CLOCK_MONOTONIC, &finish);
        inter += (finish.tv_sec - start.tv_sec) + (finish.tv_nsec - start.tv_nsec) / pow(10, 9);
    }
    inter /= 50;
    cout << "Query, ";
    cout << "response, ";
    cout << "time" << endl;

    while (getline(myfile3, line))
    {
        querynum++;

        if (line[0] == '#')
            continue;

        char *cstr = &line[0u];

        char *t = strtok(cstr, " ");
        int u = atoi(t);

        t = strtok(NULL, " ");
        int v = atoi(t);

        t = strtok(NULL, " ");
        string nodeA = string(t);

        t = strtok(NULL, " ");
        string edgeA;

        if (t == NULL)
            edgeA = "1+";
        else
            edgeA = string(t);

        automata *node = conversionNode(nodeA);
        automata *edge = conversionNode(edgeA);

        int response;

        clock_gettime(CLOCK_MONOTONIC, &start);
        response = RandomWalk(u, v, newG, node, edge, rand, max_penalty);
        clock_gettime(CLOCK_MONOTONIC, &finish);

        double time1 = max((finish.tv_sec - start.tv_sec) + (finish.tv_nsec - start.tv_nsec) / pow(10, 9) - inter, 0.00000001);

        cout << querynum << ", ";
        cout << response << ", ";
        cout << time1 << endl;

        if (response == 0)
        {
            negtime += time1;
            negn++;
        }
        else
        {
            postime += time1;
            posn++;
        }
    }
    cout << "negative, " << negn << ", " << negtime / negn << endl;
    cout << "positive, " << posn << ", " << postime / posn << endl;
    return;
}

int main(int argc, char *argv[])
{
    char *edgeFile = argv[1];
    char *labelFile = argv[2];
    char *queryFile = argv[3];
    int dir = atoi(argv[4]);
    int max_penalty = atoi(argv[5]);

    Graph *newG = new Graph(edgeFile, labelFile, dir);
    Random *rand = new Random(newG->numEdges, time(0));

    runQueries(newG, rand, queryFile, max_penalty);
    return 0;
}