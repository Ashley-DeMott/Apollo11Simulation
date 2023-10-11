#pragma once

#define TWO_PI 6.28318530718

#include <math.h>    // for floor()
#include <iostream>  // for cout
#include <cassert>   // for assert()
using namespace std;

class TestAngle;

/************************************
 * ANGLE
 * A class that represents an Angle,
 *  can be represented in radians or degrees
 ************************************/
class Angle
{
	friend TestAngle;

public:
	/************************************
	* CONSTRUCTORS
	* Three constructors: Default, non-default, copy
	************************************/
	Angle() : radians(0.0) {}
	Angle(double degrees) : radians(0.0)
	{
		setDegrees(degrees);
	}
	Angle(const Angle& rhs) : radians(rhs.radians) {}

	/**************************************************
	* GET DEGREES
	* Returns the Angle in degrees
	***************************************************/
	double getDegrees() const {
		return convertToDegrees(radians);
	}

	/**************************************************
	* GET RADIANS
	* Returns the Angle in radians
	***************************************************/
	double getRadians() const {
		return radians;
	}

	/**************************************************
	* SET DEGREES
	* Changes the Angle to a given degree, first
	*  converting it into a radian and normalizing it
	***************************************************/
	void setDegrees(double degree) {
		radians = normalize(convertToRadians(degree));
	}

	/**************************************************
	* SET RADIANS
	* Changes the Angle to a given radian value,
	*  first normalizing it (making it between 0 and 2 PI)
	***************************************************/
	void setRadians(double radian) {
		radians = normalize(radian);
	}

	/**************************************************
	* DISPLAY
	* Displays the Angle in degrees, given an ostream
	***************************************************/
	ostream& display(ostream& out) const {
		out.setf(std::ios::fixed);
		out.setf(std::ios::showpoint);
		out.precision(1);

		out << "Angle: " << getDegrees() << " degrees";
		return out;
	}

private:
	double radians; // The Angle in radians

	/**************************************************
	* NORMALIZE
	* Given a radian, returns an equivalent radian between 0 and 2 PI
	***************************************************/
	double normalize(double radian) const {
		// While less than 0,
		while (radian < 0.0)
			// Add a full rotation
			radian += TWO_PI;

		// While greater than 2 PI,
		while (radian >= TWO_PI)
			// Subtract a full rotation
			radian -= TWO_PI;

		return radian;
	}

	/**************************************************
	* CONVERT TO DEGREES
	* Converts the given raidan into degrees (between 0 and 360)
	***************************************************/
	double convertToDegrees(double radian) const {
		return normalize(radian) * 360.0 / TWO_PI;
	}

	/**************************************************
	* CONVERT TO RADIANS
	* Converts the given degree into radians (between 0 and 2 PI)
	***************************************************/
	double convertToRadians(double degree) const {
		return normalize(degree * TWO_PI / 360.0);
	}
};