#include <vector>
#include <iostream>

using namespace std;

template <class Type>
class Vector
{
private:
    Type* ArrName;
    Type* NewArrName;
    int img = 0;
    int size = 0;

    void NewMemory() {
        NewArrName = new Type[size + size / 2]; // �������� ������ ��� "�����������" ������
        img = size + size / 2; // ���������� ��� ������� � ������ ������

        for (int i = 0; i < size; i++) {
            NewArrName[i] = ArrName[i];
        }

        delete[] ArrName; // ������� �������� ������ ������
        ArrName = NewArrName; // ������������ ������ ��������� � ������ �������
        NewArrName = NULL; // ������� ����� ���������
    }

public:

    Vector() {}

    Vector(unsigned int num) {
        ArrName = new Type[num];
        size = num;
        img = num;
    };

    //������� ��� �������� ��������
    void Creat(unsigned int num) {

        ArrName = new Type[num];
        size = num;
        img = num;
    }; 

    // ����� ������� �� ����� � \n
    void Out() { 
        for (unsigned int i = 0; i < Size(); i++) {
            std::cout << ArrName[i] << ' ';
        }
        std::cout << '\n';
    };

    // ���������� ���������
    int Size() { 
        return size;
    };

    void Add(unsigned int index, Type element) {
        if (size == img) {
            NewMemory();
        }

        for (unsigned int i = 0; i < size - index; i++) { // ��������� �������� �� ����� �����, ���������� ����� ��� ������
            ArrName[size - i] = ArrName[size - i - 1];
        }
        ArrName[index] = element;
        size++;
    };

    void Delete(unsigned int index) {
        for (unsigned int i = index; i < size - 1; i++) {
            ArrName[i] = ArrName[i + 1];
        }
        ArrName[size - 1] = 0;
        size--;
    };

    void AddToTheEnd(Type element) {
        if (size == img) {
            NewMemory();
        }

        ArrName[size] = element;
        size++;
    };

    Type* Link(unsigned int index) {
        if (index < Size()) {
            return ArrName + index * sizeof(Type);
        }
        else {
            std::cout << "����� �� ������� �������" << std::endl; 
            return 0;
        }
    };

    Type& operator[](unsigned int index) {
        return ArrName[index];
    }

    ~Vector() {
        delete[]ArrName;
    };
};

template <class Type>
class List
{
private:

    unsigned int size;

    struct Leaf {
        Type element;
        Leaf* adr = NULL;
    };

    Leaf* next = NULL;
    Leaf* cur = NULL;
    Leaf* list_head = cur;

public:

    List() {};
    List(unsigned int num) {
        for (unsigned int i = 0; i < num; i++) {
            cur = new Leaf;
            cur->adr = next;
            next = cur;

        }

        list_head = cur;
        size = num;
    }

    void Creat(unsigned int num) { 
        for (unsigned int i = 0; i < num; i++) {
            cur = new Leaf;
            cur->adr = next;
            next = cur;

        }

        list_head = cur;
        size = num;
    };

    void Fill() { 
        cur = list_head;

        for (unsigned int i = 0; i < Size(); i++) {
            cur->element = i;
            cur = cur->adr;
        }
    };

    // ����� �� �����
    void Out() { 
        cur = list_head;
        for (unsigned int i = 0; i < Size(); i++) {
            std::cout << cur->element << ' ';
            cur = cur->adr;
        }
        std::cout << '\n';
    };

    // ������ (���-�� ���������)
    int Size() { 
        return size;
    };

    void Add(unsigned int index, Type element) {
        cur = list_head;
        Leaf* newleaf = new Leaf;
        for (unsigned int i = 0; i < index-1; i++) {
            cur = cur->adr;
        }
        newleaf->adr = cur->adr;
        newleaf->element = element;

        cur->adr = newleaf;

        size++;
    }

    void Delete(unsigned int index) {
        cur = list_head;
        Leaf* pre = NULL;
        for (unsigned int i = 0; i < index; i++) {
            pre = cur;
            cur = cur->adr;
        }

        next = cur->adr;
        delete cur;
        pre->adr = next;

        size--;
    };

