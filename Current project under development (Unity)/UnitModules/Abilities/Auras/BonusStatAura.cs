using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "New bonusStatAura", menuName = "Auras/BonusStatAura")]
public class BonusStatAura : AuraAbility
{
    [Serializable]
    public struct LevelOfAbility
    {
        public List<PassiveBonusData> auraBonuses;
        public float radiusOfImpact;
    }

    [SerializeField] private List<LevelOfAbility> levelsOfAbility = new List<LevelOfAbility>();

    public List<LevelOfAbility> LevelsOfAbility { get => levelsOfAbility; set => levelsOfAbility = value; }

    public override void LvlUpAbility()
    {
        /*
        //запретили работу ауры
        auraController.LvlAbilityChanging = true;
        //нашли всех юнитов в ауре
        List<Unit> unitsInArea = auraController.UpdateLvlAbility(radiusOfImpact, layersOfImpact);
        //убрали статы для каждого
        foreach (Unit unit in unitsInArea)
            DeleteImpact(unit.gameObject);
        //изменили уровень
        ++CurrentAbilityLvl;
        //нашли юнитов в зоне
        //unitsInArea = auraController.UpdateLvlAbility(radiusOfImpact, layersOfImpact);
        //добавили статы для каждого
        foreach(Unit unit in unitsInArea)
            AddImpact(unit.gameObject);
        //включили ауру
        auraController.LvlAbilityChanging = false;
        */
    }

    public override void AddImpact(GameObject targetOfImpact)
    {
        ChangerBonusStats.SetStats(targetOfImpact, levelsOfAbility[CurrentAbilityLvl - 1].auraBonuses);
    }

    public override void DeleteImpact(GameObject targetImpact)
    {
        ChangerBonusStats.UnsetStats(targetImpact, levelsOfAbility[CurrentAbilityLvl - 1].auraBonuses);
    }
}
