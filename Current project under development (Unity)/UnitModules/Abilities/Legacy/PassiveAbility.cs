using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PassiveAbility : GameAbility
{
    [SerializeField] protected bool isAura;

    public bool IsAura { get => isAura; set => isAura = value; }

    public virtual void InitPassiveAbility (GameObject ownerOfAura) { }
}
