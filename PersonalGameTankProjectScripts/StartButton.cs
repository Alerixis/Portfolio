using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

namespace Complete
{
    public class StartButton : MonoBehaviour
    {
        public void StartGame()
        {
            //Load the next level
            SceneManager.LoadScene("Level1", LoadSceneMode.Single);
        }
    }
}