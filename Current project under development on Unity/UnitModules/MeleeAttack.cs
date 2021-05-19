using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Unit))]
public class MeleeAttack : UnitAttack
{
    [Header("MeleeAttack")]
    [SerializeField] private float flightSpeed = 6f;
    [SerializeField] private GameObject meleeWeapon;
    [SerializeField] private GameObject animMeleeWeapon;

    private Vector2 direct;
    private bool waitingAttack = false;

    Unit unit;

    public override GameObject GetWeapon() { return meleeWeapon; }
    public override void SetWeapon(GameObject weapon) { meleeWeapon = weapon; }

    private void Start()
    {
        unit = GetComponent<Unit>();

        meleeWeapon = Instantiate(meleeWeapon);
        meleeWeapon.GetComponent<MeleeMovingWeapon>().SetParent = transform;
    }

    public override void Attack(Vector2 target)
    {
        if (waitingAttack) return;

        waitingAttack = true;

        //direct = 

        meleeWeapon.GetComponent<MeleeMovingWeapon>().enabled = false;
        //GameObject anim = Instantiate(animMeleeWeapon, meleeWeapon.transform.position, meleeWeapon.transform.rotation);
        if(MeleeAttackAnim())
            meleeWeapon.GetComponent<MeleeMovingWeapon>().enabled = false;

    }

    private bool MeleeAttackAnim()
    {


        StartCoroutine(UniversalWaits(0.05f));
        return true;
    }

    private IEnumerator UniversalWaits(float t = 0)
    {
        if(t == 0)
            yield return new WaitForSeconds(unit.GetSummaryAttackSpeed);
        else
            yield return new WaitForSeconds(t);
        waitingAttack = false;
    }
}
