using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

namespace Complete
{
    public class GameManager : MonoBehaviour
    {
        public float m_loadDelay = 1f;          //Wait time between spawn of level and camera pickup
        public float m_StartDelay = 5f;         //Start time delay
        public float m_EndDelay = 3f;           //End time delay
        public Camera m_GameOverCam;
        public Text m_MessageText;
        public GameObject m_TankPrefab;         //Tank prefab reference to spawn
        public GameObject m_TurretPrefab;       //Turret prefab for spawn
        
        public TankManager m_Tank;             //Manager for the Tank player
        public TurretManager[] m_Turrets;       //Manager for all of the turrets

        private WaitForSeconds m_StartWait; //Delay for start of game
        private WaitForSeconds m_EndWait; //Delay at end of game
        private WaitForSeconds m_LoadWait; 

        // Use this for initialization
        void Start()
        {

            //Start delays and end message delays
            m_LoadWait = new WaitForSeconds(m_loadDelay);
            m_StartWait = new WaitForSeconds(m_StartDelay);
            m_EndWait = new WaitForSeconds(m_EndDelay);
            
            //Once all is spawned, start the game
            StartCoroutine(GameLoop());
        }

        private void SpawnTurrets()
        {
            for (int i = 0; i < m_Turrets.Length; i++)
            {
                //Spawn in each turret in the level and complete initial setup of each
                m_Turrets[i].m_Instance = Instantiate(m_TurretPrefab, m_Turrets[i].m_SpawnPoint.position, m_Turrets[i].m_SpawnPoint.rotation) as GameObject;

            }
            
        }

        private void SpawnTank()
        {   
            //Spawn the player's tank.
            m_Tank.m_Instance = Instantiate(m_TankPrefab, m_Tank.m_SpawnPoint.position, m_Tank.m_SpawnPoint.rotation) as GameObject;
            m_Tank.Setup();
        }
//-----------------------------------------------------------------------------------------

        //Called from Start() and runs through each phase of the game
        private IEnumerator GameLoop()
        {
            //Initialize instructions and disable control
            yield return StartCoroutine(RoundStart());

            //Enable control to player and play til all turrets or player is destroyed
            yield return StartCoroutine(RoundPlay());

            if (m_Tank.m_Instance.activeSelf == false)
            {
                yield return StartCoroutine(GameOver());
            }

            //DisableTank() and end the game
            yield return StartCoroutine(RoundEnd());
        }

//---------------------------------------------------------------------------------------------------------
        private IEnumerator RoundStart()
        {
            //Load delay wait for camera smoothing
            yield return m_LoadWait;
            m_GameOverCam.enabled = true;

            //Spawn the tank
            SpawnTank();
            //Disable all interactive objects
            m_Tank.DisableControl();
            

            //Display tutorial and objective
            m_MessageText.text = "DESTROY ALL TURRETS! Hold 'Space' to charge the shot and release to shoot. WASD to drive!";
            yield return m_StartWait;
        }
//--------------------------------------------------------------------------------------
        private IEnumerator RoundPlay()
        {
            SpawnTurrets();
            m_GameOverCam.enabled = false;
            //Enable tank control and set display string to empty
            m_Tank.EnableControl();

            m_MessageText.text = string.Empty;

            //while there are active turrets, keep playing
            while (TurretsAlive())
            {
                //Check if tank is dead
                if (m_Tank.m_Instance.activeSelf == false)
                {
                    m_GameOverCam.enabled = true;
                    yield return GameOver();
                }
                yield return null;
            }
        }

        //Check if there are any living turrets.
        private bool TurretsAlive()
        {
            //Step through each turret until an active one is found.
            for (int i = 0; i < m_Turrets.Length; i++)
            {
                //If an active turret is found, return true
                if (m_Turrets[i].m_Instance.activeSelf)
                {

                    return true;
                }
            }
            //if all turrets destroyed, return false and end round
            return false;
        }
//------------------------------------------------------------------------------------------
        private IEnumerator RoundEnd()
        {
            //Disable control and display win state text
            if (m_Tank.m_Instance.activeSelf)
            {
                m_GameOverCam.enabled = true;
                m_Tank.DisableControl();
                m_MessageText.text = "You have destroyed all turrets! Congratulations! The base is yours!";
            }
            yield return m_EndWait;
            SceneManager.LoadScene("MainMenu", LoadSceneMode.Single);
        }

        private IEnumerator GameOver()
        {
            m_Tank.DisableControl();
            
            m_MessageText.text = "GAME OVER. YOU ARE DEAD.";
            yield return m_EndWait;
            SceneManager.LoadScene("MainMenu", LoadSceneMode.Single);
        }
    }
}
