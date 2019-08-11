#pragma once
#ifndef _INC_HUFFMANTREE
#define _INC_HUFFMANTREE


/*nԪ���������룬��Ҫ�е������У�������ţ������Ȩֵ�����ʣ���ָ���ӵ�ָ�����飨����Ƕ�Ԫ�Ļ���ֱ�������Һ��ӾͿ����ˣ�����
������nԪ���޷�ȷ��n�Ĵ�С�����Բ���ָ������ķ�ʽ����̬��������Ҫ�����飬����������������������1����2����3����......
���Ƿ���Ҫһ������ָ��ָ�룿������Ҫ������ı���*/
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
struct MessageSource//���������Դ���ŵģ���һ������Դ���ţ��ڶ����Ƕ�Ӧ��Ƶ��
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
	unsigned long int weight = 0;//Ȩֵ
	Node** childs;
	vector<string>encode;
	void showChild() {
		for (int i=0;i<4;i++)
		{
			childshow[i] = *(childs + i);//ֻ��������ʾ��
		}
	}
private:
	int n=2;
	Node* childshow[4];//ֻ��������ʾ��
};

//���������أ�Ϊ��ʵ�������ڵ�ıȽ�
bool operator>(const Node &a, const Node &b);
bool operator<(const Node &a, Node &b);

/*�����nԪ�����������������n�����ȫ������Add�����������һ�������εķ����϶����У��������������Node���ֱ��n��Node��ӵĺ���
���԰���Щ������һ��vector��Ȼ�����ΰ���Щ����������ͬʱ�Ѻ���ָ��ָ�����ǡ�Ϊ�˷��㺢�Ӵ����ҵ�˳���ڷ���vectorʱ��Ӧ�ô�
��С��˳���źã�����дһ����������ķ�������vector���������������sort�У�ʹ�÷���sort(a.begin(),a.end(),Greatorsort)*/
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


class HuffmanTree//nԪ���������룬��Ҫ�е������У������Ȩֵ�����ʣ���ָ���ӵ�ָ�����飨����Ƕ�Ԫ�Ļ���
{
public:
	HuffmanTree(int c) {
		n = c;
	}
	HuffmanTree() {
		n = 2;
	}
	
	
public:
	/*һ������T��������Ž�㣬��������ɵĽ��*/
	vector<Node*>nodeset;
	Node* root;//���ڵ�
	void init();
	void buildHaffmanTree();
	Node* Add(vector<Node *>t);//��Add֮ǰҪ����Ҫ��ӵĽ�����vector��
	void travel(Node* p);
	void encode(Node* p);
	vector<Code*>coderule;
	void setCodeRules(Node* pNode); 
	void readBMP();
	void culculateFrequency();
	vector<MessageSource*>List;//����������Դ�Ͷ�Ӧ��Ƶ�ʣ�Ƶ����������255 200
	int find(int c);//��������c�����Դ��û��ͳ�ƹ��������Ƶ��+1�����û�о��½�
	void EncodeBMP();
	string findCode(int c);
	UINT height = 0;//ͼƬ�߶ȺͿ��
	UINT width = 0;
	int sourcecount = 0;
	bool isLeaf(Node* p);//�����ж�ĳ������ǲ���Ҷ�ӽڵ㣬�����Ҷ�ӽ����˵�����Խ��룬������������
	void decode(Node* p);
	void avglong();//ƽ���볤
	double avglength = 0;
	void InformationEntropy();//����Ϣ�صĺ���
	double Entropy = 0;
private:
	int n=2;
	int q;
	int Q;
	int ��;
	
};
#endif // !1