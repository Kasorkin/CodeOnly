using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AuraAbility : PassiveAbility
{
    [Header("AuraData")]
    //[SerializeField] protected float radiusOfImpact;
    [SerializeField] protected bool isPeriodic;
    [SerializeField] protected LayerMask layersOfImpact;
    [SerializeField] protected GameObject auraControllerObjectPrefab;

    //public float RadiusOfImpact { get => radiusOfImpact; set => radiusOfImpact = value; }
    public bool IsPeriodic => isPeriodic;
    public LayerMask LayersOfImpact { get => layersOfImpact; set => layersOfImpact = value; }

    //
    public AuraController auraController { get; set; }
    //
    public virtual void AddImpact(GameObject targetImpact) { }
    public virtual void DeleteImpact(GameObject targetImpact) { }

    public override void InitPassiveAbility(GameObject ownerOfAura)
    {
        if (auraControllerObjectPrefab == null)
            Debug.LogWarning("auraControllerObjectPrefab in aura == null");

        //создали на карте объект
        GameObject auraControllerObject = Instantiate(auraControllerObjectPrefab);
        //прицепили к персонажу и сделали его дочерним
        auraControllerObject.transform.parent = ownerOfAura.transform;
        auraControllerObject.transform.localPosition = Vector3.zero;
        //передача данных
        CurrentAbilityLvl = startAbilityLvl;
        auraControllerObject.GetComponent<AuraController>().Init(layersOfImpact, this, ownerOfAura);

        //сохранили ссылку 
        auraController = auraControllerObject.GetComponent<AuraController>();
    }

}
