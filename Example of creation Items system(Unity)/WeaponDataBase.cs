using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "New Weapon", menuName = "Inventory/Weapon")]
public class WeaponDataBase : ItemDataBase
{
    [Header("WeaponDataBase")]
    //Характеристики
    [SerializeField]
    private int damage;
    [SerializeField]
    private float rangeOfAttack;
    [SerializeField]
    private float factorAS;
    [SerializeField]
    private EnumData.WeaponType type;

    [SerializeField]
    private int requiredStrength;
    [SerializeField]
    private int requiredAgility;
    [SerializeField]
    private int requiredIntelligence;

    [SerializeField]
    private List<GameObject> requiredPerk = new List<GameObject>();

    [SerializeField]
    private Sprite maskInGame;

    public int Damage { get => damage; set => damage = value; }
    public float RangeOfAttack { get => rangeOfAttack; set => rangeOfAttack = value; }
    public float FactorAS { get => factorAS; set => factorAS = value; }
    public EnumData.WeaponType Type { get => type; set => type = value; }
    public int RequiredStrength { get => requiredStrength; set => requiredStrength = value; }
    public int RequiredAgility { get => requiredAgility; set => requiredAgility = value; }
    public int RequiredIntelligence { get => requiredIntelligence; set => requiredIntelligence = value; }
    public List<GameObject> RequiredPerk { get => requiredPerk; set => requiredPerk = value; }
    public Sprite MaskInGame { get => maskInGame; set => maskInGame = value; }
}
