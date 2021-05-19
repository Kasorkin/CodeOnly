using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AuraController : MonoBehaviour
{
    private LayerMask layersOfImpact;
    private AuraAbility auraAbility;
    private GameObject ownerOfAura;
    private CircleCollider2D auraCollider;

    public void Init(LayerMask layersOfImpact, AuraAbility auraAbility, GameObject ownerOfAura)
    {
        auraCollider = GetComponent<CircleCollider2D>();

        this.layersOfImpact = layersOfImpact;
        this.auraAbility = auraAbility;

        //устанавливаем радиус 1-го уровня
        if (!auraAbility.IsPeriodic)
            auraCollider.radius = ((BonusStatAura)auraAbility).LevelsOfAbility[auraAbility.CurrentAbilityLvl - 1].radiusOfImpact;
        //else 
        //    auraCollider.radius = ((PeriodicAura)AuraAbility).Le
        //GetComponent<CircleCollider2D>().radius = auraAbility.LevelsOfAbility;

        this.ownerOfAura = ownerOfAura;
        AddAuraForOwner();
    }

    public void AddAuraForOwner()
    {
        //добавить эффекты на носителя ауры, если они положительные
        if (layersOfImpact.Includes(ownerOfAura.layer))
        {
            auraAbility.AddImpact(ownerOfAura);
        }
    }

    public void Update()
    {
        if (Input.GetKeyDown(KeyCode.Backspace))
            auraAbility.LvlUpAbility();
    }

    public bool LvlAbilityChanging { get; set; } = false;

    public List<Unit> UpdateLvlAbility(float radiusOfImpact, LayerMask layersOfImpact)
    {
        return SearchTarget.SearchingUnitsInArea(gameObject.transform.position, radiusOfImpact, layersOfImpact);
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (LvlAbilityChanging) return;

        if(layersOfImpact.Includes(collision.gameObject.layer))
        {
            auraAbility.AddImpact(collision.gameObject);
        }
    }

    private void OnTriggerExit2D(Collider2D collision)
    {
        if (LvlAbilityChanging) return;

        if (layersOfImpact.Includes(collision.gameObject.layer))
        {
            auraAbility.DeleteImpact(collision.gameObject);
        }
    }
}
