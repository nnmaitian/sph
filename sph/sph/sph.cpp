// sph.cpp: �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Edges.h"
#include "Nodes.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

Edges edge[100];  //��
Nodes node[100];  //��
int goal[100];    //Ŀ���
int E;            //����
int DD;           //����
int T;            //Ŀ�����
int dist[100];    //�Ӷ��㵽ԭ��ľ���
int pre[100];     //�Ӷ��㵽ԭ���·���϶����ǰ������
int l[100];       //��l����¼ǰ�ö��㲻Ϊ0�Ķ���
int load[100][100];     //��¼·��

						//���ļ�1.txt�м��ȡ����
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
		//�������ݷֱ�Ϊ�㡢�ߡ�Ŀ�������
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
		//�������ݷֱ�Ϊ�㡢�ߡ�Ŀ���ĸ���
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
	//�����ʼ��
	l[0] = DD;      //l[0]��¼��l��ĸ���
	for (int i = 1; i <= DD; i++)
	{
		for (int k = 1; k <= DD; k++)
		{
			load[i][k] = 0;
		}
		dist[i] = 99999999;
		pre[i] = 0;
	}
	//������Դ��first�����ĵ�����ݽ�dist��pre
	for (int i = 0; i < E; i++)
	{
		if (first == edge[i].reada())
		{
			dist[edge[i].readb()] = edge[i].readvalue();
			pre[edge[i].readb()] = first;  //�˴�����prev�����VS2010��std::prev()����ͬ���˻ᱨ��

		}
		if (first == edge[i].readb())
		{
			dist[edge[i].reada()] = edge[i].readvalue();
			pre[edge[i].reada()] = first;
		}
	}
	dist[first] = 0;
	pre[first] = first;
	//��ʼ����l
	for (int k = 1; k <= DD; k++)
	{
		l[k] = 1;
	}
	l[first] = 0;
	l[0]--;
	//������·��
	for (;;)
	{
		//ѡ��dist�м������С�ľ���mind,����v
		if (l[0] > 0)   //��l�ǿ�
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
			//�Զ���v��dist�����
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
	//����·��
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
	int s[100]; //��¼����ĵ�
	int goal2[100];//��¼goal�Ƿ����s�㼯
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
			//���е㵽Ŀ���ľ���
			for (int i = 1; i <= DD; i++)
			{
				if (s[i] == 1)
				{
					Dijkstra(i);
					//�����µ�dist�����ݶ�fdis�����ݽ��и���
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
			//�ҳ���С�ĵ㣨Ŀ����У�
			for (int i = 1; i <= DD; i++)
			{
				for (int j = 0; j < T; j++)
				{
					if (mind > fdis[i] && i == goal[j] && goal2[i] != 1)//������С����Ŀ����м䣬��δ����㼯s
					{
						mind = fdis[i];
						minv = i;
					}
				}
			}
			
			//�ҳ��ĵ����㼯s
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
	fload[first][0] = first;//��Դ���·������
	fload[first][1] = first;

	for (int i = 1; i <= DD; i++)
	{
		cout <<"����"<< i << "���·���� ";
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
