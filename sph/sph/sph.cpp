// sph.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Edges.h"
#include "Nodes.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

Edges edge[100];  //边
Nodes node[100];  //点
int goal[100];    //目标点
int E;            //边数
int DD;           //点数
int T;            //目标点数
int dist[100];    //从顶点到原点的距离
int pre[100];     //从顶点到原点的路径上顶点的前驱顶点
int l[100];       //表l：记录前置顶点不为0的顶点
int load[100][100];     //记录路径

						//从文件1.txt中间读取数据
void read()
{
	ifstream file("1.txt");

	string str;

	int a, b, v;
	int i = 0;
	int j = 0;
	int k = 0;
	while (file >> str)
	{
		//读入数据分别为点、边、目标点的情况
		if (str == "E")
		{
			file >> str;
			a = atoi(str.c_str());//str2int
			edge[i].write_a(a);
			file >> str;
			b = atoi(str.c_str());
			edge[i].write_b(b);
			file >> str;
			v = atoi(str.c_str());
			edge[i].write_value(v);
			edge[i].write_num(i);
			i++;
		}
		if (str == "DD")
		{
			file >> str;
			b = atoi(str.c_str());
			node[k].write_num(b);
			file >> str;
			b = atoi(str.c_str());
			node[k].write_x(b);
			file >> str;
			b = atoi(str.c_str());
			node[k].write_y(b);
			k++;
		}
		if (str == "T")
		{
			file >> str;
			goal[j] = atoi(str.c_str());
			j++;
		}
		//读入数据分别为点、边、目标点的个数
		if (str == "Nodes")
		{
			file >> str;
			DD = atoi(str.c_str());
		}
		if (str == "Edges")
		{
			file >> str;
			E = atoi(str.c_str());
		}
		if (str == "Terminals")
		{
			file >> str;
			file >> str;
			T = atoi(str.c_str());
		}
	}

	file.close();
}

void Dijkstra(int first)
{
	//cout << "1" << endl;
	//距离初始化
	l[0] = DD;      //l[0]记录表l点的个数
	for (int i = 1; i <= DD; i++)
	{
		for (int k = 1; k <= DD; k++)
		{
			load[i][k] = 0;
		}
		dist[i] = 99999999;
		pre[i] = 0;
	}
	//读入与源点first相连的点的数据进dist与pre
	for (int i = 0; i < E; i++)
	{
		if (first == edge[i].reada())
		{
			dist[edge[i].readb()] = edge[i].readvalue();
			pre[edge[i].readb()] = first;  //此处若用prev数组和VS2010的std::prev()函数同名了会报错

		}
		if (first == edge[i].readb())
		{
			dist[edge[i].reada()] = edge[i].readvalue();
			pre[edge[i].reada()] = first;
		}
	}
	dist[first] = 0;
	pre[first] = first;
	//初始化表l
	for (int k = 1; k <= DD; k++)
	{
		l[k] = 1;
	}
	l[first] = 0;
	l[0]--;
	//求出最短路径
	for (;;)
	{
		//选出dist中间距离最小的距离mind,顶点v
		if (l[0] > 0)   //表l非空
		{
			int v = 0;
			int mind = 99999999;

			for (int i = 1; i <= DD; i++)
			{
				if (dist[i] < mind && l[i] == 1)
				{
					mind = dist[i];
					v = i;
				}
			}
			l[v] = 0;
			l[0]--;
			//以顶点v把dist表更新
			for (int i = 0; i < E; i++)
			{
				if (v == edge[i].reada())
				{
					if (dist[edge[i].readb()] >(edge[i].readvalue() + dist[v]))
					{
						dist[edge[i].readb()] = (edge[i].readvalue() + dist[v]);
						pre[edge[i].readb()] = v;
					}
				}
				if (v == edge[i].readb())
				{
					if (dist[edge[i].reada()] > (edge[i].readvalue() + dist[v]))
					{
						dist[edge[i].reada()] = (edge[i].readvalue() + dist[v]);
						pre[edge[i].reada()] = v;
					}
				}
			}
		}
		else
			break;
	}
	//导出路径
	int aload = 0;
	int j = 1;

	for (int i = 1; i <= DD; i++)
	{
		if (pre[i] != 0)
		{
			aload = pre[i];
			load[i][j] = aload;
			j++;
			for (;;)
			{
				if (aload != first)
				{
					aload = pre[aload];
					load[i][j] = aload;
					j++;
				}
				else
				{
					load[i][0] = i;
					j = 1;
					break;
				}
		}
		}
	}
}

int main()
{
	read();
	int s[100]; //记录加入的点
	int goal2[100];//记录goal是否进入s点集
	int fdis[100];
	int fload[100][100];
	int t;
	int minv;
	int mind = 99999999;
	int first;

	t = T;
	std::cin >> first;
	s[first] = 1;
	goal2[first] = 1;

	for (int i = 0; i <= DD; i++)
		fdis[i] = 99999999;

	for (;;)
	{
		if (t > 0)
		{
			t = T;
			mind = 99999999;
			//所有点到目标点的距离
			for (int i = 1; i <= DD; i++)
			{
				if (s[i] == 1)
				{
					Dijkstra(i);
					//利用新的dist的数据对fdis的数据进行更新
					for (int j = 1; j <= DD; j++)
					{
						if (dist[j] < fdis[j] && dist[j] != 0 && s[j] != 1)
						{
							fdis[j] = dist[j];
							for (int k = 0; k <= DD; k++)
							{
								fload[j][k] = load[j][k];
								if (fload[j][k] == 0)
									break;
							}
						}
						
					}
				}
			}
			fdis[first] = 0;
			//找出最小的点（目标点中）
			for (int i = 1; i <= DD; i++)
			{
				for (int j = 0; j < T; j++)
				{
					if (mind > fdis[i] && i == goal[j] && goal2[i] != 1)//这点距离小，在目标点中间，且未进入点集s
					{
						mind = fdis[i];
						minv = i;
					}
				}
			}
			
			//找出的点加入点集s
			goal2[minv] = 1;
			for (int i = 0; i <= DD; i++)
			{
				if (fload[minv][i] > 0)
					s[fload[minv][i]] = 1;
				else
					break;
			}
			for (int i = 1; i <= DD; i++)
			{
				if (1 == goal2[i])
					t--;
			}
		}
		else
			break;
	}
	fload[first][0] = first;//把源点的路径加入
	fload[first][1] = first;

	for (int i = 1; i <= DD; i++)
	{
		cout <<"到第"<< i << "点的路径： ";
		for (int k = 0; k <= DD; k++)
		{
			if (fload[i][k] <= 0)
				break;
			else
				cout << fload[i][k] << "  ";
		}
		cout << endl;
	}
	
	int k;
	cin >> k;
	
	return 0;
}
