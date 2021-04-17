using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class NPCRangeAttack : MonoBehaviour
{
    [Header("RangeAttack")]
    [SerializeField] private float damage = 1f;
    [SerializeField] private float radiusOfAttack = 2f;
    [SerializeField] private float flightSpeed = 5f;
    [SerializeField] private float waitAttack = 1f;
    [SerializeField] private GameObject anim;
    private bool waitingAttack = false;

    [Header("Search")]
    [SerializeField] private float radiusSearchTarget = 10f;

    [Header("Target")]
    [SerializeField] private GameObject target = null;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        if(target != null)
        {
            RangeAttackNPC();
        }
        else
        {
            Detection();
        }
    }

    private void Detection()
    {
        if (target != null) return;

        target = SearchTarget.SearchingTarget(transform.position, (int)radiusSearchTarget, Consts.LayerLight);
        if (target == null)
            target = SearchTarget.SearchingTarget(transform.position, (int)radiusSearchTarget, Consts.LayerNeutralEnemy);
    }

    private void RangeAttackNPC()
    {
        if (waitingAttack || Vector2.Distance(gameObject.transform.position, target.transform.position) > radiusOfAttack) return;

        waitingAttack = true;

        GameObject weapon = Instantiate(anim, transform.position, transform.rotation);

        weapon.transform.right = -(target.transform.position - transform.position);
        weapon.GetComponent<Shooting>().Init(gameObject, target.transform.position, damage, radiusOfAttack, flightSpeed);

        StartCoroutine(UniversalWaits());
    }

    private IEnumerator UniversalWaits()
    {
        yield return new WaitForSeconds(waitAttack);
        waitingAttack = false;
    }
}
