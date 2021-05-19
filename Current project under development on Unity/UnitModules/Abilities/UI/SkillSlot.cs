using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class SkillSlot : MonoBehaviour
{
    [SerializeField] private Image icon;

    private HeroAbilities heroAbilities;
    private PlayerScript playerScript;

    private GameAbility abilityInSlot;

    private Vector2 posClick;

    public void AddAbility(GameAbility newAbility)
    {
        abilityInSlot = newAbility;

        //если способность пассивная
        if(newAbility.IsActive == false)
        {
            AddPassiveAbility((PassiveAbility)newAbility);
        }

        icon.sprite = abilityInSlot.Icon;
        icon.enabled = true;
    }

    public void UseAbility()
    {
        //Debug.Log("useAbility");
        Debug.Log(abilityInSlot + " " + abilityInSlot.IsActive);
        if (abilityInSlot != null && abilityInSlot.IsActive)
        {
            //Debug.Log("activityAbility");
            ActiveAbility ability = (ActiveAbility)abilityInSlot;
            if(ability.IsSelf)
            {
                //Debug.Log("selfAbility");
                SelfActiveAbility selfAbility = (SelfActiveAbility)ability;
                selfAbility.Use();
            }
            else
            {
                //Debug.Log("targetAbility");
                PositionActiveAbility positionActiveAbility = (PositionActiveAbility)ability;
                StartCoroutine(SkillUse(positionActiveAbility));
            }
        }
    }

    private void AddPassiveAbility(PassiveAbility newPassiveAbility)
    {
        newPassiveAbility.InitPassiveAbility(playerScript.gameObject);
        //включение периодической системы
        if(newPassiveAbility.IsAura && ((AuraAbility)newPassiveAbility).IsPeriodic)
        {
            
        }
    }

    private IEnumerator SkillUse(PositionActiveAbility positionActiveAbility)
    {
        while(true)
        {
            if (Input.GetMouseButton(0))
            {
                posClick = Camera.main.ScreenToWorldPoint(Input.mousePosition);
                Debug.Log("Use skill target");
                positionActiveAbility.Use(posClick);
                break;
            }
            if(Input.GetMouseButton(1))
            {
                Debug.Log("Skill Target break");
                break;
            }
            yield return new WaitForEndOfFrame();
        }
        Debug.Log("Exit coroutine");
    }

    private void Start()
    {
        heroAbilities = GetComponentInParent<AbilitiesUI>().HeroAbilities;
        if (heroAbilities == null)
            Debug.LogError("Error Hero Abilities system");
        playerScript = heroAbilities.gameObject.GetComponent<PlayerScript>();
        if(playerScript == null)
            Debug.LogError("Error playerScript system in SkillSlot");
    }
}
