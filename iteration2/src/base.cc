/**
 * @file base.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/base.h"
#include "src/params.h"
#include "src/pose.h"
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Base::Base() : ArenaImmobileEntity(), captured_(false) {
  set_type(kBase);
  set_color(BASE_COLOR);
  set_pose(BASE_INIT_POS);
  set_radius(BASE_RADIUS);
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Base::Reset() {
  set_pose(Pose(static_cast<double>((30 + (random() % 19) * 50)),
        static_cast<double>((30 + (random() % 14) * 50))));
  captured_=false;
  set_color(BASE_COLOR);
} /* Reset */

NAMESPACE_END(csci3081);
