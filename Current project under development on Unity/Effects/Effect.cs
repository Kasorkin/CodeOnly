using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Effect : ScriptableObject
{
    public virtual void AddImpact(GameObject targetOfImpact, int lvlOfEffect = 1) { }
    public virtual void RemoveImpact(GameObject targetOfImpact, int lvlOfEffect = 1) { }
}
