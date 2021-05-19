using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class UnitAttack : MonoBehaviour
{
    public virtual void Attack(Vector2 target) { }

    public virtual GameObject GetWeapon() { return null;  }
    public virtual void SetWeapon(GameObject weapon) { }
}
