using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Health))]
public class Unit : MonoBehaviour
{
    [Header("Stats")]
    [SerializeField] private float physicDamage;
    //[SerializeField] private float magicDamage;
    [SerializeField] private float attackSpeed;
    [SerializeField] private float attackRange;
    [SerializeField] private float physicArmor;
    [SerializeField] private float magicArmor;
    [SerializeField] private float moveSpeed;
    [SerializeField] private float maxHealth;
    [SerializeField] private float hpRegeneration;
    [SerializeField] private float spellPower = 0;

    [Header("BonusStats")]
    [SerializeField] private float bonusPhysicDamage;
    //[SerializeField] private float bonusMagicDamage;
    [SerializeField] private float bonusAttackSpeed;
    [SerializeField] private float bonusAttackRange;
    [SerializeField] private float bonusPhysicArmor;
    [SerializeField] private float bonusMagicArmor;
    [SerializeField] private float bonusMoveSpeed;
    [SerializeField] private float bonusMaxHealth;
    [SerializeField] private float bonusHpRegeneration;
    [SerializeField] private float bonusSpellPower = 0;

    #region ReadingMethodsStats
    public float GetPhysicArmor => physicArmor;
    public float GetMagicArmor => magicArmor;
    public float GetPhysicDamage => physicDamage;
    //public float GetMagicDamage => magicDamage;
    public float GetMoveSpeed => moveSpeed;
    public float GetAttackSpeed => attackSpeed;
    public float GetAttackRange => attackRange;
    public float GetMaxHealth => maxHealth;
    public float GetHpRegeneration => hpRegeneration;
    public float GetSpellPower => spellPower;

    public float BonusPhysicDamage => bonusPhysicDamage;
    //public float BonusMagicDamage => bonusMagicDamage;
    public float BonusAttackSpeed => bonusAttackSpeed;
    public float BonusAttackRange => bonusAttackRange;
    public float BonusPhysicArmor  => bonusPhysicArmor;
    public float BonusMagicArmor => bonusMagicArmor;
    public float BonusMoveSpeed => bonusMoveSpeed; 
    public float BonusMaxHealth => bonusMaxHealth; 
    public float BonusHpRegeneration => bonusHpRegeneration;
    public float BonusSpellPower => bonusSpellPower;

    public float GetSummaryPhysicArmor => physicArmor + bonusPhysicArmor;
    public float GetSummaryMagicArmor => magicArmor + bonusMagicArmor;
    public float GetSummaryPhysicDamage => physicDamage + bonusPhysicDamage;
    //public float GetSummaryMagicDamage => magicDamage + bonusMagicDamage;
    public float GetSummaryMoveSpeed => moveSpeed + bonusMoveSpeed;
    public float GetSummaryAttackSpeed
    {
        get
        {
            float result = attackSpeed - bonusAttackSpeed;
            if (result > 0.05f)
                return result;
            else
                return Consts.MaxAttackSpeed;
        }
    }
    public float GetSummaryAttackRange => attackRange + bonusAttackRange;
    public float GetSummaryMaxHealth => maxHealth + bonusMaxHealth;
    public float GetSummaryHpRegeneration => hpRegeneration + bonusHpRegeneration;
    public float GetSummarySpellPower => spellPower + bonusSpellPower;
    #endregion

    public List<PassiveDefenciveAbilities> PassiveDefenciveAbilities { get; set; } = new List<PassiveDefenciveAbilities>();
    public UnitStatsUI StatsUI { get; set; } = null;

    //public List<Ability> effects { get; set; } = new List<Ability>();

    private Health health;
    private Mana mana;

    private void Awake()
    {
        if (maxHealth < 1) maxHealth = 1;

        health = GetComponent<Health>();

        mana = GetComponent<Mana>();
    }

    private void Start()
    {
        health.Init(maxHealth, hpRegeneration);

        ChangePhysicDamage(0);
        ChangeAttackSpeed(0);
        ChangeAttackRange(0);
        ChangePhysicArmor(0);
        ChangeMagicArmor(0);
        ChangeMoveSpeed(0);
        ChangeMaxHealth(0);
        ChangeHpRegeneration(hpRegeneration);
        ChangeSpellPower(0);

        ChangeBonusDamage(0);
        ChangeBonusAttackSpeed(0);
        ChangeBonusAttackRange(0);
        ChangeBonusPhysicArmor(0);
        ChangeBonusMagicArmor(0);
        ChangeBonusMoveSpeed(0);
        ChangeBonusMaxHealth(0);
        ChangeBonusHpRegeneration(bonusHpRegeneration);
        ChangeBonusSpellPower(0);
    }

    public void HandlerEffects(Effect ability)
    {
        Debug.Log(ability.name + " was added");
        ability.AddEffect(this);
        StartCoroutine(WaitForEffect(ability));
    }

    private IEnumerator WaitForEffect(Effect ability)
    {
        yield return new WaitForSeconds(ability.DurationAbility);
        ability.RemoveEffect(this);
        Debug.Log(ability.name + " was deleted");
    }

    #region ChangeBaseStats
    public void ChangeManaRegeneration(float value)
    {
        if (mana != null)
        {
            mana.ChangeManaRegeneration(value);

            if (StatsUI != null)
                StatsUI.RegenerationMPText.text = "+" + Math.Round(mana.GetSummaryManaRegeneration, 2).ToString();
        }
    }

    public void ChangeMaxMana(float value)
    {
        if(mana != null)
        {
            mana.ChangeMaxMana(value);

            if (StatsUI != null)
                StatsUI.MaxMPText.text = "/" + Mathf.Round(mana.GetMaxMana).ToString();
        }
    }

