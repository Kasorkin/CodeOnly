using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// Поиск пути по алгоритму А* для проекта Unity2D
/// Кодировка из юнити слетела, потому я вкратце здесь опишу
/// Данный алгоритм позволяет работать с поиском пути как в пошаговых играх, так и в играх в реальном времени
/// Имеется стандартнаяр реализация алгоритма под 4 направления
/// Также, уже конкретно для Unity, добавлена проверка на наличие поиска препятствий
/// Поскольку путь сохраняется из конца в начало (по самому алгоритму), был добавлен метод конвертации, чтобы путь был пересохранен как "из начала в конец"
/// </summary>
public static class AlgorithmAstar 
{
    private static readonly float mass = 1;
    private static readonly int layerMask = 7;

    private static Vector2 startPos;
    private static Vector2 endPos;

    //1 - îáúåêò, 2 - ðîäèòåëü
    private static Dictionary<Vector2, Vector2> parents = new Dictionary<Vector2, Vector2>();

    public static Dictionary<Vector2, Vector2> SearchA(Vector2 startPosition, Vector2 endPosition)
    {
        startPos = startPosition;
        endPos = endPosition;

        List<Vector2> closed = new List<Vector2>();
        List<Vector2> open = new List<Vector2>();

        Dictionary<Vector2, float> generalValue = new Dictionary<Vector2, float>();
        Dictionary<Vector2, float> g = new Dictionary<Vector2, float>();

        //àëãîðèòì
        open.Add(startPos);
        g[startPos] = 0;
        generalValue[startPos] = g[startPos];

        float min = 0;
        int minIndex = 0;
        while (true)
        {
            //íàõîäèì äëèíû è ìèíèìàëüíûé ýëåìåíò èç ñïèñêà îòêðûòûõ
            for (int i = 0; i < open.Count; i++)
            {
                if (i == 0)
                {
                    minIndex = 0;
                    min = generalValue[open[0]];
                }
                if (generalValue[open[i]] < min)
                {
                    minIndex = i;
                    min = generalValue[open[i]];
                }
                //Debug.Log("Äëèíà "+ open[i] + "-ãî ýëåìåíòà = " + generalValue[open[i]]);
            }
            Vector2 currentPos = open[minIndex];
            //Debug.Log("Òåêóùàÿ ïîçèöèÿ" + currentPos);

            //äîáàâèëè â çàêðûòûé è óäàëèëè ñ îòêðûòîãî
            closed.Add(currentPos);
            open.RemoveAt(minIndex);

            //äàííûå ñîñåäåé
            //int index = currentPos.GetComponent<FieldData>().UniqueIndex;
            List<Vector2> neighbors = new List<Vector2>(5);

            //neighbors.Add(currentPos + new Vector3(-1, -1, 0));
            neighbors.Add(currentPos + new Vector2(0, -1));
            //neighbors.Add(currentPos + new Vector3(+1, -1, 0));

            neighbors.Add(currentPos + new Vector2(-1, 0));

            neighbors.Add(Vector2.zero);

            neighbors.Add(currentPos + new Vector2(+1, 0));

            //neighbors.Add(currentPos + new Vector3(-1, 1, 0));
            neighbors.Add(currentPos + new Vector2(0, 1));
            //neighbors.Add(currentPos + new Vector3(+1, 1, 0));

            for (int i = 0; i < 5; i++)
            {
                //åñëè êëåòêà íåïðîõîäèìà èëè â çàêðûòîì, òî èãíîðèðóåì å¸
                if (i == 2 || IsBarier(neighbors[i]) || closed.IndexOf(neighbors[i]) != -1)
                    continue;
                //åñëè êëåòêà íå â îòêðûòîì ñïèñêå, òî äîáàâëÿåì å¸ òóäà è ðàññ÷èòûâàåì äëÿ íå¸ ïóòü
                if (open.IndexOf(neighbors[i]) == -1)
                {
                    open.Add(neighbors[i]);
                    //òåêóùàÿ êëåòêà = ðîäèòåëüñêàÿ äëÿ ýòîé
                    parents[neighbors[i]] = currentPos;
                    //ñ÷èòàåì ñòîèìîñòü
                    g[neighbors[i]] = mass + g[currentPos];
                    //à òåïåðü îáùóþ ñòîèìîñòü
                    generalValue[neighbors[i]] = g[neighbors[i]] + Heuristic(neighbors[i]);
                }//åñëè êëåòêà â îòêðûòîì ñïèñêå, òî ïðîâåðÿåì íå äåøåâëå ëè áóäåò ïóòü ÷åðåç ýòó êëåòêó
            }
            //îñòàíîâêà åñëè äîáàâèëè íóæíóþ êëåòêó â îòêðûòûé ñïèñîê èëè ìû íå íàøëè ïóòü
            if (open.IndexOf(endPos) == -1 && open.Count == 0)
            {
                Debug.Log("Ïóòü íå îáíàðóæåí");
                return null;
            }
            else if (open.IndexOf(endPos) != -1)
            {
                Debug.Log("Ïóòü îáíàðóæåí");
                return ConvertWay();
            }
        }
    }

    //ïåðåñîõðàíÿåì ïóòü â îáðàòíîì ïîðÿäêå
    private static Dictionary<Vector2, Vector2> ConvertWay()
    {
        Dictionary<Vector2, Vector2> newWay = new Dictionary<Vector2, Vector2>();
        Vector2 curPos = endPos;
        //ïîñêîëüêó ìû èùåì ïóòü "ïåðåä òî÷êîé", òî ìû ïðîïóñêàåì ïîñëåäíþþ ïîçèöèþ
        //curPos = parents[curPos];
        while (true)
        {
            if (curPos == startPos) break;

            newWay[parents[curPos]] = curPos;
            curPos = parents[curPos];
        }
        return newWay;
    }

    private static float Heuristic(Vector2 currentPos)
    {
        return Vector2.Distance(currentPos, endPos);
    }
	
	//ïðîâåðêà íà íàëè÷èå ïðåïÿòñòâèÿ â ñëåäóþùåì êâàäðàòå* ïåðåõîäà
    private static bool IsBarier(Vector2 pos)
    {
        RaycastHit2D hit = Physics2D.BoxCast(pos, new Vector2(1,1), 0, Vector2.zero, Mathf.Infinity, 1 << layerMask); 
        if (hit.collider != null)
            return true;
        return false;
    }
}
