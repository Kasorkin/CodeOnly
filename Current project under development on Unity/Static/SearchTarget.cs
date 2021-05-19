using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public static class SearchTarget
{
    //поиск юнитов в областе (неожиданно, да?)
    public static List<Unit> SearchingUnitsInArea(Vector2 pos, float radiusSearch, LayerMask layerMask)
    {
        List<Unit> unitsInArea = new List<Unit>();

        Collider2D[] colliders = Physics2D.OverlapCircleAll(pos, radiusSearch, layerMask);

        foreach(Collider2D hit in colliders)
        {
            Unit unit = hit.GetComponent<Unit>();
            if (unit != null)
                unitsInArea.Add(unit);
        }

        return unitsInArea;
    }


    //не забыть бы проанализировать и улучшить
    public static GameObject SearchingTarget(Vector2 pos, int radiusSearch, int layerMask)
    {
        Collider2D[] colliders = Physics2D.OverlapCircleAll(pos, radiusSearch, 1 << layerMask);

        GameObject obj = NearTarget(pos, colliders);
        //улучшить, чтобы поиск был не только по контроллеру игрока
        if (obj != null && obj.GetComponent<PlayerScript>())
        {
            return obj;
        }
        return null;
    }

    // функция возвращает ближайший объект из массива, относительно указанной позиции
    public static GameObject NearTarget(Vector3 position, Collider2D[] array)
    {
        Collider2D current = null;
        float dist = Mathf.Infinity;

        //Улучшить систему отбора 
        foreach (Collider2D coll in array)
        {
            float curDist = Vector3.Distance(position, coll.transform.position);

            if (curDist < dist)
            {
                current = coll;
                dist = curDist;
            }
        }
        return (current != null) ? current.gameObject : null;
    }
}
