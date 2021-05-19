using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public static class ArmorSystem
{
    public static float CalcilationResultDamage(float inputDamage, float armor)
    {
        return inputDamage * (1 - (Consts.ArmorFarctor * armor / (1 + Consts.ArmorFarctor * armor)));
    }
}
