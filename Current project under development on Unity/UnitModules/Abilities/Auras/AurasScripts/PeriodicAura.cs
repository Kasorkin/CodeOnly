using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "New PeriodicAura", menuName = "Auras/PeriodicAura")]
public class PeriodicAura : AuraAbility
{
    public override bool IsPeriodic() => true;

    [Serializable]
    public struct AbilityLevelData
    {
        public List<Effect> stayEffects;
        public float radiusOfImpact;
        public float duration;
        public float coldownOfImpact;
    }
    
    [Header("PeriodicData")]
    [SerializeField] private List<AbilityLevelData> levelsOfAbility = new List<AbilityLevelData>();

    public List<AbilityLevelData> GetAbilityLevelsData => levelsOfAbility;

    public override void StayImpact(GameObject targetOfImpact, int currentAbilityLevel)
    {
        foreach (Effect effect in levelsOfAbility[currentAbilityLevel - 1].stayEffects)
        {
            effect.AddImpact(targetOfImpact, currentAbilityLevel);
        }
    }
}
