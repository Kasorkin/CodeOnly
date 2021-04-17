using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MMovement
{
    //��� ������
    private Rigidbody2D rigidbody;
    private Transform transform;
    private float rangeToGoal = 0.5f;

    //�������� ���� ������ ����
    private Vector2 goal;

    //��� ������ ����
    private Vector2 startCalculationPos;
    private Vector2 endCalculationPos;
    private Dictionary<Vector2, Vector2> pointsToMove = null;
    private Vector2 currentPointToMove;

    private Vector2 direction;
    private bool isCurrentPointToMove = false;

    private float speed = 4f;

    public MMovement(Rigidbody2D rigidbody, float rangeToGoal, float speed = 4f)
    {
        this.rigidbody = rigidbody;
        this.rangeToGoal = rangeToGoal;
        this.speed = speed;

        pointsToMove = null;
    }

    public void MyFixedUpdate(Transform transform, Vector2 goal)
    {
        if (Vector2.Distance(transform.position, goal) < rangeToGoal) return;

        this.goal = goal;
        this.transform = transform;
       
        //���� ���� � ���� � ������ �����
        SearchWay();
        //���� ���� � ���� ������, �� �������� ��������
        Moving();
        //������ �����, ���� ����� �� �������
        SearchNextPointToMove();
        //����� �������� �����
    }

    private void SearchWay()
    {
        if (pointsToMove != null || Vector2.Distance(transform.position, goal) < rangeToGoal) return;

        startCalculationPos = transform.position;
        endCalculationPos = goal;

        startCalculationPos.x = Mathf.RoundToInt(startCalculationPos.x);
        startCalculationPos.y = Mathf.RoundToInt(startCalculationPos.y);
        endCalculationPos.x = Mathf.RoundToInt(endCalculationPos.x);
        endCalculationPos.y = Mathf.RoundToInt(endCalculationPos.y);

        pointsToMove = AlgorithmAstar.SearchA(startCalculationPos, endCalculationPos);
        if (pointsToMove == null)
        {
            Debug.Log("���� �� ���������, �������� �����������");
            return;
        }
        Debug.Log("���� ���������, ������� ��������");
        currentPointToMove = pointsToMove[startCalculationPos];
        isCurrentPointToMove = false;
    }

    private void SearchNextPointToMove()
    {
        if (pointsToMove == null || !isCurrentPointToMove) return;

        if (Vector2.Distance(transform.position, goal) > rangeToGoal && (currentPointToMove != endCalculationPos && pointsToMove[currentPointToMove] != endCalculationPos))
        {
            Debug.Log("����� �����");
            Vector2 parent = currentPointToMove;
            currentPointToMove = pointsToMove[parent];
        }
        else
        {
            Debug.Log("����� ����" + transform.position);
            pointsToMove = null;
            currentPointToMove = Vector2.zero;
        }
    }

    private void Moving()
    {
        if (currentPointToMove == Vector2.zero || Vector2.Distance(transform.position, currentPointToMove) < 0.5f)
        {
            isCurrentPointToMove = true;
            return;
        }

        isCurrentPointToMove = false;

        Vector2 pos = transform.position;
        direction = (currentPointToMove - pos) / (currentPointToMove - pos).magnitude;
        pos += direction * Time.deltaTime * speed;
        rigidbody.MovePosition(pos);
    }
}
