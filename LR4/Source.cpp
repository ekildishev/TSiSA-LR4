#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>

std::vector<double> matrixAndVectorMultiplication(std::vector<std::vector<double>> table, std::vector<double> rating) // Умножение матрицы на вектор
{
	std::vector<double> result;
	result.resize(4);
	double parameter = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			parameter += table[i][j] * rating[j];
		}
		result[i] = parameter;
		parameter = 0;
	}
	return result;
}

double accordance(std::vector<std::vector<double>> table) // Подсчет отношения согласованности
{
	std::vector<double> lineMultiplication;
	lineMultiplication.resize(4);
	std::vector<double> columnSum;
	columnSum.resize(4);
	double line = 1, column = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			line *= table[i][j];
			column += table[j][i];
		}
		lineMultiplication[i] = line;
		columnSum[i] = column;
		line = 1;
		column = 0;
	}
	double sumLine = 0;
	for (int i = 0; i < 4; i++)
	{
		lineMultiplication[i] = pow(lineMultiplication[i], 0.25);
		sumLine += lineMultiplication[i];
	}
	for (int i = 0; i < 4; i++)
	{
		lineMultiplication[i] /= sumLine;
	}
	double lambda = 0;
	for (int i = 0; i < 4; i++)
	{
		lambda += lineMultiplication[i] * columnSum[i];
	}
	lambda = (lambda - 4) / 2.7;
	return lambda;
}

void criterionChange(std::vector<std::vector<double>> table, std::vector<std::pair<std::string, char>> device) // Метод замены критериев
{
	std::vector<std::string> criterion;
	criterion.resize(4);
	criterion[0] = "Start price";
	criterion[1] = "Repair price";
	criterion[2] = "Memory";
	criterion[3] = "Screen";
	std::vector<int> minimum;
	minimum.resize(4);
	std::vector<int> maximum;
	maximum.resize(4);
	for (int i = 0; i < 4; i++)
	{
		minimum[i] = 10;
		maximum[i] = 0;
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (table[j][i] > maximum[i])
			{
				maximum[i] = table[j][i];
			}
			if (table[j][i] < minimum[i])
			{
				minimum[i] = table[j][i];
			}
		}
	}
	std::cout << "\t|";
	for (int i = 0; i < 4; i++)
	{
		std::cout << i + 1 << "\t|";
	}
	std::cout << std::endl;
	for (int i = 0; i < 4; i++)
	{
		std::cout << device[i].second << "\t|";
		for (int j = 0; j < 4; j++)
		{
			std::cout << table[i][j] << "\t|";
		}
		std::cout << std::endl;
	}
	std::cout << "Main criterion is memory(3)\n\n";
	double maximum1, maximum2, minimum4;
	double maximumColumn = 10;
	for (int i = 0; i < 4; i++)
	{
		if (table[i][0] < maximumColumn)
		{
			maximumColumn = table[i][0];
		}
	}
	maximum1 = maximumColumn * 2.5;
	maximumColumn = 10;
	for (int i = 0; i < 4; i++)
	{
		if (table[i][1] < maximumColumn)
		{
			maximumColumn = table[i][1];
		}
	}
	maximum2 = maximumColumn * 2;
	maximumColumn = 0;
	for (int i = 0; i < 4; i++)
	{
		if (table[i][3] > maximumColumn)
		{
			maximumColumn = table[i][3];
		}
	}
	minimum4 = maximumColumn * 0.1;
	std::cout << "Maximum start price is " << maximum1 << "\n";
	std::cout << "Maximum repair price is " << maximum2 << "\n";
	std::cout << "Minimum screen is " << minimum4 << "\n\t ";
	for (int i = 0; i < 4; i++)
	{
		std::cout << i + 1 << "\t|";
	}
	std::cout << std::endl;
	std::vector<std::pair<std::vector<double>, bool>> changeTable;
	changeTable.resize(4);
	for (int i = 0; i < 4; i++)
	{
		changeTable[i].first.resize(4);
		changeTable[i].second = true;
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			changeTable[i].first[j] = (table[i][j] - minimum[j]) / (maximum[j] - minimum[j]);
		}
	}
	for (int i = 0; i < 4; i++)
	{
		changeTable[i].first[2] = table[i][2];
		changeTable[i].first[3] = (table[i][3] - minimum[3]) / (maximum[3] - minimum[3]);
	}
	for (int i = 0; i < 4; i++)
	{
		if (table[i][0] > maximum1)
		{
			changeTable[i].second = false;
		}
		if (table[i][1] > maximum2)
		{
			changeTable[i].second = false;
		}
		if (table[i][3] < minimum4)
		{
			changeTable[i].second = false;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		std::cout << device[i].second << "\t|";
		for (int j = 0; j < 4; j++)
		{
			std::cout <<std::fixed << std::setprecision(3) << changeTable[i].first[j] << "\t|";
		}
		std::cout << std::endl;
	}
	std::pair<int, double> max;
	max.second = 0;
	for (int i = 0; i < 4; i++)
	{
		double sum = 2;
		for (int j = 0; j < 2; j++)
		{
			sum -= changeTable[i].first[j];
			sum += changeTable[i].first[j + 2];
		}
		if (sum > max.second)
		{
			if (changeTable[i].second == true)
			{
				max.first = i;
				max.second = sum;
			}
		}
	}
	std::cout << "The best device is " << device[max.first].first << "(" << device[max.first].second << ")\n";
}

