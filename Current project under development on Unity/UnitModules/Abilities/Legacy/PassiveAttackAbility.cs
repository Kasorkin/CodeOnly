using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PassiveAttackAbility : GameAbility
{
    public override bool IsActive() => false;

    public virtual void Ability(DamageHandler damageHandler, int currentAbilityLevel = 1) { }

    public override void InitAbility(GameObject ownerOfAbility)
    {
        Debug.Log(this.name);
        ownerOfAbility.GetComponent<Unit>().PassiveAttackAbilities.Add(this);
    }

    /*public override bool IsActive() => false;

    [System.Serializable]
    public struct AbilityLevelData
    {
        public Effect effect;
        [Range(0, 100)]public int chance;
        public float duration;
        public float cooldown;
    }

    [Header("PassiveAttackData")]
    [SerializeField] private List<AbilityLevelData> levelsOfAbility = new List<AbilityLevelData>();

    public List<AbilityLevelData> GetAbilityLevelsData => levelsOfAbility;

    public virtual void Ability(GameObject ownerOfAbility, int currentAbilityLevel)
    {
        //если по шансу не прошел, то покеда
        if (Random.Range(1, 100) > levelsOfAbility[currentAbilityLevel - 1].chance) return;

        //ко всем атакам персонажа применили эффект текущего уровня
        UnitAttack[] unitAttacks = ownerOfAbility.GetComponents<UnitAttack>();
        foreach (UnitAttack unitAttack in unitAttacks)
        {
            unitAttack.EffectsOfAttack.Add(levelsOfAbility[currentAbilityLevel - 1].effect);
        }
    }*/
}
