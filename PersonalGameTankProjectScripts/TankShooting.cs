using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

namespace Complete
{
    public class TankShooting : MonoBehaviour
    {
        public Rigidbody m_Shell;                   // Prefab of the shell.
        public Transform m_FireTransform;           // A child of the tank where the shells are spawned.
        public Slider m_AimSlider;                  // A child of the tank that displays the current launch force.

        public AudioSource m_ShootingAudio;         // Reference to the audio source used to play the shooting audio. NB: different to the movement audio source.
        public AudioClip m_ChargingClip;            // Audio that plays when each shot is charging up.
        public AudioClip m_FireClip;                // Audio that plays when each shot is fired.
        public AudioClip m_ReloadingClip;           // Audio that play when reloading.

        public RawImage m_Ammo1;                    //All three bullet images #'d from left to right.
        public RawImage m_Ammo2;
        public RawImage m_Ammo3;

        public float m_MinLaunchForce = 15f;        // The force given to the shell if the fire button is not held.
        public float m_MaxLaunchForce = 30f;        // The force given to the shell if the fire button is held for the max charge time.
        public float m_MaxChargeTime = 0.75f;       // How long the shell can charge for before it is fired at max force.

        public int m_MaxShots = 3;                  // Max number of shots in chamber

        private float m_reloadTimer;                //timer counting to reload complete
        private float m_reloadTime = 2f;            //time it takes to reload

        private int m_CurrentLoad;                  //Current number in chamber
        private string m_FireButton;                // The input axis that is used for launching shells.
        private float m_CurrentLaunchForce;         // The force that will be given to the shell when the fire button is released.
        private float m_ChargeSpeed;                // How fast the launch force increases, based on the max charge time.
        private bool m_Fired;                       // Whether or not the shell has been launched with this button press.
        private bool m_reloading;                   // Whether youre reloading or not

        private void OnEnable()
        {
            // When the tank is turned on, reset the launch force and the UI, and fully load the gun
            m_CurrentLaunchForce = m_MinLaunchForce;
            m_AimSlider.value = m_MinLaunchForce;
            m_CurrentLoad = m_MaxShots;
        }


        private void Start ()
        {
            m_reloadTimer = 0f;

            // The fire axis is based on the player number.
            m_FireButton = "Fire";

            // The rate that the launch force charges up is the range of possible forces by the max charge time.
            m_ChargeSpeed = (m_MaxLaunchForce - m_MinLaunchForce) / m_MaxChargeTime;
        }


        private void Update ()
        { 
            // The slider should have a default value of the minimum launch force.
            m_AimSlider.value = m_MinLaunchForce;

            // If the max force has been exceeded and the shell hasn't yet been launched...
            if (m_CurrentLaunchForce >= m_MaxLaunchForce && !m_Fired && !m_reloading && m_CurrentLoad != 0)
            {
                // ... use the max force and launch the shell.
                m_CurrentLaunchForce = m_MaxLaunchForce;
                Fire();
            }
            // Otherwise, if the fire button has just started being pressed...
            else if ((Input.GetButtonDown(m_FireButton)) && !m_reloading && m_CurrentLoad != 0)
            {
                // ... reset the fired flag and reset the launch force.
                m_Fired = false;
                m_CurrentLaunchForce = m_MinLaunchForce;

                // Change the clip to the charging clip and start it playing.
                m_ShootingAudio.clip = m_ChargingClip;
                m_ShootingAudio.Play();
            }
            // Otherwise, if the fire button is being held and the shell hasn't been launched yet...
            else if (Input.GetButton(m_FireButton) && !m_Fired && !m_reloading && m_CurrentLoad != 0)
            {
                // Increment the launch force and update the slider.
                m_CurrentLaunchForce += m_ChargeSpeed * Time.deltaTime;

                m_AimSlider.value = m_CurrentLaunchForce;
            }
            // Otherwise, if the fire button is released and the shell hasn't been launched yet...
            else if (Input.GetButtonUp(m_FireButton) && !m_Fired && !m_reloading && m_CurrentLoad != 0)
            {
                // ... launch the shell.
                Fire();
            }
            //check if gun is empty, reload if so
            else if (m_CurrentLoad == 0 || m_reloading || Input.GetButtonDown("Reload"))
            {
                //Disable ability to fire and run reload sequence
               
                Reload();
            }
            ChangeAmmoCountImage();
        }

        //Reloading
        private void Reload()
        {
            m_ShootingAudio.clip = m_ReloadingClip;
            m_ShootingAudio.Play();
            m_reloading = true;
            if (m_reloadTimer <= m_reloadTime)
            {
                m_reloadTimer += Time.deltaTime;
            }
            else
            {
                m_reloading = false;
                m_reloadTimer = 0f;
                m_CurrentLoad = m_MaxShots;
            }
        }

        private void Fire ()
        {
            // Set the fired flag so only Fire is only called once.
            m_Fired = true;

            // Create an instance of the shell and store a reference to it's rigidbody.
            Rigidbody shellInstance =
                Instantiate (m_Shell, m_FireTransform.position, m_FireTransform.rotation) as Rigidbody;

            // Set the shell's velocity to the launch force in the fire position's forward direction.
            shellInstance.velocity = m_CurrentLaunchForce * m_FireTransform.forward; 

            // Change the clip to the firing clip and play it.
            m_ShootingAudio.clip = m_FireClip;
            m_ShootingAudio.Play ();

            // Reset the launch force.  This is a precaution in case of missing button events.
            m_CurrentLaunchForce = m_MinLaunchForce;

            //Decrement ammo in gun
            m_CurrentLoad--;
        }

        //Display UI Element for amount of ammo player has currently.
        private void ChangeAmmoCountImage()
        {
            if (m_CurrentLoad == m_MaxShots)
            {
                //Full clip, display all three images 
                m_Ammo1.enabled = true;
                m_Ammo2.enabled = true;
                m_Ammo3.enabled = true;
            }
            else if (m_CurrentLoad == 2)
            {
                //Two shots in clip, display two images 
                m_Ammo1.enabled = true;
                m_Ammo2.enabled = true;
                m_Ammo3.enabled = false;
            }
            else if (m_CurrentLoad == 1)
            {
                //One shot in clip, display left most image 
                m_Ammo1.enabled = true;
                m_Ammo2.enabled = false;
                m_Ammo3.enabled = false;
            }
            else if (m_CurrentLoad == 0)
            {
                //Empty clip, display none
                m_Ammo1.enabled = false;
                m_Ammo2.enabled = false;
                m_Ammo3.enabled = false;
            }
        }
    }
}