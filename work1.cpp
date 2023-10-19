#include <iostream>
#include <cmath>

double getExponentTaylorSeries(double intervalStart, double intervalEnd, int maxNumber, double intervalStep, double precision);
unsigned factorial(int factorialNo);
double power(double number, int power);

int main () {
	setlocale(LC_ALL, "RUS");

    int maxNumber;
    double intervalStart, intervalEnd, intervalStep, precision;

    try {
        std::cout << "\n\nВведите интервал числа X: \n";
        std::cin >> intervalStart;
        if (!std::cin) {
            throw "Ошибка! Значение должно быть числом.\n\n";
        }
        if (intervalStart <= -1) {
            throw "Ошибка! В интервал могут входить значения только из промежутка (-1, 1).\n\n";
        }

        std::cin >> intervalEnd;
        if (!std::cin) {
            throw "Ошибка! Значение должно быть числом.\n\n";
        }
        if ((intervalEnd >= 1)) {
            throw "Ошибка! В интервал могут входить значения только из промежутка (-1, 1).\n\n";
        }

        if (intervalStart > intervalEnd) {
            throw "Ошибка! Первая граница интервала должна быть меньше второй.\n\n";
        }

        std::cout << "Введите шаг интервала: \n";
        std::cin >> intervalStep;
        if (!std::cin || intervalStep <= 0) {
            throw "Ошибка! Значение шага интервала должно быть положительным целым числом.\n\n";
        }
    
        std::cout << "Введите максимальное число слагаемых: \n";
        std::cin >> maxNumber;
        if (!std::cin || maxNumber <= 0) {
            throw "Ошибка! Значение максимального числа слагаемых должно быть положительным целым числом.\n\n";
        }

        std::cout << "Введите точность вычислений: \n";
        std::cin >> precision;
        if (!std::cin || precision <= 0) {
            throw "Ошибка! Значение точности вычислений должно быть положительным целым числом. Например: 0.0001.\n\n";
        }

        std::cout << "\n\nТаблица:\n";
        getExponentTaylorSeries(intervalStart, intervalEnd, maxNumber, intervalStep, precision);
    }

    catch(const char* errorMessage) {
        std::cerr << errorMessage;
    }

    return 0;
}

double getExponentTaylorSeries(double intervalStart, double intervalEnd, int maxNumber, double intervalStep, double precision)
{
    int countTable = 1;
    double absError = 0;

    for (double intervalNumber = intervalStart; intervalNumber <= intervalEnd; intervalNumber += intervalStep) {
        double result = 1;
        for (int numberNo = 1; numberNo < maxNumber; numberNo++) {
            result += power(intervalNumber, numberNo)/factorial(numberNo);
            absError = abs(power(intervalNumber, numberNo + 1)/factorial(numberNo + 1));
            if (precision >= absError) {
                break;
            }
        }
        if (maxNumber == 1) {
            absError = abs(power(intervalNumber, maxNumber + 1)/factorial(maxNumber + 1));
        }
        if (precision >= absError) {
            std::cout << "-------------------------------------------------------------------------------------------\n";
            std::cout << "| " << countTable << ") " << "X: " << std::fixed << intervalNumber << " | Taylor's series: " << result << " | CMath: " << exp(intervalNumber) << " | Точность достигнута    " << " |" << '\n';
        }
        else {
            std::cout << "-------------------------------------------------------------------------------------------\n";
            std::cout << "| " << countTable << ") " << "X: " << std::fixed << intervalNumber << " | Taylor's series: " << result << " | CMath: " << exp(intervalNumber) << " | Точность не достигнута" << "  |" << '\n';
        }
        countTable++;
    }
    std::cout << "-------------------------------------------------------------------------------------------\n\n";
    return 0;
}

unsigned factorial(int factorialNo) {
    unsigned factorial = 1;
    for (int i = 2; i <= factorialNo; i++) {
        factorial *= i;
    }
    return factorial;
}

double power(double number, int power) {
    double result = 1;

    while (power != 0) {
        if (power % 2) {
            result *= number;
        }
        number *= number;
        power >>= 1;
    }
    return result;
}