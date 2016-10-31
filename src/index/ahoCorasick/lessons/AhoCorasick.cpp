#include "AhoCorasick.h"
// iNumber ： 多少个词
// pLen[] 	：每个词的长度
// pattern[] : 词典
int AhoCorasick::initialize(int iNumber, const int pLen[], const char* patterns[]) {
	for (int i = 0; i != iNumber; ++i) {  //创建节点
		insert(patterns[i], pLen[i], i);	// 构建 Trie 树
	}
	fixAhoCorasick();  //填写fail指针
	return 0;
}

int AhoCorasick::release(trieNode* &p) {
	for (std::map<unsigned, trieNode*>::iterator it = p->next.begin(); it != p->next.end(); ++it) {
		release(it->second);
	}
	delete p;
	p = NULL;
	return 0;
}

int AhoCorasick::insert(const char* pattern, int pLen, int patternIndex) {
	if (pLen <= 0) return -1;  //空串不要
	trieNode* p = root;	// 初始将root结点设为parent 结点
	for (int i = 0; i != pLen; ++i) { //循环至最底部
		unsigned index = (unsigned char)pattern[i];	// 词的每个元素
		if (p->next.find(index) == p->next.end()) {	// 当前元素不在parent的child里，则
			p->next[index] = new trieNode();		// 为当前元素申请一个新的 trieNode, 并加入到parent的child 哈希列表里。
													// 因为，对于每一个新加入的词，如果无法从root的child里找到可走的path，则需要为这个词新建立一个child的path。
		}
		p = p->next[index];	// 有了child path，则将指针p 指向这个词作为新的parent结点，然后循环处理剩下的词。非root 结点的操作同理。
	}
	p->end = true;
	p->pIndex = patternIndex;
	return 0;
}

int AhoCorasick::fixAhoCorasick() {
	std::queue<trieNode*> nodeQueue;
	nodeQueue.push(root);
	while (nodeQueue.size() > 0) {
		trieNode* parent = nodeQueue.front();	// 获取 parent 结点
		nodeQueue.pop();						// 将parent 结点从queue 删除

		// 对这个parent 结点的所有child 
		// 这个过程是一个·深度优先遍历
		for (std::map<unsigned, trieNode*>::iterator it = parent->next.begin(); it != parent->next.end(); ++it) {
			unsigned index = it->first;		// child = index 
			trieNode* child = it->second;	// 下面要为 child 的 trieNode 结构赋值
			if (parent == root) {
				child->fail = root;
			} else {
				trieNode* failp = parent->fail;// 首先取出parent 结点的失败重指
				while (failp != NULL) {		   // parent 结点的失败重指存在
					if (failp->next.find(index) != failp->next.end()) {// parent 结点失败重指的结点的child 里存在当前child.
						child->fail = failp->next[index];	// 当前child 的失败重指向parent失败重指的这个child。
						break;
					}
					failp = failp->fail;	// 反之，如果parent的失败重指结点的child 里没有当前child，则继续递归地在parent的失败重指的失败重指里查找。直到递归到最后一个失败重指的parent。
				}
				if (failp == NULL) child->fail = root;	// parent结点的失败重指不存在，则把该child的失败重指定为到root结点。结束，继续下一个child。
			}
			nodeQueue.push(child);		// 把child的信息压入queue，作为新的parent。
		}  //for
	}  //while
}

/*
 *匹配子串
 *输入：搜索串str及长度sLen
 *输出：模块串下标及其在str中的位置（最末位）组成的vector
 */
int AhoCorasick::search(const char* str, int sLen, std::vector<std::pair<unsigned, int> >& result) {
	result.clear();
	trieNode* p = root;
	for (int i = 0; i != sLen; ++i) {
		unsigned index = (unsigned char)str[i];	// 当前元素 index
		if (p == root && p->next.find(index) == p->next.end() ) // 根节点孩子里找不到当前元素index, 则跳过，继续从下一个index开始查找。
			continue;

		while (p->next.find(index) == p->next.end() && p != root) {	// 当前元素不是parent的child，且parent 不为root。则，找parent的重指看看是否有结果。
			p = p->fail;
		}

		if (p == NULL || p->next.find(index) == p->next.end()) {	// 如果当前parent和其所有的重指parent都没有index 这个child
			p = root;
			continue;
		} else {	// 当前元素是parent 的child，则
			trieNode* q = p->fail;	// 找到parent的重指
			p = p->next[index];		// parent 传承到该child
		}
		trieNode *q = p;	//	该child
		while (q) {
			if (q->end) {	// 该child 在trie中是叶子结点,则首先压入result 结果中。
				result.push_back(std::make_pair(q->pIndex, i + 1));
			}
			q = q->fail;	// 找到该child的重指，继续看还有没有可以给出的结果。
		}
	}
	return 0;
}


