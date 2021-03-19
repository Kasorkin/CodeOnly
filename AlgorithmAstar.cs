using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// Поиск пути по алгоритму А* для проекта Unity2D
/// Кодировка из юнити слетела, потому я вкратце здесь опишу
/// Данный алгоритм позволяет работать с поиском пути как в пошаговых играх, так и в играх в реальном времени
/// Имеется стандартная реализация алгоритма под 4 направления
/// Также, уже конкретно для Unity, добавлена проверка на наличие поиска препятствий
/// Поскольку путь сохраняется из конца в начало (по самому алгоритму), был добавлен метод конвертации, чтобы путь был пересохранен как "из начала в конец"
/// </summary>
public static class AlgorithmAstar 
{
    private static readonly float mass = 1;
    private static readonly int layerMask = 7;

    private static Vector2 startPos;
    private static Vector2 endPos;

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
            }
            Vector2 currentPos = open[minIndex];
		
            closed.Add(currentPos);
            open.RemoveAt(minIndex);

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
                if (i == 2 || IsBarier(neighbors[i]) || closed.IndexOf(neighbors[i]) != -1)
                    continue;
                if (open.IndexOf(neighbors[i]) == -1)
                {
                    open.Add(neighbors[i]);
                    parents[neighbors[i]] = currentPos;
                    g[neighbors[i]] = mass + g[currentPos];
                    generalValue[neighbors[i]] = g[neighbors[i]] + Heuristic(neighbors[i]);
                }
            }
            if (open.IndexOf(endPos) == -1 && open.Count == 0)
	    {
                return null;
            }
            else if (open.IndexOf(endPos) != -1)
            {
                return ConvertWay();
            }
        }
    }

    private static Dictionary<Vector2, Vector2> ConvertWay()
    {
        Dictionary<Vector2, Vector2> newWay = new Dictionary<Vector2, Vector2>();
        Vector2 curPos = endPos;

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
	
    private static bool IsBarier(Vector2 pos)
    {
        RaycastHit2D hit = Physics2D.BoxCast(pos, new Vector2(1,1), 0, Vector2.zero, Mathf.Infinity, 1 << layerMask); 
        if (hit.collider != null)
            return true;
        return false;
    }
}
