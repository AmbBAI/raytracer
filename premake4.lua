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
      defines {"WINDOWS"}
      links {"opengl32", "glu32", "thirdpart/glut/glut32"}
]]--
    configuration "linux"
      defines {"LINUX"}
      excludes {"thirdpart/glut/glut.h"}
      buildoptions {"-std=c++11"}
      links {"GL", "GLU", "glut"}
    
    configuration "macosx"
      defines {"MACOSX"}
      excludes {"thirdpart/glut/glut.h"}

    configuration {"linux or macosx", "DebugOMP or ReleaseOMP"}
      linkoptions {"-fopenmp"}


