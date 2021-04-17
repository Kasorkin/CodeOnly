using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class InventoryUI : MonoBehaviour
{
    [SerializeField] private Transform itemParent;

    [SerializeField] private HeroInventory inventory;

    private InventorySlot[] slots;

    public HeroInventory GetInventory => inventory;

    private void Start()
    {
        inventory.onItemChangedCallBack += UpdateUI;
        slots = itemParent.GetComponentsInChildren<InventorySlot>();
    }

    private void UpdateUI()
    {
        int size = slots.Length;
        for(int i = 0; i < size; ++i)
        {
            if(i < inventory.Items.Count)
            {
                slots[i].AddItem(inventory.Items[i]);
            }
            else
            {
                slots[i].ClearSlot();
            }
        }
    }
}
