using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "New RangeWeapon", menuName = "Inventory/RangeWeapon")]
public class RangeWeaponDataBase : WeaponDataBase
{
    [Header("RangeWeaponDataBase")]
    //Характеристики
    [SerializeField]
    private EnumData.RangeWeaponType weaponType;
    [SerializeField]
    private EnumData.AmmunitionType ammunitionType;

    public EnumData.RangeWeaponType WeaponType { get => weaponType; set => weaponType = value; }
    public EnumData.AmmunitionType AmmunitionType { get => ammunitionType; set => ammunitionType = value; }
}