void Paretto(std::vector<std::vector<double>> table, std::vector<std::pair<std::string, char>> device) // Формирование и сужение множества паретто
{
	std::cout << "\n\nMain criterions are Start price(1) and Memory(3)\n";
	std::vector<std::pair<int, int>> criterionTable;
	criterionTable.resize(4);
	std::cout << "\t";
	std::cout << "|Point" << "\t|d\n";
	for (int i = 0; i < 4; i++)
	{
		criterionTable[i].first = table[i][0];
		criterionTable[i].second = table[i][2];
	}
	for (int i = 0; i < 4; i++)
	{
		std::cout << device[i].second << "\t|(" << criterionTable[i].first << ", " << criterionTable[i].second << ")\t|" << 10 + criterionTable[i].first - criterionTable[i].second << "\n";
	}
	std::cout << "Dream point is (0, 10)\n";
	int maximum = 20;
	std::vector<int> maxElem;
	for (int i = 0; i < 4; i++)
	{
		if (10 + criterionTable[i].first - criterionTable[i].second <= maximum)
		{
			if (10 + criterionTable[i].first - criterionTable[i].second < maximum)
			{
				maximum = 10 + criterionTable[i].first - criterionTable[i].second;
				while (maxElem.size() != 0)
				{
					maxElem.pop_back();
				}
			}
			maxElem.push_back(i);
		}	
	}
	std::cout << "The best devices are: ";
	for (int i = 0; i < maxElem.size(); i++)
	{
		std::cout << device[maxElem[i]].first << " (" << device[maxElem[i]].second << ") ";
	}
}

