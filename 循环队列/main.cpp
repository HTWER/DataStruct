#include "CirQueue.h"

#if 0
struct car
{
	bool type;
	int number;
};

void version_one()
{
	CirQueue<car> carQueue;
	CirQueue<car> TruckQueue;
	CirQueue<car> ship;
	car temp;  // 0 or 1
	int aviTruck = 0;   //�����ϵĿ�����
	int carsOnShip = 0;
	int busOnShip = 0;

	int i = 0;
	int type;
	cout << "�������ݣ�0��������1����ͳ���#Ϊ������־����" << endl;
	while (cin >> type)   //����������
	{
		temp.type = type;
		temp.number = i++;
		carQueue.EnQueue(temp);
	}

	while (carsOnShip != 10 && (carQueue.Empty() != 1 || TruckQueue.Empty() != 1))
	{
		if ((aviTruck != 0 && TruckQueue.Empty() != 1) || (carQueue.Empty() == 1 && TruckQueue.Empty() != 1)) // ������ֱ�Ӵӿ������н�������
		{
			ship.EnQueue(TruckQueue.DeQueue());
			aviTruck--;
			carsOnShip++;
		}
		else
		{
			temp = carQueue.DeQueue();
			if (temp.type == 0)       //ȡ���˿���
			{
				if (aviTruck != 0)
				{
					ship.EnQueue(temp);
					carsOnShip++;
					aviTruck--;
				}
				else
					TruckQueue.EnQueue(temp);
			}
			else             //ȡ���˿ͳ�
			{
				ship.EnQueue(temp);
				carsOnShip++;
				busOnShip++;
				if (busOnShip == 4)
				{
					busOnShip = 0;
					aviTruck++;
				}
			}
		}
	}

	while (ship.Empty() != 1)
	{
		temp = ship.DeQueue();
		if (temp.type == 0)
			cout << "����";
		else
			cout << "�ͳ�";
		cout << temp.number << " ";
	}


	cin.clear();
	while (cin.get() != '\n');
	
}

void version_two()
{
	CirQueue<car> queue0;   //��������
	CirQueue<car> queue1;	//�ͳ�����
	CirQueue<car> ship;

	int truckNum = 1;
	int busNum = 1;
	car temp2;
	int temp;
	while (cin >> temp)
	{
		if (temp == 0)
		{
			temp2.type = 0;
			temp2.number = truckNum;
			truckNum++;
			queue0.EnQueue(temp2);
		}
		else
		{
			temp2.type = 1;
			temp2.number = busNum;
			busNum++;
			queue1.EnQueue(temp2);
		}
			
	}

	int count = 0;
	while (count!=10&&(queue0.Empty()!=1||queue1.Empty()!=1))
	{
		int i;
		for (i = 0; i < 4 && queue1.Empty() != 1; i++)
		{
				ship.EnQueue(queue1.DeQueue());
				count++;
		}

		ship.EnQueue(queue0.DeQueue());
		count++;
	}

	while (ship.Empty()!=1)
	{
		temp2 = ship.DeQueue();
		if (temp2.type==0)
		{
			cout << "����" << temp2.number << " ";
		}
		else
		{
			cout << "�ͳ�" << temp2.number << " ";
		}
	}
	


	cin.clear();
	while (cin.get() != '\n');
}

int main()
{
	//	version_one();
	version_two();
	
	system("pause");
	return 0;
}

#endif

int main()
{
	CirQueue<int> queue;
	cout << queue.IsEmpty() << endl;

	queue.Push(9);
	queue.Push(10);
	queue.Push(11);
	queue.Push(12);

	cout << queue.Pop() << endl;
	cout << queue.Back() << endl;
	cout << queue.Back() << endl;
//	cout << queue.Pop() << endl;

	system("pause");
	return 0;
}

