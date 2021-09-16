#include <iostream>
#include <string>
#include <fstream>
using namespace std;


struct Cup {
    string color;
    double price;
    double volume;
    int height;
};

struct Queue {
    struct Node { int n; char* data; Node* next; };
    Node* First = NULL;
    int count = 0;
    bool Push(char*, int);
    bool Pop(char*&, int&);
    void Info();
};

bool Queue::Push(char* data, int n) {
    if (!First) {
        First = new Node;
        First->next = NULL;
        First->n = n;
        First->data = new char[n];
        for (int i = 0; i < n; i++) {
            First->data[i] = data[i];
        }
        count = 1;
    }
    else {
        Node* temp;
        temp = First;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = new Node;
        temp->next->data = new char[n];
        temp->next->next = NULL;
        temp->next->n = n;
        for (int i = 0; i < n; i++) {
            temp->next->data[i] = data[i];
        }
        count++;
    }
    return true;
}

bool Queue::Pop(char*& data, int& n) {
    if (!First) return false;
    Node* temp = First->next;
    n = First->n;
    for (int i = 0; i < n; i++) {
        data[i] = First->data[i];
    }
    delete First->data;
    delete First;
    First = temp;
    count--;
    return true;
}

void Queue::Info() {
    if (!First) cout << "Корзина пуста" << endl;
    else {
        cout << "Размер корзины = " << count << endl;
    }
}

void Menu();
void ClearBinaryFile();
void WriteBinaryFile(char*, int);
bool ReadBinaryFile(Queue&, int);
void FeedFromBinaryFile(Queue&);
void AddProduct(Queue&);
void PullOut(Queue&);
void Clear(Queue&);
void ClearExit(Queue&);
void GetSeria(char*&, int&, Cup);
void GetDeSeria(char*, int, Cup&);
void ShowProduct(Cup);

void GetSeria(char*& data, int& n, Cup a) {
    size_t s1 = a.color.size();
    int n0 = sizeof(size_t);
    int n1 = s1;
    int n2 = sizeof(double);
    int n3 = n2;
    int n4 = sizeof(int);
    n = n0 + n1 + n2 + n3 + n4;
    data = new char[n];

    char* d0 = reinterpret_cast<char*>(&s1);
    char* d1 = const_cast<char*>(a.color.c_str());
    char* d2 = reinterpret_cast<char*>(&a.price);
    char* d3 = reinterpret_cast<char*>(&a.volume);
    char* d4 = reinterpret_cast<char*>(&a.height);

    for (int i = 0; i < n0; i++) data[i] = d0[i];
    for (int i = 0; i < n1; i++) data[i + n0] = d1[i];
    for (int i = 0; i < n2; i++) data[i + n0 + n1] = d2[i];
    for (int i = 0; i < n3; i++) data[i + n0 + n1 + n2] = d3[i];
    for (int i = 0; i < n4; i++) data[i + n0 + n1 + n2 + n3] = d4[i];
}

void GetDeSeria(char* data, int n, Cup& a) {
    int n0, n1, n2, n3, n4;
    n0 = sizeof(size_t);
    n2 = sizeof(double);
    n3 = n2;
    n4 = sizeof(int);
    size_t p = *reinterpret_cast<size_t*>(data);
    n1 = p;
    string ss1(data + n0, p);

    a.color = ss1;
    a.price = *reinterpret_cast<double*>(data + n0 + n1);
    a.volume = *reinterpret_cast<double*>(data + n0 + n1 + n2);
    a.height = *reinterpret_cast<int*>(data + n0 + n1 + n2 + n3);
}

void Menu() {
    Queue q;
    int key;
    FeedFromBinaryFile(q);
    do {
        system("cls");
        cout << "1. Добавить товар" << endl;
        cout << "2. Вытащить продукт" << endl;
        cout << "3. Очистить корзину" << endl;
        cout << "0. Выход" << endl;
        q.Info();
        cout << "Введите номер: ";
        cin >> key;

        switch (key) {
        case 1: AddProduct(q); break;
        case 2: PullOut(q); break;
        case 3: Clear(q); break;
        case 0: ClearExit(q); break;
        default:  system("cls");
            cout << "Ошибка!" << endl;
            system("pause");
        }
    } while (key);
}

void ClearBinaryFile() {
    fstream f_out;
    f_out.open("cup.dat", ios::out | ios::binary);
    f_out.close();
}

