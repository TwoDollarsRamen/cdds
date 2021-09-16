#include "EntityDisplayApp.h"

EntityDisplayApp::EntityDisplayApp(int screenWidth, int screenHeight) : m_screenWidth(screenWidth), m_screenHeight(screenHeight) {

}

EntityDisplayApp::~EntityDisplayApp() {
	CloseHandle(handle);
}

bool EntityDisplayApp::Startup() {

	InitWindow(m_screenWidth, m_screenHeight, "EntityDisplayApp");
	SetTargetFPS(60);

	handle = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, L"EntityMemory");
	if (!handle) { return false; }

	void* data = MapViewOfFile(handle, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(int));

	int count = *(int*)data;
	Entity* entities = (Entity*)((int*)data + 1);

	for (int i = 0; i < count; i++) {
		m_entities.push_back(entities[i]);
	}

	UnmapViewOfFile(data);

	return true;
}

void EntityDisplayApp::Shutdown() {

	CloseWindow();        // Close window and OpenGL context
}

void EntityDisplayApp::Update(float deltaTime) {
	void* data = MapViewOfFile(handle, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(int));

	int count = *(int*)data;
	Entity* entities = (Entity*)((int*)data + 1);

	for (int i = 0; i < count; i++) {
		m_entities[i] = entities[i];
	}

	UnmapViewOfFile(data);
}

void EntityDisplayApp::Draw() {
	BeginDrawing();

	ClearBackground(RAYWHITE);

	// draw entities
	for (auto& entity : m_entities) {
		DrawRectanglePro(
			Rectangle{ entity.x, entity.y, entity.size, entity.size }, // rectangle
			Vector2{ entity.size / 2, entity.size / 2 }, // origin
			entity.rotation,
			Color{ entity.r, entity.g, entity.b, 255 });
	}

	// output some text, uses the last used colour
	DrawText("Press ESC to quit", 630, 15, 12, LIGHTGRAY);

	EndDrawing();
}