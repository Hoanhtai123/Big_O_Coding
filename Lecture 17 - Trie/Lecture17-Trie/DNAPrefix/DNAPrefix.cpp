#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAX 4
string DNA = "ACGT";

int getIdx(char x)
{
	if (x == 'A')
		return 0;
	if (x == 'C')
		return 1;
	if (x == 'G')
		return 2;
	if (x == 'T')
		return 3;
}

struct node {
	node *child[MAX];
	int countLeaf;
	int cnt;
};

node *newNode()
{
	node *Node = new node;
	Node->countLeaf = 0;
	Node->cnt = 0;

	for (int i = 0; i < MAX; i++)
	{
		Node->child[i] = NULL;
	}
	return Node;
}

void addWord(node *root, string s)
{
	int idx;
	node *temp = root;
	for (int i = 0; i < s.size(); i++)
	{
		idx = getIdx(s[i]);
		if (temp->child[idx] == NULL)
		{
			temp->child[idx] = newNode();
		}
		temp = temp->child[idx];
		temp->cnt++;
	}
	temp->countLeaf++;
}

int findWord(node *root, string s)
{
	int ch;
	node *temp = root;
	for (int i = 0; i < s.size(); i++)
	{
		ch = s[i] - 'A';
		if (temp->child[ch] == NULL)
		{
			return 0;
		}
		temp = temp->child[ch];
	}
	return temp->cnt;

}

int findMax(node *root, int lvl)
{
	node *temp = root;
	int res = lvl*temp->cnt;

	for (int i = 0; i < 4; i++)
	{
		if (temp->child[i] != NULL)
		{
			res = max(res, findMax(temp->child[i], lvl + 1));
		}
		
	}
	return res;
}

bool isWord(node *pNode)
{
	return (pNode->countLeaf != 0);
}

bool isEmpty(node *pNode)
{
	for (int i = 0; i < MAX; i++)
	{
		if (pNode->child[i] != NULL)
		{
			return false;
		}
	}
	return true;
}

bool removeWord(node *root, string s, int level, int len)
{
	if (!root)
		return false;

	int ch = s[level] - 'A';
	if (level == len)
	{
		if (root->countLeaf > 0)
		{
			root->countLeaf--;
			return true;
		}
		return false;
	}

	int flag = removeWord(root->child[ch], s, level + 1, len);
	if (flag && !isWord(root->child[ch]) && isEmpty(root->child[ch]))
	{
		delete root->child[ch];
		root->child[ch] = NULL;
	}
	return flag;
}

void deletenode(node *pNode)
{
	for (int i = 0; i<MAX; i++)
	{
		if (pNode->child[i])
		{
			deletenode(pNode->child[i]);
			delete pNode->child[i];
		}
	}
}

int main()
{
	freopen("INPUT.INP", "rt", stdin);
	int T, n, count = 1;
	string str;

	cin >> T;

	for (int t = 0; t < T; t++)
	{
		cout << "Case " << count++ << ": ";
		node *root = newNode();

		cin >> n;
		for (int i = 0; i < n; i++)
		{
			cin >> str;
			addWord(root, str);
		}

		int max = findMax(root, 0);
		cout << max << endl;
		deletenode(root);
	}

	return 0;
}
