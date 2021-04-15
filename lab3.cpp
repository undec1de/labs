#include <iostream>
#include <math.h>
#include <fstream>
#include <sstream>
using namespace std;

struct notebook
{
    string Marka;
    string Price;
    int RAM;
    int Memory;
};

struct MyStack
{
    struct Node
    {
        notebook data;
        Node* prev;
    };
    Node* Top = NULL;
    int Count = 0;
    bool Push(notebook);
    bool Pop(notebook&);
    void Info();
};

bool MyStack::Push(notebook dt)
{
    if (!Top)
    {
        Top = new Node;
        Top->prev = NULL;
        Count = 1;
    }
    else
    {
        Node* temp;
        temp = new Node;
        temp->prev = Top;
        Top = temp;
        Count++;
    }
    Top->data = dt;
    return true;
}

bool MyStack::Pop(notebook& dt)
{
    if (!Top) return false;
    Node* temp = Top->prev;
    dt = Top->data;
    delete Top;
    Top = temp;
    Count--;
    return true;
}

void MyStack::Info()
{
   
    {
        cout << endl << "Корзина: " << endl;
        cout << "\tРазмер корзины = " << Count << endl;
        cout << "\tПроизводитель = " << Top->data.Marka << endl;
        cout << "\tЦена = " << Top->data.Price << endl;
        cout << "\tRAM = " << Top->data.RAM << endl;
        cout << "\tПамять = " << Top->data.Memory << endl << endl;
    }
}
void print(MyStack& S, MyStack& V)
{
    notebook dt;
    while (S.Count)
    {
        S.Pop(dt);
        cout << "\tПроизводитель = " << dt.Marka << endl;
        cout << "\tЦена = " << dt.Price << endl;
        cout << "\tRAM = " << dt.RAM << endl;
        cout << "\tПамять = " << dt.Memory << endl << endl;
        V.Push(dt);
    }
    while (V.Count)
    {
        V.Pop(dt);
        S.Push(dt);
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    MyStack S;
    MyStack V;
    notebook dt;
    ifstream file("file.txt");
    string line;
    while (getline(file, line))
    {
        istringstream line_F(line);
        line_F >> dt.Marka >> dt.Price >> dt.RAM >> dt.Memory;
        S.Push(dt);
    }
    file.close();
    S.Info();
    cout << "------------------------------------" << endl;
    cout << "1. Добавить товар" << endl;
    cout << "2. Вытащить товар" << endl;
    cout << "3. Очистить корзину" << endl;
    cout << "0. Выйти" << endl;
    cout << "------------------------------------" << endl;
    int a;
    do
    {
        cin >> a;
        switch (a)
        {
        case 1:
        {
            cout << "Введите товар:" << endl;
            cout << "Производитель = "; cin >> dt.Marka;
            cout << "Цена = "; cin >> dt.Price;
            cout << "RAM = "; cin >> dt.RAM;
            cout << "Память = "; cin >> dt.Memory;
            S.Push(dt);
        }
        break;
        case 2:
        {
            notebook dt_x;
            bool z = true;
            cout << "Введите товар:" << endl;
            cout << "Производитель = "; cin >> dt_x.Marka;
            cout << "Цена = "; cin >> dt_x.Price;
            cout << "RAM = "; cin >> dt_x.RAM;
            cout << "Память = "; cin >> dt_x.Memory;
            while (S.Count)
            {
                S.Pop(dt);
                if (dt.Marka != dt_x.Marka || dt.Price != dt_x.Price || dt.RAM != dt_x.RAM || dt.Memory != dt_x.Memory)
                {
                    V.Push(dt);
                }
                else
                {
                    z = false;
                    break;
                }
            }
            if (z) cout << "Товар не найден!!!" << endl;
            while (V.Count)
            {
                V.Pop(dt);
                S.Push(dt);
            }
        }
        break;
        case 3:
        {
            while (S.Count)
            {
                S.Pop(dt);
            }
        }
        break;
        }
    } while (a != 0);
}