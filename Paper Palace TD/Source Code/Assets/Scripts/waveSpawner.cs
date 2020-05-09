using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class waveSpawner : MonoBehaviour
{
    public Transform enemyPreFab;
    public Transform spawnPoint;
    public Transform palace;

    public Text waveText;

    public float timeBetweenWaves = 5f;
    private float countDown = 2f;

    private int waveNumber = 0;
    private int endWaves = 50;

    void Update()
    {
        if (countDown <= 0f && waveNumber <= endWaves)
        {
            StartCoroutine(SpawnWave());
            countDown = timeBetweenWaves;

        }

        countDown -= Time.deltaTime;
    }

    IEnumerator SpawnWave()
    {    
        waveNumber++;
        if(waveNumber <= endWaves)
        {
            waveText.GetComponent<UnityEngine.UI.Text>().text = "Wave: " + waveNumber;
        }
        else
        {
            Destroy(gameObject);
        }
        

        for (int i = 0; i < waveNumber; i++)
        {
            SpawnEnemy();
            yield return new WaitForSeconds(0.5f);
        }   
    }


    void SpawnEnemy()
    {
        Transform enemy = Instantiate(enemyPreFab, spawnPoint.position, spawnPoint.rotation);
        enemy.GetComponent<enemy>().setPalace(palace);
    }
}
