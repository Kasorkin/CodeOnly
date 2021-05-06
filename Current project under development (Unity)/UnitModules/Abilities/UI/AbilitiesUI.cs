using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AbilitiesUI : MonoBehaviour
{
    [SerializeField] private Transform abilityParent;

    [SerializeField] private HeroAbilities heroAbilities;

    private SkillSlot[] slots;

    public HeroAbilities HeroAbilities { get => heroAbilities; set => heroAbilities = value; }

    private void Awake()
    {
        heroAbilities.onAbilityChangedCallBack += UpdateUI;
        slots = abilityParent.GetComponentsInChildren<SkillSlot>();
    }

    private void UpdateUI()
    {
        int size = slots.Length;
        for (int i = 0; i < size; ++i)
        {
            if (i < heroAbilities.GameAbilities.Count)
            {
                slots[i].AddAbility(heroAbilities.GameAbilities[i]);
            }
            /*else
            {
                slots[i].ClearSlot();
            }*/
        }
    }
}
