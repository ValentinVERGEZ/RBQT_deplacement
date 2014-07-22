FILE(REMOVE_RECURSE
  "../msg_gen"
  "../srv_gen"
  "../src/rbqt_pathfinder/msg"
  "../src/rbqt_pathfinder/srv"
  "../msg_gen"
  "../srv_gen"
  "CMakeFiles/ROSBUILD_genmsg_py"
  "../src/rbqt_pathfinder/msg/__init__.py"
  "../src/rbqt_pathfinder/msg/_AstarState.py"
  "../src/rbqt_pathfinder/msg/_AstarPath.py"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_genmsg_py.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
