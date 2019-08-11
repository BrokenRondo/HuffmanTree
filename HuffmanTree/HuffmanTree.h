#pragma once
#ifndef _INC_HUFFMANTREE
#define _INC_HUFFMANTREE


/*n元霍夫曼编码，需要有的数据有：自身符号，自身的权值（概率），指向孩子的指针数组（如果是二元的话）直接左孩子右孩子就可以了，但是
由于是n元，无法确定n的大小，所以采用指针数组的方式，动态生成所需要的数组，在数组中由左至右依次是1孩子2孩子3孩子......
（是否需要一个往上指的指针？）还需要有自身的编码*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <windows.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")
using namespace std	;
using namespace Gdiplus;
struct MessageSource//用来表达信源符号的，第一个是信源符号，第二个是对应的频率
{
	int symbol = 0;
	unsigned int frequence = 0;
};
class Node
{
public:
	Node(int c) {
		n = c;
		childs= new Node*[n];
		for (int i = 0; i < n; i++)
		{
			childs[i] = nullptr;
		}
	}
	Node() {
		n = 2;
		childs = new Node*[n];
		for (int i = 0; i < n; i++)
		{
			childs[i] = nullptr;
		}
	}
	string symbol;
	unsigned long int weight = 0;//权值
	Node** childs;
	vector<string>encode;
	void showChild() {
		for (int i=0;i<4;i++)
		{
			childshow[i] = *(childs + i);//只是用来显示用
		}
	}
private:
	int n=2;
	Node* childshow[4];//只是用来显示用
};

//操作符重载，为了实现两个节点的比较
bool operator>(const Node &a, const Node &b);
bool operator<(const Node &a, Node &b);

/*如果是n元哈夫曼树，如果把这n个结点全部传入Add函数？如果用一个个传参的方法肯定不行，必须得重载两个Node相加直到n个Node相加的函数
可以把这些结点放入一个vector，然后依次把这些结点加起来，同时把孩子指针指向他们。为了方便孩子从左到右的顺序，在放入vector时就应该从
大到小的顺序排好，这里写一个降序排序的方法，将vector排序，这个函数用在sort中，使用方法sort(a.begin(),a.end(),Greatorsort)*/
bool Greatorsort(Node* a, Node* b);

class Code
{
public:
	Code() {};
	~Code() {};

	int symbol;
	string code;
	unsigned long int weight = 0;
};


class HuffmanTree//n元霍夫曼编码，需要有的数据有：自身的权值（概率），指向孩子的指针数组（如果是二元的话）
{
public:
	HuffmanTree(int c) {
		n = c;
	}
	HuffmanTree() {
		n = 2;
	}
	
	
public:
	/*一个集合T，用来存放结点，包括新组成的结点*/
	vector<Node*>nodeset;
	Node* root;//根节点
	void init();
	void buildHaffmanTree();
	Node* Add(vector<Node *>t);//在Add之前要把需要相加的结点放入vector中
	void travel(Node* p);
	void encode(Node* p);
	vector<Code*>coderule;
	void setCodeRules(Node* pNode); 
	void readBMP();
	void culculateFrequency();
	vector<MessageSource*>List;//用来储存信源和对应的频率（频数），比如255 200
	int find(int c);//用来查找c这个信源有没有统计过，如果有频率+1，如果没有就新建
	void EncodeBMP();
	string findCode(int c);
	UINT height = 0;//图片高度和宽度
	UINT width = 0;
	int sourcecount = 0;
	bool isLeaf(Node* p);//用来判断某个结点是不是叶子节点，如果是叶子结点则说明可以解码，如果不是则继续
	void decode(Node* p);
	void avglong();//平均码长
	double avglength = 0;
	void InformationEntropy();//求信息熵的函数
	double Entropy = 0;
private:
	int n=2;
	int q;
	int Q;
	int θ;
	
};
#endif // !1