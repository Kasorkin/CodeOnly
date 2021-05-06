using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class InventoryUI : MonoBehaviour
{
    [SerializeField] private Transform itemParent;

    [SerializeField] private HeroInventory inventory;

    private InventorySlot[] slots;

    public HeroInventory Inventory { get => inventory; set => inventory = value; }

    private void Start()
    {
        Inventory.onItemChangedCallBack += UpdateUI;
        slots = itemParent.GetComponentsInChildren<InventorySlot>();
    }

    private void UpdateUI()
    {
        int size = slots.Length;
        for(int i = 0; i < size; ++i)
        {
            if(i < Inventory.Items.Count)
            {
                slots[i].AddItem(Inventory.Items[i]);
            }
            else
            {
                slots[i].ClearSlot();
            }
        }
    }
}
