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
#include <iostream>
#include <stack>
#include <algorithm> // Для min()

using namespace std;

int main() {
    stack<int> mainStack; // Обычный стек
    stack<int> minStack;  // Стек для минимумов

    // Функция добавления (push)
    auto push = [&](int val) { // Лямбда-функция (просто способ создать функцию внутри main)
        mainStack.push(val);
        
        // Если стек минимумов пуст, или новое число меньше/равно текущему минимуму
        if (minStack.empty() || val <= minStack.top()) {
            minStack.push(val); // Кладем его
        } else {
            minStack.push(minStack.top()); // Иначе копируем старый минимум
        }
    };

    // Функция извлечения (pop)
    auto pop = [&]() {
        if (!mainStack.empty()) {
            mainStack.pop();
            minStack.pop(); // Удаляем из обоих стеков
        }
    };

    // Функция проверки на пустоту (empty)
    auto empty = [&]() {
        return mainStack.empty();
    };

    // Проверка работы
    push(5);
    push(3);
    push(7);
    
    cout << "Min: " << minStack.top() << endl; // 3
    pop(); // удалили 7
    cout << "Min: " << minStack.top() << endl; // 3
    pop(); // удалили 3
    cout << "Min: " << minStack.top() << endl; // 5

    if (empty()) cout << "Empty" << endl;
    else cout << "Not empty" << endl;

    return 0;
}
