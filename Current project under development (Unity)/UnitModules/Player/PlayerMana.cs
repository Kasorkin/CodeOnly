using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Photon.Pun;

public class PlayerMana : Mana
{
    //Multiplayer
    private PhotonView photonView;
    //
    private ManaBar canvasManaBar;

    public override void ChangeMaxMana(float amount)
    {
        maxMana = Mathf.Clamp(maxMana + amount, 1, Mathf.Infinity);

        if (manaBar != null)
            manaBar.SetMaxMana(maxMana);

        //UI player
        if (canvasManaBar != null)
            canvasManaBar.SetMaxMana(maxMana);

        if (unit != null)
            unit.StatsUI.MaxMPText.text = "/" +  Mathf.Round(maxMana).ToString();

        ManaChange(amount);
    }

    public override void ManaChange(float amount)
    {
        base.ManaChange(amount);

        //UI player
        if (canvasManaBar != null)
            canvasManaBar.SetMana(currentMana);

        if (unit != null)
            unit.StatsUI.CurrentMPText.text = Mathf.Round(currentMana).ToString();
    }
}
