// C program for Dijkstra's single source shortest path
// algorithm. The program is for adjacency matrix
// representation of the graph

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// A utility function to find the vertex with minimum
// distance value, from the set of vertices not yet included
// in shortest path tree
int minDistance(int dist[], bool sptSet[], int size)
{
    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < size; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// A utility function to print the constructed distance
// array
void printSolution(int dist[], int size)
{
    printf("Vertex \t\t Distance from Source\n");
    for (int i = 0; i < size; i++)
        printf("%d \t\t\t\t %d\n", i, dist[i]);
}

// Function that implements Dijkstra's single source
// shortest path algorithm for a graph represented using
// adjacency matrix representation
void dijkstra(int **graph, int src, int size)
{
    // malloc the dist and sptSet arrays
    int *dist = (int *)malloc(size * sizeof(int)); // The output array. dist[i] will hold the shortest distance from src to i

    bool *sptSet = (bool *)malloc(size * sizeof(bool)); // sptSet[i] will be true if vertex i is included in shortest path tree or shortest distance from src to i is finalized

    // Initialize all distances as INFINITE and stpSet[] as
    // false
    for (int i = 0; i < size; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < size - 1; count++)
    {
        // Pick the minimum distance vertex from the set of
        // vertices not yet processed. u is always equal to
        // src in the first iteration.
        int u = minDistance(dist, sptSet, size);

        // Mark the picked vertex as processed
        sptSet[u] = true;

        // Update dist value of the adjacent vertices of the
        // picked vertex.
        for (int v = 0; v < size; v++)

            // Update dist[v] only if is not in sptSet,
            // there is an edge from u to v, and total
            // weight of path from src to v through u is
            // smaller than current value of dist[v]
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    // print the constructed distance array
    printSolution(dist, size);
}

int parseMatrixFromArgs(int **graph, int argc, char **argv)
{
    if (argc < 4)
    {
        printf("not enough values. exiting\n");
        return 1;
    }
    int weight = 0, rows = 0, cols = 0;

    rows = atoi(argv[1]);
    cols = atoi(argv[2]);

    if (rows < 0 || cols < 0 || rows != cols)
	{
		printf("Invalid input. The number of rows and columns must be positive and equal. exiting\n");
		exit(1);
	}

    if (argc - 3 != (rows * (rows - 1) / 2))
    {
        printf("Invalid input. not enough values. exiting\n");
		exit(1);
    }

    // allocate memory for the graph
    graph = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++)
    {
        graph[i] = (int *)malloc(cols * sizeof(int));
    }

    int arg_idx = 3;
    for (int i = 0; i < rows; i++)
    {
        for (int j = i; j < cols; j++)
        {
            weight = atoi(argv[arg_idx++]);
            if (weight < 0)
            {
                printf("Weight can't be negative. exiting\n");
                exit(1);
            }

            graph[i][j] = weight;
            graph[j][i] = weight;
        }
    }
    return rows;
}

int parseMatrixFromStdin(int **graph)
{
    int weight = 0, rows = 0, cols = 0;
    printf("Enter the number of rows: ");
	scanf("%d", &rows);
	printf("Enter the number of columns: ");
	scanf("%d", &cols);

    if(rows < 0 || cols < 0 || rows != cols)
	{
		printf("Invalid input. The number of rows and columns must be positive and equal. exiting\n");
		exit(1);
	}

    // allocate memory for the graph
    graph = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++)
    {
        graph[i] = (int *)malloc(cols * sizeof(int));
    }

    int counter = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = i; j < cols; j++)
        {
            printf("Enter the weight of the edge between %d and %d: ", i, j);
            int x = scanf("%d", &weight);
            
            if (weight < 0)
            {
                printf("Weight can't be negative. exiting\n");
                exit(1);
            }

            if (weight) counter++;

            if (x == EOF && counter != rows)
            {
                printf("Invalid input. unexpected EOF, not enough values. exiting\n");
		        exit(1);
            }

            graph[i][j] = weight;
            graph[j][i] = weight;
        }
    }
    return rows;
}

// driver's code
int main(int argc, char **argv)
{
    
    /* Let us create the example graph discussed above */
    // int graph[V][V] = {{0,  4, 0,  0,  0,  0, 0,  8, 0},
    //                    {4,  0, 8,  0,  0,  0, 0, 11, 0},
    //                    {0,  8, 0,  7,  0,  4, 0,  0, 2},
    //                    {0,  0, 7,  0,  9, 14, 0,  0, 0},
    //                    {0,  0, 0,  9,  0, 10, 0,  0, 0},
    //                    {0,  0, 4, 14, 10,  0, 2,  0, 0},
    //                    {0,  0, 0,  0,  0,  2, 0,  1, 6},
    //                    {8, 11, 0,  0,  0,  0, 1,  0, 7},
    //                    {0,  0, 2,  0,  0,  0, 6,  7, 0}};

    // build the graph using the user input
    int **graph;
    int size = 0;

    printf("argc: %d\n", argc);
    if (argc > 1)
    {
        size = parseMatrixFromArgs(graph, argc, argv);
    }
    else
    {
        size = parseMatrixFromStdin(graph);
    }

    // Function call
    dijkstra(graph, 0, size);

    return 0;
}
