/*
 * File: scrambler.hpp
 * Date: April 16, 2025
 * Last Modified: -
 * Author: Stewart Nash
 * Description: Include file for scrambler structure.
 *
 */
#include <Servo.h>

class Limb {
	public:
		Servo coxa;
		Servo femur;
		Servo tibia;
		
		std::string name;
		int number;
}

class Organism {
	public:
		std::vector<Limb> appendages
}

/*
 * "right front leg": coxa(39), femur(38), tibia(37)
 * "right middle leg": coxa(36), femur(35), tibia(34)
 * "right back leg": coxa(33), femur(32), tibia(31)
 * "left front leg": coxa(22), femur(23), tibia(24)
 * "left middle leg": coxa(25), femur(26), tibia(27)
 * "left back leg": coxa(28), femur(29), tibia(30)
 */

