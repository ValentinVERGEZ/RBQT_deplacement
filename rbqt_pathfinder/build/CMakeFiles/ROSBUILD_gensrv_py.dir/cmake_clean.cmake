FILE(REMOVE_RECURSE
  "../msg_gen"
  "../srv_gen"
  "../src/rbqt_pathfinder/msg"
  "../src/rbqt_pathfinder/srv"
  "../msg_gen"
  "../srv_gen"
  "CMakeFiles/ROSBUILD_gensrv_py"
  "../src/rbqt_pathfinder/srv/__init__.py"
  "../src/rbqt_pathfinder/srv/_GeneratePath.py"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_gensrv_py.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
