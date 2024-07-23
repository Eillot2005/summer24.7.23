/*
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <algorithm>
using namespace std;
//存储job
struct S {
	int val, index, ans;
}s[100001];

int sum[101];
bool cmp(struct S a, struct S b)
{
	return a.val < b.val;
}
bool cmpid(struct S a, struct S b)
{
	return a.index < b.index;
}

int main()
{
	int T, n, m, i, j, mn, mi;
	//读取数据
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d", &n, &m);
		for (i = 0; i < n; i++)
		{
			scanf("%d", &s[i].val);
			s[i].index = i;
		}
		sort(s, s + n, cmp);//排序：sort()默认是升序。如果指定compfunction的话，就采用指定函数来判定两个元素的大小。
		//给机器赋初值，no job
		for (i = 0; i < m; i++) sum[i] = 0;
		//从val大到小进行判断
		for (i = n - 1; i >= 0; i--)
		{
			mn = sum[0];
			mi = 0;
			for (j = 1; j < m; j++)
			{
				//找到工作量最小的机器，工作值赋给mn，机器号赋给mi
				if (sum[j] < mn)
				{
					mn = sum[j];
					mi = j;
				}
			}
			//给工作量最小的机器分配工作
			s[i].ans = mi;
			sum[mi] += s[i].val;
		}
		//按照index排序
		sort(s, s + n, cmpid);
		printf("%d\n", n);
		for (i = 0; i < n; i++)
		{
			if (i) printf(" ");
			printf("%d", s[i].ans);
		}
		printf("\n");
	}
}
*/


#include<stdio.h>
#include<algorithm>
using namespace std;
struct S
{
	int val, index, ans;
}s[100001];
int sum[101];
bool cmp(struct S a,struct S b)
{
	return a.val < b.val;
}
bool cmpid(struct S a,struct S b)
{
	return a.index < b.index;
}
int main()
{
	int time;
	int n, m;
    scanf_s("%d", &time);
	while (time--)
	{
		scanf_s("%d%d", &n, &m);
		for (int i = 0; i < n; i++)
		{
			scanf_s("%d", &s[i].val);
			s[i].index = i;
		}
		sort(s, s + n, cmp);
		for (int i = 0; i < m; i++)
		{
			sum[i] = 0;
		}
		for (int i = n - 1; i >= 0; i--)
		{
			int a = sum[0];
			int b = 0;
			for (int j = 1; j < m; j++)
			{
				if (a > sum[j])
				{
					a = sum[j];
					b = j;
				}
			}
			s[i].ans = b;
			sum[b] += s[i].val;
		}
		sort(s, s + n, cmpid);
		printf("%d\n", n);
		for (int i = 0; i < n; i++)
		{
            if (i) printf(" ");
            printf("%d", s[i].ans);
		}
		printf("\n");
	}
}
