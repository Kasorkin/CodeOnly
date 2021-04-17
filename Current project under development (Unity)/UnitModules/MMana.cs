using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MMana
{
    private float currentMana = 100;
    private float maxMana = 100;
    private ManaBar manaBar;

    public MMana(float maxMana, ManaBar manaBar = null)
    {
        this.maxMana = maxMana;
        currentMana = maxMana;

        if (manaBar != null)
        {
            this.manaBar = manaBar;
            this.manaBar.SetMaxMana(maxMana);
            this.manaBar.SetMana(currentMana);
        }
    }

    public bool ManaChangeMax(float amount)
    {
        maxMana += amount;

        ManaChange(amount);

        return true;
    }

    public bool ManaChange(float amount)
    {
        currentMana = Mathf.Clamp(currentMana + amount, 0, maxMana);

        if (manaBar != null)
            manaBar.SetMana(currentMana);

        if (currentMana == 0)
            return false;

        return true;
    }
}
