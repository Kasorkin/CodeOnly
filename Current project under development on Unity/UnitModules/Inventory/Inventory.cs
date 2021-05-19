using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public struct GameItem
{
    public GameItem(ItemDataBase item)
    {
        this.item = item;
        currentCount = 1;
    }
    public ItemDataBase item; //ссылка на общие статы предмета
    public int currentCount; //текущее количество предмета
}

public class Inventory : MonoBehaviour
{
    [SerializeField] protected int slotsCount = Consts.HeroInventorySlotsCount;

    public List<GameItem> Items { get; set; } = new List<GameItem>();

    public delegate void OnItemChanged();
    public OnItemChanged onItemChangedCallBack;

    public virtual bool Add(ItemDataBase item)
    {
        GameItem gameItem = new GameItem(item);
        ChangerBonusStats.SetStats(gameObject, item.BonusStats);

        if (item.MaxInStack > 1)
        {
            //ишем такой предмет в инвентаре
            int size = Items.Count;
            for (int i = 0; i < size; ++i)
            {
                if (item == Items[i].item && item.MaxInStack > Items[i].currentCount)
                {
                    GameItem reItem = Items[i];
                    reItem.currentCount++;
                    Items[i] = reItem;

                    //UpdateUI();
                    Debug.Log("stack++");
                    return true;
                }
            }
        }

        return true;
    }

    public virtual GameItem Remove(GameItem item)
    {
        ChangerBonusStats.UnsetStats(gameObject, item.item.BonusStats);
        return item;
    }

    private void Start()
    {
        if (slotsCount > Consts.HeroInventorySlotsCount)
            slotsCount = Consts.HeroInventorySlotsCount;
    }
}
