using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public static class Consts
{
    //опыт
    public const int MaxExp = 200;
    public const float ExperienceDropRadius = 10f;
    
    //пределы характеристик
    public const float MaxMoveSpeed = 10f;
    public const float MaxAttackSpeed = 0.05f;

    //влияние геройский аттрибутов на характеристики
    public const float PrimaryAttributeDamageFactor = 1.4f;

    //strength
    public const float StrengthHpFactor = 21f;
    public const float StrengthRegenerationFactor = 0.08f;

    //agility
    public const float AgilityArmorFactor = 0.24f;
    public const float AgilityAttackSpeedFactor = 0.01f;

    //intelligence
    public const float IntelligenceManaFactor = 17f;
    public const float IntelligenceRegenerationFactor = 0.03f;

    //armor
    public const float ArmorFarctor = 0.02f;



    //НИКОГДА НЕ МЕНЯТЬ ЭТИ КОНСТАНТЫ
    public const int HeroInventorySlotsCount = 6;
    //слои
    public const int LayerNeutralEnemy = 9;
    public const int LayerDark = 7;
    public const int LayerLight = 8;
}
