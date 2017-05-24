#ifndef __LINKEDBINARYSORTTREE_H__
#define __LINKEDBINARYSORTTREE_H__

//������ʽ�Ķ���������(LinkedBinarySortTree)

#include <iostream>
#include "../ѭ������/CirQueue.h"
#include "../�ռ乲��ջ/SpaceSharedStake.h"
using namespace std;

template <class DataType>
struct TreeNode
{
	DataType data;
	TreeNode<DataType> * lchild, *rchild;
};

//�ǵݹ����ʱʹ��,���ڼ�¼�ݹ�״̬
template <class DataType>
struct State
{
	TreeNode<DataType> * ptr;
	int flag;
};

//������������+������С�Ҵ�
//���ݲ����ظ�
template <class DataType>
class LinkedBinarySortTree
{
public:
	LinkedBinarySortTree(){ root = NULL; }
	LinkedBinarySortTree(DataType a[], int n);
	~LinkedBinarySortTree(){ Release(root); }

	//ͨ��cin�����������¹���һ������
	//����������������������û�й��ɵģ���ȫ���û��Զ�����ȫ��������С�Ҵ�,���������Ƴ�ͻ,����ע��
	//void CreateByCin(){ root = CreateByCinKernel(); }

	//��ɾ��(��)
	void InsertBST(DataType a){ InsertBST(a, root); }
	void DeleteBST(DataType k){ DeleteBST(k, root); }
	TreeNode<DataType> * SearchBST(DataType k){ return SearchBST(k, root); }	//������ҹ���Ҫ�����ݲ��ܹ��ظ���������ܲ��ҵõ��Ľ������Ԥ�ڲ��������Ӳ��Ҫ�����ݿ����ظ�����ô������Ҫ����������������һ������

	//ǰ�����
	void PreOrder(){ PreOrder(root); }
	void PreOrderfd(){ PreOrderfd(root); }

	//�������
	void InOrder(){ InOrder(root); }
	void InOrderfd(){ InOrderfd(root); }

	//�������
	void PostOrder(){ PostOrder(root); }
	void PostOrderfd(){ PostOrderfd(root); }

	//�������
	void LeverOrder();

private:
	TreeNode<DataType> * root;

	//TreeNode<DataType> * CreateByCinKernel();

	void InsertBST(DataType a, TreeNode<DataType>* &root0);					//����root0Ϊ���������в�������a
	void DeleteBST(DataType k, TreeNode<DataType> * root0);					//����root0Ϊ����������ɾ������a
	TreeNode<DataType> * SearchBST(DataType k, TreeNode<DataType> * root0);		//����root0Ϊ���������в�������k��Ӧ�ڵ�ĵ�ַ
	TreeNode<DataType> * SearchBSTF(TreeNode<DataType> * tar);					//����tar�ڵ�ĸ�����ַ

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

//����ǰ�򴴽�
//��Ҫ��������������֧��>>�Ĳ���
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
	//Ѱ��p��f
	TreeNode<DataType> * p = SearchBST(k, root0);
	if (p == NULL)
	{
		cout << "��Ԫ�ز�����" << endl;
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
		//Ѱ�ұ�p���ֵ����С����һ�������� Ѱ�ұ�pС��ֵ��������һ����
		TreeNode<DataType>* s = p->rchild;
		while (s->lchild != NULL)
			s = s->lchild;

		//��ʱ��p��ֵ�ĳ�s��ֵ
		p->data = s->data;

		//Ȼ��Ϳ���ɾ��s�����
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

//ǰ��:tar�ڵ�һ������,ͨ��SearchBST�õ��ķǿ�ָ��һ������
template <class DataType>
TreeNode<DataType> * LinkedBinarySortTree<DataType>::SearchBSTF(TreeNode<DataType> * tar)
{
	if (tar == NULL)
	{
		cout << "�ýڵ㲻���ڣ��޷����Ҹ��ڵ�" << endl;
		abort();
	}

	if (tar == root)
		return NULL;	//����û�и��ڵ�

	//��ʼ״̬
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


//ǰ�����
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
	//��ԭʼ��д��
	SpaceSharedStack<TreeNode<DataType>*> stack;  //������ջ
	while (!stack.Empty(1) || bt != NULL)
	{
		while (bt != NULL)					//ɨ�����㣬֪����Ϊ�ղ��˳������ҽ�㶼�������д���
		{
			cout << bt->data << " ";		//����ǰ�Ľ�����
			stack.Push(1, bt);				//����ǰ�����ջ
			bt = bt->lchild;				//ǰ�ж���������ң�
		}									//�˳�֮�󣬿�ʼ��ջ����������һ�������Һ���
		if (!stack.Empty(1))				//��ջ��Ϊ�գ���ʼ��ջ�����������������ϸ����
		{
			bt = stack.Pop(1);
			bt = bt->rchild;				//ʹbtָ���Һ���
		}
	}
#endif
#if 1
	//��ջ��ģ��ݹ����
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
			//���»�Ҫ����
			cout << curState.ptr->data << " ";
			stack.Push(1, curState);

			//���ӵĵ���
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
				//�Һ��ӵĵ���
				State<DataType> nextState;
				nextState.flag = 0;
				nextState.ptr = curState.ptr->rchild;
				stack.Push(1, nextState);
			}
		}
	}

