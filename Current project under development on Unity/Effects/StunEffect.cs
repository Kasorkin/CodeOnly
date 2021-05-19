using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "New Stun", menuName = "Effects/StunEffect")]
public class StunEffect : Effect
{
    [System.Serializable]
    public struct EffectLevelData
    {
        public float timeOfStun;
    }

    [SerializeField] private List<EffectLevelData> effectLevelDatas;

    public List<EffectLevelData> GetEffectLevelDatas => effectLevelDatas;

    public override void AddImpact(GameObject targetOfImpact, int lvlOfEffect = 1)
    {
        if (targetOfImpact.TryGetComponent<NPC>(out NPC npcScript))
        {
            npcScript.enabled = false;
        }
        else if (targetOfImpact.TryGetComponent<PlayerScript>(out PlayerScript playerScript))
        {
            playerScript.enabled = false;
        }
    }

    public override void RemoveImpact(GameObject targetOfImpact, int lvlOfEffect = 1)
    {
        if (targetOfImpact.TryGetComponent<NPC>(out NPC npcScript))
        {
            npcScript.enabled = true;
        }
        else if (targetOfImpact.TryGetComponent<PlayerScript>(out PlayerScript playerScript))
        {
            playerScript.enabled = true;
        }
    }
}
