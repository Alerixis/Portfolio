using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Complete
{
    [Serializable]
    public class TurretManager
    {
        public Transform m_SpawnPoint;                      //Turrets spawnPoint
        public GameManager m_GameManager;                   //Reference to the game manager

        [HideInInspector] public GameObject m_Instance;     //Reference to the instance of the object spawned
    }
}