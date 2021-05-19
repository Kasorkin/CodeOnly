using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MovingForMouse : MonoBehaviour
{
    private Vector2 startPos;

    private void Start()
    {
        startPos = transform.position;
    }

    private void FixedUpdate()
    {
        movingForMouse();
    }

    private void movingForMouse()
    {
        Vector2 mousePos = Camera.main.ScreenToWorldPoint(Input.mousePosition);

        gameObject.transform.right = -(mousePos - startPos);
    }
}
