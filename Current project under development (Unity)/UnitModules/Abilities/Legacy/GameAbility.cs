using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameAbility : ScriptableObject
{
    [Header("GeneralData")]
    [SerializeField] protected Sprite icon;
    [SerializeField] [Multiline] protected string description;

    [Header("PassiveBonusStats")]
    [SerializeField] protected List<PassiveBonusData> bonusStatsOwnerOfAbility = new List<PassiveBonusData>();

    [SerializeField] protected bool isActive;

    protected static int startAbilityLvl = 1;
    public int CurrentAbilityLvl { get; set; }

    public virtual void LvlUpAbility() { }

    public List<PassiveBonusData> BonusStatsOwnerOfAbility { get => bonusStatsOwnerOfAbility; set => bonusStatsOwnerOfAbility = value; }
    public Sprite Icon { get => icon; set => icon = value; }
    public string Description { get => description; set => description = value; }
    public bool IsActive { get => isActive; set => isActive = value; }
}
