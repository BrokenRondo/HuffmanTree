#include <iostream>
#include "HuffmanTree.h"
#include "writebmp.h"
using namespace std;

int main()
{
	cout << "�������Ƕ���Ԫ���������룺";
	int c = 0;
	cin >> c;
	HuffmanTree *hfmtree = new HuffmanTree(c);
	hfmtree->readBMP();
	hfmtree->culculateFrequency();
	hfmtree->init();
	hfmtree->buildHaffmanTree();
	hfmtree->encode(hfmtree->root);
	hfmtree->travel(hfmtree->root);
	hfmtree->setCodeRules(hfmtree->root);
	hfmtree->EncodeBMP();
	hfmtree->decode(hfmtree->root);
	hfmtree->avglong();
	hfmtree->InformationEntropy();
	cout << "�Ƿ���뽲������ļ�д��ͼƬ��Y��yȷ����";
	char y; cin >> y;
	if (y=='y'||y=='Y')
	{
		writebmp(hfmtree->height, hfmtree->width);
	}
	system("pause");
	return 0;
}