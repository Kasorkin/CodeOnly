using Photon.Pun;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Health : MonoBehaviour, IPunObservable
{
    //Multiplayer
    private PhotonView photonView;
    //
    [SerializeField]
    private float currentHealth = 0;
    private float maxHealth = 0;
    private float hpRegeneration;

    [Header("Health")]
    [SerializeField] private HealthBar healthBar;

    [Header("Drop")]
    [SerializeField] private int experience = 10;
    //[SerializeField] private int gold = 10;
    [SerializeField] private List<GameObject> dropList = new List<GameObject>();

    private Unit unit;

    public void Init(float maxHealth, float hpRegeneration)
    {
        this.maxHealth = maxHealth;
        this.hpRegeneration = hpRegeneration;
        currentHealth = maxHealth;
        unit = GetComponent<Unit>();

        if (healthBar != null)
        {
            healthBar.SetMaxHealth(maxHealth);
            healthBar.SetHealth(currentHealth);
        }
    }

    public float ChangeHpRegeneration(float amount)
    {
        hpRegeneration = Mathf.Clamp(hpRegeneration + amount, 0, Mathf.Infinity);
        return hpRegeneration;
    }

    public float ChangeMaxHealth(float amount)
    {
        maxHealth = Mathf.Clamp(maxHealth + amount, 1, Mathf.Infinity);

        if (healthBar != null)
            healthBar.SetMaxHealth(maxHealth);

        HealthChange(amount);
        return maxHealth;
    }

    public void HealthChange(float amount)
    {
        currentHealth = Mathf.Clamp(currentHealth + amount, 0, maxHealth);

        if (currentHealth == 0)
            Die();

        if (healthBar != null)
            healthBar.SetHealth(currentHealth);
    }

    private void Start()
    {
        photonView = GetComponent<PhotonView>();
    }

    private void FixedUpdate()
    {
        if (!photonView.IsMine) return;

        HealthRegeneration();
    }

    private void HealthRegeneration()
    {
        HealthChange(hpRegeneration * Time.deltaTime);
    }

    private void OnTriggerEnter2D(Collider2D other)
    {
        Shooting weapon = other.gameObject.GetComponent<Shooting>();

        if (weapon && weapon.Attaker != gameObject)
        {
            float resultDamage = weapon.Damage;
            if(unit != null)
                resultDamage = ArmorSystem.CalcilationResultDamage(resultDamage, unit.Armor);

            HealthChange(-resultDamage);
            Destroy(weapon.gameObject);
        }
    }

    private void Die()
    {
        //дроп золота
        DropSystem.Drop(dropList, experience, transform);
        Destroy(gameObject);
    }

    public void OnPhotonSerializeView(PhotonStream stream, PhotonMessageInfo info)
    {
        if(stream.IsWriting)
        {
            stream.SendNext(currentHealth);
        }
        else
        {
            currentHealth = (float)stream.ReceiveNext();
            HealthChange(0);
        }
    }
}