void WriteBinaryFile(char* data, int n) {
    fstream f_out;
    f_out.open("cup.dat", ios::app | ios::binary);
    f_out.write((char*)&n, sizeof(int));
    f_out.write(data, n);
    f_out.close();
}

bool ReadBinaryFile(Queue& q, int m) {
    fstream f_in("cup.dat", ios::in | ios::binary);
    if (!f_in) {
        cout << "Ошибка, файл не обнаружен!" << endl;
        return false;
    }
    int n;
    Cup p;
    while (!f_in.eof()) {
        for (int i = 0; i < m; i++) {
            if (f_in.read((char*)&n, sizeof(int))) {
                char* data = new char[n];
                f_in.read(data, n);
                i++;
                q.Push(data, n);
                delete[] data;
            }
        }
    }
    f_in.close();
    return true;
}

void FeedFromBinaryFile(Queue& q) {
    Cup p[] = {
        {"red", 450, 0.5, 10},
        {"black", 300, 0.3, 11},
        {"green", 200, 0.4, 14}
    };
    char* data;
    int ssize, m = 3;
    system("cls");
    ClearBinaryFile();
    for (int i = 0; i < m; i++) {
        GetSeria(data, ssize, p[i]);
        ShowProduct(p[i]);
        WriteBinaryFile(data, ssize);
    }
    ReadBinaryFile(q, m);
    system("pause");
}

void AddProduct(Queue& q) {
    Cup p;
    string color;
    double price, volume;
    char* data;
    int ssize, height;
    system("cls");
    cout << "Введите характеристики товара(цвет, цена, объем, высота): " << endl;
    cin >> color >> price >> volume >> height;
    while (volume <= 0 || price < 0 || height < 0) {
        cout << "Ошибка цены, объемаб высоты!" << endl;
        cout << "Цена: ";
        cin >> price;
        cout << "Объем: ";
        cin >> volume;
        cout << "Высота: ";
        cin >> height;
    }

    p = { color, price, volume, height };
    GetSeria(data, ssize, p);
    q.Push(data, ssize);
    data = NULL;
    delete[] data;
}

void PullOut(Queue& q) {
    Cup p;
    string color;
    double price, volume;
    int ssize, height, count = q.count;
    char* data;
    system("cls");
    if (q.count == 0) {
        cout << "В корзине нет товара!" << endl;
        system("pause");
        return;
    }
    cout << "Введите характеристики товара(цвет, цена, объем, высота): ";
    cin >> color >> price >> volume >> height;
    while (volume <= 0 || price < 0 || height < 0) {
        cout << "Ошибка цены, объемаб высоты!" << endl;
        cout << "Цена: ";
        cin >> price;
        cout << "Объем: ";
        cin >> volume;
        cout << "Высота: ";
        cin >> height;
    }

    for (int i = 0; i < count; i++) {
        data = q.First->data;
        ssize = q.First->n;
        GetDeSeria(data, ssize, p);
        if ((color == p.color) && (price == p.price) && (volume == p.volume) && (height == p.height)) {
            q.Pop(data, ssize);
            cout << "Товар найден!" << endl;
            data = NULL;
            delete[] data;
            system("pause");
            return;
        }
        else {
            GetDeSeria(data, ssize, p);
            q.Pop(data, ssize);
            GetSeria(data, ssize, p);
            q.Push(data, ssize);
        }
    }
    cout << "В корзине нет товара!" << endl;
    data = NULL;
    delete[] data;
    system("pause");
}

void Clear(Queue& q) {
    Cup p;
    char* data;
    int ssize, i = 1;
    system("cls");
    while (q.count) {
        data = q.First->data;
        ssize = q.First->n;
        GetDeSeria(data, ssize, p);
        q.Pop(data, ssize);
        cout << i << ". ";
        ShowProduct(p);
        i++;
        data = NULL;
    }
    system("pause");
}

void ClearExit(Queue& q) {
    Cup p;
    char* data;
    int ssize;
    while (q.count) {
        data = q.First->data;
        ssize = q.First->n;
        GetDeSeria(data, ssize, p);
        q.Pop(data, ssize);
        data = NULL;
    }
}


void ShowProduct(Cup p) {
    cout << "\tЦвет: " << p.color
        << "\tЦена: " << p.price
        << "\tОбъем: " << p.volume
        << "\tВысота: " << p.height << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    Menu();
    return 0;
}