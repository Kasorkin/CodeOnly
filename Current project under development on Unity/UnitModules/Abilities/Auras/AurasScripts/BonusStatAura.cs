using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "New bonusStatAura", menuName = "Auras/BonusStatAura")]
public class BonusStatAura : AuraAbility
{
    public override bool IsPeriodic() => false;

    [Serializable]
    public struct LevelOfAbility
    {
        public List<PassiveBonusData> auraBonuses;
        public float radiusOfImpact;
    }

    [SerializeField] private List<LevelOfAbility> levelsOfAbility = new List<LevelOfAbility>();

    public List<LevelOfAbility> GetLevelsOfAbility => levelsOfAbility;

    public override void AddImpact(GameObject targetOfImpact, int currentAbilityLevel)
    {
        ChangerBonusStats.SetStats(targetOfImpact, levelsOfAbility[currentAbilityLevel - 1].auraBonuses);
    }

    public override void DeleteImpact(GameObject targetImpact, int currentAbilityLevel)
    {
        ChangerBonusStats.UnsetStats(targetImpact, levelsOfAbility[currentAbilityLevel - 1].auraBonuses);
    }
}
