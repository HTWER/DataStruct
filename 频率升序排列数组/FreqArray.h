#ifndef __SEQLIST_H__
#define __SEQLIST_H__

template<class DataType>
struct node
{
	int freq;					//����ʹ��Ƶ��
	DataType data;				//ʵ������
};

const int MaxSize = 100;		//�������󳤶�,������0���ڱ�

//0��λ�ÿճ������ڱ�����������ö���= =!!!!!!��
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
//	void ArraySort();				//������������ߣ���0�����м䣬�����������ұ�,�������鱾��ͻᰴ��ʹ��Ƶ���������������û���κ�����	

	DataType Get(int i);			//�����±����,�±���Զ�����������������Ե�ûʲô������
	void Insert(int i, DataType x);
	DataType Delete(int i);

	//���µ����򷵻��˰�Ƶ���������±�
	int Locate(DataType x);			//��ͨ�ķ����������ݲ���
	int SeqSearch(DataType k);		//���ڱ��ĵ�����ң������ݲ���
	/*	int BinSearch(DataType k);  //�ݹ���۰���ҷ�*/

private:
	node<DataType> data[MaxSize];
	int length;						//��¼����ʵ�����ݵĳ��ȣ�����ĳ���Ӧ����length+1
	int ArraySortByFreq(int i);		//��ĳ�����ݰ���ʹ��Ƶ��������ȷλ�ã�Ȼ�󷵻�λ���±ꣻÿ����������ʹ��Ƶ�ʷ����ı��Ҫ����һ��
};


template<class DataType>
FreqArray<DataType>::FreqArray()
{
	length = 0;
	data[0].freq = -1;
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
			data[i].data = a[i - 1];
			data[i].freq = 0;
		}
		length = n;
	}
}

template<class DataType>
DataType FreqArray<DataType>::Get(int i)
{
	if (i<1 || i>length)					//���鱾��һ��
		cout << "����λ�÷Ƿ�" << endl;
	else
		return data[i].data;
}

template<class DataType>
int FreqArray<DataType>::Locate(DataType x)
{
	for (int i = 1; i <= length; i++)
		if (data[i].data == x)
		{
			(data[i].freq)++;
			return ArraySortByFreq(i);
		}
	return 0;
}

template<class DataType>
void FreqArray<DataType>::Insert(int i, DataType x)
{
	if (length + 1 > MaxSize-1)
		cout << "��������ݣ���������" << endl;
	else if (i<1 || i>length + 1)
	{
		cout << "λ�ó��ִ���" << endl;
	}
	else
	{
		for (int j = length; j >= i; j--)
			data[j + 1].data = data[j].data;
		data[i].data = x;
		data[i].freq = 0;
		length++;
	}
}

template <class DataType>
DataType FreqArray<DataType>::Delete(int i)
{
	if (length == 0)
		cout << "��������" << endl;
	else if (i<1 || i>length)
		cout << "λ�ó��ִ���" << endl;
	else
	{
		int x = data[i].data;
		for (int j = i; j < length; j++)
			data[j].data = data[j + 1].data;
		length--;
		return x;
	}
}

template <class DataType>
void FreqArray<DataType>::PrintList()
{
	cout << endl;
	for (int i = 1; i <= length; i++)
		cout << data[i].data << " ";
	cout << endl;
}

//template <class DataType>
//void FreqArray<DataType>::ArraySort()
//{
//	//�������ƶ������
//	int index = 1;
//	for (int i = 1; i <= length; i++)
//	{
//		if (data[i].data < 0)
//		{
//			DataType temp = data[i].data;
//			data[i].data = data[index].data;
//			data[index].data = temp;
//			index++;
//		}
//	}
//	//��0�ƶ����м�
//	for (int i = index; i <= length; i++)
//	{
//		if (data[i].data == 0)
//		{
//			DataType temp = data[i].data;
//			data[i].data = data[index].data;
//			data[index].data = temp;
//			index++;
//		}
//	}
//}

template <class DataType>
int FreqArray<DataType>::SeqSearch(DataType k)
{
	data[0].data = k;
	int i;
	for (i = length; data[i].data != k&&i >= 0; i--){}
	if (i != 0)
	{
		(data[i].freq)++;
	}
	return ArraySortByFreq(i);
}

template <class DataType>
int FreqArray<DataType>::ArraySortByFreq(int i)
{
	//	cout << "adada" << data[98].freq << " " << data[99].freq << endl;
	while (i<length && data[i].freq>data[i + 1].freq)
	{
		node<DataType> temp;
		temp = data[i];
		data[i] = data[i + 1];
		data[i + 1] = temp;
		i++;
	}
	return i;
}

 //template <class DataType>
 //int FreqArray<DataType>::BinSearch(DataType k)
 //{
 //	//��סҪ������,�������ݵĴ�С�������򣬵��������������Ҫ��֤ʹ��Ƶ��������ģ���ͻ
 //	int low = 1;
 //	int high = length;

	//int index = 0;
	//if (data[low] == k)
	//{
	//	index = low;
	//}
	//else if (data[high] == k)
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
	//		if (k < data[mid].data)
	//		{
	//			high = mid - 1;
	//			if (data[high].data == k)
	//			{
	//				index = high;
	//				break;
	//			}
	//				
	//		}
	//		else if (k > data[mid].data)
	//		{
	//			low = mid + 1;
	//			if (data[low].data == k)
	//			{
	//				index = low;
	//				break;
	//			}
	//				
	//		}
	//		else if (k == data[mid].data)
	//		{
	//			index = mid;
	//			break;
	//		}
	//	}
	//}

 //	(data[index].freq)++;
	//return ArraySortByFreq(index);
 //}

#endif