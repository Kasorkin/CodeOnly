using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Unit))]
public class Mana : MonoBehaviour
{
    [Header("Mana")]
    [SerializeField] private float currentMana;
    [SerializeField] private float maxMana;
    [SerializeField] private float manaRegeneration;

    [Header("Mana")]
    [SerializeField] private ManaBar manaBar;

    private void Start()
    {
        currentMana = maxMana;

        if(manaBar != null)
        {
            manaBar.SetMaxMana(maxMana);
            manaBar.SetMana(currentMana);
        }
    }

    public float ChangeManaRegeneration(float amount)
    {
        manaRegeneration = Mathf.Clamp(manaRegeneration + amount, 0, Mathf.Infinity);
        return manaRegeneration;
    }

    public float ChangeMaxMana(float amount)
    {
        maxMana = Mathf.Clamp(maxMana + amount, 1, Mathf.Infinity);

        if (manaBar != null)
            manaBar.SetMaxMana(maxMana);

        ManaChange(amount);
        return maxMana;
    }

    public void ManaChange(float amount)
    {
        currentMana = Mathf.Clamp(currentMana + amount, 0, maxMana);

        if (manaBar != null)
            manaBar.SetMana(currentMana);
    }

    private void FixedUpdate()
    {
        ManaRegeneration();
    }

    private void ManaRegeneration()
    {
        ManaChange(manaRegeneration * Time.deltaTime);
    }
}
