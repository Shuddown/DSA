#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include "/workspaces/DSA/Stacks and Queues/Queue.c"

#define SET_VALUE 0

typedef struct Graph {
    int** adj_matrix;
    size_t num_vertices;
} Graph;

Graph* new_graph(size_t num_vertices){
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->num_vertices = num_vertices;
    graph->adj_matrix = (int**) malloc(sizeof(int*) * num_vertices);
    for(size_t i = 0; i<num_vertices; i++){
        graph->adj_matrix[i] = (int*) malloc(sizeof(int) * num_vertices);
        memset(graph->adj_matrix[i], SET_VALUE, sizeof(int) * num_vertices);
    }
    //memset(graph->adj_matrix, 0, sizeof(int) * num_vertices * num_vertices);
    return graph;
}

void add_directed_edge(Graph* graph, size_t src, size_t dest, int weight){
    graph->adj_matrix[src][dest] = weight;
}

void add_undirected_edge(Graph* graph, size_t src, size_t dest, int weight){
    add_directed_edge(graph, src, dest, weight);
    add_directed_edge(graph, dest, src, weight);
}

void print_graph(Graph* graph){
    for(int i = 0; i<graph->num_vertices; i++){
        for(int j = 0; j<graph->num_vertices; j++){
            printf("%d ", graph->adj_matrix[i][j]);
        }
        printf("\n");
    }
}

int next_unvisited_adjacent(Graph* graph, size_t src, bool* visited){
    for(size_t i = 0; i<graph->num_vertices; i++){
        if(graph->adj_matrix[src][i] != SET_VALUE && !visited[i])
            return i;
    }
    return -1;
}

void dfs(Graph* graph, size_t src, bool* visited){
    if(visited == NULL){
        visited = (bool*)malloc(sizeof(bool) * graph->num_vertices);
        memset(visited, false, sizeof(bool) * graph->num_vertices);
    }

    visited[src] = true;
    printf("%zu ", src);
    int next = next_unvisited_adjacent(graph, src, visited);
    if(next == -1) return;
    dfs(graph, next, visited);
}

void bfs(Graph* graph, size_t src){
    bool visited[graph->num_vertices];
    memset(visited, false, sizeof(bool) * graph->num_vertices);

    Queue* v_queue = new_queue(graph->num_vertices);
    visited[src] = true;
    enqueue(v_queue, src);
    while(!is_empty(v_queue)){
        size_t curr = dequeue(v_queue);
        printf("%zu ", curr);
        int next = next_unvisited_adjacent(graph, curr, visited);
        while(next != -1){
            visited[next] = true;
            enqueue(v_queue, next);
            next = next_unvisited_adjacent(graph, curr, visited);
        }
    }
    printf("\n");
}

size_t min_dist(Graph* graph, bool* visited, int* dist){
    int min = INT_MAX;
    size_t min_vertex;
    for(int i = 0; i<graph->num_vertices; i++){
        if(!visited[i] && dist[i] <= min){
            min = dist[i];
            min_vertex = i;
        }
    }
    return min_vertex;
}

void print_shortest_path(int src, int dest, int* prev){
    if(dest == -1) return;
    print_shortest_path(src, prev[dest], prev);
    printf("%d ", dest);
}

void djikstra(Graph* graph, size_t src, size_t dest){
    int dist[graph->num_vertices];
    bool visited[graph->num_vertices];
    int prev[graph->num_vertices];

    for(int i = 0; i<graph->num_vertices; i++){
        dist[i] = INT_MAX;
        prev[i] = -1;
        visited[i] = false;
    }

    dist[src] = 0;
    for(size_t i = 0; i<graph->num_vertices - 1; i++){
        size_t next = min_dist(graph, visited, dist);
        visited[next] = true;
        for(size_t j = 0 ; j<graph->num_vertices; j++){
            if(!visited[j] && graph->adj_matrix[next][j] != SET_VALUE && graph->adj_matrix[next][j] + dist[next] < dist[j]){
                dist[j] = graph->adj_matrix[next][j] + dist[next];
                prev[j] = next;
            }
        }
    }
    for(int i = 0; i<graph->num_vertices; i++){
        printf("%d ", dist[i]);
    }
    printf("\n");

    print_shortest_path(src, dest, prev);
    printf("\n");
}

void floyd_warshall(Graph* graph){
    int dist[graph->num_vertices][graph->num_vertices];
    for(int i = 0; i<graph->num_vertices; i++){
        for(int j = 0; j<graph->num_vertices; j++){
            dist[i][j] = (graph->adj_matrix[i][j] == SET_VALUE && i != j)? INT_MAX : graph->adj_matrix[i][j];
        }
    }

    for(int k = 0; k<graph->num_vertices; k++){
        for(int i = 0; i<graph->num_vertices; i++){
            for(int j = 0; j<graph->num_vertices; j++){
                if(dist[i][k] + dist[k][j] < dist[i][j]){
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    for(int i = 0; i<graph->num_vertices; i++){
        for(int j = 0; j<graph->num_vertices; j++){
            printf("%d ", dist[i][j] == INT_MAX ? -1 : dist[i][j]);
        }
        printf("\n");
    }
}

size_t indegree_of(Graph* graph, size_t vertex){
    size_t count = 0;
    for(int i = 0 ; i<graph->num_vertices; i++){
        if(graph->adj_matrix[i][vertex] != SET_VALUE) count += 1;
    }
    return count;
}

int new_indegree_zero(size_t* indegree, Graph* graph){
    for(int i = 0; i<graph->num_vertices; i++){
        if(indegree[i] == 0){
            indegree[i]--;
            return i;
        }
    }
    return -1;
}

void decrement_indegree(Graph* graph, size_t* indegree, int vertex){
    for(int i = 0; i<graph->num_vertices; i++){
        if(graph->adj_matrix[vertex][i] != SET_VALUE) indegree[i]--;
    }
}

void top_sort(Graph* graph){
    size_t indegree[graph->num_vertices];
    int top_num[graph->num_vertices];
    for(int i = 0; i<graph->num_vertices; i++){
        indegree[i] = indegree_of(graph, i);
        top_num[i] = -1;
    }
    //Queue* zero_q = new_queue(graph->num_vertices);
    for(int counter = 0; counter < graph->num_vertices; counter++){
        int vertex = new_indegree_zero(indegree, graph);
        if(vertex == -1){
            printf("The graph has a cycle\n");
            return;
        }
        top_num[vertex] = counter + 1;
        decrement_indegree(graph, indegree, vertex);
    }
    for(int i = 0; i<graph->num_vertices; i++){
        printf("%d ", top_num[i]);
    }
    printf("\n");    
}

int main(){
    Graph* graph = new_graph(5);
    add_directed_edge(graph, 0, 1, 1);
    add_directed_edge(graph, 0, 2, 1);
    add_directed_edge(graph, 1, 2, 1);
    add_directed_edge(graph, 1, 3, 1);
    add_directed_edge(graph, 2, 3, 1);
    add_directed_edge(graph, 2, 4, 1);
    add_directed_edge(graph, 3, 4, 1);
    print_graph(graph);
    printf("\n");
    // dfs(graph, 3, NULL);
    // printf("\n");
    // bfs(graph, 3);
    //djikstra(graph, 0, 4);
    //floyd_warshall(graph);
    top_sort(graph);
    return 0;
}
