using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Unit))]
public class Mana : MonoBehaviour
{
    [Header("Mana")]
    [SerializeField] protected float currentMana;
    [SerializeField] protected float maxMana;
    [SerializeField] private float manaRegeneration;

    protected float bonusMaxMana;
    private float bonusManaRegeneration;

    [Header("ManaBar")]
    [SerializeField] protected ManaBar manaBar;

    protected Unit unit;

    public float GetManaRegeneration => manaRegeneration;
    public float GetMaxMana => maxMana;
    public float GetCurrentMana => currentMana;
    public float GetSummaryManaRegeneration => manaRegeneration + bonusManaRegeneration;

    private void Start()
    {
        currentMana = maxMana;

        if(manaBar != null)
        {
            manaBar.SetMaxMana(maxMana);
            manaBar.SetMana(currentMana);
        }
        unit = GetComponent<Unit>();

        ChangeMaxMana(maxMana);
        ChangeManaRegeneration(manaRegeneration);

        ChangeBonusManaRegeneration(bonusManaRegeneration);
        ChangeBonusMaxMana(bonusMaxMana);
    }

    #region ChangeBonusStats
    public void ChangeBonusManaRegeneration(float amount)
    {
        bonusManaRegeneration = Mathf.Clamp(bonusManaRegeneration + amount, 0, Mathf.Infinity);
    }

    public void ChangeBonusMaxMana(float amount)
    {
        bonusMaxMana = Mathf.Clamp(bonusMaxMana + amount, 0, Mathf.Infinity);
        ChangeMaxMana(amount);
    }
    #endregion
    #region ChangeStats
    public void ChangeManaRegeneration(float amount)
    {
        manaRegeneration = Mathf.Clamp(manaRegeneration + amount, 0, Mathf.Infinity);
        //return manaRegeneration;
    }

    public virtual void ChangeMaxMana(float amount)
    {
        maxMana = Mathf.Clamp(maxMana + amount, 1, Mathf.Infinity);

        if (manaBar != null)
            manaBar.SetMaxMana(maxMana);

        ManaChange(amount);
        //return maxMana;
    }

    public virtual void ManaChange(float amount)
    {
        currentMana = Mathf.Clamp(currentMana + amount, 0, maxMana);

        if (manaBar != null)
            manaBar.SetMana(currentMana);
    }
    #endregion
    private void FixedUpdate()
    {
        ManaRegeneration();
    }

    private void ManaRegeneration()
    {
        ManaChange((manaRegeneration + bonusManaRegeneration) * Time.deltaTime);
    }
}
