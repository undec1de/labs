#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

struct Cup {
    string color;
    float price, volume, height;
    void Out();
};

struct DLList {
    struct Node {
        Cup data;     // Информация
        Node* next;   // Позиция следующего указателя
        Node* prev;   // Позиция предыдущего указателя
    };

    Node* F = NULL; // Указатель на первый элемент
    Node* L = NULL;     // Указатель на последний элемент
    Node* C = NULL;     // Указатель на текущий элемент
    int Count;        // Счётчик указателя

    void Out();
    void Info();
    void Clear();

    bool MoveNext();
    bool MovePrev();
    bool MoveFirst();
    bool MoveLast();

    bool Init(Cup);
    bool AddNext(Cup);
    bool AddPrev(Cup);
    bool AddFirst(Cup);
    bool AddLast(Cup);

    bool Del(Cup&);
    bool DelNext(Cup&);
    bool DelPrev(Cup&);
    bool DelFirst(Cup&);
    bool DelLast(Cup&);
};

bool DLList::MoveNext() {
    if (!F) {
        return false;
    }
    if (!C) {
        C = F; return true;
    }
    if (!C->next) {
        return false;
    }
    C = C->next;
    return true;
}

bool DLList::MovePrev() {
    if (!F)       return false;
    if (!C) {
        C = F; return true;
    }
    if (!C->prev) {
        return false;
    }
    C = C->prev;
    return true;
}

bool DLList::MoveFirst() {
    if (!F) {
        return false;
    }
    C = F;
    return true;
}

bool DLList::MoveLast() {
    if (!L) {
        return false;
    }
    C = L;
    return true;
}

bool DLList::Init(Cup data) {
    if (!F) {
        F = new Node;
        L = F;
        C = F;
        F->prev = NULL;
        F->next = NULL;
        F->data = data;
        Count = 1;
        return true;
    }
    else
        return false;
}

bool DLList::AddNext(Cup data) {
    if (!F) {
        return Init(data);
    }

    Node* temp = C->next;
    C->next = new Node;
    C->next->next = temp;
    C->next->prev = C;

    if (!temp)
        L = C->next;
    else
        temp->prev = C->next;

    C = C->next;
    C->data = data;
    Count++;
    return true;
}

bool DLList::AddPrev(Cup data) {
    if (!F) {
        return Init(data);
    }

    Node* temp = C->prev;
    C->prev = new Node;
    C->prev->next = C;
    C->prev->prev = temp;

    if (!temp) {
        F = C->prev;
    }
    else {
        temp->next = C->prev;
    }
    C = C->prev;
    C->data = data;
    Count++;
    return true;
}

bool DLList::AddFirst(Cup data) {
    if (MoveFirst()) {
        return AddPrev(data);
    }
    else return false;
}

bool DLList::AddLast(Cup data) {
    if (MoveLast()) {
        return AddNext(data);
    }
    else {
        return false;
    }
}

void DLList::Out() {
    if (!F) {
        cout << "Список пуст" << endl;
        return;
    }

    Node* temp = F;
    cout << "Список: " << endl << endl;
    do {
        temp->data.Out();
        temp = temp->next;
    } while (temp);
    cout << endl;
}

void DLList::Info() {

    if (Count)
        cout << "Количество узлов списка: "
        << Count << endl << endl;
    else
        cout << "Список пуст" << endl;
    if (C) {
        if (MoveFirst()) {
            cout << "Текущие данные узла: ";
            C->data.Out();
        }
    }
}

bool DLList::DelFirst(Cup& data) {
    if (!F)      return false;
    if (C != F) {
        MoveFirst();
    }
    Node* temp = C->next;
    data = C->data;

    if (temp) temp->prev = NULL;
    delete C;

    C = temp;
    F = temp;
    Count--;
    if (!temp) {
        L = NULL;
        return false;
    }
    return true;
}

bool DLList::DelLast(Cup& data) {
    if (!F) {
        return false;
    }
    if (C != L) {
        MoveLast();
    }
    Node* temp = C->prev;
    data = C->data;

    if (temp) temp->next = NULL;
    delete C;

    C = temp;
    L = temp;
    Count--;

    if (!temp) {
        F = NULL;
        return false;
    }
    return true;
}

bool DLList::Del(Cup& data) {
    if (!F) {
        return false;
    }
    if (!C) {
        return false;
    }
    if (C == F) {
        return DelFirst(data);
    }
    if (C == L) {
        return DelLast(data);
    }
    Node* temp = C->next;
    data = C->data;

    C->prev->next = C->next;
    C->next->prev = C->prev;

    delete C;
    C = temp;
    Count--;
    return true;
}

bool DLList::DelNext(Cup& data) {
    if (!F) {
        return false;
    }
    if (!C) {
        return false;
    }
    if (MoveNext()) {
        return Del(data);
    }
    return false;
}
bool DLList::DelPrev(Cup& data) {
    if (!F) {
        return false;
    }
    if (!C) {
        return false;
    }
    if (MovePrev()) {
        return Del(data);
    }
    return false;
}

