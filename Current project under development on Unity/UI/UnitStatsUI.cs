using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;

public class UnitStatsUI : MonoBehaviour
{
    [Header("Base")]
    [SerializeField] private TMP_Text damageText;
    [SerializeField] private TMP_Text attackSpeedText;
    [SerializeField] private TMP_Text rangeText;
    [SerializeField] private TMP_Text physicArmorText;
    [SerializeField] private TMP_Text magicArmorText;
    [SerializeField] private TMP_Text moveSpeedText;
    [SerializeField] private TMP_Text strengthText;
    [SerializeField] private TMP_Text agilityText;
    [SerializeField] private TMP_Text intelligenceText;
    [SerializeField] private TMP_Text spellPowerText;
    [Space(15)]
    [SerializeField] private TMP_Text currentHPText;
    [SerializeField] private TMP_Text maxHPText;
    [SerializeField] private TMP_Text regenerationHPText;
    [Space(15)]
    [SerializeField] private TMP_Text currentMPText;
    [SerializeField] private TMP_Text maxMPText;
    [SerializeField] private TMP_Text regenerationMPText;
    [Space(15)]
    [SerializeField] private TMP_Text currentExpText;
    [SerializeField] private TMP_Text maxExpText;


    [Header("Bonus")]
    [SerializeField] private TMP_Text bonusDamageText;
    [SerializeField] private TMP_Text bonusAttackSpeedText;
    [SerializeField] private TMP_Text bonusRangeText;
    [SerializeField] private TMP_Text bonusPhysicArmorText;
    [SerializeField] private TMP_Text bonusMagicArmorText;
    [SerializeField] private TMP_Text bonusMoveSpeedText;
    [SerializeField] private TMP_Text bonusStrengthText;
    [SerializeField] private TMP_Text bonusAgilityText;
    [SerializeField] private TMP_Text bonusIntelligenceText;
    [SerializeField] private TMP_Text bonusSpellPowerText;

    #region Get/Set methods
    public TMP_Text DamageText { get => damageText; set => damageText = value; }
    public TMP_Text AttackSpeedText { get => attackSpeedText; set => attackSpeedText = value; }
    public TMP_Text RangeText { get => rangeText; set => rangeText = value; }
    public TMP_Text PhysicArmorText { get => physicArmorText; set => physicArmorText = value; }
    public TMP_Text MagicArmorText { get => magicArmorText; set => magicArmorText = value; }
    public TMP_Text MoveSpeedText { get => moveSpeedText; set => moveSpeedText = value; }
    public TMP_Text StrengthText { get => strengthText; set => strengthText = value; }
    public TMP_Text AgilityText { get => agilityText; set => agilityText = value; }
    public TMP_Text IntelligenceText { get => intelligenceText; set => intelligenceText = value; }
    public TMP_Text SpellPowerText { get => spellPowerText; set => spellPowerText = value; }

    public TMP_Text BonusDamageText { get => bonusDamageText; set => bonusDamageText = value; }
    public TMP_Text BonusAttackSpeedText { get => bonusAttackSpeedText; set => bonusAttackSpeedText = value; }
    public TMP_Text BonusRangeText { get => bonusRangeText; set => bonusRangeText = value; }
    public TMP_Text BonusPhysicArmorText { get => bonusPhysicArmorText; set => bonusPhysicArmorText = value; }
    public TMP_Text BonusMagicArmorText { get => bonusMagicArmorText; set => bonusMagicArmorText = value; }
    public TMP_Text BonusMoveSpeedText { get => bonusMoveSpeedText; set => bonusMoveSpeedText = value; }
    public TMP_Text BonusStrengthText { get => bonusStrengthText; set => bonusStrengthText = value; }
    public TMP_Text BonusAgilityText { get => bonusAgilityText; set => bonusAgilityText = value; }
    public TMP_Text BonusIntelligenceText { get => bonusIntelligenceText; set => bonusIntelligenceText = value; }
    public TMP_Text BonusSpellPowerText { get => bonusSpellPowerText; set => bonusSpellPowerText = value; }

    public TMP_Text CurrentHPText { get => currentHPText; set => currentHPText = value; }
    public TMP_Text MaxHPText { get => maxHPText; set => maxHPText = value; }
    public TMP_Text RegenerationHPText { get => regenerationHPText; set => regenerationHPText = value; }

    public TMP_Text CurrentMPText { get => currentMPText; set => currentMPText = value; }
    public TMP_Text MaxMPText { get => maxMPText; set => maxMPText = value; }
    public TMP_Text RegenerationMPText { get => regenerationMPText; set => regenerationMPText = value; }

    public TMP_Text CurrentExpText { get => currentExpText; set => currentExpText = value; }
    public TMP_Text MaxExpText { get => maxExpText; set => maxExpText = value; }
    #endregion
}
