using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RadiusMoving : MonoBehaviour
{
    [SerializeField] private float radius = 0.5f;
    //[SerializeField] private float speed = 1f;
    //[SerializeField] private float angle = 0;
    //[SerializeField] private Vector2 midCircle;

    [SerializeField] private Transform parent;

    private new Rigidbody2D rigidbody;

    private void Start()
    {
        rigidbody = GetComponent<Rigidbody2D>();
        //midCircle = parent.position;
    }

    private void FixedUpdate()
    {
        Moving();
    }

    private void Moving()
    {

        Vector2 mousePos = Camera.main.ScreenToWorldPoint(Input.mousePosition);
        Vector2 midCircle = parent.localPosition;

        Vector2 direct = (mousePos - midCircle) / (mousePos - midCircle).magnitude;
        Vector2 pos = transform.localPosition;

        pos = direct * radius + midCircle;

        /*angle = Vector2.Angle(midCircle,mousePos);

        Vector2 pos = transform.localPosition;

        pos.x = Mathf.Cos(angle) * radius + midCircle.x;
        pos.y = Mathf.Sin(angle) * radius + midCircle.y;*/

        rigidbody.MovePosition(pos);
    }
}
