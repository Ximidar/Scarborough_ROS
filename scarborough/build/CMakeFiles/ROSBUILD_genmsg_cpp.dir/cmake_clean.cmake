FILE(REMOVE_RECURSE
  "../msg_gen"
  "../msg_gen"
  "../src/scarborough/msg"
  "CMakeFiles/ROSBUILD_genmsg_cpp"
  "../msg_gen/cpp/include/scarborough/Motor_Speed.h"
  "../msg_gen/cpp/include/scarborough/Desired_Directions.h"
  "../msg_gen/cpp/include/scarborough/YPR.h"
  "../msg_gen/cpp/include/scarborough/Kill_Switch.h"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_genmsg_cpp.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
