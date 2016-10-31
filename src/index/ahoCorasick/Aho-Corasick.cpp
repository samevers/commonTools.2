#include<iostream>
#include<string.h>
#include<malloc.h>
#include <map>
#include <queue>
#include "../../include/gary_common/gary_common.h"
#include "../../include/gary_common/gary_string.h"
#include "../../include/service_log.hpp"

using namespace std;

vector<string> pattern;
typedef struct node{
    //struct node *next[26];  //接收的态
	std::map<unsigned, node*> next;
    struct node *par;   //父亲节点
    struct node *fail;  //失败节点
    unsigned inputchar;
    int patterTag;    //是否为可接收态
    int patterNo;   //接收态对应的可接受模式
}*Tree,TreeNode;

/**
申请新的节点，并进行初始化
*/
TreeNode *getNewNode()
{
    int i;
    TreeNode* tnode=(TreeNode*)malloc(sizeof(TreeNode));
    tnode->fail=NULL;
    tnode->par=NULL;
    tnode->patterTag=0;
    return tnode;
}

/**
将Trie树中，root节点的分支节点，放入队列
*/
int  nodeToQueue(Tree root,queue<Tree> &myqueue)
{
    int i;
    //for (i = 0; i < 26; i++)
    for (map<unsigned, node*>::iterator iter = root->next.begin(); iter != root->next.end(); iter++)
    {
		unsigned index = iter->first;
		Tree nodeC = iter->second;
        myqueue.push(nodeC);
    }
    return 0;
}

/**
建立trie树
*/
Tree buildingTree()
{
    int i,j;
    Tree root=getNewNode();
    Tree tmp1=NULL,tmp2=NULL;
	int32_t size = pattern.size();
	cerr << "[buildingTree] size = " << size << endl;
	node *nn;
	int num = 1;
    for(i=0;i<size;i++)
    {
		cerr << "[buildingTree] i = " << num++ << endl;
        tmp1=root;
        for(j=0;j<strlen(pattern[i].c_str());j++)   ///对每个模式进行处理
        {
			cerr << "-------1" << endl;
			unsigned index = (unsigned char)pattern[i][j];
			cerr << "-------2 " << index << " " << tmp1<< endl;
			for(map<unsigned, node*>::iterator it = tmp1->next.begin(); it != tmp1->next.end(); it++)
				cerr << "::"<< it->first << "\t"<<it->second << endl;
            //if(tmp1->next[index]==NULL) ///是否已经有分支，Trie共用节点
            if(tmp1->next.find(index) == tmp1->next.end()) ///是否已经有分支，Trie共用节点
            {
				cerr << "-------3" << endl;
                tmp2=getNewNode();
				cerr << "-------4" << endl;
                tmp2->inputchar=index;
                tmp2->par=tmp1;
                tmp1->next[index]= nn;
                tmp1=tmp2;
				cerr << "-------5" << endl;
            }
            else
                tmp1=tmp1->next[index];
			cerr << "-------=========" << endl;
        }
        tmp1->patterTag=1;
        tmp1->patterNo=i;
    }
    return root;
}

/**
建立失败指针
*/
int buildingFailPath(Tree root)
{
    int i;
    unsigned inputchar;
    queue<Tree> myqueue;
    root->fail=root;
    //for(i=0;i<26;i++)   ///对root下面的第二层进行特殊处理
	// 把root 下的所有child 都放入到 queue 中。
	// 这个代码的总逻辑是：深度优先遍历
    map<unsigned, node*>::iterator iter;
	for(iter = root->next.begin(); iter != root->next.end(); iter++)   ///对root下面的第二层进行特殊处理
    {
		unsigned index = iter->first;// child 元素
        root->next[index]->fail=root;	// 为 root的child 们设置fail重指对象为 root。
        nodeToQueue(root->next[index],myqueue);	// 把root的child 的child们插入queue
    }

    Tree tmp=NULL,par=NULL;
    while(!myqueue.empty())
    {
        tmp=myqueue.front();
        myqueue.pop();
        nodeToQueue(tmp,myqueue);	// 删除当前节点，并将结点tmp的child们压入queue。深度优先遍历。

        inputchar=tmp->inputchar;	// 当前元素
        par=tmp->par;				// 当前元素的parent 结点

        node* failp = par->fail;
        while(failp != NULL)	// 对于当前元素查找重指对象，直到找到或者找到root为止。
        {
            if(failp->next.find(inputchar) != failp->next.end())
            {
                tmp->fail=failp->next[inputchar];
                break;
            }
            else
                failp=failp->fail;
		}	
		if(failp == NULL)
        {
            tmp->fail=root;
        }
    }
    return 0;
}

