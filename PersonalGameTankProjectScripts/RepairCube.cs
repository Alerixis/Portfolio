using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RepairCube : MonoBehaviour {

    public float speed;


	// Update is called once per frame
	void Update () {
        Spin();
        
	}

    private void Spin()
    {
        transform.Rotate(Vector3.up, speed * Time.deltaTime);
        transform.Rotate(Vector3.left, speed * Time.deltaTime);
    }
}
