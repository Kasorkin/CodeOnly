using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Photon.Pun;

public class PlayerHealth : Health
{
    //Multiplayer
    private PhotonView photonView;
    //

    private HealthBar canvasHealthBar;

    public override void Init(float maxHealth, float hpRegeneration)
    {
        base.Init(maxHealth, hpRegeneration);

        //UI player
        canvasHealthBar = GetComponent<PlayerScript>().PlayerCanvasData.UiHealhBar;
        if (canvasHealthBar != null)
        {
            canvasHealthBar.SetMaxHealth(maxHealth);
            canvasHealthBar.SetHealth(currentHealth);
        }
    }

    public override float ChangeMaxHealth(float amount)
    {
        maxHealth = Mathf.Clamp(maxHealth + amount, 1, Mathf.Infinity);

        if (healthBar != null)
            healthBar.SetMaxHealth(maxHealth);
        //UI player
        if (canvasHealthBar != null)
            canvasHealthBar.SetMaxHealth(maxHealth);

        HealthChange(amount);
        return maxHealth;
    }

    public override void HealthChange(float amount)
    {
        base.HealthChange(amount);

        //UI player
        if (canvasHealthBar != null)
            canvasHealthBar.SetHealth(currentHealth);

        if(unit != null)
            unit.StatsUI.CurrentHPText.text = Mathf.Round(currentHealth).ToString();
    }

    private void Start()
    {
        photonView = GetComponent<PhotonView>();
    }

    private void FixedUpdate()
    {
        if (!photonView.IsMine) return;

        HealthRegeneration();
    }
}
