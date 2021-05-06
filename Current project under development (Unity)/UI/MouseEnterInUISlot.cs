using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;

public class MouseEnterInUISlot : EventTrigger
{
    private PlayerScript owner;

    public override void OnPointerEnter(PointerEventData eventData)
    {
        owner.IsTriggerNonAttackArea = true;
    }

    public override void OnPointerExit(PointerEventData eventData)
    {
        owner.IsTriggerNonAttackArea = false;
    }

    private void Start()
    {
        owner = GetComponentInParent<CanvasData>().ItemsUI.GetComponent<InventoryUI>().Inventory.gameObject.GetComponent<PlayerScript>();
        //
        //owner = GetComponentInParent<InventoryUI>().Inventory.gameObject.GetComponent<PlayerScript>();
    }
}
