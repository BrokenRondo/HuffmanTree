#include <iostream>
#include "HuffmanTree.h"
#include "writebmp.h"
using namespace std;

int main()
{
	cout << "请输入是多少元哈夫曼编码：";
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
	cout << "是否解码讲解码的文件写入图片？Y或y确定：";
	char y; cin >> y;
	if (y=='y'||y=='Y')
	{
		writebmp(hfmtree->height, hfmtree->width);
	}
	system("pause");
	return 0;
}