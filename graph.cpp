//:graph.c
#include "graph.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <malloc.h>
#include <limits>
#include <queue>
#include <stack>

//struct TableEntry* 
AdjacentTable initGraph(const char* filename)
{
	if (filename != NULL)
	{
		std::ifstream dataIn(filename);
		std::string line;
		int vertexNum;
		if (dataIn)
		{
			dataIn >> vertexNum;
			if (vertexNum <= 0)
				return (AdjacentTable) NULL;
			std::cout << "Vertex Num: " << vertexNum << std::endl;
			//0空着，从1到vertexNum个TableEntry
			AdjacentTable adjacentTable = (AdjacentTable )malloc((vertexNum + 1) * sizeof(struct TableEntry));
			int oneVertex;
			struct TableEntry * entry;
			struct AdjacentNode * prev;
			int vertexSize = sizeof(struct AdjacentNode);
			//取走第一行末尾的换行符
			//dataIn.get();
			getline(dataIn, line);
			while (getline(dataIn, line))
			{
				std::istringstream iss(line);
				std::cout << line << std::endl;
				//未做异常转换的处理，默认按文件格式按要求
				iss >> oneVertex; //读入顶点的序号
				if (iss.fail())
					break;
				prev = NULL;
				entry = adjacentTable + oneVertex;
				entry->know = WHITE;
				entry->dist = std::numeric_limits<int>::max();
				//entry->path = 0;
				//读入这个顶点的邻接链
				while (iss >> oneVertex)
				{
					if (oneVertex == 0)
					{
						entry->adjacentList = NULL;
						break;
					}
					AdjacentList node = (AdjacentList )malloc(vertexSize);
					node->v = oneVertex;
					node->next = NULL;
					if (prev == NULL)
					{
						entry->adjacentList = node;	
					}
					else
					{
						prev->next = node;
					}
					prev = node;
				}
				/*
				if (entry->adjacentList != NULL)
					std::cout << entry->adjacentList->v << std::endl;
					*/
			}
			dataIn.close();
			return adjacentTable;
		}
	}
	return (AdjacentTable) NULL;
}

int getIndex(Vertex v)
{
	return v;
}

//默认顶点0是起点，广度优先算法利用队列
/*
BFS(G,s)
    for each vertex v in V[G]
        status[v] = WHITE
    status[s] = GRAY    //s是原点
    queue q
    入队(q,s);
    while q非空
        t = 出队(q);
        for each vertex v in Adj[t] //与t邻接的点
            if status[v] = WHITE    //只对未访问的操作
                status[v] = GRAY    //标记为第一次访问
                入队(q,v)
        status[t] = BLACK   //此点已经处理完了
*/
std::vector<Vertex> BFS(AdjacentTable &adjacentTable)
{
	std::cout << "BFS function: " << std::endl;
	//不做异常判断
	std::queue<Vertex> aQueue;
	std::vector<Vertex> v;
	adjacentTable[1].know = GRAY;
	//把起始顶点加入队列
	aQueue.push((Vertex)(1));
	v.push_back((Vertex)(1));
	Vertex found;
	AdjacentList adjacent;
	int index;
	while (!aQueue.empty())
	{
		found = aQueue.front();
		aQueue.pop();
		index = getIndex(found);
		adjacent = adjacentTable[index].adjacentList;
		std::cout << "found: " << found << std::endl;
		while (adjacent != NULL)
		{
			std::cout << adjacent->v << ", " << std::flush;
			if (adjacentTable[getIndex(adjacent->v)].know == WHITE)
			{
				adjacentTable[getIndex(adjacent->v)].know = GRAY;
				v.push_back(adjacent->v);
				aQueue.push(adjacent->v);
			}
			adjacent = adjacent->next;
		}
		adjacentTable[index].know = BLACK;
		//v.push_back(found);
		std::cout << std::endl;
	}
	return v;
}

//深度优先搜索利用栈或者递归
/*
WHITE表示visited=0
GRAY表示visited=1

非递归实现
 （1）栈S初始化；visited[n]=0；
 （2）访问顶点v；visited[v]=1；顶点v入栈S
 （3）while(栈S非空)
            x=栈S的顶元素(不出栈)；
            //找到一个和x邻接的且没被访问的那个顶点，就沿着它一直走到底（w进栈）
            if(存在并找到未被访问的x的邻接点w)
                    访问w；visited[w]=1；
                    w进栈;
            else
                    x出栈；
*/
std::vector<Vertex> DFS(AdjacentTable &adjacentTable)
{
	std::cout << "DFS function: " << std::endl;
	std::stack<Vertex> aStack;
	std::vector<Vertex> v;
	//访问起始顶点
	adjacentTable[1].know = GRAY;
	aStack.push((Vertex)1);
	v.push_back((Vertex)1);

	Vertex found;
	AdjacentList adjacent;
	int flag;
	while (!aStack.empty())
	{
		found = aStack.top();
		std::cout << "found: " << found << std::endl;
		adjacent = adjacentTable[found].adjacentList;
		flag = 0;
		while (adjacent != NULL)
		{
			if (adjacentTable[adjacent->v].know == WHITE)
			{
				//访问邻接的一个未访问过的顶点
				adjacentTable[adjacent->v].know = GRAY;
				std::cout << adjacent->v << ", " << std::flush;
				v.push_back(adjacent->v);
				aStack.push(adjacent->v);
				flag = 1;
				break;
			}
			adjacent = adjacent->next;
		}
		//与之邻接的顶点都访问完了，这条路走遍了，才能移除该顶点
		if (flag == 0)
		{
			aStack.pop();
		}
		std::cout << std::endl;
	}
	return v;
}

int main(int argc, char ** argv)
{
	if (argc != 2)
	{
		std::cout << "Usage: ./a.out filepath\n" << std::endl;
		return -1;
	}
	else
	{
		AdjacentTable adjacentTable = initGraph(argv[1]);
		std::cout << (adjacentTable+1)->adjacentList->v << std::endl;
		//std::vector<Vertex> bfs_vector(BFS(adjacentTable));
		std::vector<Vertex>::iterator it;
		/*
		std::cout << "BFS: " << std::endl;
		for (it = bfs_vector.begin(); it != bfs_vector.end(); ++it)
		{
			std::cout << *it << ", " << std::flush;
		}
		std::cout << std::endl;
		*/
		std::vector<Vertex> dfs_vector(DFS(adjacentTable));
		std::cout << "DFS: " << std::endl;
		for (it = dfs_vector.begin(); it != dfs_vector.end(); ++it)
		{
			std::cout << *it << ", " << std::flush;
		}
		std::cout << std::endl;
	}
}