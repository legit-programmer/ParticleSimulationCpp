workspace "ParticleSimulationC++"
	configurations {"Debug", "Release"}

project "ParticleSimulationC++"
	kind "ConsoleApp"
	language "C++"

	files { "./**.h", "./**.cpp" }

	libdirs { "C:/GL/SDLbin/lib/x86" }

	links {"opengl32", "SDL2", "SDL2main"}

	includedirs {"C:/GL/SDLbin/include", "%{wks.location}/vendor/imgui"}


	filter "configurations:Debug"
		targetdir ("%{wks.location}/bin/Debug")
		defines { "DEBUG" }
		symbols "On"

   filter "configurations:Release"
		targetdir ("%{wks.location}/bin/Release")
		defines { "NDEBUG" }
		optimize "On"