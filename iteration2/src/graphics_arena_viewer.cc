/**
 * @file graphics_arena_viewer.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include "src/graphics_arena_viewer.h"
#include "src/arena_params.h"
#include "src/rgb_color.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
GraphicsArenaViewer::GraphicsArenaViewer(
    const struct arena_params *const params,
    Arena * arena, Controller * controller) :
    GraphicsApp(
        params->x_dim + GUI_MENU_WIDTH + GUI_MENU_GAP * 2,
        params->y_dim,
        "Robot Simulation"),
    controller_(controller),
    arena_(arena) {
  auto *gui = new nanogui::FormHelper(screen());
  nanogui::ref<nanogui::Window> window =
      gui->addWindow(
          Eigen::Vector2i(10 + GUI_MENU_GAP, 10),
          "Menu");

  gui->addGroup("Simulation Control");
  playing_button_ =
    gui->addButton(
      "Play",
      std::bind(&GraphicsArenaViewer::OnPlayingBtnPressed, this));
  screen()->performLayout();
  new_button_ =
    gui->addButton(
      "New Game",
      std::bind(&GraphicsArenaViewer::OnNewBtnPressed, this));
  screen()->performLayout();
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

// This is the primary driver for state change in the arena.
// It will be called at each iteration of nanogui::mainloop()
void GraphicsArenaViewer::UpdateSimulation(double dt) {
  controller_->AdvanceTime(dt);
}

/*******************************************************************************
 * Handlers for User Keyboard and Mouse Events
 ******************************************************************************/
void GraphicsArenaViewer::OnPlayingBtnPressed() {
  // Not implemented. Sample code provided to show how to implement.
  paused_ = !paused_;
  if (!paused_) {
    controller_->AcceptCommunication(kPlay);
    playing_button_->setCaption("Playing");
  } else {
    controller_->AcceptCommunication(kPause);
    playing_button_->setCaption("Paused");
  }
}
void GraphicsArenaViewer::OnNewBtnPressed() {
  controller_->AcceptCommunication(kNewGame);
}
/** OnSpecialKeyDown is called when the user presses down on one of the
  * special keys (e.g. the arrow keys).
  */
/**
 * @TODO: Check for arrow key presses using GLFW macros, then
 * convert to appropriate enum Communication and relay to controller
 */
void GraphicsArenaViewer::OnSpecialKeyDown(int key,
  __unused int scancode, __unused int modifiers) {
  Communication key_value = kNone;
  switch (key) {
    case GLFW_KEY_LEFT: key_value = kKeyLeft;
    break;
    case GLFW_KEY_RIGHT: key_value = kKeyRight;
    break;
    case GLFW_KEY_DOWN: key_value= kKeyDown;
    break;
    case GLFW_KEY_UP: key_value = kKeyUp;
    break;
    default: {}
  }
  controller_->AcceptCommunication(key_value);
}

/*******************************************************************************
 * Drawing of Entities in Arena
 ******************************************************************************/
