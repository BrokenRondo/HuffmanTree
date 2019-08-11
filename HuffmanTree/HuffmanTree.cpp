#include "HuffmanTree.h"
#include <queue>
#include <stack>
#include <fstream>
#include <iomanip>
#include <math.h>

bool operator>(const Node &a, const Node &b)
{
	if (a.weight > b.weight) return true;
	else
	{
		return false;
	}
}
bool operator<(const Node &a, Node &b)
{
	if (a.weight < b.weight)return true;
	return false;
}

bool Greatorsort(Node* a, Node* b) {
	return a->weight > b->weight;
}

void HuffmanTree::init()
{
	//先完成需要进行哈夫曼树构造的结点的初始化
	//cout << "请输入信源符号个数:";
	//cin >> q;
	q = sourcecount;
	Q = q;
	/*cout << "请输入n元霍夫曼编码的n：";
	cin >> n;*/
	//别忘了如果不符合公式，要添加空结点,

	while ((q - n) % (n - 1) != 0) q++;
	cout << "请输入信源符号和对应的概率：" << endl;
	cout << "从文件读取：";
	ifstream fin("e:/frequence.txt");
	for (int i = 0; i < Q; i++)
	{
		Node* newNode = new Node(n);
		fin >> newNode->symbol >> newNode->weight;
		nodeset.push_back(newNode);
	}
	if (Q != q)//添加空结点
	{
		for (int i = Q; i<q; i++)
		{
			string t = "null" + std::to_string(i + 1);//因为书上是从s1开始的，下标从0开始
			Node* nullNode = new Node(n);
			nullNode->symbol = t; nullNode->weight = 0;
			nodeset.push_back(nullNode);
		}
	}
	sort(nodeset.begin(), nodeset.end(), Greatorsort);
}
Node* HuffmanTree::Add(vector<Node *>t)
{
	Node* newNode = new Node(n);
	//因为是n元哈夫曼树，所以应该是n个结点组成一个新结点，即新结点的孩子有n个
	newNode->symbol = "tNode";
	for (int i = 0; i < n; i++)
	{
		newNode->weight += t[i]->weight;
	}
	//下一步要把孩子指针数组构建好，在构建之前vector必须已经排好序了,为了防止没有排序再排序一次
	sort(t.begin(), t.end(), Greatorsort);
	for (int i = 0; i < n; i++)
	{
		newNode->childs[i] = t[i];
	}
	newNode->showChild();
	return newNode;
}

