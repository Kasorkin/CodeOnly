using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class InventorySlot : MonoBehaviour
{
    [SerializeField] private Image icon;
    [SerializeField] private Button removeButton;
    private HeroInventory inventory;

    private GameItem item;

    private bool isClick = false;

    public void AddItem(GameItem newItem)
    {
        item = newItem;

        /*if (newItem.currentCount > 1 && newItem.currentCount < newItem.item.MaxInStack)
        {
            Debug.Log("Количество предмета увеличино, отрисовка потом");
            return;
        }*/

        //Debug.Log("Отрисовка");
        icon.sprite = item.item.Icon;
        icon.enabled = true;

        removeButton.interactable = true;
        isClick = true;
    }

    public void ClearSlot()
    {
        if(isClick)
        {
            icon.sprite = null;
            icon.enabled = false;
            removeButton.interactable = false;
            isClick = false;
        }
    }

    public void OnRemoveButton()
    {
        item = inventory.Remove(item);
        if (inventory.onItemChangedCallBack != null)
        {
            inventory.onItemChangedCallBack.Invoke();
        }
    }

    public void UseItem()
    {
        if(item.item != null)
        {
            item.item.Use();
        }
    }

    private void Start()
    {
        inventory = GetComponentInParent<InventoryUI>().GetInventory;
        if (inventory == null)
            Debug.LogError("Error inventory system");
    }
}
