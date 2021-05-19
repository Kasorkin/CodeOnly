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
        //��������� ������ ����
        auraController.LvlAbilityChanging = true;
        //����� ���� ������ � ����
        List<Unit> unitsInArea = auraController.UpdateLvlAbility(radiusOfImpact, layersOfImpact);
        //������ ����� ��� �������
        foreach (Unit unit in unitsInArea)
            DeleteImpact(unit.gameObject);
        //�������� �������
        ++CurrentAbilityLvl;
        //����� ������ � ����
        //unitsInArea = auraController.UpdateLvlAbility(radiusOfImpact, layersOfImpact);
        //�������� ����� ��� �������
        foreach(Unit unit in unitsInArea)
            AddImpact(unit.gameObject);
        //�������� ����
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
