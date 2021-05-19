using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "New CriticalStrice", menuName = "PassiveAttackAbilities/CriticalStrice")]
public class CriticalStrice : PassiveAttackAbility
{
    [System.Serializable]
    public struct AbilityLevelData
    {
        [Range(0, 100)] public int chance;
        public float criticalFactor;
    }

    [SerializeField] private List<AbilityLevelData> abilityLevelDatas;

    public override void Ability(DamageHandler damageHandler, int currentAbilityLevel = 1)
    {
        if (currentAbilityLevel > abilityLevelDatas.Count)
        {
            Debug.LogError("Ќесоответствие количества уровней способности");
            return;
        }

        if (Random.Range(1, 100) <= abilityLevelDatas[currentAbilityLevel - 1].chance)
        {
            damageHandler.DirectDamage *= abilityLevelDatas[currentAbilityLevel - 1].criticalFactor;
        }
    }
}
