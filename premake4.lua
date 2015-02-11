solution "raytracer"
  configurations {"Debug", "DebugOMP", "Release", "ReleaseOMP"}

  project "raytracer"
    kind "ConsoleApp"
    language "C++"
    files {"**.h", "**.cpp", "**.cc"}
    includedirs {"raytracer/"}
    targetdir ("bin/")
    
    configuration "Debug or DebugOMP"
      defines {"DEBUG", "_DEBUG"}
      flags {"Symbols"}

    configuration "Release or ReleaseOMP"
      defines {"NDEBUG", "_RELEASE"}
      flags {"Optimize"}

--[[  configuration "windows"
      defines {"RT_WINDOWS"}
      links {"opengl32", "glu32", "thirdpart/glut/glut32"}
]]--
    configuration "linux"
      defines {"RT_LINUX"}
      excludes {"thirdpart/glut/glut.h"}
      buildoptions {"-std=c++11"}
      links {"GL", "GLU", "glut"}
    
    configuration "macosx"
      defines {"RT_MACOSX"}
      excludes {"thirdpart/glut/glut.h"}
      buildoptions {"-std=c++11", "-Wno-deprecated-declarations"}
      links {"OpenGL.framework", "GLUT.framework"}

    configuration {"linux or macosx", "DebugOMP or ReleaseOMP"}
      linkoptions {"-fopenmp"}


