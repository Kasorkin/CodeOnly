using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ItemPickup : MonoBehaviour
{
    private bool check = false;
    private PlayerScript controller;
    [SerializeField] private ItemDataBase item;

    public ItemDataBase Item => item;
    //public int CountInStack { get; set; } = 1;

    private void OnTriggerEnter2D(Collider2D other)
    {
        controller = other.GetComponent<PlayerScript>();

        if (controller != null)
        {
            check = true;
        }
    }

    private void OnTriggerExit2D(Collider2D other)
    {
        controller = other.GetComponent<PlayerScript>();

        if (controller != null)
            check = false;
    }

    private void Update()
    {
        UpdateKeyController();
    }

    private void UpdateKeyController()
    {
        if (Input.GetButtonUp("Action") && check)
        {
            //Debug.Log("Подобран предмет " + Item.name);
            //перерасчет всех объектов, входящих в коллайдер приводит к исключению
            if (controller == null) return; 

            bool wasPickedUp = controller.gameObject.GetComponent<HeroInventory>().Add(item);
            if (wasPickedUp)
            {
                //Debug.Log("Предмет уничтожен " + Item.name);
                Destroy(gameObject);
            }
        }
    }
}
