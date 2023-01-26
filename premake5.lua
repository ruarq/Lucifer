workspace "Lucifer"
	configurations { "debug", "release" }

project "lucifer"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"

	buildoptions { "`pkg-config fmt --cflags`" }
	linkoptions { "`pkg-config fmt --libs`" }

	filter { "system:unix" }
		links { "pthread" }
	filter {}

	files { "src/**.hpp", "src/**.cpp" }

	warnings "High"

	filter { "configurations:debug" }
		symbols "On"
		defines { "DEBUG" }

	filter { "configurations:release" }
		optimize "On"
