using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "New Ammo", menuName = "Inventory/Ammo")]
public class AmmoStatsDataBase : ItemDataBase
{
    [SerializeField]
    private int damageBonus;
    [SerializeField]
    private EnumData.AmmunitionType ammunitionType;

    [SerializeField]
    private Sprite animSprite;//картиночка

    public int DamageBonus { get => damageBonus; set => damageBonus = value; }
    public EnumData.AmmunitionType AmmunitionType { get => ammunitionType; set => ammunitionType = value; }
    public Sprite AnimSprite { get => animSprite; set => animSprite = value; }
}
