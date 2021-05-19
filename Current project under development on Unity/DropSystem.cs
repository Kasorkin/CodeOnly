using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public static class DropSystem 
{
    private static List<GameObject> dropList;
    private static int experience;
    private static Transform transform;

    // Start is called before the first frame update
    public static void Drop(List<GameObject> dropList, int experience, Transform transform)
    {
        DropSystem.dropList = dropList;
        DropSystem.experience = experience;
        DropSystem.transform = transform;
        DropItems();
        DropExperience();
    }

    // Update is called once per frame
    private static void DropItems()
    {
        foreach (GameObject i in dropList)
        {
            Object.Instantiate(i, transform.position, transform.rotation);
        }
    }

    private static void DropExperience()
    {
        Collider2D[] colliders = Physics2D.OverlapCircleAll(transform.position, Consts.ExperienceDropRadius, 1 << 9);

        foreach (Collider2D hit in colliders)
        {
            Hero hero = hit.GetComponent<Hero>();
            if (hero != null) hero.ChangeExperience(experience);
        }
    }
}
