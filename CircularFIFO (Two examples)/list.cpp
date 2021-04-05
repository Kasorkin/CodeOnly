#include <iostream>

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
        int temp = current->value;
        current->value = NULL;

        if(current == last)
            current = start;
        else
            current = current->next;
        return temp;
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

int main()
{
    CircularFIFO *fifo = new CircularFIFO(4);
    int value;

    while(true)
    {
        cout << "2 to Push, 1 to Pop, 0 to End" << endl;
        cin >> value;

        if(value == 2)
        {
            cout << "Enter the number = ";
            cin >> value;
            bool isPush = fifo->Push(value);
            if(!isPush)
                cout << "Buff is full" << endl;
        }
        else if(value == 1)
        {
            cout << "Result = " << fifo->Pop() << endl;
        }
        else
        {
            break;
        }
    }
    return 0;
}
