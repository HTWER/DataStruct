#ifndef __SEQLIST_H__
#define __SEQLIST_H__

#include <iostream>
using namespace std;

template<class DataType>
struct node
{
	int freq;					//����ʹ��Ƶ��
	DataType data;				//ʵ������
};

const int MaxSize = 100;		//�������󳤶�,������0�ŵĿ�λ��

//�û�ʹ��ʱ�������±��1��ʼ��ʵ������Ҳ���±�1��ʼ��
//���ݻ��Զ�����ʹ��Ƶ����������
//��ʹ��Ƶ�ʵ��������鲻��ʹ���۰���ҷ�����Ϊʹ���۰���ҵ�ǰ���ǣ����ݰ���ĳ����������������������Ȼʹ������Ƶ�ʽ��������򣬵��ǲ���һ�����ݵ�ʱ�������֪��Ƶ�ʣ�

template<class DataType>
class FreqArray
{
public:
	FreqArray();
	FreqArray(DataType a[], int n);
	~FreqArray(){}

	int Length(){ return length; }
	void PrintList();

	DataType Get(int i);			//�����±����,�±���Զ�����������������Ե�ûʲô������
	void Insert(int i, DataType x);
	DataType Delete(int i);

	//���µ����򷵻��˰�Ƶ���������±�
	int Locate(DataType x);			//��ͨ�ķ����������ݲ���
	int SeqSearch(DataType k);		//������ң������ݲ���

	//	int BinSearch(DataType k);  //�ݹ���۰���ҷ�
	//	void ArraySort();			//������������ߣ���0�����м䣬�����������ұ�,�������鱾��ͻᰴ��ʹ��Ƶ���������������û���κ�����	

private:
	node<DataType> m_data[MaxSize];
	int m_length;						//��¼����ʵ�����ݵĳ��ȣ�����ĳ���Ӧ����length+1
	int ArraySortByFreq(int i);			//��ĳ�����ݰ���ʹ��Ƶ��������ȷλ�ã�Ȼ�󷵻�λ���±ꣻÿ����������ʹ��Ƶ�ʷ����ı��Ҫ����һ��
};


template<class DataType>
FreqArray<DataType>::FreqArray()
{
	m_length = 0;
	m_data[0].freq = -1;
}

template<class DataType>
FreqArray<DataType>::FreqArray(DataType a[], int n)
{
	FreqArray<DataType>::FreqArray();
	if (n > MaxSize - 1)
		cout << "���ݹ��࣬��ʼ��ʧ��" << endl;
	else
	{
		for (int i = 1; i <= n; i++)
		{
			m_data[i].data = a[i - 1];
			m_data[i].freq = 0;
		}
		m_length = n;
	}
}

template<class DataType>
DataType FreqArray<DataType>::Get(int i)
{
	if (i<1 || i>m_length)					//���鱾��һ��
		cout << "����λ�÷Ƿ�" << endl;
	else
		return m_data[i].data;
}

template<class DataType>
int FreqArray<DataType>::Locate(DataType x)
{
	for (int i = 1; i <= m_length; i++)
		if (m_data[i].data == x)
		{
			(m_data[i].freq)++;
			return ArraySortByFreq(i);
		}
	return 0;
}

template<class DataType>
void FreqArray<DataType>::Insert(int i, DataType x)
{
	if (m_length + 1 > MaxSize - 1)
		cout << "��������ݣ���������" << endl;
	else if (i<1 || i>m_length + 1)
	{
		cout << "λ�ó��ִ���" << endl;
	}
	else
	{
		for (int j = m_length; j >= i; j--)
			m_data[j + 1].data = m_data[j].data;
		m_data[i].data = x;
		m_data[i].freq = 0;
		m_length++;
	}
}

template <class DataType>
DataType FreqArray<DataType>::Delete(int i)
{
	if (m_length == 0)
		cout << "��������" << endl;
	else if (i<1 || i>m_length)
		cout << "λ�ó��ִ���" << endl;
	else
	{
		int x = m_data[i].data;
		for (int j = i; j < m_length; j++)
			m_data[j].data = m_data[j + 1].data;
		m_length--;
		return x;
	}
}

template <class DataType>
void FreqArray<DataType>::PrintList()
{
	cout << endl;
	for (int i = 1; i <= m_length; i++)
		cout << m_data[i].data << " ";
	cout << endl;
}

template <class DataType>
int FreqArray<DataType>::SeqSearch(DataType k)
{
	for (int i = m_length; i >= 1; --i)
	{
		if (m_data[i].data == k)
		{
			(m_data[i].freq)++;
			return ArraySortByFreq(i);
		}
	}

	return 0;
}

template <class DataType>
int FreqArray<DataType>::ArraySortByFreq(int i)
{
	while (i<m_length && m_data[i].freq>m_data[i + 1].freq)
	{
		node<DataType> temp;
		temp = m_data[i];
		m_data[i] = m_data[i + 1];
		m_data[i + 1] = temp;
		i++;
	}
	return i;
}

//template <class DataType>
//void FreqArray<DataType>::ArraySort()
//{
//	//�������ƶ������
//	int index = 1;
//	for (int i = 1; i <= m_length; i++)
//	{
//		if (data[i].data < 0)
//		{
//			DataType temp = m_data[i].data;
//			m_data[i].data = m_data[index].data;
//			m_data[index].data = temp;
//			index++;
//		}
//	}
//	//��0�ƶ����м�
//	for (int i = index; i <= m_length; i++)
//	{
//		if (m_data[i].data == 0)
//		{
//			DataType temp = m_data[i].data;
//			m_data[i].data = m_data[index].data;
//			m_data[index].data = temp;
//			index++;
//		}
//	}
//}

//template <class DataType>
//int FreqArray<DataType>::BinSearch(DataType k)
//{
//	//��סҪ������,�������ݵĴ�С�������򣬵��������������Ҫ��֤ʹ��Ƶ��������ģ���ͻ
//	int low = 1;
//	int high = m_length;

//int index = 0;
//if (m_data[low] == k)
//{
//	index = low;
//}
//else if (m_data[high] == k)
//{
//	index = high;
//}
//else
//{
//	int mid;
//	while (low < high)
//	{
//		//�ж�һ�±�Եֵ
//		mid = (low + high) / 2;
//		if (k < m_data[mid].data)
//		{
//			high = mid - 1;
//			if (m_data[high].data == k)
//			{
//				index = high;
//				break;
//			}
//				
//		}
//		else if (k > m_data[mid].data)
//		{
//			low = mid + 1;
//			if (m_data[low].data == k)
//			{
//				index = low;
//				break;
//			}
//				
//		}
//		else if (k == m_data[mid].data)
//		{
//			index = mid;
//			break;
//		}
//	}
//}

//	(m_data[index].freq)++;
//return ArraySortByFreq(index);
//}

#endif