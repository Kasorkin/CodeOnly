using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

[CreateAssetMenu(fileName = "New ArmorReductionEffect", menuName = "Effects/ArmorReductionEffect")]
public class ArmorReductionEffect : Effect
{
    [Serializable]
    public struct EffectLevelData
    {
        public EnumData.ArmorType armorTypeReduction;
        public float numericValue;
    }

    [SerializeField] private List<EffectLevelData> effectLevelsData = new List<EffectLevelData>();

    public List<EffectLevelData> GetEffectLevelsData => effectLevelsData;

    public override void AddImpact(GameObject targetOfImpact, int lvlOfEffect = 1)
    {
        //может ты как-то это оптимизируешь?
        Unit target = targetOfImpact.GetComponent<Unit>();

        if (effectLevelsData[lvlOfEffect - 1].armorTypeReduction == EnumData.ArmorType.Physical)
            target.ChangeBonusPhysicArmor(-effectLevelsData[lvlOfEffect - 1].numericValue);
        else
            target.ChangeBonusMagicArmor(-effectLevelsData[lvlOfEffect - 1].numericValue);
    }

    public override void RemoveImpact(GameObject targetOfImpact, int lvlOfEffect = 1)
    {
        Unit target = targetOfImpact.GetComponent<Unit>();

        if (effectLevelsData[lvlOfEffect - 1].armorTypeReduction == EnumData.ArmorType.Physical)
            target.ChangeBonusPhysicArmor(effectLevelsData[lvlOfEffect - 1].numericValue);
        else
            target.ChangeBonusMagicArmor(effectLevelsData[lvlOfEffect - 1].numericValue);
    }
}