void HuffmanTree::buildHaffmanTree()
{
	//从集合中选取n个权值（概率）最小的结点，然后将他们组成新的结点，随后将这n个结点删除，并将新结点添加进集合，直到只剩下最后一个，这个就是根节点
	while (nodeset.size() != 1)
	{
		vector<Node*>tempvector;
		for (int i = 0; i<n; i++)
		{
			int j = nodeset.size() - n + i;//选中后n个中的第一个
			tempvector.push_back(nodeset[j]);
		}
		//然后删掉后n个
		for (int i = 0; i<n; i++)
		{
			nodeset.pop_back();
		}
		Node* newNode = Add(tempvector);
		//插入指定的位置
		/*int weight = newNode->weight;*/
		int i = 0;
		/*bool tag = nodeset[i] > newNode;
		bool tag1 = i < nodeset.size();*/
		while (nodeset.size()>0 && nodeset[i]->weight>newNode->weight && (i<nodeset.size() - 1))//如果size已经为0，此时已经到最后一步，nodeset已经清空，新结点还没有加入，size为0，如果不判断size将会访问nodeset[0]，越界.一定要放在第一个判断
		{
			i++;
		}
		if (i == nodeset.size() - 1)
		{
			nodeset.push_back(newNode);//如果是要插入在最后面，应该用push_back，因为instert（）是插入第i个下标前面，如果是最后一个i就会越界
		}
		else
		{
			nodeset.insert(nodeset.begin() + i, newNode);
		}//0的时候会不会出问题？要试一下--嗯0出问题了
	}
	root = nodeset[0];
}
void HuffmanTree::travel(Node* pNode)
{
	
	stack<Node*>stack;
	stack.push(pNode);
	Node *lpNode;

	while (!stack.empty())
	{
		lpNode = stack.top();
		stack.pop();

		//Deal();
		//处理遍历输出的函数
		cout.setf(ios::left);
		cout <<setw(10)<< lpNode->symbol << " " <<setw(10)<< lpNode->weight<<" " << "编码:";
		for (int i = 0; i < lpNode->encode.size(); i++)
		{
			cout <<setw(1)<< lpNode->encode[i];
		}
		cout << endl;
		for (int i = n-1; i >=0; i--)
		{
			if(lpNode->childs[i])
			stack.push(lpNode->childs[i]);
		}
	}
}
void HuffmanTree::encode(Node* pNode)
{
	stack<Node*>nodestack;
	stack<string>ecdstack;
	nodestack.push(pNode);
	Node *lpNode;

	while (!nodestack.empty())
	{
		lpNode = nodestack.top();
		nodestack.pop();

		//Deal();
		//处理的函数
		
		int j = 0;
		for (int i = n - 1; i >= 0; i--)
		{
			if (lpNode->childs[i]) {
				
				//要先把父节点的编码拷进去
				for (int k=0;k<lpNode->encode.size();k++)
				{
					//lpNode->childs[i]->encode[k].append(lpNode->encode[k]);
					lpNode->childs[i]->encode.push_back(lpNode->encode[k]);
				}
				lpNode->childs[i]->encode.push_back(std::to_string(i));
				nodestack.push(lpNode->childs[i]);
			}
			j++;
		}
	}
}
void HuffmanTree::setCodeRules(Node* pNode)
{
	stack<Node*>stack;
	stack.push(pNode);
	Node *lpNode;

	while (!stack.empty())
	{
		lpNode = stack.top();
		stack.pop();

		//Deal();
		//处理遍历输出的函数
		//cout << setw(10) << lpNode->symbol << " " << setw(10) << lpNode->weight << " " << "编码:";
		Code *code = new Code();
		if (lpNode->symbol!="tNode")//如果是tNode就不需要添加进去
		{
			code->symbol = atoi(lpNode->symbol.c_str());//将string转成int，因为在Code中符号是int，也是为了在解码的时候可以直接从int转化
			for (int i = 0; i < lpNode->encode.size(); i++)
			{
				code->code.append(lpNode->encode[i]);
			}
			code->weight = lpNode->weight;
			coderule.push_back(code);
		}

		for (int i = n - 1; i >= 0; i--)
		{
			if (lpNode->childs[i])
				stack.push(lpNode->childs[i]);
		}
	}
	cout << "编码构造成功！" << endl;
}
void HuffmanTree::readBMP()
{
	cout << "正在读取图片......"<<endl;
	GdiplusStartupInput gdiplusstartupinput;
	ULONG_PTR gdiplustoken;
	GdiplusStartup(&gdiplustoken, &gdiplusstartupinput, nullptr);

	wstring infilename(L"e:/xxl/read.bmp");
	string outfilename("e:/xxl/color.txt");

	//读图片
	Bitmap* bmp = new Bitmap(infilename.c_str());
	height = bmp->GetHeight();
	width = bmp->GetWidth();
	cout << "width " << width << ", height " << height << endl;

	Color color;
	ofstream fout(outfilename.c_str());

	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
		{
			bmp->GetPixel(x, y, &color);
			fout << x << " " << y << " "
				<< (int)color.GetRed() <<
				/*<< (int)color.GetGreen() << ";"
				<< (int)color.GetBlue() << */endl;//因为读取的时候灰度图像，所以RGB三个分量是一样的
		}
	string outfilename1("e:/xxl/pixel.txt");
	ofstream fout1(outfilename1.c_str());
	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
		{
			bmp->GetPixel(x, y, &color);
			fout1 << (int)color.GetRed() << " ";//直接写进像素
		}

	fout.close();
	fout1.close();

	delete bmp;
	GdiplusShutdown(gdiplustoken);
	cout << "图片像素输出完成！" << endl;
	return ;
}
int HuffmanTree::find(int c)
{
	
	for (int i = 0; i < List.size(); i++)
	{
		if (c == List[i]->symbol)
		{
			return i;
		}
	}
	return -1;
	
}
void HuffmanTree::culculateFrequency()
{
	ifstream fin;
	ofstream fout;
	string temp = "e:/xxl/pixel.txt";
	fin.open(temp.c_str(), ios::in);
	fout.open("e:/xxl/frequence.txt");
	int c = 0;
	cout << "开始统计频率......" << endl;
	while (!fin.eof())
	{
		fin >> c;
		int t = find(c);
		if (t != -1)
		{
			List[t]->frequence++;
		}
		else
		{
			MessageSource *msgs = new MessageSource;
			msgs->frequence = 1;
			msgs->symbol = c;
			List.push_back(msgs);
			sourcecount++;
		}
	}
	for (int i = 0; i < List.size(); i++)
	{
		fout << List[i]->symbol << " " << List[i]->frequence << endl;
	}
	fin.close();
	fout.close();
	cout << "频率统计完成！" << endl;
}
string HuffmanTree::findCode(int c)
{
	for (int i = 0; i < coderule.size(); i++)
	{
		if (coderule[i]->symbol == c)
			return coderule[i]->code;
		else if (c==-1)
		{
			return "";
		}
	}
	return "";
}
void HuffmanTree::EncodeBMP()
{
	cout << "正在进行编码......" << endl;
	ifstream fin("e:/xxl/pixel.txt");
	ofstream fout("e:/xxl/encode.txt");
	while (!fin.eof())
	{
		int c = -1;
		fin >> c;
		string s = findCode(c);
		fout << s;
	}
	cout << "编码完成！" << endl;
}
bool HuffmanTree::isLeaf(Node* p)
{
	bool flag = true;
	for (int i = 0; i < n; i++)
	{
		if (p->childs[i]!=NULL)
		{
			flag = false;
		}
	}
	return flag;
}
void HuffmanTree::decode(Node* p)
{
	cout << "开始解码......";
	ifstream fin("e:/xxl/encode.txt");
	ofstream fout("e:/xxl/decode.txt");
	string temp;//这个string用来存放还没有解码之前扫描过的字符串
	int i = 0;
	//int j = 0;
	while (!fin.eof() && i < height*width)
	{
		char s;
		fin >> s;
		temp += s;
		int t = (int)(s - 0x30);//码元不能超过9，不然就会出错
		p = p->childs[t];
		if (isLeaf(p))
		{
			fout << p->symbol<<" ";
			temp = "";
			i++; //j++;
			/*if (j==width)
			{
				fout << "\n";
				j = 0;
			}*/
			p = root;
		}
	}cout << i;
	cout << "解码完成！";
	fin.close();
	fout.close();
}
void HuffmanTree::avglong()
{
	unsigned long int sum = root->weight;
	for (int i=0;i<sourcecount;i++)//sourcecount个信源
	{
		double gailv = ((double)coderule[i]->weight) / (double)sum;
		avglength += gailv * coderule[i]->code.size();
	}
	cout << "平均码长为:" << avglength << endl;
}
void HuffmanTree::InformationEntropy()
{
	unsigned long int sum = root->weight;
	
	for (int i=0;i<coderule.size();i++)
	{
		Entropy +=-((double)coderule[i]->weight / (double)sum)*(log10((double)coderule[i]->weight / (double)sum)/log10((double)2));//-p(ai)*（logp(ai)）
	}
	cout << "信源熵为:" << Entropy << endl;
	cout << "编码效率=" << Entropy / avglength*100 << '%' << endl;
}