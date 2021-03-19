#include <iostream>
#include <cstdlib>
#include <locale>

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
        if(currentSizeFifo == maxSizeFifo - 1)
        {
            return false;
        }

        data[currentSizeFifo] = value;
        ++currentSizeFifo;

        return true;
    }

    int Pop()
    {
        if(currentIndex == currentSizeFifo - 1)
        {
            int temp = currentIndex;
            currentIndex = 0;
            return data[temp];
        }
        return data[currentIndex++];
    }
private:
    int *data;
    int currentIndex = 0;
    int currentSizeFifo = 0;
    int maxSizeFifo;
};

int main()
{
    setlocale(LC_ALL, "Russian");
    CircularFIFO *fifo = new CircularFIFO();
    int value;
    int i = 0;
    while(i != 4)
    {
        cout << "Enter the element = ";
        cin >> value;
        fifo->Push(value);
        i++;
    }
    while(true)
    {
        cout << "Next? 1 or 0" << endl;
        cin >> value;
        if(value == 0) break;
        cout << "Element = " << fifo->Pop() << endl;
    }
    delete fifo;
    return 0;
}
