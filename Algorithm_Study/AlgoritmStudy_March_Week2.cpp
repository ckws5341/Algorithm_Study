#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;

//#define ALGORITHM_1099
#define ALGORITHM_1095
//#define ALGORITHM_1060

#pragma region Problem 1099
#ifdef ALGORITHM_1099


const int INFINITE = 10000000;
#define _uint unsigned int
string strString;
vector<string> vecWord;
int iArrCache[50][50];

int GetTranslate(_uint begin, _uint wIndex) 
{
	string& strOrigin = vecWord[wIndex];

	_uint iEnd = begin + strOrigin.length();
	if (iEnd > strString.length())
		return -1;

	int cost = 0;
	int charCount[26] = { 0, };

	for (_uint i = 0; i < strOrigin.length(); ++i)
		 ++charCount[strOrigin[i] - 'a'];

	for (_uint i = 0; i < strOrigin.length(); ++i)
	{
		char c = strString[begin + i];
		if (c != strOrigin[i]) 
			++cost;

		--charCount[c - 'a'];
	}

	for (_uint i = 0; i < 26; ++i) 
	{
		if (charCount[i] != 0) 
			return -1;
	}

	return cost;
}

int GetMinPrice(_uint begin, _uint wIndex) 
{
	if (begin >= strString.size()) 
		return 0;       

	if (wIndex >= vecWord.size()) 
		return INFINITE;

	int& ret = iArrCache[begin][wIndex];
	
	if (ret != -1) 
		return ret;

	ret = INFINITE;
	int cost = GetTranslate(begin, wIndex);
	if (cost == -1)
		return INFINITE; 


	int nextBegin = begin + vecWord[wIndex].length();
	for (_uint i = 0; i < vecWord.size(); ++i) 
		ret = min(ret, GetMinPrice(nextBegin, i));
	

	ret += cost;
	return ret;
}

int main() 
{
	int n;
	memset(iArrCache, -1, sizeof(iArrCache));

	cin >> strString;
	cin >> n;
	vecWord.resize(n);

	for (int i = 0; i < n; ++i) 
		cin >> vecWord[i];
	

	int minCost = INFINITE;

	for (int i = 0; i < n; ++i) 
		minCost = min(minCost, GetMinPrice(0, i));
	
	if (minCost < INFINITE)
		cout << minCost;
	else
		cout << -1;

	return 0;
}
#endif
#pragma endregion

#pragma region Problem 1095
#ifdef ALGORITHM_1095
#define LLONG long long
list<int> listPrime;
map<LLONG, int> mapFrimeFactors;
void Make_Prime(int iMax)
{
	int arr[100001];
	arr[0] = 0;
	arr[1] = 0;
	for (int i = 2; i < iMax + 1; ++i)
		arr[i] = i;

	for (int i = 2; i < iMax + 1; ++i)
	{
		if (arr[i] == 0) continue;
		for (int j = i * 2; j < iMax + 1; j += i)
			arr[j] = 0;
	}
	for (int i = 2; i < iMax + 1; ++i)
	{
		if (arr[i] != 0)
		{
			listPrime.emplace_back(arr[i]);
		}
	}
}
LLONG Combination(LLONG _llTrueNum, LLONG _llFalseNum)
{
	LLONG CombinationN = _llTrueNum + _llFalseNum;

	for (auto Prime : listPrime)
	{
		int iCount = 1;
		while (pow(Prime, iCount) <= CombinationN)
		{
			LLONG llDivNum = pow(Prime, iCount);
			int FactorCount_N = CombinationN / llDivNum;
			int FactorCount_R = _llFalseNum / llDivNum + _llTrueNum / llDivNum;

			int iRes = FactorCount_N - FactorCount_R;
			auto Temp = mapFrimeFactors.find(Prime);

			if (Temp == mapFrimeFactors.end())
			{
				if(iRes != 0)
					mapFrimeFactors.emplace(Prime, iRes);
			}
			else
				Temp->second += iRes;
			++iCount;
		}
	}

	LLONG iRes = 1;
	for (auto& Prime : mapFrimeFactors)
		iRes *= pow(Prime.first, Prime.second);

	return iRes;
}

int main()
{
	list<int> arrInt;
	LLONG llTrueNum, llFalseNum, llHumanNum;
	
	int iRes = -1;

	cin >> llTrueNum;
	cin >> llFalseNum;
	cin >> llHumanNum;
	
	Make_Prime(llHumanNum);

	LLONG llMaxCount = Combination(llTrueNum, llFalseNum);
	if (llMaxCount < llHumanNum && llMaxCount > 0)
		llHumanNum = llMaxCount;

	if (llMaxCount > 0)
	{
		while (llHumanNum > 0)
		{
			if (llMaxCount % llHumanNum == 0)
			{
				iRes = llHumanNum;
				break;
			}
			else
				--llHumanNum;
		}
	}
	else
	{
		while (llHumanNum > 0)
		{
			bool bAnswer = true;
			map<LLONG, int> mapHumanFrimeFactors;
			map<LLONG, int> mapTempFrimeFactors = mapFrimeFactors;
			LLONG llTempHumanNum = llHumanNum;

			for (auto Prime : listPrime)
			{
				if (Prime >= llTrueNum + llFalseNum)
				{
					bAnswer = false;
					break;
				}
				while (llTempHumanNum % Prime == 0)
				{
					auto Temp = mapTempFrimeFactors.find(Prime);
					if (Temp == mapTempFrimeFactors.end())
					{
						bAnswer = false;
						break;
					}
					else
					{
						if (Temp->second <= 0)
						{
							bAnswer = false;
							break;
						}
						else
							Temp->second -= 1;
					}
					llTempHumanNum /= Prime;
				}
				if (llTempHumanNum <= 1)
					break;
			}

			if (bAnswer)
			{
				iRes = llHumanNum;
				break;
			}
			else
				--llHumanNum;
		}
	}
	cout << iRes << endl;
	return 0;
}
#endif
#pragma endregion

#pragma region Problem 1060
#ifdef ALGORITHM_1060


#endif
#pragma endregion


