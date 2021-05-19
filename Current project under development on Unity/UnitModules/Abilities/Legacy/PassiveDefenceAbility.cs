using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PassiveDefenceAbility : GameAbility
{
    public virtual EnumData.ArmorType GetArmorType() { return EnumData.ArmorType.Null; }

    public override bool IsActive() => false;

    public virtual void Ability(DamageHandler damageHandler, int currentAbilityLevel = 1) { }

    public override void InitAbility(GameObject ownerOfAbility)
    {
        ownerOfAbility.GetComponent<Unit>().PassiveDefenceAbilities.Add(this);
    }
}
