using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PeriodicAura : AuraAbility
{
    /*[Serializable]
    public struct LvlAbility
    {
        public float duration;
        public float coldownOfImpact;
    }
    
    [Header("PeriodicData")]
    [SerializeField] private List<LvlAbility> levelsOfAbility = new List<LvlAbility>();*/
    //[SerializeField] protected float duration;
    //[SerializeField] protected float cooldownOfImpact;

    //public float Duration { get => duration; set => duration = value; }
    //public float CooldownOfImpact { get => cooldownOfImpact; set => cooldownOfImpact = value; }

    public virtual void StayImpact() { }

    public override void AddImpact(GameObject targetImpact)
    {
        
    }

    public override void DeleteImpact(GameObject targetImpact)
    {
        
    }
}
