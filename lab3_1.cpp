#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;


struct notebook
{
    string Marka;
    int Price;
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
        cout << endl << "Информация о стеке: " << endl;
        cout << "\tРазмер стека = " << Count << endl;
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
    int m = 1;
    while (m)
    {
        S.Info();
        cout << "1. Добавить товар в корзину" << endl;
        cout << "2. Вытащить товар из корзины" << endl;
        cout << "3. Очистить корзину" << endl;
        cout << "4. Информация о корзине" << endl;
        cout << "0. Выход" << endl;
        cin >> m;
        switch (m)
        {
        case 1:
        {
            system("cls");
            cout << "Введите характеристики товара:" << endl;
            cout << "Производитель = "; cin >> dt.Marka;
            cout << "Цена = "; cin >> dt.Price;
            cout << "RAM = "; cin >> dt.RAM;
            cout << "Память = "; cin >> dt.Memory;
            S.Push(dt);
            system("cls");
            break;
        }
        case 2:
        {
            system("cls");
            notebook dt_x;
            bool metka = false;
            cout << "Введите характеристики товара:" << endl;
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
                    metka = true;
                    break;
                }
            }
            if (!metka) cout << "Продукт не найден!!!" << endl;
            while (V.Count)
            {
                V.Pop(dt);
                S.Push(dt);
            }
            system("pause");
            system("cls");
            break;
        }
        case 3:
        {
            system("cls");
            while (S.Count)
            {
                S.Pop(dt);
            }
            break;
        }
        case 4:
        {
            system("cls");
            print(S, V);
            system("pause");
            system("cls");
            break;
        }
        }
    }
}

