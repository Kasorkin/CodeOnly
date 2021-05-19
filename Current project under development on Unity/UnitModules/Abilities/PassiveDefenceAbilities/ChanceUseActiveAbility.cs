using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "New ChanceUseActiveAbility", menuName = "PassiveDefenceAbilities/ChanceUseActiveAbility")]
public class ChanceUseActiveAbility : PassiveDefenceAbility
{
    [System.Serializable]
    public struct AbilityLevelData
    {
        [Range(0, 100)] public int chance;
        public GameAbility activeAbility;
    }
    [Header("ChanceUseActiveAbilityData")]
    [SerializeField] private bool inRadiusWithOwnerCenter;
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
            if(abilityLevelDatas[currentAbilityLevel - 1].activeAbility.IsActive() == true && abilityLevelDatas[currentAbilityLevel - 1].activeAbility.IsSelf() == true)
            {

            }
            else
            {
                GameAbility ability = abilityLevelDatas[currentAbilityLevel - 1].activeAbility;

                if (inRadiusWithOwnerCenter)
                {
                    if(damageHandler.gameObject != null)
                        ability.Use(damageHandler.gameObject.transform.position);
                }
                else
                {
                    if(damageHandler.Attaker != null)
                        ability.Use(damageHandler.Attaker.transform.position);
                }
            }
        }
    }
}
