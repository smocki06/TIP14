//1
#include <iostream>
#include <string>
#include <stack>

using namespace std;

int main() {
    string s;
    getline(cin, s); // Считываем строку целиком

    stack<char> st; // Создаем стек для скобок
    bool isCorrect = true; // Флаг: пока считаем, что всё правильно

    for (int i = 0; i < s.length(); i++) {
        char c = s[i];

        if (c == '(') {
            st.push(c); // Открывающую скобку просто кладем в стек
        } 
        else if (c == ')') {
            // Если встретили закрывающую, но стек пуст — значит, пары нет
            if (st.empty()) {
                isCorrect = false;
                break;
            }
            st.pop(); // Если стек не пуст, убираем парную открывающую
        }
    }

    // В конце, если остались открытые скобки в стеке — тоже ошибка
    if (!st.empty()) {
        isCorrect = false;
    }

    // Выводим результат
    if (isCorrect == true) {
        cout << "yes" << endl;
    } else {
        cout << "no" << endl;
    }

    return 0;
}
//2
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cctype> // Для функции tolower (перевод в нижний регистр)

using namespace std;

int main() {
    string line;
    getline(cin, line); // Читаем всю строку

    stringstream ss(line); // Это как "поток" для разбиения на слова
    string word;
    vector<string> uniq; // Здесь будем хранить уникальные слова

    while (ss >> word) { // Цикл читает слова по одному (пока есть пробелы)
        
        // 1. Очистка от знаков препинания и перевод в нижний регистр
        string cleanWord = "";
        for (char c : word) {
            // Если символ не является знаком препинания (проверяем самые частые)
            if (c != '.' && c != ',' && c != '?' && c != '!' && c != '-' && c != ':') {
                cleanWord += tolower(c); // tolower делает 'А' -> 'а'
            }
        }

        // Если после очистки слово пустое (например, было просто "!!!") - пропускаем
        if (cleanWord == "") continue;

        // 2. Проверка: а есть ли уже такое слово в нашем списке?
        bool found = false;
        for (int i = 0; i < uniq.size(); i++) {
            if (uniq[i] == cleanWord) {
                found = true;
                break; // Если нашли, дальше можно не искать
            }
        }

        // 3. Если не нашли — добавляем в конец списка
        if (found == false) {
            uniq.push_back(cleanWord);
        }
    }

    // Выводим всё, что накопили
    for (int i = 0; i < uniq.size(); i++) {
        cout << uniq[i] << endl;
    }

    return 0;
}
//3
#include <iostream> // Для ввода/вывода
#include <stack>    // Для работы со стеком
#include <algorithm> // Подключили, но в этом простом коде не используем (можно убрать)

using namespace std; // Чтобы не писать std:: везде

int main() { // Главная функция
    stack<int> mainStack; // Создаем основной стек для чисел (int)
    stack<int> minStack;  // Создаем вспомогательный стек для минимумов

    // Создаем функцию push (добавление). auto — это тип, который C++ определяет сам
    auto push = [&](int val) { // [&] означает, что функция "видит" переменные снаружи (mainStack и minStack)
        mainStack.push(val); // Всегда кладем новое число val в основной стек
        
        // Если стек минимумов пуст, ИЛИ новое число меньше или равно текущему минимуму
        if (minStack.empty() || val <= minStack.top()) {
            minStack.push(val); // Кладем это число в стек минимумов
        } else { // Иначе (если число больше текущего минимума)
            minStack.push(minStack.top()); // Кладем копию текущего минимума (он не изменился)
        }
    };

    // Создаем функцию pop (удаление верхнего элемента)
    auto pop = [&]() {
        if (!mainStack.empty()) { // Если основной стек не пуст
            mainStack.pop(); // Удаляем верхний элемент из основного стека
            minStack.pop();  // И одновременно удаляем верхний элемент из стека минимумов
        }
    };

    // Создаем функцию empty (проверка на пустоту)
    auto empty = [&]() {
        return mainStack.empty(); // Возвращаем true, если основной стек пуст, иначе false
    };

    push(5); // Добавляем 5
    push(3); // Добавляем 3 (3 < 5, поэтому в minStack теперь 5, 3)
    push(7); // Добавляем 7 (7 > 3, поэтому в minStack копируется 3: 5, 3, 3)
    
    cout << "Min: " << minStack.top() << endl; // Выводим верхушку minStack (это 3) — минимум
    pop(); // Удаляем верхний элемент (7). Теперь в mainStack 5, 3. В minStack 5, 3
    cout << "Min: " << minStack.top() << endl; // Снова выводим минимум (3)
    pop(); // Удаляем 3. Теперь в mainStack 5. В minStack 5
    cout << "Min: " << minStack.top() << endl; // Выводим минимум (5)

    if (empty()) // Если стек пуст
        cout << "Empty" << endl; // Выводим "Empty"
    else // Иначе
        cout << "Not empty" << endl; // Выводим "Not empty"

    return 0; // Завершаем программу
}
