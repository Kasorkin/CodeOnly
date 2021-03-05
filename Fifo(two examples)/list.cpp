#include <iostream>
#include <locale.h>

using namespace std;

class Fifo
{
public:
    Fifo(int sizeFifo = 3)
    {
        maxSizeFifo = sizeFifo;
    }

    //метод добавления (перезапись не предусмотрена)
    bool Add(int value)
    {
        if(currentSizeFifo == maxSizeFifo)
        {
            cout << "Buff is full";
            return false;
        }
        Element *element = new Element;
        element->value = value;

        if(start == nullptr)
        {
            start = current = last = element;
        }
        else
        {
            last->next = element;
            last = element;
        }
        ++currentSizeFifo;

        return true;
    }
    //получаем текущий элемент
    int Processing()
    {
        Element *temp = current;
        if(current == last)
            current = start;
        else
            current = temp->next;
        return temp->value;
    }

private:
    struct Element
    {
        int value;
        Element *next;
    };
    int maxSizeFifo;
    int currentSizeFifo = 0;
    Element *start = nullptr, *last = nullptr, *current = nullptr;
};

//тест
int main()
{
    setlocale(LC_ALL, "Russian");
    Fifo *fifo = new Fifo(4);
    int value;
    for(int i = 0; i < 4; i++)
    {
        cout << "Ââåäèòå ýëåìåíò ";
        cin >> value;
        fifo->Add(value);
    }
    cout << endl;
    for(int i = 0; i < 9; i++)
    {
        cout << "×èñëî: " << fifo->Processing() << endl;
    }
    return 0;
}
