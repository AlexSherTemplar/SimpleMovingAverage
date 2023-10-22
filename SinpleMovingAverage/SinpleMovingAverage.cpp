#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <time.h>
#include <vector>
#include <chrono>
#include <ctime>

using namespace std;

vector<double> generateRandomData(int size, double minValue, double maxValue) {
    vector<double> data;
    srand(time(NULL));
    for (int i = 0; i < size; i++) {

        double value = minValue + rand() % (int)(maxValue - minValue + 1);
        data.push_back(value);
    }
    return data;
}

vector<double> calculateSimpleMovingAverage(const vector<double>& data, int windowSize) {
    vector<double> movingAverages;
    double sum = 0.0;

    for (int i = 0; i < windowSize - 1; i++) {
        sum += data[i]; // превентивно вычисляем сумму первых элементов
    }

    for (int i = windowSize - 1; i < data.size(); i++) { // вычисляем скользящее среднее
        sum += data[i];
        double movingAverage = sum / windowSize;
        movingAverages.push_back(movingAverage);
        sum -= data[i - windowSize + 1];
    }

    return movingAverages;
}

int main() {
    int dataSize = 1000000; // Размер данных
    int windowSize = 128; // Размер окна (количество точек для усреднения)
    double minValue = 0.0; // Минимальное значение
    double maxValue = 100.0; // Максимальное значение
    
    // Генерация случайных данных
    vector<double> data = generateRandomData(dataSize, minValue, maxValue);

    // Вычисление скользящего среднего
    auto start_time = steady_clock::now();


    vector<double> movingAverages = calculateSimpleMovingAverage(data, windowSize);

    auto end_time = steady_clock::now();
    auto elapsed_ns = duration_cast<nanoseconds>(end_time - start_time);
    cout << elapsed_ns.count() << " ns\n";
    
    return 0;
}
