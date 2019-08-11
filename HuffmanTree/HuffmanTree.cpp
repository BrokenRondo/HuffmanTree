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
	//�������Ҫ���й�����������Ľ��ĳ�ʼ��
	//cout << "��������Դ���Ÿ���:";
	//cin >> q;
	q = sourcecount;
	Q = q;
	/*cout << "������nԪ�����������n��";
	cin >> n;*/
	//��������������Ϲ�ʽ��Ҫ��ӿս��,

	while ((q - n) % (n - 1) != 0) q++;
	cout << "��������Դ���źͶ�Ӧ�ĸ��ʣ�" << endl;
	cout << "���ļ���ȡ��";
	ifstream fin("e:/frequence.txt");
	for (int i = 0; i < Q; i++)
	{
		Node* newNode = new Node(n);
		fin >> newNode->symbol >> newNode->weight;
		nodeset.push_back(newNode);
	}
	if (Q != q)//��ӿս��
	{
		for (int i = Q; i<q; i++)
		{
			string t = "null" + std::to_string(i + 1);//��Ϊ�����Ǵ�s1��ʼ�ģ��±��0��ʼ
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
	//��Ϊ��nԪ��������������Ӧ����n��������һ���½�㣬���½��ĺ�����n��
	newNode->symbol = "tNode";
	for (int i = 0; i < n; i++)
	{
		newNode->weight += t[i]->weight;
	}
	//��һ��Ҫ�Ѻ���ָ�����鹹���ã��ڹ���֮ǰvector�����Ѿ��ź�����,Ϊ�˷�ֹû������������һ��
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
	//�Ӽ�����ѡȡn��Ȩֵ�����ʣ���С�Ľ�㣬Ȼ����������µĽ�㣬�����n�����ɾ���������½����ӽ����ϣ�ֱ��ֻʣ�����һ����������Ǹ��ڵ�
	while (nodeset.size() != 1)
	{
		vector<Node*>tempvector;
		for (int i = 0; i<n; i++)
		{
			int j = nodeset.size() - n + i;//ѡ�к�n���еĵ�һ��
			tempvector.push_back(nodeset[j]);
		}
		//Ȼ��ɾ����n��
		for (int i = 0; i<n; i++)
		{
			nodeset.pop_back();
		}
		Node* newNode = Add(tempvector);
		//����ָ����λ��
		/*int weight = newNode->weight;*/
		int i = 0;
		/*bool tag = nodeset[i] > newNode;
		bool tag1 = i < nodeset.size();*/
		while (nodeset.size()>0 && nodeset[i]->weight>newNode->weight && (i<nodeset.size() - 1))//���size�Ѿ�Ϊ0����ʱ�Ѿ������һ����nodeset�Ѿ���գ��½�㻹û�м��룬sizeΪ0��������ж�size�������nodeset[0]��Խ��.һ��Ҫ���ڵ�һ���ж�
		{
			i++;
		}
		if (i == nodeset.size() - 1)
		{
			nodeset.push_back(newNode);//�����Ҫ����������棬Ӧ����push_back����Ϊinstert�����ǲ����i���±�ǰ�棬��������һ��i�ͻ�Խ��
		}
		else
		{
			nodeset.insert(nodeset.begin() + i, newNode);
		}//0��ʱ��᲻������⣿Ҫ��һ��--��0��������
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
		//�����������ĺ���
		cout.setf(ios::left);
		cout <<setw(10)<< lpNode->symbol << " " <<setw(10)<< lpNode->weight<<" " << "����:";
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
		//����ĺ���
		
		int j = 0;
		for (int i = n - 1; i >= 0; i--)
		{
			if (lpNode->childs[i]) {
				
				//Ҫ�ȰѸ��ڵ�ı��뿽��ȥ
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
		//�����������ĺ���
		//cout << setw(10) << lpNode->symbol << " " << setw(10) << lpNode->weight << " " << "����:";
		Code *code = new Code();
		if (lpNode->symbol!="tNode")//�����tNode�Ͳ���Ҫ��ӽ�ȥ
		{
			code->symbol = atoi(lpNode->symbol.c_str());//��stringת��int����Ϊ��Code�з�����int��Ҳ��Ϊ���ڽ����ʱ�����ֱ�Ӵ�intת��
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
	cout << "���빹��ɹ���" << endl;
}
void HuffmanTree::readBMP()
{
	cout << "���ڶ�ȡͼƬ......"<<endl;
	GdiplusStartupInput gdiplusstartupinput;
	ULONG_PTR gdiplustoken;
	GdiplusStartup(&gdiplustoken, &gdiplusstartupinput, nullptr);

	wstring infilename(L"e:/xxl/read.bmp");
	string outfilename("e:/xxl/color.txt");

	//��ͼƬ
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
				<< (int)color.GetBlue() << */endl;//��Ϊ��ȡ��ʱ��Ҷ�ͼ������RGB����������һ����
		}
	string outfilename1("e:/xxl/pixel.txt");
	ofstream fout1(outfilename1.c_str());
	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
		{
			bmp->GetPixel(x, y, &color);
			fout1 << (int)color.GetRed() << " ";//ֱ��д������
		}

	fout.close();
	fout1.close();

	delete bmp;
	GdiplusShutdown(gdiplustoken);
	cout << "ͼƬ���������ɣ�" << endl;
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
	cout << "��ʼͳ��Ƶ��......" << endl;
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
	cout << "Ƶ��ͳ����ɣ�" << endl;
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
	cout << "���ڽ��б���......" << endl;
	ifstream fin("e:/xxl/pixel.txt");
	ofstream fout("e:/xxl/encode.txt");
	while (!fin.eof())
	{
		int c = -1;
		fin >> c;
		string s = findCode(c);
		fout << s;
	}
	cout << "������ɣ�" << endl;
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
	cout << "��ʼ����......";
	ifstream fin("e:/xxl/encode.txt");
	ofstream fout("e:/xxl/decode.txt");
	string temp;//���string������Ż�û�н���֮ǰɨ������ַ���
	int i = 0;
	//int j = 0;
	while (!fin.eof() && i < height*width)
	{
		char s;
		fin >> s;
		temp += s;
		int t = (int)(s - 0x30);//��Ԫ���ܳ���9����Ȼ�ͻ����
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
	cout << "������ɣ�";
	fin.close();
	fout.close();
}
void HuffmanTree::avglong()
{
	unsigned long int sum = root->weight;
	for (int i=0;i<sourcecount;i++)//sourcecount����Դ
	{
		double gailv = ((double)coderule[i]->weight) / (double)sum;
		avglength += gailv * coderule[i]->code.size();
	}
	cout << "ƽ���볤Ϊ:" << avglength << endl;
}
void HuffmanTree::InformationEntropy()
{
	unsigned long int sum = root->weight;
	
	for (int i=0;i<coderule.size();i++)
	{
		Entropy +=-((double)coderule[i]->weight / (double)sum)*(log10((double)coderule[i]->weight / (double)sum)/log10((double)2));//-p(ai)*��logp(ai)��
	}
	cout << "��Դ��Ϊ:" << Entropy << endl;
	cout << "����Ч��=" << Entropy / avglength*100 << '%' << endl;
}