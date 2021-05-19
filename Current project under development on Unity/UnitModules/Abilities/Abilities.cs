using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Abilities : MonoBehaviour
{
    [SerializeField] protected int abilitiesSlotsMaxCount = 5;

    [SerializeField] protected List<GameAbility> gameAbilities = new List<GameAbility>();

    public delegate void OnAbilityChanged();
    public OnAbilityChanged onAbilityChangedCallBack;

    public List<GameAbility> GameAbilities { get => gameAbilities; set => gameAbilities = value; }

    public virtual bool AddAbility(GameAbility gameAbility)
    {
        if(abilitiesSlotsMaxCount <= GameAbilities.Count)
        {
            Debug.Log("Maximum count of abilities");
            return false;
        }

        GameAbilities.Add(gameAbility);
        LoadingAbility(gameAbility);
        return true;
    }

    public virtual bool RemoveAbility(GameAbility gameAbility)
    {
        bool isRemove = GameAbilities.Remove(gameAbility);
        if(!isRemove)
        {
            Debug.Log("Ability has not been a removed");
            return false;
        }

        ChangerBonusStats.UnsetStats(gameObject, gameAbility.BonusStatsOwnerOfAbility);
        return true;
    }

    public virtual void LoadingAbility(GameAbility gameAbility)
    {
        ChangerBonusStats.SetStats(gameObject, gameAbility.BonusStatsOwnerOfAbility);
        gameAbility.CurrentAbilityLvl = 1;
    }

    private void Start()
    {
        foreach(GameAbility gameAbility in GameAbilities)
        {
            LoadingAbility(gameAbility);
        }
    }
}
