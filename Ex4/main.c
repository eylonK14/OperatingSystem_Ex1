// C program for Dijkstra's single source shortest path
// algorithm. The program is for adjacency matrix
// representation of the graph

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

char* myGetLine(char* data)
{
    data = NULL;
    size_t len = 0;
    getline(&data, &len, stdin);
    data[strcspn(data, "\r\n")] = 0;
    return data;
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
    int weight = 0, rows = 0, cols = 0;
    printf("Enter the number of rows: ");
	scanf("%d", &rows);getchar();
	printf("Enter the number of columns: ");
	scanf("%d", &cols);getchar();    

    if(rows < 0 || cols < 0 || rows != cols)
	{
		printf("Invalid input. The number of rows and columns must be positive and equal. exiting\n");
		exit(1);
	}

    // allocate memory for the graph
    int **graph = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++)
    {
        graph[i] = (int *)malloc(cols * sizeof(int));
    }

    for (int i = 0; i < rows; i++)
    {
        printf("Enter the weight for line %d\n", i + 1);
        char *weight_str = NULL;
        weight_str = myGetLine(weight_str);
        // if (x == EOF)
        // {
        //     printf("Invalid input. unexpected EOF, not enough values. exiting\n");
        //     exit(1);
        // }
        // parse the input using strtok with the delimiter space
        char *token = strtok(weight_str, " ");
        int j = 0;
        for (j = 0; j < cols; j++)
        {
            if (token) {weight = atoi(token);}
            if (weight < 0)
            {
                printf("Weight can't be negative. exiting\n");
                exit(1);
            }

            graph[i][j] = weight;
            token = strtok(NULL, " ");
        }
        if(token == NULL && j < cols)
        {
            printf("Invalid amount of values in row\n");
            exit(1);
        }
        if(token != NULL && j == cols - 1)
        {
            printf("Invalid amount of values in row\n");
            exit(1);
        }
    }

    // Function call
    dijkstra(graph, 0, rows);

    return 0;
}
