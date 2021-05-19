using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Shooting : MonoBehaviour
{
    // [SerializeField]
    //private int timeLife = 4;

    // для перемещения
    private float flightSpeed;
    private float rangeAttack;
    private Rigidbody2D obj;
    private Vector2 startPos;
    private Vector2 direct = Vector2.zero;

    //public int TimeLife { get => timeLife; set => timeLife = value; }
    public float Damage { get; set; }
    public GameObject Attaker { get; set; }
    public EnumData.DamageType DamageType { get; set; }

    //получаем начальные данные от игрока
    public void Init(GameObject attaker, Vector2 direct, float damage = 1f, float rangeAttack = 2f, float flightSpeed = 10f, EnumData.DamageType damageType = EnumData.DamageType.Physical)
    {
        Attaker = attaker;
        this.direct = (direct - (Vector2)transform.position) / (direct - (Vector2)transform.position).magnitude;
        Damage = damage;
        this.rangeAttack = rangeAttack;
        this.flightSpeed = flightSpeed;
        DamageType = damageType;
    }

    private void Start()
    {
        obj = gameObject.GetComponent<Rigidbody2D>();
        startPos = transform.position;
    }

    private void FixedUpdate()
    {
        WeaponMoving();
    }

    private void WeaponMoving()
    {
        Vector2 posWeapon = obj.transform.position;
        //само перемещение
        posWeapon += direct * Time.deltaTime * flightSpeed;
        obj.MovePosition(posWeapon);

        //радиус
        if (Vector2.Distance(transform.position, startPos) > rangeAttack)
            Destroy(gameObject);
    }
}
