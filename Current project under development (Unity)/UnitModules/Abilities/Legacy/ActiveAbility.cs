using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ActiveAbility : GameAbility
{
    [SerializeField] protected bool isSelf;

    public bool IsSelf { get => isSelf; set => isSelf = value; }
}
