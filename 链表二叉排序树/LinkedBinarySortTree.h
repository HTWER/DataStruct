#ifndef __LINKEDBINARYSORTTREE_H__
#define __LINKEDBINARYSORTTREE_H__

//链表形式的二叉排序树(LinkedBinarySortTree)

#include <iostream>
#include "../循环队列/CirQueue.h"
#include "../空间共享栈/SpaceSharedStake.h"
using namespace std;

template <class DataType>
struct TreeNode
{
	DataType data;
	TreeNode<DataType> * lchild, *rchild;
};

//非递归遍历时使用,用于记录递归状态
template <class DataType>
struct State
{
	TreeNode<DataType> * ptr;
	int flag;
};

//二叉树：链表+满足左小右大
//数据不可重复
template <class DataType>
class LinkedBinarySortTree
{
public:
	LinkedBinarySortTree(){ root = NULL; }
	LinkedBinarySortTree(DataType a[], int n);
	~LinkedBinarySortTree(){ Release(root); }

	//通过cin输入流来重新构建一棵树；
	//由于这样构建出来的树是没有规律的，完全由用户自定，完全不满足左小右大,和这里的设计冲突,所以注释
	//void CreateByCin(){ root = CreateByCinKernel(); }

	//增删查(改)
	void InsertBST(DataType a){ InsertBST(a, root); }
	void DeleteBST(DataType k){ DeleteBST(k, root); }
	TreeNode<DataType> * SearchBST(DataType k){ return SearchBST(k, root); }	//这里查找功能要求数据不能够重复，否则可能查找得到的结果会与预期不符；如果硬性要求数据可以重复，那么查找需要遍历整个树来返回一个数组

	//前序遍历
	void PreOrder(){ PreOrder(root); }
	void PreOrderfd(){ PreOrderfd(root); }

	//中序遍历
	void InOrder(){ InOrder(root); }
	void InOrderfd(){ InOrderfd(root); }

	//后序遍历
	void PostOrder(){ PostOrder(root); }
	void PostOrderfd(){ PostOrderfd(root); }

	//层序遍历
	void LeverOrder();

private:
	TreeNode<DataType> * root;

	//TreeNode<DataType> * CreateByCinKernel();

	void InsertBST(DataType a, TreeNode<DataType>* &root0);					//在以root0为根的子树中插入数据a
	void DeleteBST(DataType k, TreeNode<DataType> * root0);					//在以root0为根的子树中删除数据a
	TreeNode<DataType> * SearchBST(DataType k, TreeNode<DataType> * root0);		//在以root0为根的子树中查找数据k对应节点的地址
	TreeNode<DataType> * SearchBSTF(TreeNode<DataType> * tar);					//查找tar节点的父结点地址

	void PreOrder(TreeNode<DataType>* bt);
	void PreOrderfd(TreeNode<DataType>* bt);

	void InOrder(TreeNode<DataType>* bt);
	void InOrderfd(TreeNode<DataType>* bt);

	void PostOrder(TreeNode<DataType>* bt);
	void PostOrderfd(TreeNode<DataType>* bt);

	void Release(TreeNode<DataType>* bt);
};

template <class DataType>
LinkedBinarySortTree<DataType>::LinkedBinarySortTree(DataType a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		InsertBST(a[i], root);
	}
}

//按照前序创建
//需要该数据数据类型支持>>的操作
//template <class DataType>   
//TreeNode<DataType> * LinkedBinarySortTree<DataType>::CreateByCinKernel()
//{
//	DataType ch;
//	TreeNode<DataType> * bt;
//	cin >> ch;
//
//	if (ch == '#')
//		bt = NULL;
//	else
//	{
//		bt = new TreeNode < DataType > ;
//		bt->data = ch;
//		bt->lchild = CreateByCinKernel();
//		bt->rchild = CreateByCinKernel();
//	}
//
//	return bt;
//}

template <class DataType>
void LinkedBinarySortTree<DataType>::InsertBST(DataType a, TreeNode<DataType>* &root0)
{
	if (root0 == NULL)
	{
		TreeNode<DataType> * temp = new TreeNode < DataType > ;
		temp->data = a;
		temp->lchild = NULL;
		temp->rchild = NULL;

		root0 = temp;
	}
	else if (a < root0->data)
	{
		InsertBST(a, root0->lchild);
	}
	else
	{
		InsertBST(a, root0->rchild);
	}
}

