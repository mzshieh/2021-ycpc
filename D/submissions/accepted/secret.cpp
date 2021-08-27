#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <time.h>       /* time */
using namespace std;

bool flg_show = false;

class EDGE {
public:
	int edgeID;
	int cost;
	vector<int> nodeID;
};

class NODE {
public:
	NODE( ) {
		parentNode = 0;
	}
	string name;
	int nodeID;
	int moonStones;
	int influence_cost;
	vector<EDGE*> edges;
	//
	int total_influence_cost;
	//
	int cost;
	int total_stones;
	NODE *parentNode;
	int numNodes;
	//
	bool flg_visited;
	int depth;
};


vector<NODE*> nodes;
vector<EDGE*> edges;
map<string,int> graphMap;

void clearPathInfo( )
{
	for (int j =0; j < nodes.size( ); ++j ) {
		nodes[j]->total_influence_cost = 0;
		nodes[j]->cost = -1;
		nodes[j]->total_stones = -1;
		nodes[j]->parentNode = 0;
		nodes[j]->numNodes = 0;
	}
}

void solve(NODE *dest, vector<NODE*> &active)
{
	while (!active.empty()) {
      NODE *v= active.back();
      active.pop_back( );
	  int src_nodeID = v->nodeID;
	  for (int i =0; i < v->edges.size( ); ++i) {
		  int cost = v->edges[i]->cost;
		  int nodeID = v->edges[i]->nodeID[0];
		  if (nodeID==src_nodeID) {
			  nodeID = v->edges[i]->nodeID[1];
		  }
		  NODE *u = nodes[nodeID];
		  int new_cost = cost + v->cost + v->total_influence_cost;
		  int new_stones = u->moonStones + v->total_stones;
		  bool flg = false;
          if (
			  u->cost < 0
			  || 
			  ( u->cost > new_cost )
			  ) {
              flg = true; 
          } else if ( 
			  (u->cost == new_cost)
			  &&
			  (new_stones > u->moonStones)
			  ) 
		  {
			  flg = true;
		  }

		  if (flg) {
			  u->cost = new_cost;
			   u->total_stones = new_stones;
			   u->numNodes = v->numNodes + 1;
			   u->parentNode = v;
			   active.push_back( u);
		  }
      }
   }

}

void computeTotalInfluenceCostOfNodes(NODE *node, int k) {

	node->total_influence_cost = 0;
	
	node->depth = 0;
	node->flg_visited = true;

	vector<NODE*> visited_nodes;
	vector<NODE*> active;
	active.push_back( node );
	
	int total_influence = 0;
	while (!active.empty()) {
      NODE *v= active.back();
      active.pop_back( );

	  visited_nodes.push_back( v );

	  if (v->flg_visited==false) {
		  if ( k >= v->depth ) {
			total_influence += v->influence_cost;
			v->flg_visited = true;
		  }
	  }
	  if (v->depth + 1 >k) continue;
	  int src_nodeID = v->nodeID;
	  for (int i =0; i < v->edges.size( ); ++i) {
		  int nodeID = v->edges[i]->nodeID[0];
		  if (nodeID==src_nodeID) {
			  nodeID = v->edges[i]->nodeID[1];
		  }
		  NODE *u = nodes[nodeID];
		  
		  if ( 
			  (u->depth==-1)
			  ||
			  u->depth > v->depth + 1) {
			  u->depth = v->depth + 1;
			  active.push_back( u );
			  
		  }
	  }
	}

	node->total_influence_cost = total_influence;
	//

	for (int j =0; j < visited_nodes.size( ); ++j ) {
		visited_nodes[j]->flg_visited = false;
		visited_nodes[j]->depth = -1;
	}
}

void computeTotalInfluenceCostOfNodes( int k )
{
	for (int j =0; j < nodes.size( ); ++j ) {
		nodes[j]->flg_visited = false;
		nodes[j]->total_influence_cost = 0;
		nodes[j]->depth = -1;
	}

	for (int j =0; j < nodes.size( ); ++j ) {
		computeTotalInfluenceCostOfNodes( nodes[j], k );
	}
}

void solve( 
	int src_nodeID,
	int dst_nodeID,
	int k = 1
	)
{
	//cout << "Solve:" << src_nodeID << "\t" << dst_nodeID << endl;
	clearPathInfo( );
	nodes[src_nodeID]->numNodes = 1;
	nodes[src_nodeID]->cost = 0; 
	nodes[src_nodeID]->total_stones = nodes[src_nodeID]->moonStones;
	//
	computeTotalInfluenceCostOfNodes( k );
	//
	vector<NODE*> active;
	active.push_back(nodes[src_nodeID]);

	NODE *destNode = nodes[dst_nodeID];
	solve(destNode, active);

	
}

void clearGraph( )
{
	for (int j =0; j < nodes.size( ); ++j ) {
		delete nodes[j];
	}
	for (int j =0; j < edges.size( ); ++j ) {
		delete edges[j];
	}
}

void readFile( 
	const char *fileName  
	, int &src_nodeID
	, int &dst_nodeID
	, int &k
	)
{
	int src, dst;
	graphMap.clear( );

	int numNodes;
	int numEdges;
	cin >> numNodes >> numEdges >> k;
	
	string srcName, dstName;
	cin >> srcName >> dstName;

	

	nodes.resize( numNodes );
	edges.resize( numEdges );
	//
	for (int i =0; i < numNodes; ++i ) {
		int nodeID;
		int moonStones;
		int influence_cost;
		string name;

		//input >> nodeID >> moonStones >> influence_cost;
		//cout << "nodeID:" << nodeID << "\t" << moonStones << "\t" << influence_cost << endl;
		///////////////////////////////////////////
		cin >> name >> moonStones >> influence_cost;

		nodeID = i;
		///////////////////////////////////////////
		graphMap[name] = nodeID;

		NODE *node = new NODE;
		node->nodeID = nodeID;
		node->moonStones = moonStones;
		node->influence_cost = influence_cost;

		nodes[i] = node;
		//

	}

	src_nodeID = graphMap[srcName];
	dst_nodeID = graphMap[dstName];

	for (int i =0; i < numEdges; ++i ) {

		EDGE *edge = new EDGE;
		int node0, node1;
		int cost;
		string name0, name1;

		cin >> name0 >> name1 >> cost;

		node0 = graphMap[name0];
		node1 = graphMap[name1];

		edge->cost = cost;
		edge->nodeID.push_back( node0 );
		edge->nodeID.push_back( node1 );

		nodes[node0]->edges.push_back(edge);
		nodes[node1]->edges.push_back(edge);

		edges[i] = edge;
	}

	// input.close( );


}

void solveInputFile( const char *fileName, bool flg_show )
{
	int src_nodeID, dst_nodeID;
	int k;
	readFile( fileName, src_nodeID, dst_nodeID, k );

	solve(src_nodeID, dst_nodeID, k);
	//
	NODE *destNode = nodes[dst_nodeID];

	cout << destNode->cost << " " 
		<< destNode->total_stones << endl;
}

int main(int argc, char *argv[ ]) {
	int flg_output = false;
	// if (argc<=1) return 0;
	solveInputFile( "", flg_output );
	return 0;
}


