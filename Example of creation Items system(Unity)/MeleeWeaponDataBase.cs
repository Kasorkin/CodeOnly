using UnityEngine;
using System.Collections.Generic;


[CreateAssetMenu(fileName ="New MeleeWeapon", menuName ="Inventory/MeleeWeapon")]
public class MeleeWeaponDataBase : WeaponDataBase
{
    [Header("MeleeWeaponDataBase")]
    //Характеристики
    [SerializeField]
    private EnumData.MeleeWeaponType weaponType;

    //в самом перке должно содержаться описание и тп
    [SerializeField]
    private Sprite animSprite;//картиночка

    public Sprite AnimSprite { get => animSprite; set => animSprite = value; }
    public EnumData.MeleeWeaponType WeaponType { get => weaponType; set => weaponType = value; }
}
