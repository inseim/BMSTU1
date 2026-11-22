// Лабораторная работа №4. Вариант 13.
// Объект - книга (поля: ФИО автора, название, издательство, год издания, число страниц).
// Исходный контейнер vector, копируем в deque. Сортировка по ФИО автора.
// Элементы контейнеров - объекты класса, а не указатели.
// Исходные данные читаются из input.txt, результаты выводятся в output.txt.
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm> // copy, sort
using namespace std;

class Book // Класс - книга
{
    string author;    // ФИО автора
    string title;     // Название
    string publisher; // Издательство
    int year;         // Год издания
    int pages;        // Число страниц
public:
    Book() // Конструктор без параметров (нужен, потому что контейнер для копирования создается сразу нужного размера)
    {
        author = ""; title = ""; publisher = ""; year = 0; pages = 0;
    }
    Book(string author, string title, string publisher, int year, int pages) // Конструктор для инициализации полей
    {
        this->author = author; this->title = title; this->publisher = publisher; this->year = year; this->pages = pages;
    }
    // Конструктор копирования, конструктор перемещения и операции присваивания не нужны:
    // в классе нет указателей и динамической памяти, поля копируются и перемещаются
    // корректно стандартными средствами, которые создает компилятор.
    bool operator <(const Book & c) const // Сравнение по ФИО автора (используется при сортировке)
    {
        return author < c.author;
    }
    friend ostream & operator <<(ostream & out, const Book & c); // Дружественная функция вставки в поток
};
ostream & operator <<(ostream & out, const Book & c) // Вставка объекта в поток
{
    out << c.author << ". " << c.title << ". " << c.publisher << ", " << c.year << ", " << c.pages << " p.";
    return out;
}

int main()
{
    ifstream fin("input.txt"); // Входной файл
    ofstream fout("output.txt"); // Выходной файл
    if (!fin) // Ошибка файл не открыт
    {
        cerr << "Error, input.txt not found" << endl;
        return 1;
    }
    int n; // Число объектов
    fin >> n;
    fin.ignore(2, '\n'); // Пропускаем символы перехода на новую строку
    vector<Book> items; // Исходный контейнер vector
    for (int i = 0; i < n; i++) // Читаем объекты из файла
    {
        string author, title, publisher;
        int year, pages;
        getline(fin, author); // Строки могут содержать пробелы
        getline(fin, title);
        getline(fin, publisher);
        fin >> year >> pages; // Год и число страниц в одной строке
        fin.ignore(2, '\n');
        items.push_back(Book(author, title, publisher, year, pages));
    }

    // Копируем исходный контейнер vector в deque алгоритмом copy (до сортировки)
    deque<Book> copy_items(items.size()); // Нужный размер контейнера задаем заранее
    copy(items.begin(), items.end(), copy_items.begin());

    fout << "Source container (vector):" << endl;
    for (const Book & c : items) fout << c << endl; // Используем перегруженную операцию <<

    sort(items.begin(), items.end()); // Сортировка алгоритмом sort: итератор на начало и итератор на конец
    fout << endl << "Container after sorting (std::sort by author):" << endl;
    for (const Book & c : items) fout << c << endl;

    fout << endl << "Copy of the source container (deque, algorithm copy):" << endl;
    for (const Book & c : copy_items) fout << c << endl;

    if (n > 0) // Демонстрация копирования объекта (стандартные конструктор копирования и присваивание)
    {
        Book first = items.front(); // Конструктор копирования
        Book other;
        other = first; // Присваивание с копированием
        fout << endl << "Copy constructor: " << first << endl;
        fout << "Assignment:       " << other << endl;
    }
    return 0;
}
