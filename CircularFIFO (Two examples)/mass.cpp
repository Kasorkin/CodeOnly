#include <iostream>
#include <cstdlib>

using namespace std;

class CircularFIFO
{
public:
    CircularFIFO(int sizeFifo = 3)
    {
        maxSizeFifo = sizeFifo;
        data = new int[sizeFifo];
    }
    ~CircularFIFO()
    {
        delete data;
    }

    bool Push(int value)
    {
        if(currentSizeFifo == maxSizeFifo)
        {
            return false;
        }

        data[currentSizeFifo] = value;
        ++currentSizeFifo;

        return true;
    }

    int Pop()
    {
        int temp = data[currentIndex];
        data[currentIndex] = NULL;

        if(currentIndex == currentSizeFifo - 1)
            currentIndex = 0;
        else
            ++currentIndex;

        return temp;
    }

private:
    int *data;
    int currentIndex = 0;
    int currentSizeFifo = 0;
    int maxSizeFifo;
};

int main()
{
    CircularFIFO *fifo = new CircularFIFO();
    int value;
    int i = 0;

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
    delete fifo;
    return 0;
}
