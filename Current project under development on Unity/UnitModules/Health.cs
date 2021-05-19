using Photon.Pun;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Health : MonoBehaviour, IPunObservable
{
    //Multiplayer
    //private PhotonView photonView;
    //
    [SerializeField] protected float currentHealth = 0;
    protected float maxHealth = 0;
    private float hpRegeneration;

    //bonus
    protected float bonusMaxHealth = 0f;
    private float bonusHpRegeneration = 0f;

    [Header("Health")]
    [SerializeField] protected HealthBar healthBar;

    [Header("Drop")]
    [SerializeField] private int experience = 10;
    //[SerializeField] private int gold = 10;
    [SerializeField] private List<GameObject> dropList = new List<GameObject>();

    protected Unit unit;

    public virtual void Init(float maxHealth, float hpRegeneration)
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

    #region ChangeBonusStats
    public virtual float ChangeBonusHpRegeneration(float amount)
    {
        bonusHpRegeneration = Mathf.Clamp(bonusHpRegeneration + amount, 0, Mathf.Infinity);
        return bonusHpRegeneration;
    }

    public virtual float ChangeBonusMaxHealth(float amount)
    {
        bonusMaxHealth = Mathf.Clamp(bonusMaxHealth + amount, 0, Mathf.Infinity);
        return bonusMaxHealth;
    }
    #endregion
    #region ChangeStats
    public float ChangeHpRegeneration(float amount)
    {
        hpRegeneration = Mathf.Clamp(hpRegeneration + amount, 0, Mathf.Infinity);
        return hpRegeneration;
    }

    public virtual float ChangeMaxHealth(float amount)
    {
        maxHealth = Mathf.Clamp(maxHealth + amount, 1, Mathf.Infinity);

        if (healthBar != null)
            healthBar.SetMaxHealth(maxHealth);

        HealthChange(amount);
        return maxHealth;
    }

    public virtual void HealthChange(float amount)
    {
        currentHealth = Mathf.Clamp(currentHealth + amount, 0, maxHealth);

        if (currentHealth == 0)
            Die();

        if (healthBar != null)
            healthBar.SetHealth(currentHealth);
    }
    #endregion
    #region Other

    public virtual void InputDamage(float damage, EnumData.DamageType damageType = EnumData.DamageType.Physical)
    {
        if (unit != null)
        {
            if (damageType == EnumData.DamageType.Physical)
            {
                foreach (var passiveDefensiveAbility in unit.PassiveDefenciveAbilities)
                {
                    damage = passiveDefensiveAbility.Ability(damage);
                }
                damage = ArmorSystem.CalcilationResultDamage(damage, unit.GetSummaryPhysicArmor);
            }
        }

        HealthChange(-damage);
    }

    private void FixedUpdate()
    {
        //if (!photonView.IsMine) return;

        HealthRegeneration();
    }

    protected void HealthRegeneration()
    {
        HealthChange((hpRegeneration + bonusHpRegeneration) * Time.deltaTime);
    }

    private void OnTriggerEnter2D(Collider2D other)
    {
        //if(gameObject.Ge)

        Shooting weapon = other.gameObject.GetComponent<Shooting>();

        if (weapon && weapon.Attaker != gameObject)
        {
            InputDamage(weapon.Damage, weapon.DamageType);            
            Destroy(weapon.gameObject);
        }
    }

    private void Die()
    {
        Destroy(unit.GetComponent<UnitAttack>().GetWeapon());

        //дроп золота
        DropSystem.Drop(dropList, experience, gameObject.transform);
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
    #endregion
}
