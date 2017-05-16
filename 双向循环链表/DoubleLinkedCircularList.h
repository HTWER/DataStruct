#include <iostream>
using namespace std;

//˫��ѭ������

//�û�ʹ��ʱ���±��1��ʼ

//����ڵ�
template <class DataType>
struct Node
{
	DataType data;
	Node<DataType> * left;
	Node<DataType> * right;
};

template <class DataType>
class LinkList
{
public:
	LinkList();
	LinkList(DataType a[], int n);
	~LinkList();

	void Insert(int i, DataType x);	//��ָ��λ�ò�������
	DataType Erase(int i);			//��ɾ��λ�õ����ݷ���
	int Find(DataType x);			//ȷ������λ��
	DataType At(int i);				//��λ�û�ȡ����

	void PrintList();				//����������
	void PrintList2();				//����������

	int Length();					//��ȡ������

private:
	Node<DataType> * rear;			//һ��û�����ݵĽڵ㣬һֱ��ȷ����ѭ�����У�ͳһ������ͷǿ�����Ĳ���
	int length;						//��¼��������
};

template <class DataType>
LinkList<DataType>::LinkList()
{
	rear = new Node<DataType>();
	rear->right = rear;				//������ѭ������������������ڵ�Ҫ�Լ�ָ���Լ�
	rear->left = rear;

	length = 0;
}

template <class DataType>
LinkList<DataType>::LinkList(DataType a[], int n)
{
	this->LinkList<DataType>::LinkList();		//Ϊʲô����Ҫ����д��

	for (int i = 0; i < n; ++i)
		Insert(length + 1, a[i]);
}

template <class DataType>
LinkList<DataType>::~LinkList()
{
	for (int i = 0; i < length; ++i)
		Erase(1);

	delete rear;
}

template <class DataType>
void LinkList<DataType>::Insert(int index, DataType x)
{
	if (index > length + 1)						//�����ڳ��ȵĺ�һλ����
	{
		cout << "���ݲ���ʧ��" << endl;
		abort();
	}

	Node<DataType>* p = rear;
	for (int i = 0; i < index - 1; ++i)			//��λ������λ�õ�ǰһλ
		p = p->right;
	Node<DataType>* s = new Node < DataType > ;
	s->data = x;
	s->left = p;
	s->right = p->right;
	p->right = s;
	s->right->left = s;

	++length;
}

template <class DataType>
DataType LinkList<DataType>::Erase(int index)
{
	if (length == 0)
	{
		cout << "����Ϊ�գ��޷�ɾ��" << endl;
		abort();
	}

	if (index<1 || index>length)
	{
		cout << "Խ��ɾ��" << endl;
		abort();
	}

	Node<DataType>* p = rear;
	for (int i = 0; i < index - 1; ++i)		//��λ��ɾ��λ�õ�ǰһλ
		p = p->right;
	Node<DataType>* q = p->right;
	p->right = q->right;
	q->right->left = q->left;
	DataType x = q->data;
	delete q;

	--length;

	return x;
}

template <class DataType>
int LinkList<DataType>::Find(DataType x)
{
	if (rear->right == rear)
	{
		cout << "����Ϊ�գ��޷���λ����" << endl;
		abort();
	}

	Node<DataType>* p = rear;
	for (int i = 1; i <= length; ++i)
	{
		p = p->right;
		if (p->data == x)
			return i;
	}

	return 0;
}

template <class DataType>
DataType LinkList<DataType>::At(int index)
{
	if (index > length)
	{
		cout << "Խ�����" << endl;
		abort();
	}

	Node<DataType>* p = rear;
	for (int i = 0; i < index; ++i)
		p = p->right;

	return p->data;
}

template <class DataType>
void LinkList<DataType>::PrintList()
{
	Node<DataType>* p = rear;
	for (int i = 0; i < length; ++i)
	{
		p = p->right;
		cout << p->data << " ";
	}
	cout << endl;
}

template <class DataType>
void LinkList<DataType>::PrintList2()
{
	Node<DataType>* p = rear;
	for (int i = 0; i < length; ++i)
	{
		p = p->left;
		cout << p->data << " ";
	}
	cout << endl;
}

template <class DataType>
int LinkList<DataType>::Length()
{
	return length;
}
