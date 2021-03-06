// Rishabh Agarwal  ECE 273
//
//  
//
//  Created by Rishabh Agarwal on 4/3/14.
//
//
typedef struct start
{
    int V;
    int *path;
    double **graph_matrx;
    int graphchoice;
    int rover_ptr;
    double *node_length;
    
}home;
typedef struct node
{
    float vertex1; 
    float vertex2; 
}vertex;

void construct(home *node_ptr, int V,int graphchoice,int rover_ptr);
void destruct(home *node_ptr);
void graph_display_full(home *node_ptr , int d,int rover_ptr);
void short_path(home *node_ptr, int s_v,int rover_ptr);
void dijkstras_graph(home *node_ptr,int graphchoice, int V, int approx_vertices,int rover_ptr);
void graph_display(home *node_ptr, int V,int rover_ptr);
void longest_path(home *node_ptr,int V,int rover_ptr);
