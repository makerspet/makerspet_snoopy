# [Maker's Pet](https://makerspet.com) makerspet_snoopy Pet robot model and configurations

## Modding the robot
- copy `makerspet_snoopy` to `awesome_droid`, where `awesome_droid` is a name you picked for your modded robot
- rename references files, folders and file contents to replace `makerspet_snoopy` with `awesome_droid`, incuding `package.xml`,
`CMakeLists.txt`, `urdf/makerspet_snoopy.urdf.xacro`, `sdf/makerspet_snoopy`, `sdf/makerspet_snoopy/model.*`
- edit parameters in `urdf/awesome_droid.urdf.xacro` to tweak your pet robot size
- generate SDF file as follows
```
ros2 run makerspet_snoopy urdf2sdf.sh /ros_ws/src/awesome_droid/urdf/ awesome_droid
cd /ros_ws
colcon build --symlink-install --packages-select awesome_droid

ros2 launch kaiaai_gazebo world.launch.py description:=awesome_droid
```

## Command cheat sheet
<details>
<summary>Operate a modded pet robot residing `awesome_droid` repo:</summary>
```
# Launch the physical robot
ros2 launch kaiaai_bringup main.launch.py description:=awesome_droid

# Monitor robot's sensors
ros2 launch kaiaai_bringup rviz2.launch.py description:=awesome_droid

# Launch the robot in a simulation - drive manually or let it self-drive
ros2 launch kaiaai_gazebo world.launch.py description:=awesome_droid
ros2 run kaiaai_teleop teleop_keyboard description:=awesome_droid
ros2 launch kaiaai_gazebo self_drive_gazebo.launch.py description:=awesome_droid
ros2 launch kaiaai_bringup rviz2.launch.py description:=awesome_droid

# Launch the robot in a simulation - create, save a map
ros2 launch kaiaai_gazebo world.launch.py description:=awesome_droid
ros2 launch kaiaai_bringup cartographer.launch.py use_sim_time:=true description:=awesome_droid
ros2 launch kaiaai_gazebo self_drive_gazebo.launch.py description:=awesome_droid
ros2 run nav2_map_server map_saver_cli -f $HOME/my_map

# Launch the robot in a simulation - let it navigate automatically using an existing map
ros2 launch kaiaai_gazebo world.launch.py description:=awesome_droid
ros2 launch kaiaai_bringup navigation.launch.py use_sim_time:=true map:=$HOME/my_map.yaml description:=awesome_droid

# Inspect or edit robot's URDF model - useful when modding a robot
ros2 launch kaiaai_bringup inspect_urdf.launch.py description:=awesome_droid model:=my_model
ros2 launch kaiaai_bringup edit_urdf.launch.py description:=awesome_droid model:=my_model

# Convert URDF robot model file into SDF Gazebo simulation model file
ros2 run awesome_droid urdf2sdf.sh /ros_ws/src/awesome_droid/urdf/ r2d2
cd /ros_ws && colcon build --symlink-install --packages-select awesome_droid
```
</details>
