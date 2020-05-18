using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class turret : MonoBehaviour
{

    private Transform target;
    
    [Header("Attributes")]
    public float fireRange = 15f;
    public float fireRate = 1f;
    private float fireCountdown = 0f;
    public float turretArea = 12f;
    public float moveSpeed = 0.1f;
   
    [Header("Unity Setup Fields")]
    public string enemyTag = "Enemy";
    public GameObject bulletPrefab;
    public Transform firePoint;
    private bool placed = false;
    private bool colliding = false;
    private Transform currentPlayer;

    // Start is called before the first frame update
    void Start()
    {
        InvokeRepeating("UpdateTarget", 0f, 0.5f);
    }

    public void setOwner(Transform current)
    {
        currentPlayer = current;
    }

    void UpdateTarget ()
    {
        GameObject[] enemies = GameObject.FindGameObjectsWithTag(enemyTag);
        
        float shortestDistance = Mathf.Infinity;
        GameObject nearestEnemy = null;
        
        foreach (GameObject enemy in enemies) 
        {
            float distanceToEnemy = Vector3.Distance(transform.position, enemy.transform.position);
            if(distanceToEnemy < shortestDistance)
            {
                shortestDistance = distanceToEnemy;
                nearestEnemy = enemy;
            }
        }

        if(nearestEnemy != null && shortestDistance <= fireRange)
        {
            target = nearestEnemy.transform;
        }
        else
        {
            target = null;
        }
    }

    // Update is called once per frame
    void Update()
    {
        if(placed == false)
        {
            Vector3 mousePos = Camera.main.ScreenToWorldPoint(Input.mousePosition);
            mousePos.z = transform.position.z;
            float speed = 150;
            transform.position = Vector3.Lerp(transform.position, mousePos, speed * Time.deltaTime);
        }

        //if the turret has no target then it's rotation does not change
        if(target == null)
        {
            return;
        }



        //if the turret has a target then lock down on it
        //target lockdown section

        float angleRad = Mathf.Atan2(target.position.y - transform.position.y, target.position.x - transform.position.x);
        float angleDeg = (180 / Mathf.PI) * angleRad;
        transform.rotation = Quaternion.Euler(0, 0, angleDeg - 90f);

        if(fireCountdown <= 0f && placed == true)
        {
            Shoot();
            fireCountdown = 1f / fireRate;
        }

        fireCountdown -= Time.deltaTime;
    }

    void Shoot()
    {
        GameObject currentBullet = (GameObject) Instantiate(bulletPrefab, firePoint.position, firePoint.rotation);
        Bullet bullet = currentBullet.GetComponent<Bullet>();
        bullet.setOwner(currentPlayer);

        if(bullet != null)
        {
            bullet.Chase(target);
        }
    }

    void OnDrawGizmosSelected()
    {
        Gizmos.color = Color.red;
        Gizmos.DrawWireSphere(transform.position, fireRange);
        Gizmos.DrawWireSphere(transform.position, turretArea);
    }

    void OnMouseDown()
    {
        if (colliding == false && placed == false)
        {
            placed = true;
            Behaviour halo = (Behaviour)GetComponent("Halo");
            halo.enabled = false;
        }
    }
    void OnMouseEnter()
    {
        Behaviour halo = (Behaviour)GetComponent("Halo");
        halo.enabled = true;
    }
    void OnMouseExit()
    {
        Behaviour halo = (Behaviour)GetComponent("Halo");
        halo.enabled = false;
    }

    void OnCollisionEnter2D(Collision2D other)
    {
        colliding = true;
    }
    void OnCollisionExit2D(Collision2D other)
    {
        colliding = false;
    }

}
