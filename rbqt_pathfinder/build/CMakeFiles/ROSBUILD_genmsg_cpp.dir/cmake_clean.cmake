FILE(REMOVE_RECURSE
  "../msg_gen"
  "../srv_gen"
  "../src/rbqt_pathfinder/msg"
  "../src/rbqt_pathfinder/srv"
  "../msg_gen"
  "../srv_gen"
  "CMakeFiles/ROSBUILD_genmsg_cpp"
  "../msg_gen/cpp/include/rbqt_pathfinder/AstarState.h"
  "../msg_gen/cpp/include/rbqt_pathfinder/AstarPath.h"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_genmsg_cpp.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
