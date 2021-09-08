project "imgui"
	kind "StaticLib"
	language "C++"
	staticruntime "on"

	architecture "x64"

	targetdir "bin"
	objdir "obj"

	includedirs {
		"include",
		"../glfw/include"
	}

	files {
		"include/**.h",
		"src/**.cpp"
	}

	filter "configurations:debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:release"
		runtime "Release"
		optimize "on"
