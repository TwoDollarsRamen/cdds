workspace "cdds"
	configurations { "debug", "release" }

	startproject "linkedlist"

include "ext/imgui"
include "ext/glfw"

include "linkedlist"
include "listtest"
include "bintree"
include "hash"
