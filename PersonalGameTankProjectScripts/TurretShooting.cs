using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Complete
{
    public class TurretShooting : MonoBehaviour
    {
        public LayerMask m_ObjectMask;      //Filters what the raycast hits.


        public Rigidbody m_Shell;           //Prefab of the shell it shoots
        public Transform m_FireSpawn;       //Position for where the shell spawns

        public float m_FireDelay = 2f;     //Delay between shots from turret
        public AudioSource m_ShootAudioSource;    //Ref to audio source of turret
        public AudioClip m_FireAudio;               //Ref to audio file sound
        public float m_LaunchForce = 50f;         //Force with which the turret fires the shell.
        public float turnspeed;             //Speed with which the turret turns


        private float m_timer;              //Timer between shots
        public int waitingTime = 2;             //time between shots
        private RaycastHit m_hitPlayer;

        private void Start()
        {
            m_timer = 0;
            turnspeed = 10f;        
        }

        //Updated each frame
        private void Update()
        {
            RaycastHit hitPlayer;
            float distance = 50f;
            Vector3 forward = transform.TransformDirection(Vector3.forward) * distance;
            Debug.DrawRay(transform.position, forward, Color.green);

            m_timer += Time.deltaTime;

            //Grab quaternion euler value for rotations towards the player
            Quaternion neededRotation = Quaternion.LookRotation((GameObject.FindGameObjectWithTag("Player").gameObject.transform.position - transform.position));

            //Rotate a small amount each from until the turret is pointing at the player's tank
            transform.rotation = Quaternion.RotateTowards(transform.rotation, neededRotation, Time.deltaTime * turnspeed);

            //Check if turret is pointed at the player and check if target is held long enough to fire.
            
            if(m_timer >= waitingTime)
            {
                m_timer = 0;

                if (Physics.Raycast(transform.position, forward, out hitPlayer))
                {
                    if (hitPlayer.collider.tag == "Player")
                    {
                        Fire();                   
                    }
                }
            }
        }

        private void Fire()
        {
            //Spawn the instance of the shell
 
            Rigidbody shellInstance = Instantiate(m_Shell, m_FireSpawn.position, m_FireSpawn.rotation) as Rigidbody;

            //Apply force to the shell and launch it forward
            shellInstance.velocity = m_LaunchForce * m_FireSpawn.forward;

            //Play audio
            m_ShootAudioSource.Play();           
        }
    }
}
