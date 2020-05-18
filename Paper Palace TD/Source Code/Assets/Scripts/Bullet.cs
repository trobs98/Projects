using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bullet : MonoBehaviour { 
   
    private Transform target;
    public float speed = 70f;
    public int damage = 30;
    private Transform owner;
    
    public void Chase(Transform _target)
    {
        target = _target;
    }
    public void setOwner(Transform o)
    {
        owner = o;
    }
    
    // Update is called once per frame
    void Update()
    {
        if(target == null)
        {
            Destroy(gameObject);
            return;
        }

        Vector3 direction = target.position - transform.position;
        float distanceThisFrame = speed * Time.deltaTime;

        if(direction.magnitude <= distanceThisFrame)
        {
            HitTarget();
            return;
        }

        transform.Translate(direction.normalized * distanceThisFrame, Space.World);
    }

    void HitTarget()
    {
        Destroy(gameObject);
        Damage(target);
    }

    void Damage(Transform en)
    {
        enemy e = en.GetComponent<enemy>();
        
        if(e != null)
        {
            e.TakeDamage(damage, owner);
        }
       
    }
}
