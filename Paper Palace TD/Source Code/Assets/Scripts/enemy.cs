using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class enemy : MonoBehaviour
{
    public float speed = 10;
    private Transform target;
    private int wavePointIndex = 0;
    private Transform palace; 

    private int enemyWorth = 1;
    public int hitPoints = 10;

    void Start()
    {
        target = Waypoints.points[0];
    }

    void Update()
    {
        Vector3 direction = target.position - transform.position;
        transform.Translate(direction.normalized * speed * Time.deltaTime, Space.World);
    
        if(Vector3.Distance(transform.position, target.position) <= 0.2f)
        {
            GetNextWaypoint();
        }
    }

    public void setPalace(Transform p)
    {
        palace = p;
    }

    void GetNextWaypoint()
    {
        if(wavePointIndex >= Waypoints.points.Length - 1)
        {
            Destroy(gameObject);
            DamageBuilding(hitPoints);
            return;
        }
        wavePointIndex++;
        target = Waypoints.points[wavePointIndex];
    }

    public void TakeDamage(int damage, Transform o)
    {
        if(hitPoints - damage <= 0)
        {
            Destroy(gameObject);
            o.GetComponent<Playert>().addCash(enemyWorth);
        }
        else
        {
            hitPoints -= damage;
        }
    }

    public void DamageBuilding(int damage)
    {
        palace.GetComponent<Playert>().removeHP(damage);
    }
}
