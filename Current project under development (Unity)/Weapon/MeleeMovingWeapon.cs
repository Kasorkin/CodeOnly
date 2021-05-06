using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MeleeMovingWeapon : MonoBehaviour
{
    [SerializeField] private float radius = 0.5f;
    [SerializeField] private Transform parent;

    private new Rigidbody2D rigidbody;
    private bool isPlayer;
    private bool isMeleeAttack;

    public Transform SetParent { set => parent = value; }
    public Vector2 TargetPos { get; set; }

    private void Start()
    {
        rigidbody = GetComponent<Rigidbody2D>();

        if(parent.GetComponent<PlayerScript>() != null)
            isPlayer = true;
        else if (parent.GetComponent<NPC>() != null)
            isPlayer = false;
        else
            Debug.LogError("Script Controller is not found");
    }

    private void FixedUpdate()
    {
        if(isPlayer)
            TargetPos = Camera.main.ScreenToWorldPoint(Input.mousePosition);

        RadiusMoving();
        movingForMouse();
    }

    private void movingForMouse()
    {
        gameObject.transform.right = -(TargetPos - (Vector2)transform.position);
    }

    private void RadiusMoving()
    {
        Vector2 midCircle = parent.localPosition;
        Vector2 direct = -(TargetPos - midCircle) / (TargetPos - midCircle).magnitude;
        Vector2 pos = transform.localPosition;

        pos = direct * radius + midCircle;

        rigidbody.MovePosition(pos);
    }
}
