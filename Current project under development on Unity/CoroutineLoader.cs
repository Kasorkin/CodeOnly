using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CoroutineLoader : MonoBehaviour
{
    public static bool GlobalUniversalWaits(float time = 0.05f)
    {
        TimeWaits(time);
        return true;
    }

    private static IEnumerator TimeWaits(float time)
    {
        yield return new WaitForSeconds(time);
    }
}
