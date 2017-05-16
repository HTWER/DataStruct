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
	int aviTruck = 0;   //可以上的卡车数
	int carsOnShip = 0;
	int busOnShip = 0;

	int i = 0;
	int type;
	cout << "输入数据（0代表卡车，1代表客车，#为结束标志）：" << endl;
	while (cin >> type)   //创建车队列
	{
		temp.type = type;
		temp.number = i++;
		carQueue.EnQueue(temp);
	}

	while (carsOnShip != 10 && (carQueue.Empty() != 1 || TruckQueue.Empty() != 1))
	{
		if ((aviTruck != 0 && TruckQueue.Empty() != 1) || (carQueue.Empty() == 1 && TruckQueue.Empty() != 1)) // 卡车可直接从卡车队列进入的情况
		{
			ship.EnQueue(TruckQueue.DeQueue());
			aviTruck--;
			carsOnShip++;
		}
		else
		{
			temp = carQueue.DeQueue();
			if (temp.type == 0)       //取出了卡车
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
			else             //取出了客车
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
			cout << "卡车";
		else
			cout << "客车";
		cout << temp.number << " ";
	}


	cin.clear();
	while (cin.get() != '\n');
	
}

void version_two()
{
	CirQueue<car> queue0;   //卡车队列
	CirQueue<car> queue1;	//客车队列
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
			cout << "卡车" << temp2.number << " ";
		}
		else
		{
			cout << "客车" << temp2.number << " ";
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

