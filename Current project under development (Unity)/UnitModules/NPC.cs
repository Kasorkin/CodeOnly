using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class NPC : MonoBehaviour
{
    [Header("Health")]
    [SerializeField] private float maxHealth = 100;
    [SerializeField] private HealthBar healthBar = null;

    [Header("Mana")]
    [SerializeField] private float maxMana;
    [SerializeField] private ManaBar manaBar;

    [Header("Movement")]
    [SerializeField] private float speed = 3.5f;
    [SerializeField] private float rangeToGoal = 0.5f;
    [SerializeField] private float radiusSearchTarget = 10f;

    [Header("Drop")]
    [SerializeField] private int experience = 10;
    [SerializeField] private List<GameObject> dropList = new List<GameObject>();

    [Header("Target")]
    [SerializeField] private GameObject target = null;

    //модули
    public MHealth HealthModule { get; set; }
    public MMana ManaModule { get; set; }
    public MMovement MovementModule { get; set; }

    private void Awake()
    {
        HealthModule = new MHealth(maxHealth, healthBar);
        ManaModule = new MMana(maxMana, manaBar);
        MovementModule = new MMovement(GetComponent<Rigidbody2D>(), rangeToGoal, speed);
    }

    private void Start()
    {
        
    }

    private void FixedUpdate()
    {
        if (target != null)
        {
            //MovementModule.MyFixedUpdate(transform, target.transform.position);
        }
        else
        {
            //Detection();
        }
            
    }

    private void Detection()
    {
        if (target != null) return;

        target = SearchTarget.SearchingTarget(transform.position, (int)radiusSearchTarget, Consts.LayerLight);
        if(target == null)
            target = SearchTarget.SearchingTarget(transform.position, (int)radiusSearchTarget, Consts.LayerNeutralEnemy);
    }


    private void OnTriggerEnter2D(Collider2D other)
    {
        Shooting weapon = other.gameObject.GetComponent<Shooting>();

        if (weapon && weapon.Attaker != gameObject)
        {
            //HealthChange(-other.gameObject.GetComponent<WeaponStats>().Data.Damage);
            bool isAlive = HealthModule.HealthChange(-weapon.Damage);
            Destroy(weapon.gameObject);

            if (!isAlive)
            {
                DropSystem.Drop(dropList, experience, transform);
                Destroy(gameObject);
            }
        }
    }

}
