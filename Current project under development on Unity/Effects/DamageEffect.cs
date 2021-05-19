using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "New DamageEffect", menuName = "Effects/DamageEffect")]
public class DamageEffect : Effect
{
    [Serializable]
    public struct EffectLevelData
    {
        public EnumData.DamageType effectDamageType;
        public float damage;
    }

    [SerializeField] private List<EffectLevelData> effectLevelsData = new List<EffectLevelData>();

    public List<EffectLevelData> GetEffectLevelsData => effectLevelsData;

    public override void AddImpact(GameObject targetOfImpact, int lvlOfEffect = 1)
    {
        //может ты как-то это оптимизируешь?
        DamageHandler damageHandler = targetOfImpact.GetComponent<DamageHandler>();
        damageHandler.InputDamage(effectLevelsData[lvlOfEffect - 1].damage, effectLevelsData[lvlOfEffect - 1].effectDamageType);
    }
}
