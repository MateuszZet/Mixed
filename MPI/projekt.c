#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // sleep
#include <iostream>
#include <list>
#include <iterator>
#include <cstdio>
#include <vector>
#include <list>
#include <utility>
#include <cstdlib>
#include <ctime>
#include <bits/stdc++.h>
#include<iterator>

using namespace std;

//function for printing the elements in a list
void showlist(list <pair<int,int>> g)
{
    int v,w;
    for(auto it = g.begin(); it != g.end(); ++it){
		w = it->first;
        v = it->second;
		cout << w << "," << v << " ";}
}

//function for printing the elements in a list
void showlist2(list <int> g)
{
    for(auto it = g.begin(); it != g.end(); ++it){
		cout << *it <<" ";}
}

void showvec(vector <int> g)
{
    for(auto it = g.begin(); it != g.end(); ++it){
		cout << *it <<" ";}
}

// To add an edge
void addEdge(vector <pair<int, int> > adj[], int u,
                                     int v, int wt)
{
    adj[u].push_back(make_pair(wt, v));
    adj[v].push_back(make_pair(wt, u));
}
 
// Print adjacency list representaion of graph
void printGraph(vector<pair<int,int> > adj[], int V)
{
    int v, w;
    for (int u = 0; u < V; u++)
    {
        cout << u << ": ";
        for (auto it = adj[u].begin(); it!=adj[u].end(); it++)
        {
            w = it->first;
            v = it->second;
            cout << w << ","
                 << v << " ";
        }
        cout << "\n";
    }
}

pair<int,int> getNode(vector<pair<int,int> > adj[], int V, int V2 )
{
		pair<int,int> node;
		node = adj[V].at(V2);
        return node;
    
}

list<pair<int,int>> getNeighbors(vector<pair<int,int> > adj[], int V)
{
		list<pair<int,int>> neighbors;
		for (auto it = adj[V].begin(); it!=adj[V].end(); it++)
        {
            neighbors.push_back(*it);
			
        }
        return neighbors;
    
}

list<int> getNeighbors2(vector<pair<int,int> > adj[], int V)
{
		list<int> neighbors;
		int v,w;
		for(auto it = adj[V].begin(); it!=adj[V].end(); it++)
		{
			v = it->second;
			neighbors.push_back(v);
		}
		return neighbors;
    
}

bool sortbysec(const pair<int,int> &a,
              const pair<int,int> &b)
{
    return (a.second < b.second);
}

void best_fs(int finish, vector<pair<int, int> > adj[], int V){
	list <pair<int,int>> open, neighbors;
	list<int> closed , neighbors2, route, route2;
	closed.push_back(0);
	int current =  0;
	int counter = 0;
	while(current != finish && closed.size() != V )
	{
		neighbors = getNeighbors(adj,current);
		open.splice(open.end(), neighbors);
		open.sort();
		cout << "\nOPEN is : ";showlist(open);
		auto next = open.front().second;

		while(find(closed.begin(), closed.end(), next) != closed.end())
		{
			open.pop_front();
			if(!open.empty()){
				next = open.front().second;
			}
			
			
		}
		
		if(!open.empty()){
			open.pop_front();
			closed.push_back(next);
			current = next;
			cout << "\nClosed is : ";showlist2(closed);cout<<endl;
			if (current == finish){cout << "FOUNDED IN "<<counter<<" STEPS";}
			counter++;
		}
		
	}
	
}

list <pair<int,int>> MPI_bfs(vector<pair<int, int> > adj[], int V, int current){
	list <pair<int,int>> neighbors;
	
		neighbors = getNeighbors(adj,current);
		neighbors.sort();
		return neighbors;
	
}

