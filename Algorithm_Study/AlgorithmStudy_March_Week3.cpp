#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;

//#define ALGORITHM_1107
//#define ALGORITHM_1111
#define ALGORITHM_1132

#pragma region Problem 1107
#ifdef ALGORITHM_1107
//ÀÚ¸´¼öº°·Î 

#define INFINITE 9999999
int main()
{
	int iInputChannel = 0;
	int iBrokenButtonNum = 0;
	vector<int> vecBrokenBtn;
	int iRes = 0;

	cin >> iInputChannel;
	cin >> iBrokenButtonNum;
	for (int i = 0; i < iBrokenButtonNum; ++i)
	{
		int iTemp = 0;
		cin >> iTemp;
		vecBrokenBtn.emplace_back(iTemp);
	}
	bool bClickButton = false;
	int iDistance = abs(iInputChannel - 100);
	int iClosestNum = 0;
	if(iInputChannel > 100)
		iClosestNum = iDistance + 100;
	else
		iClosestNum = 100 - iDistance;

	if (iInputChannel == 100)
	{
		iRes = 0;
	}
	else if (iInputChannel == 99 || iInputChannel == 101)
	{
		iRes = 1;
	}
	else if (iInputChannel == 98 || iInputChannel == 102)
	{
		iRes = 2;
	}
	else
	{
		for (int i = 0; i <= 999999; ++i)
		{
			int iPn = i;
			int iPnNum = 0;
			do 
			{
				++iPnNum;
				iPn /= 10;
			} while (iPn >= 1);
			if (abs(iInputChannel - i) + iPnNum < iDistance + iPnNum)
			{
				bool bClickBrokenBtn = false;
				int iTemp = i;
				do
				{
					int iCheck = iTemp % 10;
					for (auto& BrokenBtn : vecBrokenBtn)
					{
						if (BrokenBtn == iCheck)
						{
							bClickBrokenBtn = true;
							break;
						}
					}
					if (bClickBrokenBtn)
						break;

					iTemp /= 10;
				}while (iTemp >= 1);
				if (bClickBrokenBtn)
					continue;

				bClickButton = true;
				iClosestNum = i;
				iDistance = abs(iInputChannel - i);
			}
		}

		int iPn = iClosestNum;
		int iPnNum = 0;
		if (bClickButton)
		{
			do
			{
				++iPnNum;
				iPn /= 10;
			} while (iPn >= 1);
		}

		cout << iClosestNum  << " " << iPnNum << " " << iDistance << endl;
		iRes = iPnNum + iDistance;
	}
	
	cout << iRes << endl;
	return 0;
}
#endif
#pragma endregion

#pragma region Problem 1111
#ifdef ALGORITHM_1111

int main()
{
	int iA = 0, iB = 0;
	int iInputCount = 0;
	int iRes = 0;
	vector<int> vecInput;

	cin >> iInputCount;
	for (int i = 0; i < iInputCount; ++i)
	{
		int iTemp = 0;
		cin >> iTemp;
		vecInput.emplace_back(iTemp);
	}

	if (iInputCount == 1)
	{
		cout << "A" << endl;
		return 0;
	}
	if (iInputCount == 2)
	{
		if (vecInput[0] == vecInput[1])
			cout << vecInput[0] << endl;
		else
			cout << "A" << endl;

		return 0;
	}

	if (vecInput[0] == vecInput[1])
		iA = 0;
	else
		iA = (vecInput[2] - vecInput[1]) / (vecInput[1] - vecInput[0]);

	iB = vecInput[1] - (vecInput[0] * iA);
	

	for (int i = 0; i < iInputCount - 1; ++i)
	{
		if (vecInput[i] * iA + iB != vecInput[i + 1])
		{
			cout << "B" << endl;
			return 0;
		}
	}

	iRes = vecInput[iInputCount - 1] * iA + iB;

	cout << iRes << endl;

	return 0;
}
#endif
#pragma endregion

#pragma region Problem 1132
#ifdef ALGORITHM_1132

#define LLONG long long

int main()
{
	int iInputCount;
	vector<string> vecInputString;
	map<string, LLONG> mapWeight;
	int iKeyValue[10];
	LLONG llRes = 0;

	char cKey = 'A';
	for (int i = 0; i < 10; ++i)
	{
		string strKey = "";
		strKey = cKey + i;
		mapWeight.emplace(strKey, 0);

		iKeyValue[i] = 0;
	}

	cin >> iInputCount;
	for (int i = 0; i < iInputCount; ++i)
	{
		string strTemp;
		cin >> strTemp;
		vecInputString.push_back(strTemp);
	}



	for (int i = 0; i < (int)vecInputString.size(); ++i)
	{
		for (int j = 0; j < (int)vecInputString[i].length(); ++j)
		{
			string strKeyTemp = "";
			strKeyTemp += vecInputString[i][j];
			mapWeight.find(strKeyTemp)->second += (LLONG)pow(10, vecInputString[i].length() - j - 1);
		}
	}

	list<LLONG> sortWeight;
	for (auto& Weight : mapWeight)
		sortWeight.emplace_back(Weight.second);
	sortWeight.sort(greater<LLONG>());

	
	int iValue = 9;
	for (auto& Weight : sortWeight)
	{
		if (Weight <= 0)
			break;

		char cKeyTemp[2];
		for (auto& WeightMap : mapWeight)
		{
			if (Weight == WeightMap.second)
			{
				strcpy_s(cKeyTemp, sizeof(WeightMap.first.c_str()) + 1, WeightMap.first.c_str());

				char cTemp = cKeyTemp[0];
				int iKey = (int)(cTemp - 'A');
				if (iKeyValue[iKey] != 0)
					continue;

				break;
			}
		}
		
		char cTemp = cKeyTemp[0];
		int iKey = (int)(cTemp - 'A');
		iKeyValue[iKey] = iValue;
		--iValue;
	}

	char cCheck = 'A';
	bool bIsZeroNo[10] = { false, };
	for (int i = 0; i < 10; ++i)
	{
		for (auto& String : vecInputString)
		{
			if (String[0] == 'A' + i)
				bIsZeroNo[i] = true;	
		}
	}

	int iCount = 0;
	vector<int> PlusValue;
	if (sortWeight.back() != 0)
	{
		for (int i = 0; i < 10; ++i)
		{
			if (iKeyValue[i] == iCount && bIsZeroNo[i] == true)
			{
				PlusValue.emplace_back(i);
				i = -1;
				iCount += 1;
			}
			else if (iKeyValue[i] == iCount && bIsZeroNo[i] == false)
			{
				for (auto& PlusIndex : PlusValue)
				{
					iKeyValue[PlusIndex] += 1;
				}
				iKeyValue[i] = 0;
				break;
			}
		}
	}

	int i = 0;
	for (auto& Weight : mapWeight)
	{
		llRes += Weight.second * iKeyValue[i];
		i++;
	}

	cout << llRes;

	return 0;
}

#endif
#pragma endregion


