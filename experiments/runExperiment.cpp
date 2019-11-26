#include "../parseRegEx/regexToAutomata.cc"

#ifndef random_H
#define random_H
#include "../random/random.cc"
#endif

#ifndef Graph_H
#define Graph_H
#include "../Graph/Graph.cc"
#endif

#include "../Methods/rr_comb.cc"
#include "../Methods/rr_qt.cc"
#ifdef __MACH__
#include <mach/mach.h>
#endif

#include "stdlib.h" 
#include "stdio.h"
#include "string.h"

#include <fstream>

std::ofstream logfile;

int parseLine(char* line){
    // This assumes that a digit will be found and the line ends in " Kb".
    int i = strlen(line);
    const char* p = line;
    while (*p <'0' || *p > '9') p++;
    line[i-3] = '\0';
    i = atoi(p);
    return i;
}

double getValue(){ // This value is in KB!
    #ifdef __MACH__

    struct task_basic_info t_info;
    mach_msg_type_number_t t_info_count = TASK_BASIC_INFO_COUNT;

    if (KERN_SUCCESS != task_info(mach_task_self(),
                                TASK_BASIC_INFO, (task_info_t)&t_info, 
                                &t_info_count))
    {
        return -1;
    }
    return (double)t_info.virtual_size/1024;
    #else
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];

    while (fgets(line, 128, file) != NULL){
        if (strncmp(line, "VmSize:", 7) == 0){
            result = parseLine(line);
            break;
        }
    }
    fclose(file);
    return (double)result;
    #endif
}


void runQueries(Graph *newG, Random *rand, char *queryFile, int max_penalty)
{
    string line;
    double negtime = 0, postime = 0;
    double labeltime = 0, edgetime = 0;
    int negn = 0, posn = 0, numl = 0, nume = 0;
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
    logfile << "Query, ";
    logfile << "response, ";
    logfile << "time" << endl;

    while (getline(myfile3, line))
    {
        querynum++;
        if (line[0] == '#')
            continue;
        

        char *cstr = &line[0u];

        char *t = strtok(cstr, " ");
		string inputType = string(t);


		if (inputType.compare("edge") == 0) {
			t = strtok(NULL, " ");
			int u = atoi(t);

			t = strtok(NULL, " ");
			int v = atoi(t);

			for (int j = newG->numNodes; j <= max(u,v); j++) {
				newG->addNode();
                
                if (++newG->toUpdate == newG->numNodes/10) {
                    newG->updateParams();
                    newG->toUpdate = 0;
                }
			}

			t = strtok(NULL, " ");
			int l;

			if (t == NULL) {
				l = 0;
			}
			else 
				l = atoi(t);

            clock_gettime(CLOCK_MONOTONIC, &start);
            newG->addEdge(u, v, l);
            clock_gettime(CLOCK_MONOTONIC, &finish);
			
            edgetime+=max((finish.tv_sec - start.tv_sec) + (finish.tv_nsec - start.tv_nsec) / pow(10, 9) - inter, 0.00000001);
			nume++;
		}

		else if (inputType.compare("label") == 0) {
			t = strtok(NULL, " ");
			int u = atoi(t);

			t = strtok(NULL, " ");
			int l = atoi(t);


            clock_gettime(CLOCK_MONOTONIC, &start);
			newG->addLabel(u, l);
            clock_gettime(CLOCK_MONOTONIC, &finish);
            labeltime+=max((finish.tv_sec - start.tv_sec) + (finish.tv_nsec - start.tv_nsec) / pow(10, 9) - inter, 0.00000001);
            ++numl;
		}

        else if (inputType.compare("querytime") == 0) {
            t = strtok(NULL, " ");
            int u = atoi(t);

            t = strtok(NULL, " ");
            int v = atoi(t);

            t = strtok(NULL, " ");
            string nodeA = string(t);

            t = strtok(NULL, " ");
            string fn = string(t);

            automata *node = conversionNode(nodeA);

            int response;

            
	        Function fns(fn);

            clock_gettime(CLOCK_MONOTONIC, &start);
            response = RandomWalkQT(u, v, newG, node, fns, rand, max_penalty);
            clock_gettime(CLOCK_MONOTONIC, &finish);

            double time1 = max((finish.tv_sec - start.tv_sec) + (finish.tv_nsec - start.tv_nsec) / pow(10, 9) - inter, 0.00000001);

            logfile << querynum << ", ";
            logfile << response << ", ";
            logfile << time1 << endl;

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

        else {
            t = strtok(NULL, " ");
            int u = atoi(t);

            t = strtok(NULL, " ");
            int v = atoi(t);

            t = strtok(NULL, " ");
            string nodeA = string(t);

            t = strtok(NULL, " ");
            string edgeA;

            if (t == NULL)
                edgeA = "U";
            else
                edgeA = string(t);

            automata *node = conversionNode(nodeA);
            automata *edge = conversionNode(edgeA);

            int response;

            clock_gettime(CLOCK_MONOTONIC, &start);
            response = RandomWalk(u, v, newG, node, edge, rand, max_penalty);
            clock_gettime(CLOCK_MONOTONIC, &finish);

            double time1 = max((finish.tv_sec - start.tv_sec) + (finish.tv_nsec - start.tv_nsec) / pow(10, 9) - inter, 0.00000001);
            logfile << querynum << ", ";
            logfile << response << ", ";
            logfile << time1 << endl;

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
    }
    cout << "negative, " << negn << ", " << negtime / negn << endl;
    cout << "positive, " << posn << ", " << postime / posn << endl;
    cout << "labeltime, " << numl<< ", "  << labeltime/ numl<< endl;
    cout << "edgetime, " << nume << ", " << edgetime/nume<< endl;
    return;
}

int main(int argc, char *argv[])
{
    char *edgeFile = argv[1];
    char *labelFile = argv[2];
    char *attrFile = argv[3];
    char *queryFile = argv[4];
    logfile.open(argv[5]);
    int dir = atoi(argv[6]);
    int max_penalty = atoi(argv[7]);
    double v1 = getValue();
    Graph *newG = new Graph(edgeFile, labelFile, attrFile, dir);
    cout << "Memory Used: " << (getValue() - v1)/1024 << endl;
    Random *rand = new Random(newG->numEdges, time(0));
    runQueries(newG, rand, queryFile, max_penalty);
    logfile.close();
    return 0;
}