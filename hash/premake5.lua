project "hash"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"

	architecture "x64"

	targetdir "bin"
	objdir "obj"

	includedirs {
		"include",
	}

	files {
		"include/**.hpp",
		"src/**.cpp"
	}

	filter "configurations:debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:release"
		runtime "Release"
		optimize "on"
