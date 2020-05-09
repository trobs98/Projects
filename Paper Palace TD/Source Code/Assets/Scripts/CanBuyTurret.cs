using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class CanBuyTurret : MonoBehaviour
{
    
    private int turretCost = 10;
    public Transform turretPrefab;
    public Text currencyText;
    public Transform currentPlayer;


    // Update is called once per frame
    void Update()
    {
        currencyText.GetComponent<UnityEngine.UI.Text>().text = "Currency: \n$" + currentPlayer.GetComponent<Playert>().getCash();
    }

    public void createTurret()
    {
        if (currentPlayer.GetComponent<Playert>().getCash() >= turretCost)
        {
            Transform tur = Instantiate(turretPrefab, transform.position, transform.rotation);
            tur.GetComponent<turret>().setOwner(currentPlayer);
            currentPlayer.GetComponent<Playert>().removeCash(turretCost);
        }

    }
}
