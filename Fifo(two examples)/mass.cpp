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
    //добавление элементов в очередь (перезапись не предусмотрена)
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
    //получение конкретного элемента очереди
    int Processing()
    {
        //если возвращаемый элемент - последний
        if(currentIndex == currentSizeFifo - 1)
        {
            //создаем временную переменную
            int temp = currentIndex;
            //указываем следующий возвращаемый элемент как первый
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
    Fifo *fifo = new Fifo();
    int value;
    int i = 0;
    while(i != 4)
    {
        cout << "Введите добавляемый элемент = ";
        cin >> value;
        fifo->Add(value);
        i++;
    }
    while(true)
    {
        cout << "Получить следующий элемент? 1 or 0" << endl;
        cin >> value;
        if(value == 0) break;
        cout << "Результат = " << fifo->Processing() << endl;

    }
    delete fifo;
    return 0;
}
