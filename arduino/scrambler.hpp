/*
 * File: scrambler.hpp
 * Date: April 16, 2025
 * Last Modified: -
 * Author: Stewart Nash
 * Description: Include file for scrambler structure.
 *
 */
#include <Servo.h>
#include <vector>
/*
 * "right front leg": coxa(39), femur(38), tibia(37)
 * "right middle leg": coxa(36), femur(35), tibia(34)
 * "right back leg": coxa(33), femur(32), tibia(31)
 * "left front leg": coxa(22), femur(23), tibia(24)
 * "left middle leg": coxa(25), femur(26), tibia(27)
 * "left back leg": coxa(28), femur(29), tibia(30)
 */
const int RIGHT_FRONT_COXA = 39;
const int RIGHT_FRONT_FEMUR = 38;
const int RIGHT_FRONT_TIBIA = 37;
const int RIGHT_MIDDLE_COXA = 36;
const int RIGHT_MIDDLE_FEMUR = 35;
const int RIGHT_MIDDLE_TIBIA = 34;
const int RIGHT_BACK_COXA = 33;
const int RIGHT_BACK_FEMUR = 32;
const int RIGHT_BACK_TIBIA = 31;
const int LEFT_FRONT_COXA = 22;
const int LEFT_FRONT_FEMUR = 23;
const int LEFT_FRONT_TIBIA = 24;
const int LEFT_MIDDLE_COXA = 25;
const int LEFT_MIDDLE_FEMUR = 26;
const int LEFT_MIDDLE_TIBIA = 27;
const int LEFT_BACK_COXA = 28;
const int LEFT_BACK_FEMUR = 29;
const int LEFT_BACK_TIBIA = 30;

class Limb {
	public:
		Limb(int c, int f, int t, int n, std::string designator);
		Servo coxa;
		Servo femur;
		Servo tibia;
		
		int number;
		std::string name;
		
		int coxaAttachment;
		int femurAttachment;
		int tibiaAttachment;
}

class Organism {
	public:
		Organism();
		std::vector<Limb> appendages;
		
		void addAppendage(Limb appendage);
		Limb getAppendage(int index);
}

Limb::Limb(int c, int f, int t, int n, std::string designator="") : coxaAttachment(c), femurAttachment(f), tibiaAttachment(t), number(n) {
	name = designator;
	
	  coxa.attach(coxaAttachment);
	  femur.attach(coxaAttachment);
	  tibia.attach(tibiaAttachment);
};

Organism::Organism() {

}

void Organism::addAppendage(Limb appendage) {
	appendage.push_back(appendage);
}

Limb Organism::getAppendage(int index) {
	//if (index >= 0 && index < appendages.size()) {
	//	return appendages(index);
	//} else {
	//	return appendages[0];
	//}
	return appendages[index];
}

