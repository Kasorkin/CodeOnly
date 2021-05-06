using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class NPC : MonoBehaviour
{
    [Header("Movement")]
    [SerializeField] private float rangeToGoal = 0.5f;
    [SerializeField] private float radiusSearchTarget = 10f;

    [Header("NextPointToMove")]
    [SerializeField] private GameObject nextPoint = null;

    [Header("Target")]
    [SerializeField] private GameObject target = null;

    Unit unit;
    UnitAttack[] unitAttacks;
    MovingForMouseInRadius movingForMouseInRadius;
    //встроенные модули
    public MMovement MovementModule { get; set; }

    private void Start()
    {
        unitAttacks = GetComponents<UnitAttack>();
        unit = GetComponent<Unit>();
        MovementModule = new MMovement(GetComponent<Rigidbody2D>(), rangeToGoal, unit.GetSummaryMoveSpeed);

        //скриптов может быть много, но оружие должно быть одно!
        //if(CoroutineLoader.GlobalUniversalWaits())
            movingForMouseInRadius = unitAttacks[0].GetWeapon().GetComponent<MovingForMouseInRadius>();
    }

    private void FixedUpdate()
    {
        if(target != null)
        {
            movingForMouseInRadius.TargetPos = target.transform.position;

            foreach (UnitAttack unitAttack in unitAttacks)
                unitAttack.Attack(target.transform.position);
        }
        else
        {
            Detection();
        }
            

        /*if (nextPoint != null)
        {
            //MovementModule.MyFixedUpdate(transform, nextPoint.transform.position);
        }
        else
        {
            SearchNextPointToMove();
        }*/
            
    }

    private void SearchNextPointToMove()
    {

    }

    private void Detection()
    {
        if (target != null) return;

        target = SearchTarget.SearchingTarget(transform.position, (int)radiusSearchTarget, Consts.LayerLight);
        if (target == null)
            target = SearchTarget.SearchingTarget(transform.position, (int)radiusSearchTarget, Consts.LayerNeutralEnemy);
    }
}
