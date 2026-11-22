// Лабораторная работа №5. Вариант 13.
// Класс «книга» из лабораторной работы №4 (поля: ФИО автора, название, издательство, год издания, число страниц).
// Объекты добавляются в контейнер set (сортировка по ФИО автора, как в ЛР4)
// и в контейнер unordered_set. Исходные данные читаются из input.txt (как в ЛР4),
// объекты контейнеров выводятся в output.txt для контроля.
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <unordered_set>
using namespace std;

class Book // Класс - книга
{
    string author;    // ФИО автора
    string title;     // Название
    string publisher; // Издательство
    int year;         // Год издания
    int pages;        // Число страниц
public:
    Book() // Конструктор без параметров
    {
        author = ""; title = ""; publisher = ""; year = 0; pages = 0;
    }
    Book(string author, string title, string publisher, int year, int pages) // Конструктор для инициализации полей
    {
        this->author = author; this->title = title; this->publisher = publisher; this->year = year; this->pages = pages;
    }
    // Конструктор копирования, конструктор перемещения и операции присваивания не нужны:
    // в классе нет указателей и динамической памяти, поэтому подходят стандартные, которые
    // создает компилятор.
    bool operator <(const Book & c) const // Сравнение по ФИО автора (используется при упорядочивании в set)
    {
        return author < c.author;
    }
    string getKey() const // Ключ (нужен для хеш-функции)
    {
        return author;
    }
    bool operator ==(const Book & c) const // Для unordered_set: объекты равны, если равны ключи
    {
        return author == c.author;
    }
    friend ostream & operator <<(ostream & out, const Book & c); // Дружественная функция вставки в поток
};
ostream & operator <<(ostream & out, const Book & c) // Вставка объекта в поток
{
    out << c.author << ". " << c.title << ". " << c.publisher << ", " << c.year << ", " << c.pages << " p.";
    return out;
}
struct BookHash // Хеш-функция для unordered_set: хеш от ключа
{
    size_t operator()(const Book & c) const
    {
        return hash<string>()(c.getKey());
    }
};

int main()
{
    ifstream fin("input.txt"); // Входной файл
    ofstream fout("output.txt"); // Выходной файл
    if (!fin) // Ошибка файл не открыт
    {
        cerr << "Error, input.txt not found" << endl;
        return 1;
    }
    int n; // Число объектов в файле
    fin >> n;
    fin.ignore(2, '\n'); // Пропускаем символы перехода на новую строку
    set<Book> s; // Упорядоченный контейнер
    unordered_set<Book, BookHash> u; // Неупорядоченный контейнер
    for (int i = 0; i < n; i++) // Читаем объекты из файла и добавляем в оба контейнера
    {
        string author, title, publisher;
        int year, pages;
        getline(fin, author); // Строки могут содержать пробелы
        getline(fin, title);
        getline(fin, publisher);
        fin >> year >> pages; // Год и число страниц в одной строке
        fin.ignore(2, '\n');
        Book c(author, title, publisher, year, pages);
        s.insert(c); // Если объект с таким ключом уже есть, второй раз не добавляется
        u.insert(c);
    }
    fout << "Read from file: " << n << " objects" << endl << endl;
    fout << "set (sorted by author), " << s.size() << " objects:" << endl;
    for (const Book & c : s) fout << c << endl; // Используем перегруженную операцию <<
    fout << endl << "unordered_set (order is not defined), " << u.size() << " objects:" << endl;
    for (const Book & c : u) fout << c << endl;
    return 0;
}
