solution "raytracer"
  configurations {"Debug", "Release"}
  language "C++"
  startproject "raytracer"

  configuration "Debug"
    defines { "DEBUG" }
    flags { "Symbols"}
    targetsuffix "_d"

  configuration "Release"
    defines { "NDEBUG" }
    flags { "Optimize"}

  project "raytracer"
    kind "ConsoleApp"
    includedirs {"raytracer/", "thirdpart/"}
    targetdir ("bin/")
    libdirs {"lib/"}
    files {
        "raytracer/**.h",
        "raytracer/**.cpp",
    }

    configuration "Debug"
      defines { "DEBUG" }
      flags { "Symbols"}
      targetsuffix "_d"
      links { "glfw_d" }

    configuration "Release"
      defines { "NDEBUG" }
      flags { "Optimize"}
      links { "glfw" }

    configuration "windows"
      defines { "_CRT_SECURE_NO_WARNINGS" }
      links {"opengl32.lib"}

    configuration "macosx"
      buildoptions {"-std=c++11", "-Wno-deprecated-declarations"}
      links {"Cocoa.framework", "OpenGL.framework", "IOKit.framework", "CoreVideo.framework", "Carbon.framework"}

  project "glfw"
      kind "StaticLib"
      targetdir ("lib/")
      includedirs {"thirdpart/glfw/"}

      files {
          "thirdpart/glfw/include/GLFW/*.h",
          "thirdpart/glfw/src/context.c",
          "thirdpart/glfw/src/init.c",
          "thirdpart/glfw/src/input.c",
          "thirdpart/glfw/src/monitor.c",
          "thirdpart/glfw/src/window.c",
      }

      defines {"_GLFW_USE_OPENGL"}

      configuration "windows"
        defines { "_GLFW_WIN32", "_GLFW_WGL", "_CRT_SECURE_NO_WARNINGS" }
        files {
            "thirdpart/glfw/src/win32*.c",
            "thirdpart/glfw/src/wgl_context.c",
            "thirdpart/glfw/src/egl_context.c",
            "thirdpart/glfw/src/osmesa_context.c",
            "thirdpart/glfw/src/vulkan.c",
        }

      configuration "macosx"
        defines { "_GLFW_COCOA", "_GLFW_NSGL" }
        files {
            "thirdpart/glfw/src/cocoa*.m",
            "thirdpart/glfw/src/cocoa*.c",
            "thirdpart/glfw/src/posix_thread.c",
            "thirdpart/glfw/src/nsgl_context.m",
            "thirdpart/glfw/src/egl_context.c",
            "thirdpart/glfw/src/osmesa_context.c",
            "thirdpart/glfw/src/vulkan.c",
        }