/***************** MAIN **********************/
int main(int argc,char *argv[]){
	srand( time( NULL ) );
	int myid, numprocs;
	
	
	//inicjalizacja MPI
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	
	int size,closed_size;
	int V = atoi(argv[1]);
	int finish = V-1;
	vector<pair<int, int> > adj[V], value_l;
	vector<int> node_list, tmp_l;
	vector<int> closed;
	list <pair<int,int>> open;
	double t0,t1, s0, s1;
	
	struct elem { 
        int first; 
        int second; 
    } node, gnode,my_node;
	
	//CREATE GRAPH (ADJ LIST)
		for(int i=0; i<V; i++){
			node_list.push_back(i);
		}
		
		for(int i=0; i<V; i++){
			tmp_l = node_list;
			//int top = (rand() % 5) + 1;
			for(int y =0; y<numprocs*2; y++){
				int index = rand() % tmp_l.size(); // pick a random index
				int value = tmp_l[index]; // a random value taken from that list
				
				auto p = make_pair(value, i);
					
				if((value != i-1) && (value != i+1) && (value != i) && (find(value_l.begin(), value_l.end(), p) == value_l.end())){
					addEdge(adj,i, value, rand()%100);
				}
				tmp_l.erase(tmp_l.begin()+index);
				value_l.push_back(make_pair(i,value));
			}
			
		}
	//END CREATE GRAPH
	gnode.second = 0;
	int counter = 0;
	if(myid ==0){
		printGraph(adj, V);
		t0 = MPI_Wtime();
		best_fs(finish, adj,V);
		t1 = MPI_Wtime();
		cout<<endl<<endl;
		
	}
	
	s0 = MPI_Wtime();
	while(gnode.second != finish && closed.size() < V){
		if(myid == 0){
		elem tmp_node;
		closed.push_back(gnode.second);
		open = getNeighbors(adj,gnode.second);
		open.sort();
		//cout <<counter<<" ID: "<<myid<<": OPEN : ";showlist(open);cout<<endl;
	
		my_node.first = open.front().first;
		my_node.second = open.front().second;
		
		for(int i=0; i<numprocs; i++){
			node.first = open.front().first;
			node.second = open.front().second;
			
			
			open.pop_front();
			if(i != myid){
				MPI_Send(&node,1,MPI_2INT,i,0,MPI_COMM_WORLD);
			}
			
		
		}
		
		//cout <<counter<<" ID: "<<myid<<": CLOSED : ";showvec(closed);cout<<endl;
			closed_size = closed.size();
		
		
			open = MPI_bfs(adj,V,my_node.second);
			while(find(closed.begin(), closed.end(), my_node.second) != closed.end())
			{
				open.pop_front();
				if(!open.empty()){
					my_node.second = open.front().second;
					my_node.first = open.front().first;
				}
			}
			node = my_node;
		
		//cout <<counter<<" ID: "<<myid<<" NEXT NODE: "<<node.first<<" "<<node.second<<endl;
			
	}
	
	MPI_Bcast(&closed_size,1,MPI_INT,0,MPI_COMM_WORLD);
	closed.resize(closed_size);
	MPI_Bcast(&closed.front(),closed.size(),MPI_INT,0,MPI_COMM_WORLD);
	 
	if(myid != 0){
		MPI_Recv(&node,1,MPI_2INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		//cout <<counter<<" ID: "<<myid<<" RECIVED NODE: " << node.first<<" "<<node.second<<endl;
		
		open = getNeighbors(adj,node.second);
		open.sort();
		node.second = open.front().second;
		node.first = open.front().first;
		
		while(find(closed.begin(), closed.end(), node.second) != closed.end())
		{
			open.pop_front();
			if(!open.empty()){
				node.second = open.front().second;
				node.first = open.front().first;
			}
			
			
		}
		closed.push_back(node.second);
		//cout <<counter<<" ID: "<<myid<<" NEXT NODE: "<<node.first<<" "<<node.second<<endl;
	}
	
	
	MPI_Allreduce(&node, &gnode, 1, MPI_FLOAT_INT, MPI_MINLOC, MPI_COMM_WORLD);
	
	
		cout<<counter<<": GNODE IS "<<gnode.first<<" "<<gnode.second<<endl;
		if(gnode.second == finish){
			cout<< "FOUND IN "<<counter<<" STEPS"<<endl;
		}
		
	
	counter++;
	
	}
	s1 = MPI_Wtime();
	if(myid == 0){
		cout<<"NUMPROC: "<<numprocs<<" V: "<<V<<endl;
		printf("BFS TIME: %.16f\n",t1-t0);
		printf("PARALLEL BFS TIME: %.16f\n",s1-s0);
	}
	MPI_Finalize();
	return 0;
}