#endif
}

//�������
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
	//��ԭʼ��д��
	SpaceSharedStack<TreeNode<DataType>*> stack;  //������ջ
	//����
	while (stack.IsEmpty(1) != 1 || bt != NULL)
	{
		while (bt != NULL)             //ɨ�����㣬֪����Ϊ�ղ��˳������ҽ�㶼�������д���
		{
			stack.Push(1, bt);      //����ǰ�����ջ
			bt = bt->lchild;             //ǰ���򣬶���������ң�
		}                            //�˳�֮�󣬿�ʼ��ջ����������һ�������Һ���

		if (stack.IsEmpty(1) != 1)       //��ջ��Ϊ�գ���ʼ��ջ�����������������ϸ����
		{
			bt = stack.Pop(1);
			cout << bt->data << " ";       //����ǰ�Ľ�����
			bt = bt->rchild;        //ʹbtָ���Һ���
		}
	}
#endif
#if 1
	//��ջ��ģ��ݹ�
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

//�������
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
	//��ԭʼ��д��
	SpaceSharedStack<State<DataType> > stack;  //������ջ
	State<DataType> temp;
	//����
	while (stack.IsEmpty(1) != 1 || bt != NULL)
	{
		while (bt != NULL)             //ɨ�����㣬֪����Ϊ�ղ��˳������ҽ�㶼�������д���
		{
			temp.ptr = bt;
			temp.flag = 1;
			stack.Push(1, temp);      //����ǰ�����ջ
			bt = bt->lchild;             //������ʲô�򣬶���������ң�
		}                            //�˳�֮�󣬿�ʼ��ջ����������һ�������Һ���

		while (stack.IsEmpty(1) != 1 && (stack.GetTop(1)).flag == 2)        //�ڶ��εķ���   //��ѭ����stackΪ���ˣ���ʱbtҲ����NULL�������
		{
			bt = (stack.Pop(1)).ptr;
			cout << bt->data << " ";
			bt = NULL;   //�ؼ�
		}

		//		cout << bt->data;       //����ǰ�Ľ�����

		if (stack.IsEmpty(1) != 1)       //��ջ��Ϊ�գ���ʼ��ջ�����������������ϸ����
		{
			temp = stack.Pop(1);
			bt = (temp.ptr)->rchild;    //ʹbtָ���Һ���

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
void LinkedBinarySortTree<DataType>::LeverOrder()			//˼�룺�ȷ��ʵĽ��ĺ��� Ҫ�� ����ʵĽ��ĺ��� �ȷ��� (����ߵı��ұߵĺ����ȷ���)
{
	if (root == NULL)
		return;

	CirQueue<TreeNode<DataType>*> queue;
	queue.Push(root);

	TreeNode<DataType>* temp;
	while (!queue.IsEmpty())				//����ֻҪ��Ϊ�ն����Լ�������Ԫ�أ�һ��Ϊ�գ�Ҳ֤�����Ѿ������棬��Ϊֻ�в������µĺ��ӵ�ʱ��Ż��������
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
		//ע��˳��
		Release(bt->lchild);
		Release(bt->rchild);
		delete bt;
	}
}

#endif 