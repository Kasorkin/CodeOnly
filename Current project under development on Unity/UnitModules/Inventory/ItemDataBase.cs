using UnityEngine;

[CreateAssetMenu(fileName = "New Item", menuName = "Inventory/Item")]
public class ItemDataBase : ScriptableObject
{
    [Header("ItemDataBase")]
    [SerializeField] private GameObject prefab;
    [SerializeField] private Sprite icon;
    [SerializeField] private int cost;
    [SerializeField] private int maxInStack = 1;
    [SerializeField][Multiline] private string descriprion;

    public GameObject Prefab => prefab;
    public Sprite Icon => icon;
    public int Cost => cost;
    public int MaxInStack => maxInStack;
    public string Descriprion => descriprion;

    public virtual void Use()
    {
        Debug.Log("Using itemData " + name);
    }
}