void weightAndUnion(std::vector<std::vector<double>> table, std::vector<std::pair<std::string, char>> device) // Взвешивание и объединение критериев
{
	std::cout << "Table\n\t|";
	for (int i = 0; i < 4; i++)
	{
		std::cout << i + 1 << "\t";
	}
	std::cout << std::endl;
	for (int i = 0; i < 4; i++)
	{
		std::cout << device[i].second << "\t|";
		for (int j = 0; j < 4; j++)
		{
			std::cout << table[i][j] << "\t|";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	std::cout << "Normalized table\n";
	std::vector<int> total;
	total.resize(4);
	int columnTotal = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			columnTotal += table[j][i];
		}
		total[i] = columnTotal;
		columnTotal = 0;
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			table[j][i] /= total[i];
		}
	}
	std::cout << "\t|";
	for (int i = 0; i < 4; i++)
	{
		std::cout << i + 1 << "\t|";
	}
	std::cout << std::endl;
	for (int i = 0; i < 4; i++)
	{
		std::cout << device[i].second << "\t|";
		for (int j = 0; j < 4; j++)
		{
			std::cout << table[i][j] << "\t|";
		}
		std::cout << std::endl;
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			table[i][j] = 1- table[i][j];
		}
	}
	std::cout << std::endl;
	std::cout << "Rating\n";
	double G12 = 1;
	double G13 = 0.5;
	double G14 = 1;
	double G23 = 0;
	double G24 = 1;
	double G34 = 1;
	std::vector<double> rating;
	rating.resize(4);
	rating[0] = (G12 + G13 + G14) / 6;
	rating[1] = (1 - G12 + G23 + G24) / 6;
	rating[2] = (2 - G13 - G23 + G34) / 6;
	rating[3] = (3 - G14 - G24 - G34) / 6;
	for (int i = 0; i < 4; i++)
	{
		std::cout << rating[i] << "\t";
	}
	std::cout << std::endl;
	std::cout << "Multiplication result\n";
	std::vector<double> multiplicationResult = matrixAndVectorMultiplication(table, rating);
	double maximum = 0;
	int maximumIndex;
	for (int i = 0; i < 4; i++)
	{
		std::cout << multiplicationResult[i] << "\t";
		if (multiplicationResult[i] > maximum)
		{
			maximum = multiplicationResult[i];
			maximumIndex = i;
		}
	}
	std::cout << std::endl << std::endl;
	std::cout << "The best device is " << device[maximumIndex].first << "(" << device[maximumIndex].second << ")\n";
}

