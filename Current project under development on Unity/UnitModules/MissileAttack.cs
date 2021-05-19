using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Unit))]
public class MissileAttack : UnitAttack
{
    [Header("MissileAttack")]
    [SerializeField] private float flightSpeed = 6f;
    [SerializeField] private GameObject rangeWeapon;
    [SerializeField] private GameObject bulletObject;

    private bool waitingAttack = false;

    Unit unit;

    public override GameObject GetWeapon() { return rangeWeapon; }
    public override void SetWeapon(GameObject weapon) { rangeWeapon = weapon; }

    private void Start()
    {
        unit = GetComponent<Unit>();

        rangeWeapon = Instantiate(rangeWeapon);
        rangeWeapon.GetComponent<MovingForMouseInRadius>().SetParent = transform;
        //rangeWeapon.GetComponent<MeleeMovingWeapon>().SetParent = transform;
    }

    public override void Attack(Vector2 target) //MousePos or targetPos
    {
        if (waitingAttack) return;

        waitingAttack = true;

        GameObject bullet = Instantiate(bulletObject, rangeWeapon.transform.position, rangeWeapon.transform.rotation);

        bullet.transform.right = -(target - (Vector2)rangeWeapon.transform.position);

        bullet.GetComponent<Shooting>().Init(gameObject, target, unit.GetSummaryPhysicDamage, unit.GetSummaryAttackRange, flightSpeed);

        StartCoroutine(UniversalWaits());
    }

    private IEnumerator UniversalWaits()
    {
        yield return new WaitForSeconds(unit.GetSummaryAttackSpeed);
        waitingAttack = false;
    }
}
