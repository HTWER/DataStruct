#ifndef __INFIXTOSUFFIX_H__
#define __INFIXTOSUFFIX_H__

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

//Ҫ�����������⣺
//1.ʹ��״̬���������ӳɷ�(δʹ��״̬��)
//2.��׺ת��׺

//��double������װ����string��
string ConvertToString(double x)
{
	ostringstream o;
	if (o << x)
		return o.str();
	return "0";
}

//��string������ת����double��
double StringToDouble(const string& s)
{
	istringstream i(s);
	double x;
	if (i >> x)
		return x;
	return 0.0;
}

//�����׺���ʽ��ֵ
double CalSuffix(vector<string>& tar)
{
	vector<double> var;		//���ڴ洢����

	for (int i = 0; i < tar.size(); i++)
	{
		if (tar[i] != "+"&&tar[i] != "-"&&tar[i] != "*"&&tar[i] != "/")		//��ȡ������
		{
			var.push_back(StringToDouble(tar[i]));
		}
		else																//��ȡ������
		{
			//����ջ������������,ע��˳��
			double op2 = var.back();
			var.pop_back();
			double op1 = var.back();
			var.pop_back();

			//���ݷ��Ž��м���
			double res;
			if (tar[i] == "+")
				res = op1 + op2;
			else if (tar[i] == "-")
				res = op1 - op2;
			else if (tar[i] == "*")
				res = op1 * op2;
			else
				res = op1 / op2;

			//����Ľ��ѹ��ջ
			var.push_back(res);
		}
	}
	return var[0];
}

//��׺ת��׺
vector<string> InfixToSuffix(string & ori)
{
	vector<string> res;		//���ս��,���ַ��������˷ָ�����ȡ
	vector<char> operate;	//����ջ

	//ת������
	for (int i = 0; i < ori.size(); i++)
	{
		if (ori[i] >= '0'&&ori[i] <= '9')		//��������,ֻ��ʶ������
		{
			string number;
			while (ori[i] >= '0'&&ori[i] <= '9'&&i < ori.size())
			{
				number+=ori[i];
				i++;
			}
			i--;

			res.push_back(number);
		}
		else if (ori[i] == '(')					//����������
		{
			operate.push_back(ori[i]);
		}
		else if (ori[i] == ')')					//���������ţ���������������ֱ�����յ���"("
		{
			while (operate.back() != '(')
			{
				string temp(1,operate.back());
				res.push_back(temp);
				operate.pop_back();
			}
			operate.pop_back();
		}
		else if (ori[i] == '+' || ori[i] == '-' || ori[i] == '*' || ori[i] == '/')									//���������
		{
			if (ori[i] == '-' && (i - 1 < 0 || ori[i - 1] == '+' || ori[i - 1] == '-' || ori[i - 1] == '*' || ori[i - 1] == '/' || ori[i - 1] == '('))		//��⸺��
			{
				//��ȡ��������
				string number;
				number.push_back(ori[i]);
				i++;
				while (ori[i] >= '0'&&ori[i] <= '9'&&i < ori.size())
				{
					number.insert(number.end(), ori[i]);
					i++;
				}
				i--;

				res.push_back(number);
			}
			else	//���ϲ�����
			{
				//��ǰ����������Ƚ�ֱ��ѹջ
				if (operate.empty() || operate.back() == '(')		
				{
					operate.push_back(ori[i]);
				}
				else
				{
					//���ڼ�⵱ǰ�ַ������ȼ�
					int weight = 0;
					if (ori[i] == '*' || ori[i] == '/')												
					{
						weight = 1;
					}

					//���ڼ��ջ�е��ַ������ȼ�
					int weight2 = 0;
					if (operate[operate.size() - 1] == '*' || operate[operate.size() - 1] == '/')  
					{
						weight2 = 1;
					}

					//��ǰ�ַ������ȼ�����ջ�е��ַ�
					if (weight > weight2)   
					{
						//ֱ�������ջ
						operate.push_back(ori[i]);		
					}
					else                    
					{
						//��������ջ�����ݵ������
						string temp(1, operate.back());
						res.push_back(temp);
						operate.pop_back();
						i--;
					}
				}

			}
		}
		else
		{
			cout << "����δ֪�ַ���ת��ʧ��" << endl;
			abort();
		}
	}

	//�����������ջ�л��з��ţ���ȫ������
	while (operate.empty() != 1)
	{
		string temp(1, operate.back());
		res.push_back(temp);
		operate.pop_back();
	}

	//������
	for (int i = 0; i < res.size(); i++)
	{
		cout << res[i] << " ";
	}
	cout << endl;

	return res;
}

#endif