#include "Simulator.h"

const bool Simulator::safelyLanded() {
    bool safelyLanded = false;

    // If the Lander has hit the ground,
    if (hitGround()) {
        // The Lander must be travelling at a safe speed AND be on the platform
        safelyLanded = (lm.getVel() < SAFE_LANDING_VEL) && ground.onPlatform(*(lm.getPos()), lm.getWidth());

        // The LM has landed
        lm.land(safelyLanded);
    }
    else {
        // Cannot determine if the lm has landed safely if not on the ground
        assert(false);
    }

    // Must meet both conditions
    return safelyLanded;
}

void Simulator::createStars() {
    // For every star, generate a random X and Y position
    for (int i = 0; i < NUM_STARS; i++) {
        double posX = random(0.0, ptUpperRight.getX());
        double posY = random(0.0, ptUpperRight.getY());

        // Add the new Star to the list of Stars
        stars.push_back(new Star(Point(posX, posY)));
    }
    assert(stars.size() == NUM_STARS); // Make sure it generates all 50 stars
}