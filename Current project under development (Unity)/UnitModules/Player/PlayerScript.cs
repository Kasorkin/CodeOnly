using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Photon.Pun;

[RequireComponent(typeof(Unit))]
public class PlayerScript : MonoBehaviour
{
    //Multiplayer
    private PhotonView photonView;
    //
    private new Rigidbody2D rigidbody;
    private float horizontal;
    private float vertical;

    Unit unit;
    RangeAttack[] rangeAttacks;

    private HealthBar HealthBar { get; set; }
    private ManaBar ManaBar { get; set; }

    private void Start()
    {
        //multiplayer
        photonView = GetComponent<PhotonView>();
        //
        rangeAttacks = GetComponents<RangeAttack>();
        unit = GetComponent<Unit>();
        rigidbody = GetComponent<Rigidbody2D>();
    }

    private void Update()
    {
        //multiplayer
        if (!photonView.IsMine) return;

        if (Input.GetKeyDown(KeyCode.Space))
            GetComponent<Health>().HealthChange(-10);

        UpdateKeyAttack();
    }

    private void UpdateKeyAttack()
    {
        if (Input.GetMouseButtonDown(0))
        {
            Vector2 MousePos = Camera.main.ScreenToWorldPoint(Input.mousePosition);
            foreach (RangeAttack rangeAttack in rangeAttacks)
                rangeAttack.Attack(MousePos);
            //missileAttack.Attack(MousePos);
        }
    }

    private void FixedUpdate()
    {
        //multiplayer
        if (!photonView.IsMine) return;
        //
        horizontal = Input.GetAxis("Horizontal");
        vertical = Input.GetAxis("Vertical");

        Move();
    }

    private void Move()
    {
        Vector2 pos = rigidbody.position;

        pos.x = pos.x + unit.MoveSpeed * horizontal * Time.deltaTime;
        pos.y = pos.y + unit.MoveSpeed * vertical * Time.deltaTime;

        rigidbody.MovePosition(pos);
    }
}
