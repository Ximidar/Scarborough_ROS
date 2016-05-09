FILE(REMOVE_RECURSE
  "../msg_gen"
  "../msg_gen"
  "../src/scarborough/msg"
  "CMakeFiles/ROSBUILD_genmsg_py"
  "../src/scarborough/msg/__init__.py"
  "../src/scarborough/msg/_Motor_Speed.py"
  "../src/scarborough/msg/_Desired_Directions.py"
  "../src/scarborough/msg/_YPR.py"
  "../src/scarborough/msg/_Kill_Switch.py"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_genmsg_py.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
