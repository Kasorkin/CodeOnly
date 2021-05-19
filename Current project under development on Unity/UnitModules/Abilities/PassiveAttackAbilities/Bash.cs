using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "New Bash", menuName = "PassiveAttackAbilities/Bash")]
public class Bash : PassiveAttackAbility
{
    [System.Serializable]
    public struct AbilityLevelData
    {
        [Range(0, 100)] public int chance;
        public float stunDuration;
        public float bonusDamage;
        public EnumData.DamageType damageType;
    }

    [SerializeField] private Effect stunEffect;

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
            stunEffect.AddImpact(damageHandler.gameObject, currentAbilityLevel - 1);

            //damageHandler.Damage += abilityLevelDatas[currentAbilityLevel - 1].bonusDamage;
            damageHandler.InputDamage(abilityLevelDatas[currentAbilityLevel - 1].bonusDamage, abilityLevelDatas[currentAbilityLevel - 1].damageType);

            if(damageHandler.gameObject != null)
                new GameObject().AddComponent<CoroutineLoader>().RemoveEffect(abilityLevelDatas[currentAbilityLevel - 1].stunDuration, stunEffect.RemoveImpact, damageHandler.gameObject, currentAbilityLevel - 1);
        }
    }
}
