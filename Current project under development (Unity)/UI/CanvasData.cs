using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CanvasData : MonoBehaviour
{
    [SerializeField] private HealthBar uiHealhBar;
    [SerializeField] private ManaBar uiManaBar;
    [SerializeField] private ExpBar uiExpBar;
    [SerializeField] private GameObject heroPortait;
    [SerializeField] private GameObject unitData;
    [SerializeField] private GameObject skillsUI;
    [SerializeField] private GameObject itemsUI;

    public HealthBar UiHealhBar { get => uiHealhBar; set => uiHealhBar = value; }
    public ManaBar UiManaBar { get => uiManaBar; set => uiManaBar = value; }
    public ExpBar UiExpBar { get => uiExpBar; set => uiExpBar = value; }
    public GameObject HeroPortait { get => heroPortait; set => heroPortait = value; }
    public GameObject UnitData { get => unitData; set => unitData = value; }
    public GameObject SkillsUI { get => skillsUI; set => skillsUI = value; }
    public GameObject ItemsUI { get => itemsUI; set => itemsUI = value; }
    //лист статов

    private void Start()
    {
        
    }

}
