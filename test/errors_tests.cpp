#include <gtest/gtest.h>

#include <franka/errors.h>
#include <research_interface/robot/rbk_types.h>

#include "helpers.h"

TEST(Errors, IsInitializedToNoErrors) {
  franka::Errors errors;

  EXPECT_FALSE(errors);
}

TEST(Errors, EvaluatedToTrueOnError) {
  research_interface::robot::RobotState state;
  state.errors[rand() % state.errors.size()] = true;

  franka::Errors errors(state.errors);

  EXPECT_TRUE(errors);
}

TEST(Errors, CanGetNamesOfErrors) {
  research_interface::robot::RobotState state;
  std::fill(state.errors.begin(), state.errors.end(), false);
  state.errors[0] = true;
  state.errors[2] = true;

  franka::Errors errors(state.errors);

  std::string expected = "joint_position_limits_violation, self_collision_avoidance_violation";
  EXPECT_EQ(expected, franka::activeErrorsString(errors));
}

TEST(Errors, CanBeStreamed) {
  franka::Errors errors;

  std::stringstream ss;
  ss << errors;
  std::string output(ss.str());

  EXPECT_PRED2(stringContains, output, "joint_position_limits_violation");
  EXPECT_PRED2(stringContains, output, "cartesian_position_limits_violation");
  EXPECT_PRED2(stringContains, output, "self_collision_avoidance_violation");
  EXPECT_PRED2(stringContains, output, "joint_velocity_violation");
  EXPECT_PRED2(stringContains, output, "cartesian_velocity_violation");
  EXPECT_PRED2(stringContains, output, "force_control_safety_violation");
  EXPECT_PRED2(stringContains, output, "joint_reflex");
  EXPECT_PRED2(stringContains, output, "cartesian_reflex");
  EXPECT_PRED2(stringContains, output, "max_goal_pose_deviation_violation");
  EXPECT_PRED2(stringContains, output, "max_path_pose_deviation_violation");
  EXPECT_PRED2(stringContains, output, "cartesian_velocity_profile_safety_violation");
  EXPECT_PRED2(stringContains, output, "joint_position_motion_generator_start_pose_invalid");
  EXPECT_PRED2(stringContains, output, "joint_motion_generator_position_limits_violation");
  EXPECT_PRED2(stringContains, output, "joint_motion_generator_velocity_limits_violation");
  EXPECT_PRED2(stringContains, output, "joint_motion_generator_velocity_discontinuity");
  EXPECT_PRED2(stringContains, output, "joint_motion_generator_acceleration_discontinuity");
  EXPECT_PRED2(stringContains, output, "cartesian_position_motion_generator_start_pose_invalid");
  EXPECT_PRED2(stringContains, output, "cartesian_motion_generator_elbow_limit_violation");
  EXPECT_PRED2(stringContains, output, "cartesian_motion_generator_velocity_limits_violation");
  EXPECT_PRED2(stringContains, output, "cartesian_motion_generator_velocity_discontinuity");
  EXPECT_PRED2(stringContains, output, "cartesian_motion_generator_acceleration_discontinuity");
  EXPECT_PRED2(stringContains, output, "cartesian_motion_generator_elbow_sign_inconsistent");
  EXPECT_PRED2(stringContains, output, "cartesian_motion_generator_start_elbow_invalid");
  EXPECT_PRED2(stringContains, output, "force_controller_desired_force_tolerance_violation");
}