using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Health))]
public class Unit : MonoBehaviour
{
    [Header("Stats")]
    [SerializeField] private float damage;
    [SerializeField] private float attackSpeed;
    [SerializeField] private float attackRange;
    [SerializeField] private float armor;
    [SerializeField] private float moveSpeed;
    [SerializeField] private float maxHealth;
    [SerializeField] private float hpRegeneration;
    [SerializeField] private float spellPower = 0;

    public float Armor => armor;
    public float Damage => damage;
    public float MoveSpeed => moveSpeed;
    public float AttackSpeed => attackSpeed;
    public float AttackRange => attackRange;
    public float MaxHealth => maxHealth;
    public float HpRegeneration => hpRegeneration;
    public float SpellPower => spellPower;

    private Health health;
    private Mana mana;

    private void Awake()
    {
        if (maxHealth < 1) maxHealth = 1;

        health = GetComponent<Health>();
        health.Init(maxHealth, hpRegeneration);

        mana = GetComponent<Mana>();
    }

    public void ChangeManaRegeneration(float value)
    {
        if (mana != null)
            mana.ChangeManaRegeneration(value);
    }

    public void ChangeMaxMana(float value)
    {
        if(mana != null)
            mana.ChangeMaxMana(value);
    }

    public void ChangeHpRegeneration(float value)
    {
        hpRegeneration = health.ChangeHpRegeneration(value);
    }

    public void ChangeMaxHealth(float value)
    {
        maxHealth = health.ChangeMaxHealth(value);
    }

    public void ChangeArmor(float value)
    {
        armor = Mathf.Clamp(armor + value, 0, Mathf.Infinity);
    }

    public void ChangeDamage(float value)
    {
        damage = Mathf.Clamp(damage + value, 0, Mathf.Infinity);
    }

    public void ChangeMoveSpeed(float value)
    {
        moveSpeed = Mathf.Clamp(moveSpeed + value, 0, Consts.MaxMoveSpeed);
    }

    public void ChangeAttackSpeed(float value)
    {
        attackSpeed = Mathf.Clamp(attackSpeed - value, Consts.MaxAttackSpeed, Mathf.Infinity);
    }

    public void ChangeAttackRange(float value)
    {
        attackRange = Mathf.Clamp(attackRange + value, 0, Mathf.Infinity);
    }

    public void ChangeSpellPower(float value)
    {
        spellPower = Mathf.Clamp(spellPower + value, 0, Mathf.Infinity);
    }
}
