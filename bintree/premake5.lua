project "bintree"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"

	architecture "x64"

	targetdir "bin"
	objdir "obj"

	includedirs {
		"include",
		"../ext/glfw/include",
		"../ext/imgui/include"
	}

	files {
		"include/**.hpp",
		"src/**.cpp"
	}

	links {
		"glfw",
		"imgui"
	}

	filter "configurations:debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:release"
		runtime "Release"
		optimize "on"

	filter "system:linux"
		links {
			"pthread",
			"dl",
			"X11",
			"m",
			"GL",
		}

	filter "system:windows"
		links {
			"opengl32",
			"gdi32",
			"user32",
			"kernel32"
		}