template <class DataType>
void LinkedBinarySortTree<DataType>::DeleteBST(DataType k, TreeNode<DataType> * root0)
{
	//寻找p和f
	TreeNode<DataType> * p = SearchBST(k, root0);
	if (p == NULL)
	{
		cout << "该元素不存在" << endl;
		abort();
	}

	TreeNode<DataType> * f = SearchBSTF(p);

	if (p->lchild == NULL&&p->rchild == NULL)
	{
		if (f == NULL)
		{
			root = NULL;
		}
		else
		{
			if (f->lchild == p)
				f->lchild = NULL;
			else
				f->rchild = NULL;
		}

		delete p;
	}
	else if (p->lchild == NULL&&p->rchild != NULL)
	{
		if (f == NULL)
		{
			root = p->rchild;
		}
		else
		{
			if (f->lchild == p)
				f->lchild = p->rchild;
			else
				f->rchild = p->rchild;
		}

		delete p;
	}
	else if (p->lchild != NULL&&p->rchild == NULL)
	{
		if (f == NULL)
		{
			root = p->lchild;
		}
		else
		{
			if (f->lchild == p)
				f->lchild = p->lchild;
			else
				f->rchild = p->lchild;
		}

		delete p;
	}
	else
	{
		//寻找比p大的值中最小的那一个（或者 寻找比p小的值中最大的那一个）
		TreeNode<DataType>* s = p->rchild;
		while (s->lchild != NULL)
			s = s->lchild;

		//这时将p的值改成s的值
		p->data = s->data;

		//然后就可以删除s结点了
		DeleteBST(s->data, p->rchild);
	}
}

template <class DataType>
TreeNode<DataType> * LinkedBinarySortTree<DataType>::SearchBST(DataType k, TreeNode<DataType> * root0)
{
	if (root0 == NULL)
		return NULL;
	else if (k == root0->data)
		return root0;
	else if (k < root0->data)
		return SearchBST(k, root0->lchild);
	else if (k > root0->data)
		return SearchBST(k, root0->rchild);
}

//前提:tar节点一定存在,通过SearchBST得到的非空指针一定可以
template <class DataType>
TreeNode<DataType> * LinkedBinarySortTree<DataType>::SearchBSTF(TreeNode<DataType> * tar)
{
	if (tar == NULL)
	{
		cout << "该节点不存在，无法查找父节点" << endl;
		abort();
	}

	if (tar == root)
		return NULL;	//代表没有父节点

	//初始状态
	TreeNode<DataType> * f = root;

	while (f->lchild != tar&&f->rchild != tar)
	{
		if (tar->data < f->data)
			f = f->lchild;
		else
			f = f->rchild;
	}

	return f;
}


//前序遍历
template <class DataType>
void LinkedBinarySortTree<DataType>::PreOrder(TreeNode<DataType>* bt)
{
	if (bt == NULL)
		return;
	else
	{
		cout << bt->data << " ";
		PreOrder(bt->lchild);
		PreOrder(bt->rchild);
	}
}

template <class DataType>
void LinkedBinarySortTree<DataType>::PreOrderfd(TreeNode<DataType>* bt)
{
#if 0
	//最原始的写法
	SpaceSharedStack<TreeNode<DataType>*> stack;  //创建空栈
	while (!stack.Empty(1) || bt != NULL)
	{
		while (bt != NULL)					//扫描左结点，知道他为空才退出；左右结点都由它进行处理
		{
			cout << bt->data << " ";		//将当前的结点输出
			stack.Push(1, bt);				//将当前结点入栈
			bt = bt->lchild;				//前中都是先左后右，
		}									//退出之后，开始弹栈，即处理上一个结点的右孩子
		if (!stack.Empty(1))				//若栈不为空，则开始弹栈，弹出来的正好是上个结点
		{
			bt = stack.Pop(1);
			bt = bt->rchild;				//使bt指向右孩子
		}
	}
#endif
#if 1
	//用栈来模拟递归过程
	SpaceSharedStack<State<DataType>> stack;
	State<DataType> firstState;
	firstState.ptr = root;
	firstState.flag = 0;
	stack.Push(1, firstState);

	while (!stack.IsEmpty(1))
	{
		State<DataType> curState = stack.Pop(1);
		curState.flag++;
		if (curState.flag == 1)
		{
			//等下还要回来
			cout << curState.ptr->data << " ";
			stack.Push(1, curState);

			//左孩子的调用
			if (curState.ptr->lchild != NULL)
			{
				State<DataType> nextState;
				nextState.flag = 0;
				nextState.ptr = curState.ptr->lchild;
				stack.Push(1, nextState);
			}
		}
		else if (curState.flag == 2)
		{
			if (curState.ptr->rchild != NULL)
			{
				//右孩子的调用
				State<DataType> nextState;
				nextState.flag = 0;
				nextState.ptr = curState.ptr->rchild;
				stack.Push(1, nextState);
			}
		}
	}

#endif
}

//中序遍历
template <class DataType>
void LinkedBinarySortTree<DataType>::InOrder(TreeNode<DataType>* bt)
{
	if (bt == NULL)
		return;
	else
	{
		InOrder(bt->lchild);
		cout << bt->data << " ";
		InOrder(bt->rchild);
	}
}

