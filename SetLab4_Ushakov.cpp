#include "SetLab4_Ushakov.h"
#include <iostream>

// Используем, чтобы не писать std::
using namespace std;

// --- Вспомогательный метод ---
int MySet::getRandomInt(int minVal, int maxVal) {
    static random_device rd;
    static mt19937 gen(rd());
    std::uniform_int_distribution<> dist(minVal, maxVal);
    return dist(gen);
}

// --- F1. Конструктор по умолчанию ---
MySet::MySet() {
    // _elements (std::list) по умолчанию создается пустым.
    // Ничего делать не нужно.
}

// --- F5. Параметризованный конструктор ---
MySet::MySet(int count, int minVal, int maxVal, char setRule) {
    // _elements уже пустой (благодаря F1)

    // Проверка возможности создания (та же логика, что в ЛР 2 и 3)
    int availableCount = 0;
    for (int i = minVal; i <= maxVal; ++i) {
        if (setRule == 'A' && i % 9 == 0) availableCount++;
        else if (setRule == 'B' && i % 3 == 0) availableCount++;
        else if (setRule != 'A' && setRule != 'B') availableCount++;
    }

    if (count > availableCount) {
        cerr << "Ошибка F5: Невозможно создать множество. "
            << "Требуемое кол-во (" << count
            << ") > чем доступно (" << availableCount << ")" << endl;
        return; // _elements остается пустым
    }

    // Цикл генерации
    int elementsAdded = 0;
    int attempts = 0;
    int maxAttempts = count * 150 + 1000;

    while (elementsAdded < count && attempts < maxAttempts) {
        int randomValue = getRandomInt(minVal, maxVal);
        attempts++;

        // Проверяем правило
        bool passesRule = false;
        if (setRule == 'A') passesRule = (randomValue % 9 == 0);
        else if (setRule == 'B') passesRule = (randomValue % 3 == 0);
        else passesRule = true;

        if (passesRule) {
            // Используем метод AddElement (F4)
            if (this->AddElement(randomValue)) {
                elementsAdded++;
            }
        }
    }
}

// --- F8. Деструктор ---
MySet::~MySet() {
    // std::list сам управляет своей памятью.
    // Деструктор list вызовется автоматически.
    // Ничего делать не нужно.
}

// --- F2. Пустое множество? ---
bool MySet::IsEmpty() const {
    // Используем метод контейнера
    return _elements.empty();
}

// --- F3. Проверка принадлежности ---
bool MySet::IsInSet(int value) const {
    // Используем итераторы и std::find
    // (Подключен через <algorithm> в .h)
    return (std::find(_elements.begin(), _elements.end(), value) != _elements.end());
}

// --- F4. Добавление элемента ---
bool MySet::AddElement(int value) {
    if (this->IsInSet(value)) { // F3
        return false; // Элемент уже есть
    }

    // ТРЕБОВАНИЕ: Добавление строго в начало списка
    _elements.push_front(value);
    return true; // Элемент добавлен
}

// --- F6. Мощность множества ---
int MySet::GetPower() const {
    // Используем метод контейнера
    return _elements.size();
}

// --- F7. Вывод в строку ---
string MySet::GetSetAsString(char separator) const {
    if (this->IsEmpty()) { // F2
        return "Множество пустое";
    }

    stringstream ss;
    // Используем итераторы для обхода
    for (auto it = _elements.begin(); it != _elements.end(); ++it) {
        ss << *it; // Разыменовываем итератор, чтобы получить значение

        // Проверка, чтобы не ставить разделитель в конце
        auto next_it = it;
        ++next_it;
        if (next_it != _elements.end()) {
            ss << separator;
        }
    }
    return ss.str();
}

// --- F9. Подмножество? ---
bool MySet::IsSubset(const MySet& otherSet) const {
    if (this->IsEmpty()) { // F2
        return true;
    }

    // Идем по 'this' (A)
    for (auto it = _elements.begin(); it != _elements.end(); ++it) {
        // Если элемента *it из A нет в B (F3)
        if (!otherSet.IsInSet(*it)) {
            return false;
        }
    }
    return true; // Все элементы A найдены в B
}

// --- F10. Равенство? ---
bool MySet::IsEqual(const MySet& otherSet) const {
    // Оптимизация: если размеры не равны, они точно не равны
    if (this->GetPower() != otherSet.GetPower()) { // F6
        return false;
    }

    // Если размеры равны, достаточно проверить, что A ⊂ B
    return this->IsSubset(otherSet); // F9

    // (Альтернатива, как в ЛР3: 
    // return this->IsSubset(otherSet) && otherSet.IsSubset(*this); )
}

// --- F11. Объединение ---
MySet MySet::Union(const MySet& otherSet) const {
    MySet result; // F1

    // Добавляем все из 'this' (A)
    for (int elem : _elements) { // Упрощенный цикл for
        result.AddElement(elem); // F4
    }

    // Добавляем все из 'otherSet' (B)
    for (int elem : otherSet._elements) {
        result.AddElement(elem); // F4 (сама проверит дубликат)
    }

    return result;
}

// --- F12. Пересечение ---
MySet MySet::Intersection(const MySet& otherSet) const {
    MySet result; // F1

    // Идем по 'this' (A)
    for (int elem : _elements) {
        // Если элемент A есть в B (F3)
        if (otherSet.IsInSet(elem)) {
            result.AddElement(elem); // F4
        }
    }
    return result;
}

// --- F13. Разность ---
MySet MySet::Difference(const MySet& otherSet) const {
    MySet result; // F1

    // Идем по 'this' (A)
    for (int elem : _elements) {
        // Если элемент A НЕту в B (F3)
        if (!otherSet.IsInSet(elem)) {
            result.AddElement(elem); // F4
        }
    }
    return result;
}

// --- F14. Симметричная разность ---
MySet MySet::SymmetricDifference(const MySet& otherSet) const {
    // Логика не меняется, просто вызываются новые методы

    MySet tempUnion = this->Union(otherSet); // F11
    MySet tempIntersection = this->Intersection(otherSet); // F12
    MySet result = tempUnion.Difference(tempIntersection); // F13

    return result;
    // tempUnion и tempIntersection удалятся автоматически (вызов F8)
}