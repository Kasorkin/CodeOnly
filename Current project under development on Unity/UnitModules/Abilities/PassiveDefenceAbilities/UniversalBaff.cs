using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "New UniversalBaff", menuName = "PassiveDefenceAbilities/UniversalBaff")]
public class UniversalBaff : PassiveDefenceAbility
{
    [System.Serializable]
    public struct AbilityLevelData
    {
        [Range(0, 100)] public int chance;
        public List<PassiveBonusData> passiveBonusData;
        public float duration;
    }
    [SerializeField] private List<AbilityLevelData> abilityLevelDatas;

    public override void Ability(DamageHandler damageHandler, int currentAbilityLevel = 1)
    {
        if (currentAbilityLevel > abilityLevelDatas.Count)
        {
            Debug.LogError("Несоответствие количества уровней способности");
            return;
        }

        if (Random.Range(1, 100) <= abilityLevelDatas[currentAbilityLevel - 1].chance)
        {
            ChangerBonusStats.SetStats(damageHandler.gameObject, abilityLevelDatas[currentAbilityLevel - 1].passiveBonusData);
            //отмена
            new GameObject().AddComponent<CoroutineLoader>().UnsetStatsWaiter(abilityLevelDatas[currentAbilityLevel - 1].duration, damageHandler.gameObject, abilityLevelDatas[currentAbilityLevel - 1].passiveBonusData);
        }
    }
}
