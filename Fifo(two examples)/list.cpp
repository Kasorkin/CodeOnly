#include <iostream>
#include <locale.h>

using namespace std;

class CircularFIFO
{
public:
    CircularFIFO(int sizeFifo = 3)
    {
        maxSizeFifo = sizeFifo;
    }

    bool Push(int value)
    {
        if(currentSizeFifo == maxSizeFifo)
        {
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
    int Pop()
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
    Element *start = nullptr, *last = nullptr, *current = nullptr;

    int maxSizeFifo;
    int currentSizeFifo = 0;
};

int main()
{
    setlocale(LC_ALL, "Russian");
    CircularFIFO *fifo = new CircularFIFO(4);
    int value;
    for(int i = 0; i < 4; i++)
    {
        cout << "Enter element ";
        cin >> value;
        bool isPush = fifo->Push(value);
        if(!isAdd)
            cout << "Buff is full" << endl;
    }
    cout << endl;
    for(int i = 0; i < 9; i++)
    {
        cout << "Element: " << fifo->Pop() << endl;
    }
    return 0;
}
