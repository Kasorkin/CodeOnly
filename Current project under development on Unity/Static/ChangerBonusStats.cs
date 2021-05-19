using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public static class ChangerBonusStats
{
    public static void SetStats(GameObject unit, List<PassiveBonusData> bonusStats)
    {
        //Debug.Log("SetStats");
        foreach (PassiveBonusData i in bonusStats)
        {
            ChangeStat(unit, i, true);
        }
    }

    public static void UnsetStats(GameObject unit, List<PassiveBonusData> bonusStats)
    {
        //Debug.Log("UnsetStats");
        foreach (PassiveBonusData i in bonusStats)
        {
            ChangeStat(unit, i, false);
        }
    }

    private static void ChangeStat(GameObject gameObject, PassiveBonusData statInfo, bool isIncrease)
    {
        Unit unit = gameObject.GetComponent<Unit>();

        if (unit == null) return;

        float value = statInfo.upValue;

        if (!isIncrease)
            value = -statInfo.upValue;

        switch(statInfo.stat)
        {
            case EnumData.BonusStat.BonusMaxHealth:
                unit.ChangeBonusMaxHealth(value);
                break;
            case EnumData.BonusStat.BonusHpRegeneration:
                unit.ChangeBonusHpRegeneration(value);
                break;
            case EnumData.BonusStat.BonusDamage:
                unit.ChangeBonusDamage(value);
                break;
            case EnumData.BonusStat.BonusAttackRange:
                unit.ChangeBonusAttackRange(value);
                break;
            case EnumData.BonusStat.BonusAttackSpeed:
                unit.ChangeBonusAttackSpeed(value);
                break;
            case EnumData.BonusStat.BonusArmor:
                unit.ChangeBonusPhysicArmor(value);
                break;
            case EnumData.BonusStat.BonusMoveSpeed:
                unit.ChangeBonusMoveSpeed(value);
                break;
            case EnumData.BonusStat.BonusSpellPower:
                unit.ChangeBonusSpellPower(value);
                break;
            case EnumData.BonusStat.BonusMaxMana:
                gameObject.GetComponent<Mana>().ChangeBonusMaxMana(value);
                break;
            case EnumData.BonusStat.BonusManaRegeneration:
                gameObject.GetComponent<Mana>().ChangeBonusManaRegeneration(value);
                break;
            case EnumData.BonusStat.BonusStrength:
                gameObject.GetComponent<Hero>().ChangeBonusStrength(value);
                break;
            case EnumData.BonusStat.BonusAgility:
                gameObject.GetComponent<Hero>().ChangeBonusAgility(value);
                break;
            case EnumData.BonusStat.BonusIntelligence:
                gameObject.GetComponent<Hero>().ChangeBonusIntelligence(value);
                break;
        }
    }
}
