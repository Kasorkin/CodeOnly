using UnityEngine;

[CreateAssetMenu(fileName = "New Item", menuName = "Inventory/Item")]
public class ItemDataBase: ScriptableObject
{
    [Header("ItemDataBase")]
    [SerializeField]
    private GameObject item;//префаб предмета
    [SerializeField]
    private Sprite icon;//картиночка 
    [SerializeField]
    private uint cost; //стоимость
    [SerializeField]
    private EnumData.ItemType itemType;//название типа предмета
    [SerializeField]
    private int mass; //вес предмета
    [SerializeField]
    private int maxInStack = 1;
    [SerializeField][Multiline]
    private string description;// описание предмета
    [SerializeField]
    private int currentInStack = 1;


    public GameObject Item => item;
    public Sprite Icon => icon;
    public string Description => description;
    public uint Cost { get => cost; set => cost = value; }
    public EnumData.ItemType ItemType { get => itemType; set => itemType = value; }
    public int MaxInStack { get => maxInStack; set => maxInStack = value; }
    public int CurrentInStack { get => currentInStack; set => currentInStack = value; }

    public virtual void Use()
    {
        //float k = 0;
        //if (itemType.GetType().Name == "MeleeWeaponDataBase")
            //k = ((MeleeWeaponDataBase)itemType).Damage;
           
        Debug.Log("Using itemData" + name);
    }
}
