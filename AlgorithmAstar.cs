using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// –еализаци€ алгоритма ј* дл€ 2D игры в Unity
/// </summary>
public static class AlgorithmAstar 
{
    private static readonly float mass = 1;
    private static readonly int layerMask = 7;

    private static Vector2 startPos;
    private static Vector2 endPos;

    //1 - объект, 2 - родитель
    private static Dictionary<Vector2, Vector2> parents = new Dictionary<Vector2, Vector2>();

    public static Dictionary<Vector2, Vector2> SearchA(Vector2 startPosition, Vector2 endPosition)
    {
        startPos = startPosition;
        endPos = endPosition;

        List<Vector2> closed = new List<Vector2>();
        List<Vector2> open = new List<Vector2>();

        Dictionary<Vector2, float> generalValue = new Dictionary<Vector2, float>();
        Dictionary<Vector2, float> g = new Dictionary<Vector2, float>();

        //алгоритм
        open.Add(startPos);
        g[startPos] = 0;
        generalValue[startPos] = g[startPos];

        float min = 0;
        int minIndex = 0;
        while (true)
        {
            //находим длины и минимальный элемент из списка открытых
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
                //Debug.Log("ƒлина "+ open[i] + "-го элемента = " + generalValue[open[i]]);
            }
            Vector2 currentPos = open[minIndex];
            //Debug.Log("“екуща€ позици€" + currentPos);

            //добавили в закрытый и удалили с открытого
            closed.Add(currentPos);
            open.RemoveAt(minIndex);

            //данные соседей
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
                //если клетка непроходима или в закрытом, то игнорируем еЄ
                if (i == 2 || IsBarier(neighbors[i]) || closed.IndexOf(neighbors[i]) != -1)
                    continue;
                //если клетка не в открытом списке, то добавл€ем еЄ туда и рассчитываем дл€ неЄ путь
                if (open.IndexOf(neighbors[i]) == -1)
                {
                    open.Add(neighbors[i]);
                    //текуща€ клетка = родительска€ дл€ этой
                    parents[neighbors[i]] = currentPos;
                    //считаем стоимость
                    g[neighbors[i]] = mass + g[currentPos];
                    //а теперь общую стоимость
                    generalValue[neighbors[i]] = g[neighbors[i]] + Heuristic(neighbors[i]);
                }//если клетка в открытом списке, то провер€ем не дешевле ли будет путь через эту клетку
            }
            //остановка если добавили нужную клетку в открытый список или мы не нашли путь
            if (open.IndexOf(endPos) == -1 && open.Count == 0)
            {
                Debug.Log("ѕуть не обнаружен");
                return null;
            }
            else if (open.IndexOf(endPos) != -1)
            {
                Debug.Log("ѕуть обнаружен");
                return ConvertWay();
            }
        }
    }

    //пересохран€ем путь в обратном пор€дке
    private static Dictionary<Vector2, Vector2> ConvertWay()
    {
        Dictionary<Vector2, Vector2> newWay = new Dictionary<Vector2, Vector2>();
        Vector2 curPos = endPos;
        //поскольку мы ищем путь "перед точкой", то мы пропускаем последнюю позицию
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
	
	//проверка на наличие преп€тстви€ в следующем квадрате* перехода
    private static bool IsBarier(Vector2 pos)
    {
        RaycastHit2D hit = Physics2D.BoxCast(pos, new Vector2(1,1), 0, Vector2.zero, Mathf.Infinity, 1 << layerMask); 
        if (hit.collider != null)
            return true;
        return false;
    }
}
