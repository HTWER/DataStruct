#ifndef __SEQLIST_H__
#define __SEQLIST_H__

#include <iostream>
using namespace std;

template<class DataType>
struct node
{
	int freq;					//数据使用频率
	DataType data;				//实际数据
};

const int MaxSize = 100;		//链表的最大长度,包括了0号的空位置

//用户使用时，数据下标从1开始；实际数据也从下标1开始；
//数据会自动按照使用频率升序排序
//带使用频率调整的数组不可使用折半查找法，因为使用折半查找的前提是，数据按照某种条件进行了排序；这里虽然使用了了频率进行了排序，但是查找一个数据的时候根本不知道频率；

template<class DataType>
class FreqArray
{
public:
	FreqArray();
	FreqArray(DataType a[], int n);
	~FreqArray(){}

	int Length(){ return length; }
	void PrintList();

	DataType Get(int i);			//按照下标查找,下标会自动调整，这个函数就显得没什么意义了
	void Insert(int i, DataType x);
	DataType Delete(int i);

	//以下的排序返回了按频率排序后的下标
	int Locate(DataType x);			//普通的方法，按内容查找
	int SeqSearch(DataType k);		//倒序查找，按内容查找

	//	int BinSearch(DataType k);  //递归的折半查找法
	//	void ArraySort();			//将负数放在左边，将0放在中间，将正数放在右边,由于数组本身就会按照使用频率来排序，这个函数没有任何意义	

private:
	node<DataType> m_data[MaxSize];
	int m_length;						//记录的是实际数据的长度，数组的长度应该是length+1
	int ArraySortByFreq(int i);			//对某个数据按照使用频率排序到正确位置，然后返回位置下标；每当现有数据使用频率发生改变就要调用一次
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
		cout << "数据过多，初始化失败" << endl;
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
	if (i<1 || i>m_length)					//跟书本不一样
		cout << "查找位置非法" << endl;
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
		cout << "若添加数据，将会上溢" << endl;
	else if (i<1 || i>m_length + 1)
	{
		cout << "位置出现错误" << endl;
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
		cout << "数据下溢" << endl;
	else if (i<1 || i>m_length)
		cout << "位置出现错误" << endl;
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
//	//将负数移动到左边
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
//	//将0移动到中间
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
//	//记住要先排序,按照数据的大小进行排序，但是数组的内容又要保证使用频率是升序的，冲突
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
//		//判断一下边缘值
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