using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "New TargetAreaAbility", menuName = "PositionActiveAbilities/TargetAreaAbility")]
public class TargetAreaAbility : PositionActiveAbility
{
    //здесь должен быть список атакующих эффектов
    [Header("Effects")]
    [SerializeField] private List<Effect> effects = new List<Effect>();

    [Header("HealOrDamage")]
    [SerializeField] private float value;
    [SerializeField] private bool isDamage;
    [SerializeField] private float radius;
    [SerializeField] private EnumData.DamageType damageType;
    [SerializeField] private LayerMask layersOfEffect;

    public override void Use(Vector2 pos)
    {
        List<Unit> unitsInArea = SearchTarget.SearchingUnitsInArea(pos, radius, layersOfEffect);
        
        foreach (Unit unit in unitsInArea)
        {
            if (isDamage)
                unit.GetComponent<Health>().InputDamage(value, damageType);
            else
                unit.GetComponent<Health>().HealthChange(value);
        }
    }
}
