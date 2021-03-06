//Rishabh Agarwal      ECE 223
// MP6
//
//
//
//
// Created by Rishabh Agarwal on 4/3/13

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Dijkstras.h"
#define unreachable 87654


//------------------------construct function start-------------------//
void construct(home *node_ptr,int graphchoice,int V,int rover_ptr)
 {

	int incr = 0;
	node_ptr->graph_matrx = (double **)malloc (V * sizeof (double*));
	rover_ptr=0;
	node_ptr->graphchoice = graphchoice;
	node_ptr->V = V;
	node_ptr->path= (int *)malloc(V * sizeof(int));
	node_ptr->node_length = (double *)malloc (V * sizeof (double));
	if(rover_ptr==0)
	{
	while (incr<V)
	{
		
		node_ptr->graph_matrx[incr]=(double *)malloc (V * sizeof(double));
		incr++;
	}
	}
	
 }
//-------------------construct ends--------------------------------------//
//-------------------------destruct start--------------------------------//
void destruct (home *node_ptr)
{
if(node_ptr==NULL)
return;
int incr=0;
 while (incr < node_ptr->V)
   {
   free(node_ptr->graph_matrx[incr]);
   incr++;
   }
free(node_ptr->path);
free(node_ptr->graph_matrx);
free(node_ptr->node_length);
}
//------------------------------destruct end-------------------------------//
//------------------------dijkstras_graph start-----------------------------//
void dijkstras_graph(home*node_ptr,int approx_vertices , int V, int graphchoice, int rover_ptr)
{
if(node_ptr==NULL)
return;
	int incr=0;
	int incr2=0;
	int yy=0;
        while(yy<10)
        {
        yy++;
        }
	
	node_ptr->graphchoice=graphchoice;
	if(graphchoice == 1)
	{
		    while (incr<V)
	      {
		   incr2=0;
		   do
		    {
		    	node_ptr->graph_matrx[incr][incr2]= unreachable;
 	          if(incr==incr2)
		 	  {
		 		node_ptr->graph_matrx[incr][incr2]=0;
		 	  }
		    incr2++;
		    }while(incr2<V);
		    
		    incr++;
	      }
	      node_ptr->graph_matrx[1][6]=5;
	      node_ptr->graph_matrx[2][3]=7;
	      node_ptr->graph_matrx[2][4]=3;
	      node_ptr->graph_matrx[2][6]=10;
	      node_ptr->graph_matrx[3][4]=5;
	      node_ptr->graph_matrx[6][0]=4;
	      node_ptr->graph_matrx[6][3]=8;
	      node_ptr->graph_matrx[6][4]=9;
	      node_ptr->graph_matrx[3][5]=1;
	      node_ptr->graph_matrx[4][5]=6;
	      node_ptr->graph_matrx[5][6]=7;
	      node_ptr->graph_matrx[1][2]=3;
	 }
	 
    if(graphchoice==2)
	{
	    incr=0;
    	 while(incr<V)
    	 {
    	 incr2=0;
    	  do
    	  {
	   node_ptr->graph_matrx[incr][incr2]= abs((incr-incr2)) + pow(((incr-incr2) + 2),2) + 3*incr2;
    	   if(incr!=incr2)
         { incr2++;
          }
          else
          {
          node_ptr->graph_matrx[incr][incr2]=0;
          incr2++;
          }
          }while(incr2<V);
          incr++;
        }  
   }
   
 if(graphchoice==3)
{
 int pie=3.14;
 
 double d=0,total=0,mean=0;
  
  int incr=0,incr2=0,min=unreachable,max=0,ptr;
  vertex array[V];
 
  int op =0;
  op=V-1;
  array[op].vertex1=1;
  array[op].vertex2=1;
   array[0].vertex1=0;
  array[0].vertex2=0;  
    
    incr=1;
    while(incr<V-1) 
	      {
	      array[incr].vertex1=drand48();
	      array[incr].vertex2=drand48();
	      incr++;
	      }
	      
 double c=0.0,m=0.0,f=0.0;
int yy=0;
while(yy<10)
{
yy++;
}
double xx=V*pie;
c= sqrt ((approx_vertices/(xx)));
 m= log10(1+ pow((1/c),2));

incr=0;
while(incr<V)
{
 for(incr2=0;incr2<V;incr2++)
 {
   d = sqrt((pow((array[incr].vertex1 - array[incr2].vertex1),2)) + (pow((array[incr].vertex2 - array[incr2].vertex2),2))); 
   
    if(incr==incr2)
  {
  node_ptr->graph_matrx[incr][incr2]=0;
  }
 else if(d <= c/2) 
  {
  //f= log10(1+(pow(1/(d+(c/1000)),2)));
  //total++;
   //ptr++;
  node_ptr->graph_matrx[incr][incr2]=1;
 
  }
  else if(d>=c/2 && d<= 0.75*c)
  {
  node_ptr->graph_matrx[incr][incr2]=2;
  }
  
  else if(0.75*c > d && d<c)
  {
  node_ptr->graph_matrx[incr][incr2]=4;
  }
 
  else
  {
  node_ptr->graph_matrx[incr][incr2]=unreachable;
  }
  
  }
  
 if (ptr>min) 
    {
         max=ptr;
    }
  else if(ptr<min)
    {
        min=ptr;
    }
	         
  incr++;
 }
    mean=total/V; 
    printf("Mean of adjacent vertices: %g\n",mean);
    printf("Maximum adjacent vertices:%d\n",max);
    printf("Minimum adjacent vertices: %d\n",min);
	 
 while(yy<10)
{
yy++;
}
 }
 else 
 return ;
}
//---------------------dijkstra function ends---------------------------//
//----------------------short_path start--------------------------------//