void rankingAnalysis(std::vector<std::pair<std::string, char>> device) // Метод анализа иерархий
{
	std::vector<std::vector<double>> price;
	std::vector<std::vector<double>> repair;
	std::vector<std::vector<double>> memory;
	std::vector<std::vector<double>> screen;
	std::vector<std::vector<double>> criterion;
	price.resize(4);
	repair.resize(4);
	memory.resize(4);
	screen.resize(4);
	criterion.resize(4);
	for (int i = 0; i < 4; i++)
	{
		price[i].resize(4);
		repair[i].resize(4);
		memory[i].resize(4);
		screen[i].resize(4);
		criterion[i].resize(4);
	}
	for (int i = 0; i < 4; i++)
	{
		price[i][i] = repair[i][i] = memory[i][i] = screen[i][i] = criterion[i][i] = 1;
	}
	price[0][1] = 1;
	price[0][2] = 1. / 5;
	price[0][3] = 1. / 2;
	price[1][2] = 1. / 5;
	price[1][3] = 1. / 2;
	price[2][3] = 3;
	std::cout << "Start price\n";
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < i; j++)
		{
			price[i][j] = 1. / price[j][i];
		}
	}
	std::vector<double> lineTotal;
	lineTotal.resize(4);
	double total = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			total += price[i][j];
		}
		lineTotal[i] = total;
		total = 0;
	}
	std::vector<double> linePriceNormalize;
	linePriceNormalize.resize(4);
	double sum = 0;
	for (int i = 0; i < 4; i++)
	{
		sum += lineTotal[i];
	}
	for (int i = 0; i < 4; i++)
	{
		linePriceNormalize[i] = lineTotal[i] / sum;
	}
	std::cout << "\t|";
	for (int i = 0; i < 4; i++)
	{
		std::cout << device[i].second << "\t|";
	}
	std::cout << "Sum\t|Norma\t|";
	std::cout << std::endl;
	for (int i = 0; i < 4; i++)
	{
		std::cout << device[i].second << "\t|";
		for (int j = 0; j < 4; j++)
		{
			std::cout << price[i][j] << "\t|";
		}
		std::cout << lineTotal[i] << "\t|" << linePriceNormalize[i] << "\t|";
		std::cout << std::endl;
	}
	std::cout << "Accordance " << accordance(price) << "\n";
	repair[0][1] = 2;
	repair[0][2] = 3;
	repair[0][3] = 5;
	repair[1][2] = 2;
	repair[1][3] = 3;
	repair[2][3] = 2;
	std::cout << "\nRepair price\n";
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < i; j++)
		{
			repair[i][j] = 1. / repair[j][i];
		}
	}
	total = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			total += repair[i][j];
		}
		lineTotal[i] = total;
		total = 0;
	}
	std::vector<double> lineRepairNormalize;
	lineRepairNormalize.resize(4);
	sum = 0;
	for (int i = 0; i < 4; i++)
	{
		sum += lineTotal[i];
	}
	for (int i = 0; i < 4; i++)
	{
		lineRepairNormalize[i] = lineTotal[i] / sum;
	}
	std::cout << "\t|";
	for (int i = 0; i < 4; i++)
	{
		std::cout << device[i].second << "\t|";
	}
	std::cout << "Sum\t|Norma\t|";
	std::cout << std::endl;
	for (int i = 0; i < 4; i++)
	{
		std::cout << device[i].second << "\t|";
		for (int j = 0; j < 4; j++)
		{
			std::cout << repair[i][j] << "\t|";
		}
		std::cout << lineTotal[i] << "\t|" << lineRepairNormalize[i] << "\t|";
		std::cout << std::endl;
	}
	std::cout << "Accordance " << accordance(repair) << "\n";
	memory[0][1] = 1;
	memory[0][2] = 5;
	memory[0][3] = 5;
	memory[1][2] = 5;
	memory[1][3] = 5;
	memory[2][3] = 1;
	std::cout << "\nMemory\n";
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < i; j++)
		{
			memory[i][j] = 1 / memory[j][i];
		}
	}
	total = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			total += memory[i][j];
		}
		lineTotal[i] = total;
		total = 0;
	}
	std::vector<double> lineMemoryNormalize;
	lineMemoryNormalize.resize(4);
	sum = 0;
	for (int i = 0; i < 4; i++)
	{
		sum += lineTotal[i];
	}
	for (int i = 0; i < 4; i++)
	{
		lineMemoryNormalize[i] = lineTotal[i] / sum;
	}
	std::cout << "\t|";
	for (int i = 0; i < 4; i++)
	{
		std::cout << device[i].second << "\t|";
	}
	std::cout << "Sum\t|Norma\t|";
	std::cout << std::endl;
	for (int i = 0; i < 4; i++)
	{
		std::cout << device[i].second << "\t|";
		for (int j = 0; j < 4; j++)
		{
			std::cout << memory[i][j] << "\t|";
		}
		std::cout << lineTotal[i] << "\t|" << lineMemoryNormalize[i] << "\t|";
		std::cout << std::endl;
	}
	std::cout << "Accordance " << accordance(memory) << "\n";
	screen[0][1] = 2;
	screen[0][2] = 5;
	screen[0][3] = 7;
	screen[1][2] = 3;
	screen[1][3] = 6;
	screen[2][3] = 3;
	std::cout << "\nScreen size\n";
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < i; j++)
		{
			screen[i][j] = 1 / screen[j][i];
		}
	}
	total = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			total += screen[i][j];
		}
		lineTotal[i] = total;
		total = 0;
	}
	std::vector<double> lineScreenNormalize;
	lineScreenNormalize.resize(4);
	sum = 0;
	for (int i = 0; i < 4; i++)
	{
		sum += lineTotal[i];
	}
	for (int i = 0; i < 4; i++)
	{
		lineScreenNormalize[i] = lineTotal[i] / sum;
	}
	std::cout << "\t|";
	for (int i = 0; i < 4; i++)
	{
		std::cout << device[i].second << "\t|";
	}
	std::cout << "Sum\t|Norma\t|";
	std::cout << std::endl;
	for (int i = 0; i < 4; i++)
	{
		std::cout << device[i].second << "\t|";
		for (int j = 0; j < 4; j++)
		{
			std::cout << screen[i][j] << "\t|";
		}
		std::cout << lineTotal[i] << "\t|" << lineScreenNormalize[i] << "\t|";
		std::cout << std::endl;
	}
	std::cout << "Accordance " << accordance(screen) << "\n";
	criterion[0][1] = 5;
	criterion[0][2] = 1. / 2;
	criterion[0][3] = 7;
	criterion[1][2] = 1. / 5;
	criterion[1][3] = 6;
	criterion[2][3] = 7;
	std::cout << "\nCriterion\n";
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < i; j++)
		{
			criterion[i][j] = 1. / criterion[j][i];
		}
	}
	total = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			total += criterion[i][j];
		}
		lineTotal[i] = total;
		total = 0;
	}
	std::vector<double> lineCriterionNormalize;
	lineCriterionNormalize.resize(4);
	sum = 0;
	for (int i = 0; i < 4; i++)
	{
		sum += lineTotal[i];
	}
	for (int i = 0; i < 4; i++)
	{
		lineCriterionNormalize[i] = lineTotal[i] / sum;
	}
	std::cout << "\t|";
	for (int i = 0; i < 4; i++)
	{
		std::cout << i + 1 << "\t|";
	}
	std::cout << "Sum\t|Norma\t|";
	std::cout << std::endl;
	for (int i = 0; i < 4; i++)
	{
		std::cout << i + 1 << "\t|";
		for (int j = 0; j < 4; j++)
		{
			std::cout << criterion[i][j] << "\t|";
		}
		std::cout << lineTotal[i] << "\t|" << lineCriterionNormalize[i] << "\t|";
		std::cout << std::endl;
	}
	std::cout << "Accordance " << accordance(criterion) << "\n";
	std::vector<std::vector<double>> table;
	table.resize(4);
	table[0] = linePriceNormalize;
	table[1] = lineRepairNormalize;
	table[2] = lineMemoryNormalize;
	table[3] = lineScreenNormalize;
	std::vector<std::vector<double>> matrix;
	matrix.resize(4);
	for (int i = 0; i < 4; i++)
	{
		matrix[i].resize(4);
		for (int j = 0; j < 4; j++)
		{			
			matrix[i][j] = table[j][i];
		}
	}
	std::vector<double> multiplicationResult = matrixAndVectorMultiplication(matrix, lineCriterionNormalize);
	std::cout << "\nMultiplication result\n";
	double maximum = 0;
	int maximumIndex;
	for (int i = 0; i < 4; i++)
	{
		std::cout << multiplicationResult[i] << "\t";
		if (multiplicationResult[i] > maximum)
		{
			maximum = multiplicationResult[i];
			maximumIndex = i;
		}
	}
	std::cout << std::endl;
	std::cout << "The best device is " << device[maximumIndex].first << "(" << device[maximumIndex].second << ")\n";
}

