using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Playert : MonoBehaviour
{
    public Text hpText;
    public Transform gameOver;
    private int hitPoints = 30;
    private int currentCash = 20;

    public void removeCash(int turretCost)
    {
        currentCash -= turretCost;
    }
    public void addCash(int amountGained)
    {
        currentCash += amountGained;
    }
    public int getCash()
    {
        return currentCash;
    }

    public void removeHP(int damage)
    {
        if(hitPoints - damage <= 0)
        { 
            Instantiate(gameOver, gameOver.position, gameOver.rotation);
        }
        else
        {
            hitPoints -= damage;
            hpText.GetComponent<UnityEngine.UI.Text>().text = "Palace HP: \n" + hitPoints;
    
        }
    }

    public int getHP()
    {
        return hitPoints;
    }
}
