using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "New SelfAbility", menuName = "SelfActiveAbilities/SelfActiveAbility")]
public class SelfActiveAbility : GameAbility
{
    public override bool IsActive() => true;
    public override bool IsSelf() => true;

    public override void Use(Vector2 targetPos)
    {
        
    }
}
