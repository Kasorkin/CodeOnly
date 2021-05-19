using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Unit))]
public class DamageHandler : MonoBehaviour
{
    private Health health;
    private Unit unit;
    private Abilities abilities;

    [Header("Drop")]
    [SerializeField] private int experience = 10;
    //[SerializeField] private int gold = 10;
    [SerializeField] private List<GameObject> dropList = new List<GameObject>();

    public float DirectDamage { get; set; }
    public GameObject Attaker { get; set; }
    public Abilities GetAbilities => abilities;
    public Unit GetUnit => unit;

    public void InputDamage(float damage, EnumData.DamageType damageType = EnumData.DamageType.Physical, bool isTrigger = false)
    {
        if (!isTrigger)
            PassiveAbilitiesHandler();

        switch (damageType)
        {
            case EnumData.DamageType.Physical:
                damage = PhysicalDamageHandler(damage);
                break;
            case EnumData.DamageType.Magical:
                damage = MagicalDamageHandler(damage);
                break;
            case EnumData.DamageType.Pure:
                damage = PureDamageHandler(damage);
                break;
        }

        Debug.Log(-damage);
        health.HealthChange(-damage);
    }

    public void Die()
    {
        Destroy(unit.GetComponent<UnitAttack>().GetWeapon());

        //дроп золота
        DropSystem.Drop(dropList, experience, gameObject.transform);
        Destroy(gameObject);
    }

    private void PassiveAbilitiesHandler()
    {
        foreach (var passiveDefenseAbility in unit.PassiveDefenceAbilities)
        {
            passiveDefenseAbility.Ability(this, abilities.LevelOfThisAbility(passiveDefenseAbility));
        }
    }

    private float PhysicalDamageHandler(float damage)
    {
        return ArmorSystem.CalcilationResultDamage(damage, unit.GetSummaryPhysicArmor);    
    }

    private float MagicalDamageHandler(float damage)
    {
        return damage;
    }

    private float PureDamageHandler(float damage)
    {
        return damage;
    }

    private void Start()
    {
        health = GetComponent<Health>();
        unit = GetComponent<Unit>();
        abilities = GetComponent<Abilities>();
    }

    private void OnTriggerEnter2D(Collider2D other)
    {
        Shooting weapon = other.gameObject.GetComponent<Shooting>();

        if (weapon && weapon.Attaker != gameObject)
        {
            DamageHandler attackerHandler = weapon.Attaker.GetComponent<DamageHandler>();

            DirectDamage = weapon.Damage;

            foreach (var passiveAttackAbility in attackerHandler.GetUnit.PassiveAttackAbilities)
            {
                passiveAttackAbility.Ability(this, attackerHandler.GetAbilities.LevelOfThisAbility(passiveAttackAbility));
            }

            Attaker = weapon.Attaker;
            InputDamage(DirectDamage, weapon.DamageType, false);
            Destroy(weapon.gameObject);
        }
    }
}
