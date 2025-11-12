#pragma once

#include <string>
#include <sstream>
#include <random>
#include <list> 
#include <algorithm> 

// Класс "Множество" на основе std::list
class MySet {
private:
    // --- Параметр класса ---
    std::list<int> _elements; // Вместо Node* _head

    // --- Вспомогательный метод (нужен для F5) ---
    int getRandomInt(int minVal, int maxVal);

public:
    // --- Методы класса (F1-F14) ---

    // F1. Конструктор по умолчанию (создание пустого множества)
    MySet();

    // F5. Параметризованный конструктор (создание множества)
    MySet(int count, int minVal, int maxVal, char setRule = ' ');

    // F8. Деструктор (теперь он будет пустым, list чистит себя сам)
    ~MySet();

    // F2. Пустое множество?
    bool IsEmpty() const;

    // F3. Проверка принадлежности (используем итераторы)
    bool IsInSet(int value) const;

    // F4. Добавление элемента (строго в начало!)
    bool AddElement(int value);

    // F6. Мощность множества
    int GetPower() const;

    // F7. Вывод в строку (используем итераторы)
    std::string GetSetAsString(char separator) const;

    // F9. Подмножество?
    bool IsSubset(const MySet& otherSet) const;

    // F10. Равенство?
    bool IsEqual(const MySet& otherSet) const;

    // F11. Объединение
    MySet Union(const MySet& otherSet) const;

    // F12. Пересечение
    MySet Intersection(const MySet& otherSet) const;

    // F13. Разность
    MySet Difference(const MySet& otherSet) const;

    // F14. Симметричная разность
    MySet SymmetricDifference(const MySet& otherSet) const;
};