void DLList::Clear() {
    if (!MoveFirst()) {
        cout << "Список пуст" << endl;
        return;
    }
    Cup k;
    while (Del(k));
}

void Cup::Out() {
    cout << "Цвет: " << color << "\t\t" << "Цена: " << price << "\t" << "Объем: " << volume << "\t" << "Высота: " << height << endl << endl;
}

bool GetFile(DLList&, Cup&);
bool WriteFile(DLList&, Cup&);
void GetCup(Cup&);

int main() {
    setlocale(LC_ALL, "Russian");
    Cup Info;
    DLList DLList;
    GetFile(DLList, Info);
    DLList.Out();
    int num, key = 0, key1 = 0, key2 = 0;
    do {
        cout << "1) Добавить элемент" << endl
            << "2) Удалить элемент" << endl
            << "3) Очистить список" << endl
            << "4) Выгрузить данные" << endl
            << "0) Выход" << endl;
        cout << endl << "Выберите действие: ";
        cin >> key;
        cout << endl;
        switch (key) {
        case 1:
            cout << "1) Добавить в начаоло" << endl
                << "2) Добавить в конец" << endl
                << "3) Добавить на k позицию" << endl
                << "0) Назад" << endl;
            cout << endl << "Выберите действие: ";
            cin >> key1;
            cout << endl;
            switch (key1) {
            case 1:
                GetCup(Info);
                DLList.AddFirst(Info);
                DLList.Out();
                break;
            case 2:
                GetCup(Info);
                DLList.AddLast(Info);
                DLList.Out();
                break;
            case 3:
                cout << "Введите позицию: ";
                cin >> num;
                GetCup(Info);
                if (num == 1) {
                    DLList.AddFirst(Info);
                    DLList.Out();
                    break;
                }
                else if (num == DLList.Count + 1) {
                    DLList.AddLast(Info);
                    DLList.Out();
                    break;
                }
                DLList.MoveFirst();
                for (int i = 1; i < num - 1; i++) {
                    DLList.MoveNext();
                }
                DLList.AddNext(Info);
                DLList.Out();
                break;
            default:
                if (key1 != 0) {
                    cout << "Нет такого действия!" << endl << endl;
                }
                break;
            }
            break;
        case 2:
            cout << "1) Удалить первый элем." << endl
                << "2) Удалить последний элем." << endl
                << "3) Удалить k позицию" << endl
                << "0) Назад" << endl;
            cout << endl << "Выберите действие: ";
            cin >> key2;
            cout << endl;
            switch (key2) {
            case 1:
                DLList.DelFirst(Info);
                DLList.Out();
                break;
            case 2:
                DLList.DelLast(Info);
                DLList.Out();
                break;
            case 3:
                cout << "Введите позицию: ";
                cin >> num;
                if (num == 1) {
                    DLList.DelFirst(Info);
                    DLList.Out();
                    break;
                }
                else if (num == DLList.Count) {
                    DLList.DelLast(Info);
                    DLList.Out();
                    break;
                }
                DLList.MoveFirst();
                for (int i = 1; i < num; i++) {
                    DLList.MoveNext();
                }
                DLList.Del(Info);
                DLList.Out();
                break;
            default:
                if (key2 != 0) {
                    cout << "Нет такого действия!" << endl << endl;
                }
                break;
            }
            break;
        case 3:
            DLList.Clear();
            DLList.Out();
            break;
        case 4:
            WriteFile(DLList, Info);
            break;
        default:
            if (key != 0) {
                cout << "Нет такого действия!" << endl << endl;
            }
            DLList.Clear();
            DLList.Out();
            break;
        }
    } while (key != 0);
}

bool GetFile(DLList& DLList, Cup& Info) {
    ifstream F("Cup.txt");
    if (!F) {
        cout << "Файл не найден!" << endl;
        return false;
    }
    while (F >> Info.color >> Info.price >> Info.volume >> Info.height) {
        DLList.AddNext(Info);
    }
    F.close();
    return true;
}

bool WriteFile(DLList& DLList, Cup& Info) {
    ofstream F("Cup.txt");
    if (!F) {
        cout << "Файл не найден!" << endl;
        return false;
    }
    DLList.MoveFirst();
    do {
        F << DLList.C->data.color << " " << DLList.C->data.price << " " << DLList.C->data.volume << " " << DLList.C->data.height << endl;
    } while (DLList.MoveNext());
    DLList.MoveFirst();
    F.close();
    return true;
}

void GetCup(Cup& Info) {
    cout << "Введите цвет: ";
    cin >> Info.color;
    cout << endl;
    cout << "Введите цену: ";
    cin >> Info.price;
    cout << endl;
    cout << "Введите объем: ";
    cin >> Info.volume;
    cout << endl;
    cout << "Введите высоту: ";
    cin >> Info.height;
    cout << endl;
}