using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "New Block", menuName = "PassiveDefenceAbilities/Block")]
public class Block : PassiveDefenceAbility
{
    public override EnumData.ArmorType GetArmorType() => EnumData.ArmorType.Physical;

    [System.Serializable]
    public struct AbilityLevelData
    {
        [Range(0, 100)] public int chance;
        public bool isFullBlock;
        public int valueBlocked;
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
            if (abilityLevelDatas[currentAbilityLevel - 1].isFullBlock)
            {
                damageHandler.DirectDamage = 0;
                return;
            }

            float resultDamage = damageHandler.DirectDamage - abilityLevelDatas[currentAbilityLevel - 1].valueBlocked;

            if (resultDamage > 0)
                damageHandler.DirectDamage = resultDamage;
            else
                damageHandler.DirectDamage = 0;
        }
    }
}