    void AddToTheEnd(Type element) {
        cur = list_head;
        Leaf* newleaf = new Leaf;
        for (unsigned int i = 0; i < Size()-1; i++) {
            cur = cur->adr;
        }
        newleaf->adr = cur->adr;
        newleaf->element = element;

        cur->adr = newleaf;

        size++;
    };

    void AddInTheBegin(Type element) {
        cur = list_head;
        Leaf* newleaf = new Leaf;
        
        newleaf->adr = cur;
        newleaf->element = element;

        list_head = newleaf;

        size++;
    };

    Leaf* Link(unsigned int index) {
        cur = list_head;
        for (unsigned int i = 0; i < index; i++) {
            cur = cur->adr;
        }

        return cur;
    };

    ~List() {
        for (int i = 0; i < Size(); i++) {
            cur = list_head->adr;
            delete list_head;
            list_head = cur;
        }
    };

    Type& operator[](unsigned int index) {
        cur = list_head;
        for (int i = 0; i < index; i++) {
            cur = cur->adr;
        }
        return cur->element;
    }

};


int main() {

    setlocale(0, "ru");
    std::cout << "�������� ������ �������:" << std::endl;
    std::cout << '\n';

    // �������� � ����������

    //Vector<int> my(5);
    Vector<int> my;
    my.Creat(5);
    std::cout << "������: " << my.Size() << std::endl;

    for (int i = 0; i < my.Size(); i++) {
        my[i] = i;
    }

    std::cout << "��������� ������: " << std::endl;
    for (int i = 0; i < my.Size(); i++) {
        std::cout << my[i] << ' ';
    }
    std::cout << std::endl;
    std::cout << '\n';

    // ���������� �������� �� ������� (������-�������)

    std::cout << "������� 10 �� ����� �������� � ������� 3:" << std::endl;
    my.Add(3, 10);
    my.Out();
    std::cout << "������: " << my.Size() << std::endl;
    std::cout << '\n';

    // �������� �������� �� �������
    
    std::cout << "�������� �������� � �������� 2:" << std::endl;

    my.Delete(2); 
    my.Out();
    std::cout << "������: " << my.Size() << std::endl;
    std::cout << '\n';

    // ������� ������

    std::cout << "���������� 0 ������: " << std::endl;
    my.AddToTheEnd(0);
    my.Out();    
    std::cout << '\n';

    // ��������� ������

    for (int i = 0; i < my.Size(); i++) {
        std::cout << my.Link(i) << '\n';
    }
    std::cout << '\n';


    std::cout << "\n**********\n";

    std::cout << "�������� ������ ������:" << std::endl;
    std::cout << '\n';

    // �������� ������
    std::cout << "�o������� ������: " << std::endl;

    //List<int> li;
    //li.Creat(5);
    //li.Fill();

    List<int> li(9);
    for (int i = 0; i < li.Size(); i++) {
        li[i] = i;
    }
    li.Out();

    std::cout << "������: " << li.Size() << std::endl;
    std::cout << '\n';

    // ���������� ��������
    std::cout << "������� 9 �� ����� �������� � �������� 3:" << std::endl;
    li.Add(3, 9);
    li.Out();
    std::cout << '\n';

    // �������� �������� 
    std::cout << "�������� ��������� � �������� 2:" << std::endl;
    li.Delete(2);
    li.Out();
    std::cout << '\n';

    // ������ � �����
    std::cout << "������� ������ 12:" << std::endl;
    li.AddToTheEnd(12);
    li.Out();
    std::cout << '\n';

    // ������� � ������
    std::cout << "������� ������� 199:" << std::endl;
    li.AddInTheBegin(199);
    li.Out();
    std::cout << '\n';

    // ��������� ������
    std::cout << "��������� ������:" << std::endl;
    for (unsigned int i = 0; i < li.Size(); i++) {
        std::cout << li.Link(i) << ' ';
    }
    std::cout << std::endl;

    return 0;
}