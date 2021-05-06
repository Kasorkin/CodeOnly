using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class InventorySlot : MonoBehaviour
{
    [SerializeField] private Image icon;
    [SerializeField] private Button removeButton;
    private HeroInventory inventory;
    private PlayerScript playerScript;

    private GameItem itemInSlot;

    private bool isClick = false;

    public void AddItem(GameItem newItem)
    {
        itemInSlot = newItem;

        /*if (newItem.currentCount > 1 && newItem.currentCount < newItem.item.MaxInStack)
        {
            Debug.Log("Количество предмета увеличино, отрисовка потом");
            return;
        }*/
        //Debug.Log("Отрисовка");
        icon.sprite = itemInSlot.item.Icon;
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
        itemInSlot = inventory.Remove(itemInSlot);

        if (inventory.onItemChangedCallBack != null)
        {
            inventory.onItemChangedCallBack.Invoke();
        }
    }

    public void UseItem()
    {
        if(itemInSlot.item != null && itemInSlot.item.Active)
        {
            itemInSlot.item.Use();
        }
    }

    private void Start()
    {
        inventory = GetComponentInParent<InventoryUI>().Inventory;
        if (inventory == null)
            Debug.LogError("Error inventory system");
        playerScript = inventory.gameObject.GetComponent<PlayerScript>();
        if (playerScript == null)
            Debug.LogError("Error playerScript system in InventorySlot");
    }
}
