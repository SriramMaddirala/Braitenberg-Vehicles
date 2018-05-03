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
#include <math.h>
#include "src/graphics_arena_viewer.h"
#include "src/arena_params.h"
#include "src/rgb_color.h"
#include "src/params.h"
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
 // vvvv  ADDED THIS ONE LINE to register the window  vvvv
 // gui->addGroup creates a heading within the window
  window->setLayout(new nanogui::GroupLayout());
  gui->addGroup("Simulation Control");
  playing_button_ =
    gui->addButton(
      "Play",
      std::bind(&GraphicsArenaViewer::OnPlayingBtnPressed, this));
 playing_button_->setFixedWidth(100);
 screen()->setSize({X_DIM, Y_DIM}); 

  gui->addGroup("Arena Configuration");

  // Creating a panel impacts the layout. Widgets, sliders, buttons can be
  // assigned to either the window or the panel.
  nanogui::Widget *panel = new nanogui::Widget(window);

  // *************** SLIDER 1 ************************//
  new nanogui::Label(panel, "Number of Robots", "sans-bold");
  nanogui::Slider *slider = new nanogui::Slider(panel);
  // The starting value (range is from 0 to 1)
  // Note that below the displayed value is 10* slider value.
  slider->setValue(0.5f);
  slider->setFixedWidth(100);
  
  // Display the corresponding value of the slider in this textbox
  nanogui::TextBox *textBox = new nanogui::TextBox(panel);
  textBox->setFixedSize(nanogui::Vector2i(60, 25));
  textBox->setFontSize(20);
  textBox->setValue("5");

  // This is the lambda function called while the user is moving the slider
  slider->setCallback(
    [textBox](float value) {
      textBox->setValue(std::to_string(int(value*10)));
    }
  );
  // This is the lambda function called once the user is no longer manipulating the slider.
  // Note robot_count_ is set, which is a graphics_arena_ variable in this version, although
  // you should communicate that value to the controller so that it can configure the Arena.
  slider->setFinalCallback(
    [&](float value) {
      arena_->set_robotnum(int(value*10));
     }
  );

  // *************** SLIDER 2 ************************//
  new nanogui::Label(panel, "Number of Lights", "sans-bold");
  nanogui::Slider *slider2 = new nanogui::Slider(panel);
  slider2->setValue(0.0f);
  slider2->setFixedWidth(100);
  //textBox->setUnits("%");

  nanogui::TextBox *textBox2 = new nanogui::TextBox(panel);
  textBox2->setFixedSize(nanogui::Vector2i(60, 25));
  textBox2->setFontSize(20);
  textBox2->setValue("0");
  //textBox2->setAlignment(nanogui::TextBox::Alignment::Right);

  slider2->setCallback(
    [textBox2](float value) {
      textBox2->setValue(std::to_string(int(value*5)));
    }
  );

  slider2->setFinalCallback(
    [&](float value) {
      arena_->set_lightnum(int(value*5));
    }
  );

  // *************** SLIDER 3 ************************//
  new nanogui::Label(panel, "Percentage of Robots that exhibit Fear", "sans-bold");
  nanogui::Slider *slider3 = new nanogui::Slider(panel);
  slider3->setValue(0.0f);
  slider3->setFixedWidth(100);
  //textBox->setUnits("%");

  nanogui::TextBox *textBox3 = new nanogui::TextBox(panel);
  textBox3->setFixedSize(nanogui::Vector2i(60, 25));
  textBox3->setFontSize(20);
  textBox3->setValue("0");
  //textBox2->setAlignment(nanogui::TextBox::Alignment::Right);

  slider3->setCallback(
    [textBox3](float value) {
      textBox3->setValue(std::to_string(int(value*10)));
    }
  );

  slider3->setFinalCallback(
    [&](float value) {
      arena_->set_fearnum(int(value*10));
     }
  );

 // *************** SLIDER 4 ************************//
  new nanogui::Label(panel, "Sensitivity of Robots to Light", "sans-bold");
  nanogui::Slider *slider4 = new nanogui::Slider(panel);
  slider4->setValue(0.0f);
  slider4->setFixedWidth(100);
  //textBox->setUnits("%");

  nanogui::TextBox *textBox4 = new nanogui::TextBox(panel);
  textBox4->setFixedSize(nanogui::Vector2i(60, 25));
  textBox4->setFontSize(20);
  textBox4->setValue("0");
  //textBox2->setAlignment(nanogui::TextBox::Alignment::Right);

  slider4->setCallback(
    [textBox4](float value) {
      textBox4->setValue(std::to_string(int(value*10)));
    }
  );

  slider4->setFinalCallback(
    [&](float value) {
      arena_->set_sensenum(int(value*10));
    }
  );
 // *************** SLIDER 5 ************************//
  new nanogui::Label(panel, "Food", "sans-bold");
  nanogui::Slider *slider5 = new nanogui::Slider(panel);
  slider5->setValue(0.0f);
  slider5->setFixedWidth(100);
  //textBox->setUnits("%");

  nanogui::TextBox *textBox5 = new nanogui::TextBox(panel);
  textBox5->setFixedSize(nanogui::Vector2i(60, 25));
  textBox5->setFontSize(20);
  textBox5->setValue("0");
  //textBox2->setAlignment(nanogui::TextBox::Alignment::Right);

  slider5->setCallback(
    [textBox5](float value) {
      textBox5->setValue(std::to_string(int(value*10)));
    }
  );

  slider5->setFinalCallback(
    [&](float value) {
      arena_->set_foodnum(int(value*10));
    }
  );


  // Lays out all the components with "15" units of inbetween spacing
  panel->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Vertical, nanogui::Alignment::Middle, 0, 15));