/**
进行多模式搜索，即搜寻AC自动机
*/
int searchAC(Tree root,char* str,int len) {
    TreeNode *tmp=root;
    int i=0;
    while(i < len)
    {
		unsigned pos = (unsigned char)str[i];
        if (tmp->next.find(pos) != tmp->next.end())
        {
            tmp=tmp->next[pos];
            if(tmp->patterTag==1)    ///如果为接收态
            {
                cout<<i-strlen(pattern[tmp->patterNo].c_str())+1<<'\t'<<tmp->patterNo<<'\t'<<pattern[tmp->patterNo]<<endl;
            }
            i++;
        }
        else
        {
            if(tmp==root)
                i++;
            else
            {
                tmp=tmp->fail;
                if(tmp->patterTag==1)    //如果为接收态
                    cout<<i-strlen(pattern[tmp->patterNo].c_str())+1<<'\t'<<tmp->patterNo<<'\t'<<pattern[tmp->patterNo]<<endl;
            }
        }
    }
    while(tmp!=root)
    {
        tmp=tmp->fail;
        if(tmp->patterTag==1)
            cout<<i-strlen(pattern[tmp->patterNo].c_str())+1<<'\t'<<tmp->patterNo<<'\t'<<pattern[tmp->patterNo]<<endl;
    }
    return 0;
}

/**
释放内存，DFS
*/
int destory(Tree tree)
{
    if(tree==NULL)
        return 0;
    queue<Tree> myqueue;
    TreeNode *tmp=NULL;

    myqueue.push(tree);
    tree=NULL;
    while(!myqueue.empty())
    {
        tmp=myqueue.front();
        myqueue.pop();

        for (int i = 0; i < 26; i++)
        {
            if(tmp->next[i]!=NULL)
                myqueue.push(tmp->next[i]);
        }
        free(tmp);
    }
    return 0;
}
int main()
{
	string dictFile = "novel.zuozhe";
	ifstream infileDict;
	int ret = spaceGary::open_f(dictFile, infileDict);
	if(ret == -1)
		return -1;
	string line;
	cerr<<"[main::%s] Begin to read file to pattern.\n"<< endl;
	while(getline(infileDict,line))
	{
		spaceGary::StringTrim(line);
		pattern.push_back(line);
	}
	infileDict.close();
	cerr<<"[main::%s] Over reading file to pattern.\n" << endl;
	//
    char a[]="美女大作战柳下挥";
	cerr<<"[main::%s] Begin to buildingTree().\n"<< endl;
    Tree root=buildingTree();   ///建立Trie树
	cerr<<"[main::%s] Over buildingTree().\nAnd to buildingFailPath()\n"<< endl;
    buildingFailPath(root); ///添加失败转移
	cerr<<"[main::%s] Over buildingFailPath().\n" << endl;
    cout<<"待匹配字符串："<<a<<endl;
    cout<<"模式"<<pattern[0]<<" "<<pattern[1]<<" "<<pattern[2]<<" "<<pattern[3]<<" "<<endl<<endl;
    cout<<"匹配结果如下："<<endl<<"位置\t"<<"编号\t"<<"模式"<<endl;
    searchAC(root,a,strlen(a)); ///搜索
    destory(root);  ///释放动态申请内存
    return 0;
}
