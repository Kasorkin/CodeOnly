using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HeroInventory : Inventory
{
    public override bool Add(ItemDataBase item)
    {
        GameItem gameItem = new GameItem(item);

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

                    if (onItemChangedCallBack != null)
                    {
                        onItemChangedCallBack.Invoke();
                    }
                    Debug.Log("stack++");
                    return true;
                }
            }
        }

        if(Items.Count >= slotsCount)
        {
            Debug.Log("Нет места");
            return false;
        }

        Items.Add(gameItem);

        if (onItemChangedCallBack != null)
        {
            onItemChangedCallBack.Invoke();
        }

        Debug.Log("Предмет добавлен");
        return true;
    }

    public override GameItem Remove(GameItem item)
    {
        if(item.currentCount > 1)
        {
            int index = Items.IndexOf(item);
            GameItem reItem = Items[index];

            reItem.currentCount--;
            Items[index] = reItem;

            Instantiate(item.item.Prefab, transform.position, transform.rotation);
            return Items[index];
        }
        else
        {
            bool isRemove = Items.Remove(item);

            if (!isRemove)
            {
                Debug.Log("Error: The item is not been removed");
                return item;
            }
        }
        Instantiate(item.item.Prefab, transform.position, transform.rotation);

        return item;
    }
}
