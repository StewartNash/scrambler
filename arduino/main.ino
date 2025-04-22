/*
 * File: main.ino
 * Date: April 14, 2025
 * Last Modified: -
 * Author: Stewart Nash
 * Description: Main entry point for scrambler Arduino
 * code.
 *
 */

#include "scrambler.hpp"

#include <ros.h>
//#include <std_msgs/Empty.h>
#include <std_msgs/String.h>
#include <std_msgs/Int16MultiArray.h>
//#include <Servo.h>

const int NUMBER_OF_LIMBS = 6;

ros::NodeHandle nh;
Organism myOrganism;

bool isInitialized = false;

/*
void messageCallback(const std_msgs::Empty& toggle_message) {
	digitalWrite(13, HIGH - digitalRead(13)); // Blink the LED
}

ros::Subscriber<std_msgs::Empty> subscription_("toggle_led", &messageCallback);
*/

void messageCallback(const std_msgs::Int16MultiArray message) {
	if (isInitialized) {
		for (int i = 0; i < NUMBER_OF_LIMBS; i++) {
			myOrganism.appendages[i].coxa.write(message.data[3 * i + 0]);
			myOrganism.appendages[i].femur.write(message.data[3 * i + 1]);
			myOrganism.appendages[i].tibia.write(message.data[3 * i + 2]);
		}
		digitalWrite(13, HIGH - digitalRead(13)); // Blink the LED
	} else {
		// Warn, not initialized
	}
}

ros::Subscriber<std_msgs::Int16MultiArray> subscription_("toggle_led", &messageCallback);

void setup() {
	pinMode(13, OUTPUT);
	nh.initNode();
	nh.subscribe(subscription_);
}

void loop() {
	nh.spinOnce();
	delay(1);
}

void initialize() {
	myOrganism.addAppendage(Limb(
  		RIGHT_FRONT_COXA,
  		RIGHT_FRONT_FEMUR,
  		RIGHT_FRONT_TIBIA,
  		0,
  		"right front leg"));
	myOrganism.addAppendage(Limb(
  		RIGHT_MIDDLE_COXA,
  		RIGHT_MIDDLE_FEMUR,
  		RIGHT_MIDDLE_TIBIA,
  		1,
  		"right middle leg"));
	myOrganism.addAppendage(Limb(
  		RIGHT_BACK_COXA,
  		RIGHT_BACK_FEMUR,
  		RIGHT_BACK_TIBIA,
  		2,
  		"right back leg"));
	myOrganism.addAppendage(Limb(
  		LEFT_FRONT_COXA,
  		LEFT_FRONT_FEMUR,
  		LEFT_FRONT_TIBIA,
  		3,
  		"left front leg"));
	myOrganism.addAppendage(Limb(
  		LEFT_MIDDLE_COXA,
  		LEFT_MIDDLE_FEMUR,
  		LEFT_MIDDLE_TIBIA,
  		4,
  		"left middle leg"));
	myOrganism.addAppendage(Limb(
  		LEFT_BACK_COXA,
  		LEFT_BACK_FEMUR,
  		LEFT_BACK_TIBIA,
  		5,
  		"left back leg"));
	isInitialized = true;
}
