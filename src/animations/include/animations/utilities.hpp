/*
 * File: utilities.hpp
 * Author: Stewart Nash
 * Date: April 25, 2025
 * Last modified: -
 * Description: Utility functions for animations
 *
 */
#pragma once

class AnimationReader {
	public:
		void readAngles(std::string filename);
		void readPositions(std::string filename);
		std::vector<double> getAngles();
		std::vector<double> getPositions();
		std::vector<int> convertToInteger(std::vector<double> valueArray);
	private:
		bool isRead;
		std::vector<double> angles;
		std::vector<double> positions;
};
