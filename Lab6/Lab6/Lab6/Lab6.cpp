// Lab6.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <cmath>

const double accuracy =  0.000001;

double gauss(unsigned m, double** matrix)
{ 
	double result = 1; //(1)
	for (unsigned i = 0; i < m; ++i)
	{
		// ����� �����, ���� ������ matrix[i][i] ������� �� ��, ��� ������ �� ��� �� ������� ��������� 
		if (fabs(matrix[i][i]) < accuracy) //(2)
		{
			for (unsigned j = i + 1; j < m; ++j)
			{ 
				if (fabs(matrix[j][i]) > accuracy) //(3)
				{
				double* buffer = matrix[i]; //(4)
				matrix[i] = matrix[j]; //(5)
				matrix[j] = buffer; //(6)
				result *= (-1);
				break;
				}
			}
		}
		// ���� ����� �� ��������� � ������������ ����� ���� 
		if (fabs(matrix[i][i]) < accuracy) //(7)
		{
		return 0; //(8)
		}
		// ��������� ����� �������� ������������ 
		result *= matrix[i][i];//; (9)
		// �������� � ������������ ����
		for (unsigned j = i + 1; j < m; ++j)
		{ 
			if (fabs(matrix[j][i]) >= accuracy) //(10)
			{
				double q = matrix[j][i] / matrix[i][i]; //(11)
				for (unsigned k = i; k < m; ++k)
				{ 
					matrix[j][k] -= matrix[i][k] * q; //(12)
				}
			}
		}
	} 
	return result; //(13)
}

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

