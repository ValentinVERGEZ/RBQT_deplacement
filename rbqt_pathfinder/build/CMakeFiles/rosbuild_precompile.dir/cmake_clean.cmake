FILE(REMOVE_RECURSE
  "../msg_gen"
  "../srv_gen"
  "../src/rbqt_pathfinder/msg"
  "../src/rbqt_pathfinder/srv"
  "../msg_gen"
  "../srv_gen"
  "CMakeFiles/rosbuild_precompile"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/rosbuild_precompile.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
