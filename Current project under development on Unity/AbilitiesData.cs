using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public static class AbilitiesData
{
    public static void SelfHealing(GameObject unit,float value)
    {
        unit.GetComponent<Health>().HealthChange(value);
    }
}