    public void ChangeHpRegeneration(float value)
    {
        hpRegeneration = health.ChangeHpRegeneration(value);

        if(StatsUI != null)
            StatsUI.RegenerationHPText.text = "+" + Math.Round(GetSummaryHpRegeneration, 2).ToString();
    }

    public void ChangeMaxHealth(float value)
    {
        maxHealth = health.ChangeMaxHealth(value);

        if (StatsUI != null)
            StatsUI.MaxHPText.text = "/" + maxHealth.ToString();
    }

    public void ChangePhysicArmor(float value)
    {
        physicArmor = Mathf.Clamp(physicArmor + value, 0, Mathf.Infinity);

        if (StatsUI != null)
            StatsUI.PhysicArmorText.text = Mathf.Round(physicArmor).ToString();
    }

    public void ChangeMagicArmor(float value)
    {
        magicArmor = Mathf.Clamp(magicArmor + value, 0, Mathf.Infinity);

        if (StatsUI != null)
            StatsUI.MagicArmorText.text = Mathf.Round(magicArmor).ToString();
    }

    public void ChangePhysicDamage(float value)
    {
        physicDamage = Mathf.Clamp(physicDamage + value, 0, Mathf.Infinity);

        if (StatsUI != null)
            StatsUI.DamageText.text = Mathf.Round(physicDamage).ToString();
    }

    public void ChangeMoveSpeed(float value)
    {
        moveSpeed = Mathf.Clamp(moveSpeed + value, 0, Consts.MaxMoveSpeed);

        if (StatsUI != null)
            StatsUI.MoveSpeedText.text = Math.Round(moveSpeed,2).ToString();
    }

    public void ChangeAttackSpeed(float value)
    {
        attackSpeed = Mathf.Clamp(attackSpeed - value, Consts.MaxAttackSpeed, Mathf.Infinity);

        if (StatsUI != null)
            StatsUI.AttackSpeedText.text = Math.Round(attackSpeed, 2).ToString();
    }

    public void ChangeAttackRange(float value)
    {
        attackRange = Mathf.Clamp(attackRange + value, 0, Mathf.Infinity);

        if (StatsUI != null)
            StatsUI.RangeText.text = Mathf.Round(attackSpeed).ToString();
    }

    public void ChangeSpellPower(float value)
    {
        spellPower = Mathf.Clamp(spellPower + value, 0, Mathf.Infinity);

        if (StatsUI != null)
            StatsUI.SpellPowerText.text = Mathf.Round(spellPower).ToString();
    }
    #endregion
    #region ChangeBonusStats
    public void ChangeBonusManaRegeneration(float value)
    {
        if (mana != null)
        {
            mana.ChangeBonusManaRegeneration(value);

            if (StatsUI != null)
                StatsUI.RegenerationMPText.text = "+" + Math.Round(mana.GetSummaryManaRegeneration, 2).ToString();
        }
    }

    public void ChangeBonusMaxMana(float value)
    {
        if (mana != null)
        {
            mana.ChangeBonusMaxMana(value);

            if (StatsUI != null)
                StatsUI.MaxMPText.text = "/" + Mathf.Round(mana.GetMaxMana).ToString();
        }
    }

    public void ChangeBonusHpRegeneration(float value)
    {
        bonusHpRegeneration = health.ChangeBonusHpRegeneration(value);

        if (StatsUI != null)
            StatsUI.RegenerationHPText.text = "+" + Math.Round(GetSummaryHpRegeneration, 2).ToString();
    }

    public void ChangeBonusMaxHealth(float value)
    {
        bonusMaxHealth = health.ChangeBonusMaxHealth(value);
        ChangeMaxHealth(value);
    }

    public void ChangeBonusPhysicArmor(float value)
    {
        bonusPhysicArmor += value;

        if (StatsUI != null)
            StatsUI.BonusPhysicArmorText.text = "+" + bonusPhysicArmor.ToString();
    }

    public void ChangeBonusMagicArmor(float value)
    {
        bonusMagicArmor += value;

        if (StatsUI != null)
            StatsUI.BonusMagicArmorText.text ="+" + bonusMagicArmor.ToString();
    }

    public void ChangeBonusDamage(float value)
    {
        bonusPhysicDamage = bonusPhysicDamage + value;

        if (StatsUI != null)
            StatsUI.BonusDamageText.text = "+" + bonusPhysicDamage.ToString();
    }

    public void ChangeBonusMoveSpeed(float value)
    {
        bonusMoveSpeed = Mathf.Clamp(bonusMoveSpeed + value, 0, Consts.MaxMoveSpeed);

        if (StatsUI != null)
            StatsUI.BonusMoveSpeedText.text = "+" + Math.Round(bonusMoveSpeed, 2).ToString();
    }

    public void ChangeBonusAttackSpeed(float value)
    {
        //bonusAttackSpeed = Mathf.Clamp(bonusAttackSpeed - value, Consts.MaxAttackSpeed, Mathf.Infinity);
        bonusAttackSpeed = bonusAttackSpeed + value;

        if (StatsUI != null)
            StatsUI.BonusAttackSpeedText.text = "-" + bonusAttackSpeed.ToString();
    }

    public void ChangeBonusAttackRange(float value)
    {
        bonusAttackRange = Mathf.Clamp(bonusAttackRange + value, 0, Mathf.Infinity);

        if (StatsUI != null)
            StatsUI.BonusRangeText.text = "+" + bonusAttackRange.ToString();
    }

    public void ChangeBonusSpellPower(float value)
    {
        bonusSpellPower = Mathf.Clamp(bonusSpellPower + value, 0, Mathf.Infinity);

        if (StatsUI != null)
            StatsUI.BonusSpellPowerText.text = "+" + bonusSpellPower.ToString();
    }
    #endregion
}