void short_path(home *node_ptr,int s_v, int rover_ptr)
{
if(node_ptr==NULL)
return;
if(s_v > node_ptr->V)
{
return;
}
int yy=0;
while(yy<10)
{
yy++;
}
 
 int V=0;
 V=node_ptr->V;
 int v[V],incr=0,incr2=0,min=0;
 
 incr=V-1; 
 while (incr>=0)
 {
  node_ptr->node_length[incr]=unreachable;
  
  node_ptr->path[incr] = 0;
  v[incr]=0;
  incr--;
 }
 node_ptr->path[s_v] = -2*unreachable; 
 node_ptr->node_length[s_v]=0;
 
 
 for(incr2=0;incr2<V;incr2++)
 {
  min=-2;
  incr=0;
   while(incr < V)
   {
    if(v[incr]==0)
    {
    if(min== -2 ||( node_ptr->node_length[incr] < node_ptr->node_length[min]))
     {
      min=incr;
      
     }
    }
    incr++;
   }
   v[min]=1;
   incr=0;
   while(incr<V)
    { 
     if(node_ptr->graph_matrx[min][incr]!=0 || node_ptr->graph_matrx[min][incr] !=unreachable )
     {
      
      if((node_ptr->graph_matrx[min][incr]+node_ptr->node_length[min] ) < node_ptr->node_length[incr] )
      {
      node_ptr->path[incr] = min;
      node_ptr->node_length[incr] = node_ptr->graph_matrx[min][incr] +node_ptr->node_length[min] ;
      }
    }
    incr++;
   }   
 }
}   			 
//------------------------short path end---------------------//
//--------------------------longest_path----------------------------//	     
void longest_path(home *node_ptr,int V,int rover_ptr)
{
if(node_ptr==NULL)
return;
int incr2=0;
int shad=1,length=0;
int sv=0,dv=0;
int count=0;
int yy=0;
while(yy<10)
{
yy++;
}

while(count < V)
{

 if(count<V)
 short_path(node_ptr,count,0);
 
 for(incr2=0;incr2<V;incr2++)
 {
  if(node_ptr->node_length[incr2]!=unreachable && (node_ptr->node_length[incr2] > length))
  {
    dv=incr2;
    length=node_ptr->node_length[incr2];
    sv=count;
    }
    else if(node_ptr->node_length[incr2]==unreachable)
    {
    shad=-77;
    }
 }
   
  count+=1; 
}



 short_path(node_ptr,sv,0);
 printf("\n Diameter %g  path :",node_ptr->node_length[dv]);
 
graph_display_full(node_ptr,dv,0);

 printf("\n");



 
 if(shad!=-77)
 printf("graph is connected");
 else
 printf("graph is not connected");

}
// --------------------------longest part ends------------------//
//------------------------graph_display start----------------------//
void graph_display(home *node_ptr,int V,int rover_ptr)

{
if(node_ptr==NULL)
return;
	int incr=0,incr2=0;
	
int yy=0;
while(yy<10)
{
yy++;
}

	while(incr<V)
	{
		while(incr2<V)
		{
			printf("%g\t ",node_ptr->graph_matrx[incr][incr2]);
			incr2++;
		}
		incr++;
	printf("\n");
	}
}
//-----------------------graph_display end---------------------------//
//-------------------------graph_display_full------------------------//
void graph_display_full(home *node_ptr,int destination,int rover_ptr)
{
if(node_ptr==NULL)
return;
int incr;
int path[node_ptr->V];
int flag=0;
	
	int random=destination;
	
	while(random!= (-2*unreachable))
	     {
	     path[flag]=random;
	     random= node_ptr->path[random];
	     flag++;
	     }
 	for(incr=flag-1;incr>=0;incr--)
 	  {
 	   printf("%d",path[incr]);
 	   if(incr!=0)
 	   {
 	    printf("----");
 	   }
 	  }	

}
//----------------------------graph display full end----------------------//
