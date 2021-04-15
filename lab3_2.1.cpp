#include <iostream>
#include <math.h>
#include <fstream>
#include <sstream>
using namespace std;

struct tovar
{
    int quantity;
    double price;
};

struct MyQueue
{
    struct Node
    {
        tovar data;
        Node* next;
    };
    Node* First = NULL;
    int Count = 0;
    double full_cost = 0;
    int full_quantity = 0;
    double income = 0;
    bool Push(tovar);
    bool Pop(tovar&);
    void Info();
};

bool MyQueue::Push(tovar dt)
{
    if (!First)
    {
        First = new Node;
        First->next = NULL;
        First->data = dt;
        Count = 1;
        full_cost += dt.price * dt.quantity;
        full_quantity += dt.quantity;
    }
    else
    {
        Node* temp;
        temp = First;
        while (temp->next != NULL) temp = temp->next;
        temp->next = new Node;
        temp->next->data = dt;
        temp->next->next = NULL;
        Count++;
        full_cost += dt.price * dt.quantity;
        full_quantity += dt.quantity;
    }
    return true;
}

bool MyQueue::Pop(tovar& dt)
{
    if (!First) return false;
    Node* temp = First->next;
    dt = First->data;
    delete First;
    First = temp;
    Count--;
    return true;
}

void MyQueue::Info()
{
    {
        cout << endl << "Склад: " << endl;
        cout << "\tРазмер склада = " << Count << endl;
        cout << "\tТовар = " << First->data.quantity << endl;
        cout << "\tЦена за 1шт = " << First->data.price << endl << endl;
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    MyQueue Q;
    tovar dt;
    tovar dt_x;
    ifstream file("file2.txt");
    string line;
    while (getline(file, line))
    {
        istringstream line_F(line);
        line_F >> dt.quantity >> dt.price;
        Q.Push(dt);
    }
    file.close();
    int a;
    Q.Info();
    cout << "1. Поступление товара" << endl;
    cout << "2. Продажа товара" << endl;
    cout << "3. Отчёт" << endl;
    cout << "0. Выход" << endl;
    do
    {
        cin >> a;
        switch (a)
        {
        case 1:
        {
            cout << "Введите цену и кол-во товара:" << endl;
            cout << "Кол-во товара = "; cin >> dt.quantity;
            cout << "Цена за 1шт = "; cin >> dt.price;
            Q.Push(dt);
        }
        break;
        case 2:
        {
            cout << "Введите цену и кол-во товара:" << endl;
            cout << "Кол-во товара ="; cin >> dt_x.quantity;
            cout << "Цена за 1шт = "; cin >> dt_x.price;
            dt = Q.First->data;
            if ((dt_x.price >= dt.price) * (dt_x.quantity <= dt.quantity))
            {
                while (dt_x.quantity)
                {
                    if (dt_x.quantity <= dt.quantity)
                    {
                        Q.income += dt_x.quantity * (dt_x.price - dt.price);
                        Q.full_cost -= dt.price * dt_x.quantity;
                        Q.full_quantity -= dt.quantity;
                        dt.quantity -= dt_x.quantity;
                        dt_x.quantity = 0;
                        Q.First->data.quantity = dt.quantity;
                    }
                    else
                    {
                        Q.income += dt.quantity * (dt_x.price - dt.price);
                        Q.full_cost -= dt.price * dt.quantity;
                        Q.full_quantity -= dt.quantity;
                        dt_x.quantity -= dt.quantity;
                        dt.quantity = 0;
                    }
                    if (dt.quantity == 0)
                    {
                        Q.Pop(dt);
                        dt = Q.First->data;
                    }

                    cout << "Покупка удалась" << endl;
                }
            }
            else
            {
                cout << "Покупка не удалась" << endl;
            }

        }
        break;
        case 3:
        {
            cout << "Размер склада = " << Q.Count << endl;
            cout << "Цена товаров = " << Q.full_cost << endl;
            cout << "Кол-во товаров = " << Q.full_quantity << endl;
            cout << "Прибыль от продажи = " << Q.income << endl;
        }
        break;
        }
    } while (a != 0);


    while (Q.Count)
    {
        Q.Pop(dt);
    }

    return 0;
}