/*void GraphicsArenaViewer::DrawRobotSensor(NVGcontext *ctx, const Robot *const robot){
  double xpos = static_cast<float>(robot->get_pose().x);
  double ypos = static_cast<float>(robot->get_pose().y);
  double angle = (robot->get_pose().theta)*M_PI/180;  

  nvgSave(ctx);
  nvgTranslate(ctx, xpos, ypos);
  nvgRotate(ctx, angle);

  // sensor cone outline
  nvgSave(ctx);
  nvgRotate(ctx, 0.5 * 45);
  nvgBeginPath(ctx);
  nvgMoveTo(ctx, 0.0, 0.0);
  nvgLineTo(ctx, 5, 0.0);
  nvgArc(ctx, 0.0, 0.0, 10, 0.0, -45, NVG_CCW);
  nvgLineTo(ctx, 0.0, 0.0);
  nvgStrokeColor(ctx, nvgRGBA(100, 0, 0, 100));
  nvgStroke(ctx);
  nvgRestore(ctx);

  // blue for right sensor cone
  nvgSave(ctx);
  nvgRotate(ctx, 0.5 * 45);
  nvgBeginPath(ctx);
  nvgMoveTo(ctx, 0.0, 0.0);
  nvgLineTo(ctx, 5, 0.0);
  nvgArc(ctx, 0.0, 0.0, 10, 0.0, -0.5 * 45, NVG_CCW);
  nvgLineTo(ctx, 0.0, 0.0);
  nvgFillColor(ctx, nvgRGBA(100, 10, 255, 150));
  nvgFill(ctx);
  nvgRestore(ctx);

  // yellow for left sensor cone
  nvgSave(ctx);
  nvgBeginPath(ctx);
  nvgMoveTo(ctx, 0.0, 0.0);
  nvgLineTo(ctx, 5, 0.0);
  nvgArc(ctx, 0.0, 0.0, 10, 0.0, -0.5 * 45, NVG_CCW);
  nvgLineTo(ctx, 0.0, 0.0);
  nvgFillColor(ctx, nvgRGBA(255, 255, 100, 150));
  nvgFill(ctx);
  nvgRestore(ctx);

  nvgRestore(ctx);

}
*/
void GraphicsArenaViewer::DrawRobot(NVGcontext *ctx,
                                     const Robot *const robot) {
  // translate and rotate all graphics calls that follow so that they are
  // centered, at the position and heading of this robot
  nvgSave(ctx);
  nvgTranslate(ctx,
               static_cast<float>(robot->get_pose().x),
               static_cast<float>(robot->get_pose().y));
  nvgRotate(ctx,
            static_cast<float>(robot->get_pose().theta * M_PI / 180.0));

  // robot's circle
  nvgBeginPath(ctx);
  nvgCircle(ctx, 0.0, 0.0, static_cast<float>(robot->get_radius()));
  nvgFillColor(ctx,
               nvgRGBA(robot->get_color().r, robot->get_color().g,
                       robot->get_color().b, 255));
  nvgFill(ctx);
  nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgStroke(ctx);

  // robot id text label
  nvgSave(ctx);
  nvgRotate(ctx, static_cast<float>(M_PI / 2.0));
  nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
  std::string str;
  str = robot->get_name();
  str += " ";
  str += std::to_string(robot->get_lives());
  nvgText(ctx, 0.0, 10.0, str.c_str(), nullptr);
  nvgRestore(ctx);
  nvgRestore(ctx);
}
void GraphicsArenaViewer::DrawArena(NVGcontext *ctx) {
  nvgBeginPath(ctx);
  // Creates new rectangle shaped sub-path.
  nvgRect(ctx, 0, 0, arena_->get_x_dim(), arena_->get_y_dim());
  nvgStrokeColor(ctx, nvgRGBA(255, 255, 255, 255));
  nvgStroke(ctx);
}

void GraphicsArenaViewer::DrawEntity(NVGcontext *ctx,
                                       const ArenaEntity *const entity) {
  // obstacle's circle
  nvgBeginPath(ctx);
  nvgCircle(ctx,
            static_cast<float>(entity->get_pose().x),
            static_cast<float>(entity->get_pose().y),
            static_cast<float>(entity->get_radius()));
  nvgFillColor(ctx,
               nvgRGBA(entity->get_color().r, entity->get_color().g,
                       entity->get_color().b, 255));
  nvgFill(ctx);
  nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgStroke(ctx);

  // obstacle id text label
  nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgText(ctx,
          static_cast<float>(entity->get_pose().x),
          static_cast<float>(entity->get_pose().y),
          entity->get_name().c_str(), nullptr);
}
void GraphicsArenaViewer::DrawText(NVGcontext *ctx) {
  switch (status_) {
    case kWon: nvgText(ctx, 40, 100, "WINNER", NULL);
    paused_ = true;
    break;
    case kLost: nvgText(ctx, 40, 100, "LOSER", NULL);
    paused_ = true;
    break;
    default: {}
  }
}
void GraphicsArenaViewer::DrawUsingNanoVG(NVGcontext *ctx) {
  // initialize text rendering settings
  nvgFontSize(ctx, 18.0f);
  nvgFontFace(ctx, "sans-bold");
  nvgTextAlign(ctx, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);
  DrawArena(ctx);
  DrawText(ctx);
  std::vector<ArenaEntity *> entities = arena_->get_entities();
  for (auto &entity : entities) {
    DrawEntity(ctx, entity);
  } /* for(i..) */
 // std::vector<Robot *> robots = arena_->robot();
  //for (auto &robot : robots) {
  DrawRobot(ctx, arena_->robot());
  //DrawRobotSensor(ctx, arena_->robot());
  //}
}
void GraphicsArenaViewer::AcceptCommunication(Communication com) {
  status_ = com;
}
NAMESPACE_END(csci3081);
