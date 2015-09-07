//:graph.c
#include "graph.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <malloc.h>
#include <limits>

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
						prev = node;
					}
					else
					{
						prev->next = node;
					}
				}
				if (entry->adjacentList != NULL)
					std::cout << entry->adjacentList->v << std::endl;
			}
			dataIn.close();
			return adjacentTable;
		}
	}
	return (AdjacentTable) NULL;
}

std::vector<Vertex> BFS(AdjacentTable adjacentTable)
{
	
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
	}
}