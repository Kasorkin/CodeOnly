using System;
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

    [Header("BonusStats")]
    [SerializeField] private float bonusStrength;
    [SerializeField] private float bonusAgility;
    [SerializeField] private float bonusIntelligence;

    [Header("Exp")]
    [SerializeField] private int currentLevel;
    //[SerializeField] private ExpBar expBar;

    public float GetStrenght => strenght;
    public float GetAgility => agility;
    public float GetIntelligence => intelligence;

    private Unit unit;

    private ExpBar uiExpBar;

    private void Awake()
    {
        unit = GetComponent<Unit>();
    }

    private void Start()
    {
        if(GetComponent<PlayerScript>() != null)
            uiExpBar = GetComponent<PlayerScript>().PlayerCanvasData.UiExpBar.GetComponent<ExpBar>();

        if (currentLevel <= 0) currentLevel = 1;

        unit.ChangeMaxHealth(strenght * Consts.StrengthHpFactor);
        unit.ChangeHpRegeneration(strenght * Consts.StrengthRegenerationFactor);
        unit.ChangePhysicArmor(agility * Consts.AgilityArmorFactor);
        unit.ChangeAttackSpeed(agility * Consts.AgilityAttackSpeedFactor);
        unit.ChangeMaxMana(intelligence * Consts.IntelligenceManaFactor);
        unit.ChangeManaRegeneration(intelligence * Consts.IntelligenceRegenerationFactor);

        ChangeStrength(0);
        ChangeAgility(0);
        ChangeIntelligence(0);

        ChangeExperience(0);

        ChangeBonusStrength(0);
        ChangeBonusAgility(0);
        ChangeBonusIntelligence(0);

        switch (primaryStat)
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
        //expBar.AddExperience(value);
        uiExpBar.AddExperience(value);

        if(uiExpBar.Lvl > currentLevel)
        {
            currentLevel = uiExpBar.Lvl;
            ChangeStrength(growthStrength);
            ChangeAgility(growthAgility);
            ChangeIntelligence(growthIntelligence);
        }

        if (unit?.StatsUI != null)
        {
            unit.StatsUI.CurrentExpText.text = uiExpBar.slider.value.ToString();
            unit.StatsUI.MaxExpText.text = "/" + uiExpBar.slider.maxValue.ToString();
        }
    }
    #region ChangeBaseStats
    public void ChangeStrength(float value)
    {
        strenght = Mathf.Clamp(strenght + value, 0, Mathf.Infinity);
        unit.ChangeMaxHealth(value * Consts.StrengthHpFactor);
        unit.ChangeHpRegeneration(value * Consts.StrengthRegenerationFactor);

        if(primaryStat == EnumData.PrimaryAttribute.Strength)
            ChangePrimaryAttributeDamage(value);

        if (unit?.StatsUI != null)
            unit.StatsUI.StrengthText.text = strenght.ToString();
    }

    public void ChangeAgility(float value)
    {
        agility = Mathf.Clamp(agility + value, 0, Mathf.Infinity);
        unit.ChangeAttackSpeed(value * Consts.AgilityAttackSpeedFactor);
        unit.ChangePhysicArmor(value * Consts.AgilityArmorFactor);

        if (primaryStat == EnumData.PrimaryAttribute.Agility)
            ChangePrimaryAttributeDamage(value);

        if (unit?.StatsUI != null)
            unit.StatsUI.AgilityText.text = agility.ToString();
    }

    public void ChangeIntelligence(float value)
    {
        intelligence = Mathf.Clamp(intelligence + value, 0, Mathf.Infinity);
        unit.ChangeMaxMana(value * Consts.IntelligenceManaFactor);
        unit.ChangeManaRegeneration(value * Consts.IntelligenceRegenerationFactor);

        if (primaryStat == EnumData.PrimaryAttribute.Intelligence)
            ChangePrimaryAttributeDamage(value);

        if (unit?.StatsUI != null)
            unit.StatsUI.IntelligenceText.text = intelligence.ToString();
    }
    #endregion
    #region ChangeBonusStat
    public void ChangeBonusStrength(float value)
    {
        bonusStrength = Mathf.Clamp(bonusStrength + value, 0, Mathf.Infinity);
        unit.ChangeBonusMaxHealth(value * Consts.StrengthHpFactor);
        unit.ChangeBonusHpRegeneration(value * Consts.StrengthRegenerationFactor);

        if (primaryStat == EnumData.PrimaryAttribute.Strength)
            ChangePrimaryAttributeBonusDamage(value);

        if (unit?.StatsUI != null)
            unit.StatsUI.BonusStrengthText.text = "+" + bonusStrength.ToString();
    }

    public void ChangeBonusAgility(float value)
    {
        bonusAgility = Mathf.Clamp(bonusAgility + value, 0, Mathf.Infinity);
        unit.ChangeBonusAttackSpeed(value * Consts.AgilityAttackSpeedFactor);
        unit.ChangeBonusPhysicArmor(value * Consts.AgilityArmorFactor);

        if (primaryStat == EnumData.PrimaryAttribute.Agility)
            ChangePrimaryAttributeBonusDamage(value);

        if (unit?.StatsUI != null)
            unit.StatsUI.BonusAgilityText.text = "+" + bonusAgility.ToString();
    }

    public void ChangeBonusIntelligence(float value)
    {
        bonusIntelligence = Mathf.Clamp(bonusIntelligence + value, 0, Mathf.Infinity);
        unit.ChangeBonusMaxMana(value * Consts.IntelligenceManaFactor);
        unit.ChangeBonusManaRegeneration(value * Consts.IntelligenceRegenerationFactor);

        if (primaryStat == EnumData.PrimaryAttribute.Intelligence)
            ChangePrimaryAttributeBonusDamage(value);

        if (unit?.StatsUI != null)
            unit.StatsUI.BonusIntelligenceText.text = "+" + bonusIntelligence.ToString();
    }

    private void ChangePrimaryAttributeDamage(float value = 0)
    {
        unit.ChangePhysicDamage(value * Consts.PrimaryAttributeDamageFactor);
    }

    private void ChangePrimaryAttributeBonusDamage(float value = 0)
    {
        unit.ChangeBonusDamage(value * Consts.PrimaryAttributeDamageFactor);
    }
    #endregion
}
