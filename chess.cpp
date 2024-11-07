#include<cstdio>
#include<windows.h>
#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<ctime>
using namespace std;
const int dir[8][2]={{2,1},{1,2},{-1,2},{-2,1},{-2,-1},{-1,-2},{1,-2},{2,-1}}; 
int INCREMENT=10;
int order[8][8][8];//对于每一个节点而言，他们所需要的dir方向都不一样 
int degree[8][8];
FILE *fp1,*fp2;
typedef struct Point
{
	int x;int y;int direction;
	Point(){}
	Point(int xpos,int ypos,int dir):x(xpos),y(ypos),direction(dir){} 
	Point& operator=(const Point& point1)
	{
		if (this!=&point1)
		{
			x=point1.x;
			y=point1.y;
			direction=point1.direction;
		}
		return *this;
	}
}Point;
typedef struct ValuePoint
{
	int x;
	int y;
	int value;
	int ord;
	ValuePoint(){}
	ValuePoint(int xpos,int ypos,int uvalue,int order):x(xpos),y(ypos),value(uvalue),ord(order){}
	bool operator<(const ValuePoint& point1)
	{
		return value<point1.value;
	}
}ValuePoint;
int flag[8][8];
long long num=0; 
typedef	struct
{
	int head;
	int stacksize;
	Point *stack;
	inline void InitStack()
	{
		stack=new Point[100];
		head=0;
	}	
	inline void push(Point &p)
	{
		stack[++head]=p;
	}
	inline void pop()
	{
		head--;
	} 
	inline void top(Point &p)
	{
		p=stack[head];
	}
	inline bool empty()
	{
		return head==0;
	}
	inline void change()
	{
		stack[head].direction++;
	}
}SqStack;
SqStack st;
void print()
{
	for (int i=0;i<8;i++)
	{
		for (int j=0;j<8;j++)
		{
			fprintf(fp1,"%d ",flag[i][j]);
		}
		fprintf(fp1,"\n");
	}
	fprintf(fp1,"\n");
}
bool check(int x,int y)
{
	if (x>7||x<0||y>7||y<0)return false;
	if (flag[x][y])return false;
	return true; 
}
void setorder()
{
	ValuePoint list[9];
	for (int i=0;i<8;i++)
	{
		for (int j=0;j<8;j++)
		{
			degree[i][j]=0;
			for (int type=0;type<8;type++)
			{
				if (check(i+dir[type][0],j+dir[type][1]))degree[i][j]++;
			}
		}
	}
	for (int i=0;i<8;i++)
	{
		for (int j=0;j<8;j++)
		{
			int length=0;
			for (int type=0;type<8;type++)
			{
				int x1=i+dir[type][0];
				int y1=j+dir[type][1];
				if (!check(x1,y1))continue;
				list[++length]=ValuePoint(x1,y1,degree[x1][y1],type);
			}
			sort(list+1,list+length+1);
			for (int k=0;k<length;k++)
			{
				order[i][j][k]=list[k+1].ord;
			}
		} 
	}
}
int main()
{
	LARGE_INTEGER t1,t2,tc;
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1); 
    fp1=fopen("chess.txt","w");
	int x,y;
	srand(time(0));
	x=rand()%8;
	y=rand()%8;
	setorder();
	st.InitStack() ;
	Point init=Point(x-1,y-1,0);
	st.push(init);
	flag[init.x][init.y]=1;
	int step=2;
	Point towards,head;
	int x1,y1;
	while(!st.empty())
	{
		st.top(head);
		if (step==65)
		{
			num++;
			if (num<2)print();break;
			st.pop();
			step--;
			flag[head.x][head.y]=0;
			continue;
		}
		if (head.direction>degree[head.x][head.y])
		{
			st.pop();
			step--;
			flag[head.x][head.y]=0;
			continue;
		}	
		st.change();
		x1=head.x+dir[order[head.x][head.y][head.direction]][0];
		y1=head.y+dir[order[head.x][head.y][head.direction]][1];
		if (check(x1,y1))
		{
			towards=Point(x1,y1,0);
			flag[x1][y1]=step;
			step++;
			st.push(towards);
		}
	}
	fclose(fp1);
	fp2=fopen("time.txt","w");
	QueryPerformanceCounter(&t2);
    double time=(double)(t2.QuadPart-t1.QuadPart)/(double)tc.QuadPart; 
    fprintf(fp2,"time=%lf ms",time*1000);
	fclose(fp2); 
	
}
