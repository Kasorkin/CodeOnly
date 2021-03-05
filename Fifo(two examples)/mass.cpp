#include <iostream>
#include <cstdlib>
#include <locale>

using namespace std;

class Fifo
{
public:
    Fifo(int sizeFifo = 3)
    {
        maxSizeFifo = sizeFifo;
        data = new int[sizeFifo];
    }
    ~Fifo()
    {
        delete data;
    }
    //добавление элемента (перезапись не предусмотрена)
    bool Add(int value)
    {
        if(currentSizeFifo == maxSizeFifo - 1)
        {
            cout << "Buff if full" << endl;
            return false;
        }

        data[currentSizeFifo] = value;
        ++currentSizeFifo;

        return true;
    }
    //получаем текущий элемент
    int Processing()
    {
        //если элемент последний, то возвращаем его и ставим текущим начальный элемент
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

//тест FIFO
int main()
{
    setlocale(LC_ALL, "Russian");
    Fifo *fifo = new Fifo();
    int value;
    int i = 0;
    while(i != 4)
    {
        cout << "Ââåäèòå äîáàâëÿåìûé ýëåìåíò = ";
        cin >> value;
        fifo->Add(value);
        i++;
    }
    while(true)
    {
        cout << "Ïîëó÷èòü ñëåäóþùèé ýëåìåíò? 1 or 0" << endl;
        cin >> value;
        if(value == 0) break;
        cout << "Ðåçóëüòàò = " << fifo->Processing() << endl;

    }
    delete fifo;
    return 0;
}