int main()
{
	std::vector<std::vector<double>> table;
	table.resize(4);
	for (int i = 0; i < 4; i++)
	{
		table[i].resize(4);
	}
	table[0][0] = 8;
	table[1][0] = 8;
	table[2][0] = 3;
	table[3][0] = 7;
	table[0][1] = 4;
	table[1][1] = 5;
	table[2][1] = 7;
	table[3][1] = 8;
	table[0][2] = 8;
	table[1][2] = 8;
	table[2][2] = 3;
	table[3][2] = 3;
	table[0][3] = 8;
	table[1][3] = 7;
	table[2][3] = 3;
	table[3][3] = 1;
	std::vector<std::pair<std::string, char>> device;
	device.resize(4);  
	device[0].first = "Computer";
	device[1].first = "Notebook";
	device[2].first = "Pad";
	device[3].first = "Smartphone";
	for (int i = 0; i < 4; i++)
	{
		device[i].second = 'A' + i;
	}
	criterionChange(table, device);
	std::cout << "\n\n\n\n\n\n\n";
	Paretto(table, device);
	std::cout << "\n\n\n\n\n\n\n";
	weightAndUnion(table, device);
	std::cout << "\n\n\n\n\n\n\n";
	rankingAnalysis(device);
	system("pause");
	return 0;
}