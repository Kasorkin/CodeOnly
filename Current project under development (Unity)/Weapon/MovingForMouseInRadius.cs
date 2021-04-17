using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MovingForMouseInRadius : MonoBehaviour
{
    [SerializeField] private float radius = 0.5f;
    [SerializeField] private Transform parent;

    private new Rigidbody2D rigidbody;
    private Vector2 mousePos;

    public Transform SetParent { set => parent = value; }

    private void Start()
    {
        rigidbody = GetComponent<Rigidbody2D>();
    }

    private void FixedUpdate()
    {
        mousePos = Camera.main.ScreenToWorldPoint(Input.mousePosition);
        RadiusMoving();
        movingForMouse();
    }

    private void movingForMouse()
    {
        gameObject.transform.right = -(mousePos - (Vector2)transform.position);
    }

    private void RadiusMoving()
    {
        Vector2 midCircle = parent.localPosition;
        Vector2 direct = (mousePos - midCircle) / (mousePos - midCircle).magnitude;
        Vector2 pos = transform.localPosition;

        pos = direct * radius + midCircle;

        rigidbody.MovePosition(pos);
    }
}
