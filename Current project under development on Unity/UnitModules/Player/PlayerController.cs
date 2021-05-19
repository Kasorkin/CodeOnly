using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Photon.Pun;

public class PlayerController : MonoBehaviour//, IPunObservable
{
    [Header("Health")]
    [SerializeField] private float maxHealth;
    [SerializeField] private HealthBar healthBar;

    [Header("Mana")]
    [SerializeField] private float maxMana;
    [SerializeField] private ManaBar manaBar;

    [Header("RangeAttack")]
    [SerializeField] private GameObject rangeWeapon;
    [SerializeField] private float damage = 1f;
    [SerializeField] private float radiusOfAttack = 2f;
    [SerializeField] private float flightSpeed = 5f;
    [SerializeField] private float waitAttack = 1f;
    [SerializeField] private GameObject anim;
    private bool waitingAttack = false;

    [Header("Movement")]
    [SerializeField] private float speedWalk = 3f;

    private new Rigidbody2D rigidbody;
    private float horizontal;
    private float vertical;

    //модули
    public MHealth HealthModule { get; set; }
    public MMana ManaModule { get; set; }
    public MExperience ExperienceModule { get; set; }

    private void Awake()
    {
        HealthModule = new MHealth(maxHealth, healthBar);
        ManaModule = new MMana(maxMana, manaBar);
    }

    private void Start()
    {
        rigidbody = GetComponent<Rigidbody2D>();
        //photonView = GetComponent<PhotonView>();
        //spriteRenderer = GetComponent<SpriteRenderer>();
    }

    private void Update()
    {
        //if (Input.GetKeyDown(KeyCode.Space))
        //    HealthModule.HealthChange(-20);

        UpdateKeyAttack();
    }

    private void UpdateKeyAttack()
    {
        if (Input.GetMouseButtonDown(0))
        {
            RangeAttack();
        }
    }

    private void FixedUpdate()
    {
        horizontal = Input.GetAxis("Horizontal");
        vertical = Input.GetAxis("Vertical");

        Move();
    }

    private void RangeAttack()
    {
        if (waitingAttack) return;

        waitingAttack = true;

        //рассчитываем данные для поворота и создаем объект
        Vector2 MousePos = Camera.main.ScreenToWorldPoint(Input.mousePosition);

        GameObject weapon = Instantiate(anim, rangeWeapon.transform.position, rangeWeapon.transform.rotation);

        weapon.transform.right = -(MousePos - (Vector2)rangeWeapon.transform.position);

        weapon.GetComponent<Shooting>().Init(gameObject, MousePos, damage, radiusOfAttack, flightSpeed);
        /*GameObject weapon = Instantiate(anim, transform.position, transform.rotation);
        //поворот объекта в нужную сторону
        weapon.transform.right = -(MousePos - (Vector2)transform.position);
        //передаем объекту необходимые данные
        weapon.GetComponent<Shooting>().WeaponMove(gameObject, MousePos, damage, radiusOfAttack, flightSpeed);*/

        StartCoroutine(UniversalWaits());

    }

    private IEnumerator UniversalWaits()
    {
        yield return new WaitForSeconds(waitAttack);
        waitingAttack = false;
    }

    private void Move()
    {
        Vector2 pos = rigidbody.position;

        pos.x = pos.x + speedWalk * horizontal * Time.deltaTime;
        pos.y = pos.y + speedWalk * vertical * Time.deltaTime;

        rigidbody.MovePosition(pos);
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
                Destroy(gameObject);
        }
    }

    /*private void TTTPhoton()
    {
        //startclass
            /*private PhotonView photonView;
    private SpriteRenderer spriteRenderer;

    private bool isRed;

    public void OnPhotonSerializeView(PhotonStream stream, PhotonMessageInfo info)
    {
        if(stream.IsWriting)
        {
            stream.SendNext(isRed);
        }
        else
        {
            //возвращает всегда тип object
            isRed = (bool)stream.ReceiveNext();
        }
    }
    //update
    if (photonView.IsMine)
    {

    if (Input.GetKey(KeyCode.LeftArrow)) transform.Translate(-Time.deltaTime * 5, 0, 0);

    if (Input.GetKey(KeyCode.Space))
    {
        isRed = true;

    }
    else
    {
        isRed = false;
    }
    }


    if (isRed)
    {
    spriteRenderer.color = Color.red;

    }
    else
    {
    spriteRenderer.color = Color.white;
    }
    }*/
}
