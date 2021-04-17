using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Unit)), RequireComponent(typeof(Mana))]
public class Hero : MonoBehaviour
{
    [Header("PrimaryStat")]
    [SerializeField] private EnumData.PrimaryAttribute primaryStat;

    [Header("HeroStats")]
    [SerializeField] private float strenght;
    [SerializeField] private float agility;
    [SerializeField] private float intelligence;

    [Header("GrowthStats")]
    [SerializeField] private float growthStrength;
    [SerializeField] private float growthAgility;
    [SerializeField] private float growthIntelligence;

    [Header("Exp")]
    [SerializeField] private int currentLevel;
    [SerializeField] private ExpBar expBar;

    public float Strenght => strenght;
    public float Agility => agility;
    public float Intelligence => intelligence;

    private Unit unit;

    private void Awake()
    {
        unit = GetComponent<Unit>();
    }

    private void Start()
    {
        if (currentLevel <= 0) currentLevel = 1;

        unit.ChangeMaxHealth(strenght * Consts.StrengthHpFactor);
        unit.ChangeHpRegeneration(strenght * Consts.StrengthRegenerationFactor);
        unit.ChangeArmor(agility * Consts.AgilityArmorFactor);
        unit.ChangeAttackSpeed(agility * Consts.AgilityAttackSpeedFactor);
        unit.ChangeMaxMana(intelligence * Consts.IntelligenceManaFactor);
        unit.ChangeManaRegeneration(intelligence * Consts.IntelligenceRegenerationFactor);    
        
        switch(primaryStat)
        {
            case EnumData.PrimaryAttribute.Strength:
                ChangePrimaryAttributeDamage(strenght);
                break;
            case EnumData.PrimaryAttribute.Agility:
                ChangePrimaryAttributeDamage(agility);
                break;
            case EnumData.PrimaryAttribute.Intelligence:
                ChangePrimaryAttributeDamage(intelligence);
                break;
        }
    }

    public void ChangeExperience(int value)
    {
        if (value == 0) return;

        expBar.AddExperience(value); 

        if(expBar.Lvl > currentLevel)
        {
            currentLevel = expBar.Lvl;
            ChangeStrength(growthStrength);
            ChangeAgility(growthAgility);
            ChangeIntelligence(growthIntelligence);
        }
    }

    public void ChangeStrength(float value)
    {
        if (value == 0) return;

        strenght = Mathf.Clamp(strenght + value, 0, Mathf.Infinity);
        unit.ChangeMaxHealth(value * Consts.StrengthHpFactor);
        unit.ChangeHpRegeneration(value * Consts.StrengthRegenerationFactor);

        if(primaryStat == EnumData.PrimaryAttribute.Strength)
            ChangePrimaryAttributeDamage(value);
    }

    public void ChangeAgility(float value)
    {
        if (value == 0) return;

        agility = Mathf.Clamp(agility + value, 0, Mathf.Infinity);
        unit.ChangeAttackSpeed(value * Consts.AgilityAttackSpeedFactor);
        unit.ChangeArmor(value * Consts.AgilityArmorFactor);

        if (primaryStat == EnumData.PrimaryAttribute.Agility)
            ChangePrimaryAttributeDamage(value);
    }

    public void ChangeIntelligence(float value)
    {
        if (value == 0) return;

        intelligence = Mathf.Clamp(intelligence + value, 0, Mathf.Infinity);
        unit.ChangeMaxMana(value * Consts.IntelligenceManaFactor);
        unit.ChangeManaRegeneration(value * Consts.IntelligenceRegenerationFactor);

        if (primaryStat == EnumData.PrimaryAttribute.Intelligence)
            ChangePrimaryAttributeDamage(value);
    }

    private void ChangePrimaryAttributeDamage(float value = 0)
    {
        unit.ChangeDamage(value * Consts.PrimaryAttributeDamageFactor);
    }
}
