using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

namespace Complete
{
    public class QuitButton : MonoBehaviour
    {
        public void QuitGame()
        {
            //Quit the game
            Application.Quit();
        }
    }
}