template <class DataType>
void LinkedBinarySortTree<DataType>::InOrderfd(TreeNode<DataType>* bt)
{
#if 0
	//最原始的写法
	SpaceSharedStack<TreeNode<DataType>*> stack;  //创建空栈
	//核心
	while (stack.IsEmpty(1) != 1 || bt != NULL)
	{
		while (bt != NULL)             //扫描左结点，知道他为空才退出；左右结点都由它进行处理
		{
			stack.Push(1, bt);      //将当前结点入栈
			bt = bt->lchild;             //前中序，都是先左后右，
		}                            //退出之后，开始弹栈，即处理上一个结点的右孩子

		if (stack.IsEmpty(1) != 1)       //若栈不为空，则开始弹栈，弹出来的正好是上个结点
		{
			bt = stack.Pop(1);
			cout << bt->data << " ";       //将当前的结点输出
			bt = bt->rchild;        //使bt指向右孩子
		}
	}
#endif
#if 1
	//用栈来模拟递归
	SpaceSharedStack<State<DataType>> stack;
	State<DataType> firstState;
	firstState.ptr = root;
	firstState.flag = 0;
	stack.Push(1, firstState);

	while (!stack.IsEmpty(1))
	{
		State<DataType> curState = stack.Pop(1);
		curState.flag++;

		if (curState.flag == 1)
		{
			stack.Push(1, curState);
			if (curState.ptr->lchild != NULL)
			{
				State<DataType> nextState;
				nextState.flag = 0;
				nextState.ptr = curState.ptr->lchild;
				stack.Push(1, nextState);
			}
		}
		else if (curState.flag == 2)
		{
			cout << curState.ptr->data << " ";
			if (curState.ptr->rchild != NULL)
			{
				State<DataType> nextState;
				nextState.flag = 0;
				nextState.ptr = curState.ptr->rchild;
				stack.Push(1, nextState);
			}
		}
	}

#endif
}

//后序遍历
template <class DataType>
void LinkedBinarySortTree<DataType>::PostOrder(TreeNode<DataType>* bt)
{
	if (bt == NULL)
		return;
	else
	{
		PostOrder(bt->lchild);
		PostOrder(bt->rchild);
		cout << bt->data << " ";
	}
}

template <class DataType>
void LinkedBinarySortTree<DataType>::PostOrderfd(TreeNode<DataType>* bt)
{
#if 0
	//最原始的写法
	SpaceSharedStack<State<DataType> > stack;  //创建空栈
	State<DataType> temp;
	//核心
	while (stack.IsEmpty(1) != 1 || bt != NULL)
	{
		while (bt != NULL)             //扫描左结点，知道他为空才退出；左右结点都由它进行处理
		{
			temp.ptr = bt;
			temp.flag = 1;
			stack.Push(1, temp);      //将当前结点入栈
			bt = bt->lchild;             //无论是什么序，都是先左后右，
		}                            //退出之后，开始弹栈，即处理上一个结点的右孩子

		while (stack.IsEmpty(1) != 1 && (stack.GetTop(1)).flag == 2)        //第二次的访问   //当循环到stack为空了，这时bt也等于NULL，即完成
		{
			bt = (stack.Pop(1)).ptr;
			cout << bt->data << " ";
			bt = NULL;   //关键
		}

		//		cout << bt->data;       //将当前的结点输出

		if (stack.IsEmpty(1) != 1)       //若栈不为空，则开始弹栈，弹出来的正好是上个结点
		{
			temp = stack.Pop(1);
			bt = (temp.ptr)->rchild;    //使bt指向右孩子

			temp.flag = 2;
			stack.Push(1, temp);
		}
	}
#endif
#if 1
	SpaceSharedStack<State<DataType>> stack;
	State<DataType> firstState;
	firstState.flag = 0;
	firstState.ptr = root;
	stack.Push(1, firstState);

	while (!stack.IsEmpty(1))
	{
		State<DataType> curState = stack.Pop(1);
		curState.flag++;
		if (curState.flag == 1)
		{
			stack.Push(1, curState);
			if (curState.ptr->lchild != NULL)
			{
				State<DataType> nextState;
				nextState.flag = 0;
				nextState.ptr = curState.ptr->lchild;
				stack.Push(1, nextState);
			}
		}
		else if (curState.flag == 2)
		{
			stack.Push(1, curState);
			if (curState.ptr->rchild != NULL)
			{
				State<DataType> nextState;
				nextState.flag = 0;
				nextState.ptr = curState.ptr->rchild;
				stack.Push(1, nextState);
			}
		}
		else if (curState.flag == 3)
		{
			cout << curState.ptr->data << " ";
		}
	}

#endif
}

template <class DataType>
void LinkedBinarySortTree<DataType>::LeverOrder()			//思想：先访问的结点的孩子 要比 后访问的结点的孩子 先访问 (且左边的比右边的孩子先访问)
{
	if (root == NULL)
		return;

	CirQueue<TreeNode<DataType>*> queue;
	queue.Push(root);

	TreeNode<DataType>* temp;
	while (!queue.IsEmpty())				//队列只要不为空都可以继续出队元素；一旦为空，也证明书已经遍历玩，因为只有不再有新的孩子的时候才会慢慢变空
	{
		temp = queue.Back();
		queue.Pop();

		cout << temp->data << " ";
		if (temp->lchild != NULL)
			queue.Push(temp->lchild);
		if (temp->rchild != NULL)
			queue.Push(temp->rchild);
	}

}

template <class DataType>
void LinkedBinarySortTree<DataType>::Release(TreeNode<DataType>* bt)
{
	if (bt != NULL)
	{
		//注意顺序
		Release(bt->lchild);
		Release(bt->rchild);
		delete bt;
	}
}

#endif 