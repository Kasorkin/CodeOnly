using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AuraController : MonoBehaviour
{
    private LayerMask layersOfImpact;
    private AuraAbility auraAbility;
    private GameObject ownerOfAura;
    private CircleCollider2D auraCollider;
    private List<GameObject> gameObjectsInAura = new List<GameObject>(); 

    public int LevelOfAura { get; set; } = 1;

    public void Init(LayerMask layersOfImpact, AuraAbility auraAbility, GameObject ownerOfAura)
    {
        auraCollider = GetComponent<CircleCollider2D>();

        this.layersOfImpact = layersOfImpact;
        this.auraAbility = auraAbility;

        //устанавливаем радиус 1-го уровня
        if (!auraAbility.IsPeriodic())
            auraCollider.radius = ((BonusStatAura)auraAbility).GetLevelsOfAbility[LevelOfAura - 1].radiusOfImpact;
        else
            auraCollider.radius = ((PeriodicAura)auraAbility).GetAbilityLevelsData[LevelOfAura - 1].radiusOfImpact;

        this.ownerOfAura = ownerOfAura;
        AddAuraForOwner();
    }

    public void AddAuraForOwner()
    {
        //добавить эффекты на носителя ауры, если они положительные
        if (layersOfImpact.Includes(ownerOfAura.layer))
        {
            auraAbility.AddImpact(ownerOfAura, LevelOfAura);
        }
    }

    public void Update()
    {
        if (Input.GetKeyDown(KeyCode.Backspace))
            auraAbility.LvlUpAbility(LevelOfAura);
    }

    public bool LvlAbilityChanging { get; set; } = false;

    public void UpdateLevelAbility(float radiusOfImpact, LayerMask layersOfImpact)
    {
        LvlAbilityChanging = true;

        List<Unit> unitsInArea;
        if(auraAbility.IsPeriodic())
            unitsInArea = SearchTarget.SearchingUnitsInArea(gameObject.transform.position, ((PeriodicAura)auraAbility).GetAbilityLevelsData[LevelOfAura].radiusOfImpact, layersOfImpact);
        else
            unitsInArea = SearchTarget.SearchingUnitsInArea(gameObject.transform.position, ((BonusStatAura)auraAbility).GetLevelsOfAbility[LevelOfAura].radiusOfImpact, layersOfImpact);

        foreach (Unit unit in unitsInArea)
        {
            auraAbility.DeleteImpact(unit.gameObject, LevelOfAura);
        }

        LevelOfAura++;
        if (auraAbility.IsPeriodic())
            unitsInArea = SearchTarget.SearchingUnitsInArea(gameObject.transform.position, ((PeriodicAura)auraAbility).GetAbilityLevelsData[LevelOfAura].radiusOfImpact, layersOfImpact);
        else
            unitsInArea = SearchTarget.SearchingUnitsInArea(gameObject.transform.position, ((BonusStatAura)auraAbility).GetLevelsOfAbility[LevelOfAura].radiusOfImpact, layersOfImpact);

        foreach (Unit unit in unitsInArea)
        {
            auraAbility.AddImpact(unit.gameObject, LevelOfAura);
        }

        LvlAbilityChanging = false;
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (LvlAbilityChanging) return;

        if(layersOfImpact.Includes(collision.gameObject.layer))
        {
            if (auraAbility.IsPeriodic())
            {
                gameObjectsInAura.Add(collision.gameObject);
                if (gameObjectsInAura.Count == 1)
                    StayAura();
            }
            else
            {
                auraAbility.AddImpact(collision.gameObject, LevelOfAura);
            }
        }
    }
    
    private void StayAura()
    {
        StartCoroutine(Stay());
    }

    private IEnumerator Stay()
    {
        PeriodicAura periodicAura = (PeriodicAura)auraAbility;
        while (gameObjectsInAura.Count != 0)
        {
            int size = gameObjectsInAura.Count;
            foreach (GameObject gameObject in gameObjectsInAura)
            {
                /*if (gameObject == null)
                {
                    Debug.Log("update");
                    AuraUpdate();
                    break;
                }*/
                
                periodicAura.StayImpact(gameObject, LevelOfAura);
                if (size != gameObjectsInAura.Count)
                    break;
            }
            yield return new WaitForSeconds (periodicAura.GetAbilityLevelsData[LevelOfAura - 1].coldownOfImpact);
        }
    }

    /*private void AuraUpdate()
    {
        List<Unit> searchList = SearchTarget.SearchingUnitsInArea(gameObject.transform.position, ((PeriodicAura)auraAbility).GetAbilityLevelsData[LevelOfAura].radiusOfImpact, layersOfImpact);
        gameObjectsInAura.Clear();
        foreach (Unit unit in searchList)
        {
            gameObjectsInAura.Add(unit.gameObject);
        }
        Debug.Log("updateEnd");
    }*/

    private void OnTriggerExit2D(Collider2D collision)
    {
        if (LvlAbilityChanging) return;

        if (layersOfImpact.Includes(collision.gameObject.layer))
        {
            if (auraAbility.IsPeriodic())
            {
                gameObjectsInAura.Remove(collision.gameObject);
            }
            else
            {
                auraAbility.DeleteImpact(collision.gameObject, LevelOfAura);
            }
        }
    }
}
