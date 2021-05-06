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
    UnitAttack[] rangeAttacks;

    [SerializeField] private CanvasData playerCanvasData;

    public CanvasData PlayerCanvasData { get => playerCanvasData; set => playerCanvasData = value; }
    public bool IsTriggerNonAttackArea { get; set; } = false;

    private void Start()
    {
        //multiplayer
        photonView = GetComponent<PhotonView>();
        //
        rangeAttacks = GetComponents<UnitAttack>();
        unit = GetComponent<Unit>();
        rigidbody = GetComponent<Rigidbody2D>();

        unit.StatsUI = playerCanvasData.GetComponentInChildren<UnitStatsUI>();
    }

    private void Update()
    {
        //multiplayer
        if (!photonView.IsMine) return;

        if (Input.GetKeyDown(KeyCode.Tab))
            GetComponent<Hero>().ChangeExperience(100);

        UpdateKeyAttack();
    }

    private void UpdateKeyAttack()
    {
        if (Input.GetMouseButtonDown(0) && !IsTriggerNonAttackArea)
        {
            Vector2 MousePos = Camera.main.ScreenToWorldPoint(Input.mousePosition);
            foreach (UnitAttack rangeAttack in rangeAttacks)
                rangeAttack.Attack(MousePos);
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

        pos.x = pos.x + unit.GetMoveSpeed * horizontal * Time.deltaTime;
        pos.y = pos.y + unit.GetMoveSpeed * vertical * Time.deltaTime;

        rigidbody.MovePosition(pos);
    }
}
