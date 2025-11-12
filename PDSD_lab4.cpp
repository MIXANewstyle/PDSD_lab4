#include <iostream>
#include <string>
#include <clocale>      // для setlocale
#include <random>       // для генерации размера
#include <iomanip>      // для boolalpha (вывод true/false)

// !!! ИЗМЕНЕНИЕ: Подключаем НОВЫЙ .h файл !!!
#include "SetLab4_Ushakov.h" 

using namespace std;

// Глобальный генератор для main (чтобы получить размер)
int GetRandomInt(int minVal, int maxVal) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(minVal, maxVal);
    return dist(gen);
}


int main() {
    setlocale(LC_ALL, "Russian");
    cout << boolalpha;

    cout << "--- Тестирование класса MySet (на std::list) ---" << endl;

    // 1. Создание исходных данных (Тест F5)
    int sizeA = GetRandomInt(6, 9);
    int sizeB = GetRandomInt(6, 9);
    int minRange = 10;
    int maxRange = 99;

    cout << "Генерация множеств A и B (диапазон ["
        << minRange << ", " << maxRange << "])..." << endl;

    cout << "Создаем A (кратные 9), требуемый размер: " << sizeA << endl;
    MySet setA(sizeA, minRange, maxRange, 'A');

    cout << "Создаем B (кратные 3), требуемый размер: " << sizeB << endl;
    MySet setB(sizeB, minRange, maxRange, 'B');


    // 2. Тестирование (F6, F7)
    cout << "\n--- Тест F6 (Мощность) и F7 (Вывод) ---" << endl;
    cout << "Мощность A: " << setA.GetPower() << endl; // F6
    cout << "Множество A: " << setA.GetSetAsString(',') << endl; // F7
    cout << "Мощность B: " << setB.GetPower() << endl; // F6
    cout << "Множество B: " << setB.GetSetAsString(',') << endl; // F7

    // 3. Тестирование операций (F9, F10, F11, F12, F13, F14)

    cout << "\n--- Тест F9 (Подмножество) ---" << endl;
    cout << "  A является подмножеством B? -> " << setA.IsSubset(setB) << endl;
    cout << "  A является подмножеством A? -> " << setA.IsSubset(setA) << endl;

    cout << "\n--- Тест F10 (Равенство) ---" << endl;
    cout << "  A равно B? -> " << setA.IsEqual(setB) << endl;
    cout << "  A равно A? -> " << setA.IsEqual(setA) << endl;

    cout << "\n--- Тест F11 (Объединение) ---" << endl;
    MySet setUnion = setA.Union(setB);
    cout << "  Объединение (A U B): " << setUnion.GetSetAsString(',') << endl;

    cout << "\n--- Тест F12 (Пересечение) ---" << endl;
    MySet setInter = setA.Intersection(setB);
    cout << "  Пересечение (A и B): " << setInter.GetSetAsString(',') << endl;

    cout << "\n--- Тест F13 (Разность) ---" << endl;
    MySet setDiffAB = setA.Difference(setB);
    cout << "  Разность (A \\ B): " << setDiffAB.GetSetAsString(',') << endl;
    MySet setDiffBA = setB.Difference(setA);
    cout << "  Разность (B \\ A): " << setDiffBA.GetSetAsString(',') << endl;

    cout << "\n--- Тест F14 (Симметричная разность) ---" << endl;
    MySet setSymDiff = setA.SymmetricDifference(setB);
    cout << "  Симм. разность (A и B): " << setSymDiff.GetSetAsString(',') << endl;


    // 4. Тестирование F8 (Деструктор)
    cout << "\n--- Тест F8 (Очистка памяти) ---" << endl;
    cout << "Завершение main()..." << endl;
    cout << "Деструкторы для всех объектов (setA, setB, setUnion...) "
        << "будут вызваны АВТОМАТИЧЕСКИ." << endl;

    return 0; // <--- Здесь сработают ~MySet() (F8)
}