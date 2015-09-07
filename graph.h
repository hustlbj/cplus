//:graph.h
#ifndef _MYGRAPH_H
#define _MYGRAPH_H

#define MAX_LINE 1024

typedef int Vertex; 

enum color 
{
	WHITE,
	GRAY,
	BLACK, 
};
struct AdjacentNode
{
	Vertex v;
	AdjacentNode * next;
};
typedef struct AdjacentNode * AdjacentList;

/*				adjacentList
TableEntry[0]->Vertex->Vertex->Vertex
TableEntry[1]->Vertex
TableEntry[2]->Vertex->Vertex

*/
struct TableEntry
{
	color know; //是否被发现，WHITE未发现，GRAY第一次访问，BLACK第二次访问
	int dist; //距启起点的距离
	AdjacentList adjacentList; //这个顶点的邻接顶点
	Vertex path; //保存这个节点的前一个节点，在发现的路径中
};
typedef struct TableEntry* AdjacentTable; 

#endif