screen()->performLayout();
  food_button_ =
    gui->addButton(
      "Food",
      std::bind(&GraphicsArenaViewer::OnFoodBtnPressed, this));
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
   controller_->AcceptCommunication(kPause);
    playing_button_->setCaption("Paused");
}
void GraphicsArenaViewer::OnFoodBtnPressed() {
  food_ = !food_;
  if (!food_) {
//    controller_->AcceptCommunication(kSFood);
    food_button_->setCaption("Food");
    arena_->set_foodbool(true);
   } else {
  // controller_->AcceptCommunication(kSNoFood);
    food_button_->setCaption("No Food");
    arena_->set_foodbool(false);
  }
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
void GraphicsArenaViewer::DrawRobotSensor(NVGcontext *ctx, const Robot *const robot){
  double xpos = static_cast<float>(robot->get_pose().x);
  double ypos = static_cast<float>(robot->get_pose().y);
  double xanglel = cos(robot->get_pose().theta -40);
  double yanglel = sin(robot->get_pose().theta -40);
  double xangler = cos(robot->get_pose().theta +40);
  double yangler = sin(robot->get_pose().theta +40);
  nvgBeginPath(ctx);
  nvgCircle(ctx,
            (xpos+(robot->get_radius()*(xanglel))),
            (ypos+(robot->get_radius()*(yanglel))),
            static_cast<float>(2));
  nvgFillColor(ctx,
               nvgRGBA(200, 10,
                       200, 255));
  nvgFill(ctx);
  nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgStroke(ctx);
 
 nvgBeginPath(ctx);
  nvgCircle(ctx,
            (xpos+(robot->get_radius()*(xangler))),
            (ypos+(robot->get_radius()*(yangler))),
            static_cast<float>(2));
  nvgFillColor(ctx,
               nvgRGBA(200, 10,
                       200, 255));
  nvgFill(ctx);
  nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgStroke(ctx);

  nvgBeginPath(ctx);
  nvgCircle(ctx,
            xpos,
            ypos,
            static_cast<float>(2));
  nvgFillColor(ctx,
               nvgRGBA(250, 250,
                       0, 255));
  nvgFill(ctx);
  nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgStroke(ctx);

}

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
  nvgText(ctx, 0.0, 0.5, str.c_str(), nullptr);
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
  std::vector<Robot *> robot_entities = arena_->get_robotentities();
  for (auto &entity : entities) {
     if(entity->get_type()!=kRobot){
     DrawEntity(ctx, entity);
     }
  } /* for(i..) */
 for(auto &ent1: robot_entities){
     DrawRobot(ctx, ent1);
     DrawRobotSensor(ctx,ent1);
  }
}
void GraphicsArenaViewer::AcceptCommunication(Communication com) {
  status_ = com;
}
NAMESPACE_END(csci3081);
