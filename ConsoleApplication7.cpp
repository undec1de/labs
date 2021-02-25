#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
using namespace std;

void fillarr(double* arr, int n);
void printarr(double* arr, int n);
double* createarr(int n);
void reassign(double*& arr, int& n, int k, double number);
void del(double*& arr, int& n, int k);
void zd7(double*& arr, int& n, double number, double x);
void zd8(double*& arr, int& n, double x);
int check_n();
void number_menu(double& number);

int main()
{
    setlocale(LC_ALL, "Russian");
    int n = check_n();
    if (!n)
    {
        cout << "Данные файла неверны" << endl;
        return 0;
    }
    double* arr = createarr(n);
    fillarr(arr, n);
    double number;
    int m = 1;
    while (m)
    {
        system("cls");
        cout << "Массив: ";
        printarr(arr, n);
        cout << "Введите номер задания (1-8) (0 - выход): "; cin >> m;
        switch (m)
        {
        case 1:
        {
            number_menu(number);
            reassign(arr, n, n + 1, number);
            break;
        }
        case 2:
        {
            number_menu(number);
            reassign(arr, n, 1, number);
            break;
        }
        case 3:
        {
            unsigned int k;
            cout << "Введите позицию элемента: "; cin >> k;
            number_menu(number);
            reassign(arr, n, k, number);
            break;
        }
        case 4:
        {
            del(arr, n, n);
            break;
        }
        case 5:
        {
            del(arr, n, 1);
            break;
        }
        case 6:
        {
            unsigned int k;
            cout << "Введите позицию элемента: "; cin >> k;
            del(arr, n, k);
            break;
        }
        case 7:
        {
            double x;
            cout << "Введите элемент, после которого вы хотите добавить элемент: "; cin >> x;
            number_menu(number);
            zd7(arr, n, number, x);
            system("pause");
            break;
        }
        case 8:
        {
            double x;
            cout << "Введите элемент, который хотите удалить: "; cin >> x;
            zd8(arr, n, x);
            system("pause");
            break;
        }
        }
    }
    delete[] arr;
}
void number_menu(double& number)
{
    int m = 1;
    double a = -100;
    double b = 100;
    cout << "Какое число мы добавим?" << endl;
    cout << "1 - случайное число" << endl;
    cout << "2 - ввести число" << endl;
    cin >> m;
    switch (m)
    {
    case 1:
    {
        srand(time(0));
        number = a + (b - a) * (double)rand() / RAND_MAX;
        m = 0;
        break;
    }
    case 2:
    {
        cout << "Введите число: ";
        cin >> number;
        m = 0;
        break;
    }
    default:
    {
        cout << "Ошибка" << endl;
        break;
    }
    }
}
void fillarr(double* arr, int n)
{
    fstream A("data.txt", ios::in);
    for (int i = 0; i < n; i++)
    {
        A >> arr[i];
    }
    A.close();
}
void printarr(double* arr, int n)
{
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}
double* createarr(int n)
{
    double* arr = new double[n];
    return arr;
}
void reassign(double*& arr, int& n, int k, double number)
{
    k--;
    if (k >= 0 && k <= n)
    {
        double* buff = new double[n + 1];
        for (int i = 0; i < k; i++)
            buff[i] = arr[i];
        buff[k] = number;
        n++;
        for (int i = k + 1; i < n; i++)
            buff[i] = arr[i - 1];
        delete[] arr;
        arr = buff;
    }
    else cout << "ошибка";
}
void del(double*& arr, int& n, int k)
{
    k--;
    if (k >= 0 && k <= n)
    {
        double* buff = new double[n - 1];
        for (int i = 0; i < k; i++)
            buff[i] = arr[i];
        n--;
        for (int i = k; i < n; i++)
            buff[i] = arr[i + 1];
        delete[] arr;
        arr = buff;
    }
    else cout << "ошибка";
}
void zd7(double*& arr, int& n, double number, double x)
{
    int k = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == x)
        {
            k = i + 1;
            break;
        }
    }
    if (k > 0)
    {
        double* buff = new double[n + 1];
        for (int i = 0; i < k; i++)
        {
            buff[i] = arr[i];
        }
        n++;
        buff[k] = number;
        for (int i = k + 1; i < n; i++)
        {
            buff[i] = arr[i - 1];
        }
        delete[] arr;
        arr = buff;
    }
    else cout << "элемент не найден" << endl;
}
void zd8(double*& arr, int& n, double x)
{
    int k = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == x)
        {
            k++;
        }
    }
    if (k > 0)
    {
        k = 0;
        double* buff = new double[n - k];
        for (int i = 0; i < n; i++)
        {
            if (arr[i] == x)
            {
                k++;
            }
            else buff[i - k] = arr[i];
        }
        n -= k;
        delete[] arr;
        arr = buff;
    }
    else cout << "элемент не найден" << endl;
}
int check_n()
{
    double a;
    int k = 0;
    fstream A("data.txt", ios::in);
    while (A >> a)
    {
        k++;
    }
    A.close();
    return k;
}
