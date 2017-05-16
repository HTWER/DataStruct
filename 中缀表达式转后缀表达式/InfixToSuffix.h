#ifndef __INFIXTOSUFFIX_H__
#define __INFIXTOSUFFIX_H__

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

//要处理两个问题：
//1.使用状态机解析句子成分(未使用状态机)
//2.中缀转后缀

//将double型数据装换成string型
string ConvertToString(double x)
{
	ostringstream o;
	if (o << x)
		return o.str();
	return "0";
}

//将string型数据转换成double型
double StringToDouble(const string& s)
{
	istringstream i(s);
	double x;
	if (i >> x)
		return x;
	return 0.0;
}

//计算后缀表达式的值
double CalSuffix(vector<string>& tar)
{
	vector<double> var;		//用于存储数据

	for (int i = 0; i < tar.size(); i++)
	{
		if (tar[i] != "+"&&tar[i] != "-"&&tar[i] != "*"&&tar[i] != "/")		//读取到数据
		{
			var.push_back(StringToDouble(tar[i]));
		}
		else																//读取到符号
		{
			//弹出栈顶的两个数据,注意顺序
			double op2 = var.back();
			var.pop_back();
			double op1 = var.back();
			var.pop_back();

			//根据符号进行计算
			double res;
			if (tar[i] == "+")
				res = op1 + op2;
			else if (tar[i] == "-")
				res = op1 - op2;
			else if (tar[i] == "*")
				res = op1 * op2;
			else
				res = op1 / op2;

			//运算的结果压回栈
			var.push_back(res);
		}
	}
	return var[0];
}

//中缀转后缀
vector<string> InfixToSuffix(string & ori)
{
	vector<string> res;		//最终结果,对字符串进行了分割，方便读取
	vector<char> operate;	//符号栈

	//转换过程
	for (int i = 0; i < ori.size(); i++)
	{
		if (ori[i] >= '0'&&ori[i] <= '9')		//遇上数字,只能识别整数
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
		else if (ori[i] == '(')					//遇上左括号
		{
			operate.push_back(ori[i]);
		}
		else if (ori[i] == ')')					//遇上右括号，将操作符弹出，直到最终弹出"("
		{
			while (operate.back() != '(')
			{
				string temp(1,operate.back());
				res.push_back(temp);
				operate.pop_back();
			}
			operate.pop_back();
		}
		else if (ori[i] == '+' || ori[i] == '-' || ori[i] == '*' || ori[i] == '/')									//遇上运算符
		{
			if (ori[i] == '-' && (i - 1 < 0 || ori[i - 1] == '+' || ori[i - 1] == '-' || ori[i - 1] == '*' || ori[i - 1] == '/' || ori[i - 1] == '('))		//检测负数
			{
				//获取负数内容
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
			else	//遇上操作符
			{
				//当前操作符无序比较直接压栈
				if (operate.empty() || operate.back() == '(')		
				{
					operate.push_back(ori[i]);
				}
				else
				{
					//用于检测当前字符的优先级
					int weight = 0;
					if (ori[i] == '*' || ori[i] == '/')												
					{
						weight = 1;
					}

					//用于检测栈中的字符的优先级
					int weight2 = 0;
					if (operate[operate.size() - 1] == '*' || operate[operate.size() - 1] == '/')  
					{
						weight2 = 1;
					}

					//当前字符的优先级大于栈中的字符
					if (weight > weight2)   
					{
						//直接入符号栈
						operate.push_back(ori[i]);		
					}
					else                    
					{
						//弹出符号栈顶内容到结果中
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
			cout << "遇上未知字符，转换失败" << endl;
			abort();
		}
	}

	//如果还操作符栈中还有符号，则全部弹出
	while (operate.empty() != 1)
	{
		string temp(1, operate.back());
		res.push_back(temp);
		operate.pop_back();
	}

	//输出结果
	for (int i = 0; i < res.size(); i++)
	{
		cout << res[i] << " ";
	}
	cout << endl;

	return res;
}

#endif