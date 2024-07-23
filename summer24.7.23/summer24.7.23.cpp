//赫夫曼数和赫夫曼编码
//赫夫曼树是一种带权路径长度最短的二叉树，也称为最优二叉树
//赫夫曼编码是一种变长编码，即不等长编码，赫夫曼编码是赫夫曼树的应用之一
//赫夫曼编码的特点是没有任何字符的编码是其他字符编码的前缀，所以赫夫曼编码也称为前缀编码
//赫夫曼编码的实现步骤：
//1.统计字符出现的次数
//2.构建赫夫曼树
//3.根据赫夫曼树生成赫夫曼编码
//4.根据赫夫曼编码对字符进行编码
//5.根据赫夫曼编码对编码进行解码
#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
/*树结构*/
//用数组连续存储，不会浪费空间
//用数组下标存储左右孩子、父亲结点
typedef struct
{
	int weight;
	int left;
	int right;
	int parent;
}Node, * HuffmanTree;

//存储赫夫曼编码
typedef char* HuffmanCode;
void select(HuffmanTree* T, int n, int* m1, int* m2);

/*创建赫夫曼树*/
//传入n个权重，作为哈夫曼树的n个叶子结点
void CreateHuffmanTree(HuffmanTree* T, int w[], int n)
{
	int m = 2 * n - 1;//n个叶子结点，共m个结点
	int m1, m2;//用于建立下一个结点的两结点，值为最小的两个
	*T = (HuffmanTree)malloc((m + 1) * sizeof(Node));
	//初始化前n个结点（叶子结点），权重赋值，暂时没有左右孩子与父亲
	for (int i = 1; i <= n; i++)
	{
		(*T)[i].weight = w[i];
		(*T)[i].left = 0;
		(*T)[i].right = 0;
		(*T)[i].parent = 0;
	}
	//初始化[n+1,m]个结点(非叶子结点)
	for (int i = n + 1; i <= m; i++)
	{
		(*T)[i].weight = 0;
		(*T)[i].left = 0;
		(*T)[i].right = 0;
		(*T)[i].parent = 0;
	}
	//开始建树，第i个结点的两孩子为m1,m2，权重为两孩子结点权重之和
	for (int i = n + 1; i <= m; i++)
	{
		select(T, i - 1, &m1, &m2);
		(*T)[i].left = m1;
		(*T)[i].right = m2;
		(*T)[m1].parent = i;
		(*T)[m2].parent = i;
		(*T)[i].weight = (*T)[m1].weight + (*T)[m2].weight;

		printf("%d (%d %d)\n", (*T)[i].weight, (*T)[m1].weight, (*T)[m2].weight);
	}
	printf("\n");
}

/*选取得到n个无父节点的两最小结点*/
void select(HuffmanTree* T, int n, int* m1, int* m2)
{
	int m;//存储最小值的数组下标
	//给m赋初值
	for (int i = 1; i <= n; i++)
	{
		if ((*T)[i].parent == 0)
		{
			m = i;
			break;
		}
	}
	//找到当前最小的权重（叶子结点）
	for (int i = 1; i <= n; i++)
	{
		if ((*T)[i].parent == 0 && (*T)[i].weight < (*T)[m].weight)
		{
			m = i;
		}
	}
	//先赋给m1保存一个，再去寻找第二小的值
	*m1 = m;
	for (int i = 1; i <= n; i++)
	{
		if ((*T)[i].parent == 0 && i != *m1)
		{
			m = i;
			break;
		}
	}
	for (int i = 1; i <= n; i++)
	{
		if ((*T)[i].parent == 0 && i != *m1 && (*T)[i].weight < (*T)[m].weight)
		{
			m = i;
		}
	}
	//保存第二小的数
	*m2 = m;
}

/*创建哈夫曼编码*/
//从n个叶子结点到根节点逆向求解
void CreateHuffmanCode(HuffmanTree* T, HuffmanCode* C, int n)
{
	//编码长度为s-1,第s位为\0
	int s = n - 1;
	//当前结点的父节点数组下标
	int p = 0;
	//为哈夫曼编码分配空间
	C = (HuffmanCode*)malloc((n + 1) * sizeof(char*));
	//临时保存当前叶子结点的哈夫曼编码
	char* cd = (char*)malloc(n * sizeof(char));
	//最后一位为\0
	cd[n - 1] = '\0';

	for (int i = 1; i <= n; i++)
	{
		s = n - 1;
		//c指向当前结点,p指向此结点的父节点,两者交替上升，直到根节点
		for (int c = i, p = (*T)[i].parent; p != 0; c = p, p = (*T)[p].parent)
		{
			//判断此结点为父节点的左孩子还是右孩子
			if ((*T)[p].left == c)
				cd[--s] = '0';//左孩子就是编码0
			else
				cd[--s] = '1';//右孩子就是编码1
		}
		//为第i个编码分配空间
		C[i] = (char*)malloc((n - s) * sizeof(char));
		//将此编码赋值到整体编码中
		strcpy(C[i], &cd[s]);
	}
	//释放
	free(cd);
	//打印编码序列
	for (int i = 1; i <= n; i++)
	{
		printf("%d %s", (*T)[i].weight, C[i]);
		printf("\n");
	}
}

int main()
{
	HuffmanTree T;
	HuffmanCode C;
	int n, w1, * w;
	scanf_s("%d", &n);
	w = (int*)malloc((n + 1) * sizeof(int));
	for (int i = 1; i <= n; i++)
	{
		scanf_s("%d", &w1);
		w[i] = w1;
	}
	printf("\n");
	CreateHuffmanTree(&T, w, n);
	CreateHuffmanCode(&T, &C, n);
	return 0;
}