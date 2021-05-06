using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HeroAbilities : Abilities
{
    public override bool AddAbility(GameAbility gameAbility)
    {
        if (abilitiesSlotsMaxCount <= GameAbilities.Count)
        {
            Debug.Log("Maximum count of abilities");
            return false;
        }

        GameAbilities.Add(gameAbility);
        LoadingAbility(gameAbility);

        if (onAbilityChangedCallBack != null)
        {
            onAbilityChangedCallBack.Invoke();
        }

        return true;
    }

    public override bool RemoveAbility(GameAbility gameAbility)
    {
        bool isRemove = GameAbilities.Remove(gameAbility);
        if (!isRemove)
        {
            Debug.Log("Ability has not been a removed");
            return false;
        }

        ChangerBonusStats.UnsetStats(gameObject, gameAbility.BonusStatsOwnerOfAbility);
        return true;
    }

    public override void LoadingAbility(GameAbility gameAbility)
    {
        ChangerBonusStats.SetStats(gameObject, gameAbility.BonusStatsOwnerOfAbility);
        gameAbility.CurrentAbilityLvl = 1;
    }

    private void Start()
    {
        foreach (GameAbility gameAbility in GameAbilities)
        {
            LoadingAbility(gameAbility);
        }
        if (onAbilityChangedCallBack != null)
        {
            onAbilityChangedCallBack.Invoke();
        }
    }
}
