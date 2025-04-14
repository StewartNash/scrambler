/*
 * File: main.ino
 * Date: April 14, 2025
 * Last Modified: -
 * Author: Stewart Nash
 * Description: Main entry point for scrambler Arduino
 * code.
 *
 */

#include <ros.h>
#include <std_msgs/Empty.h>
#incldue <std_msgs/String.h>
#include <Servo.h>

ros::NodeHandle nh;

void messageCallback(const std_msgs::Empty& toggle_message) {
	digitalWrite(13, HIGH - digitalRead(13)); // Blink the LED
}

ros::Subscriber<std_msgs::Empty> subscription_("toggle_led", &messageCallback);

void setup() {
	pinMode(13, OUTPUT);
	nh.initNode();
	nh.subscribe(subscription_);
}

void loop() {
	nh.spinOnce();
	delay(1);
} 
