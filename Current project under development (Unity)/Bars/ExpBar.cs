using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ExpBar : MonoBehaviour
{
    public Slider slider;

    public int Lvl { get; set; } = 0;

    private void Start()
    {
        slider.value = 0;
        slider.maxValue = Consts.MaxExp;
    }

    public void AddExperience(int exp)
    {
        float remainderExp = 0;

        if (slider.value + exp >= slider.maxValue)
        {
            remainderExp = slider.maxValue - slider.value;
            remainderExp = exp - remainderExp;
            LvlUp(Mathf.RoundToInt(remainderExp));
        }
        else
            slider.value += exp;
    }

    private void LvlUp(int remainderExp)
    {
        ++Lvl;
        //Debug.Log(Lvl);
        slider.maxValue = Consts.MaxExp * Lvl;
        if (remainderExp > slider.maxValue)
            AddExperience(Mathf.RoundToInt(remainderExp - slider.maxValue));
        slider.value = remainderExp;
    }   
}
