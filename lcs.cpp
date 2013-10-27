#include <iostream>
#include <vector>
#include <string>
#include <cassert>

//#define PRINT_MATRIX

using namespace std;

enum DIR
{
	LCS_NONE,
	LCS_RIGHT,
	LCS_DOWN,
	LCS_ANY,
};

struct LCSPair
{
	int length;
	DIR dir;
	LCSPair()
	{
		length = 0;
		dir = LCS_NONE;
	}
};

vector<char> LongestCommonSubsequence(const string& str1, const string& str2)
{
	if (str1.empty() || str2.empty())
		return vector<char>();

	vector<char> result;
	vector<vector<LCSPair> > traceMatrix(str1.size(), vector<LCSPair>(str2.size()));
#ifdef PRINT_MATRIX
	cout << "\t\t";
	for (size_t j = 0; j < str2.size(); j++)
		cout << str2[j] << "\t\t";
	cout << endl;
#endif
	for (size_t i = 0; i < str1.size(); ++i)
	{
#ifdef PRINT_MATRIX
		cout << str1[i] << "\t\t";
#endif
		for (size_t j = 0; j < str2.size(); ++j)
		{
			if (str1[i] == str2[j])
			{
				if (i == 0)
					traceMatrix[i][j].length = 1;
				else if (j == 0)
					traceMatrix[i][j].length = 1;
				else
					traceMatrix[i][j].length = traceMatrix[i][j - 1].length + 1;

				traceMatrix[i][j].dir = LCS_ANY;
			} 
			else
			{
				int temp_i = i;
				int temp_j = j;
				DIR dir = LCS_NONE;
				if (traceMatrix[i][j > 0 ? j - 1 : 0].length < traceMatrix[i > 0 ? i - 1 : 0 ][j].length)
				{
					temp_i--;
					dir = LCS_DOWN;
				}
				else
				{
					temp_j--;
					dir = LCS_RIGHT;
				}

				traceMatrix[i][j].length = (temp_i < 0 || temp_j < 0) ? 0 : traceMatrix[temp_i][temp_j].length;
				traceMatrix[i][j].dir = dir;
			}
#ifdef PRINT_MATRIX
			cout << traceMatrix[i][j].length << ", " << traceMatrix[i][j].dir << "\t\t";
#endif
		}
#ifdef PRINT_MATRIX
		cout << endl;
#endif
	}

	int i = str1.size() - 1;
	int j = str2.size() - 1;
	while (1)
	{
		switch(traceMatrix[i][j].dir)
		{
		case LCS_DOWN:
			i--;
			break;
		case LCS_RIGHT:
			j--;
			break;
		case LCS_ANY:
			result.insert(result.begin(), str1[i]);
			i--;
			j--;
			break;
		}

		if ((i < 0) || (j < 0))
			break;

		DIR currentDir = traceMatrix[i][j].dir;
		if (i == 0 && currentDir == LCS_DOWN)
			break;
		if (j == 0 && currentDir == LCS_RIGHT)
			break;
	}
	return result;
}

int main()
{
	string test1("GATCGATCGGACTGGGATC");
	string test2("CTAGGCATTAGCCTGA");

	vector<char> result = LongestCommonSubsequence(test1, test2);

	char *buffer = new char[result.size() + 1];
	fill(buffer, buffer + result.size() + 1, 0);
	copy(result.begin(),  result.end(), buffer);

	cout << "string A = " << test1 << endl;
	cout << "string B = " << test2 << endl;
	cout << "LCS of A and B is : " << buffer  << endl;
	delete []buffer;
}
