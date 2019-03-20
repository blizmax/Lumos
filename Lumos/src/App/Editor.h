#pragma once
#include "Maths/Vector2.h"

namespace Lumos
{
	class Application;
	class Entity;
	class Console;

	class Editor
	{
		friend class Application;
	public:
		Editor(Application* app, uint width, uint height);
		~Editor();

		void OnImGui();
		void DrawConsole();
		void DrawMenuBar();
		void DrawHierarchyWindow();
		void DrawEngineInfoWindow();
		void DrawInspectorWindow();
		void DrawSceneView();
		void DrawSceneInfoWindow();
		void AddDockSpace();

		void SelectEntity();

		uint GetImGuizmoOperation() const { return m_ImGuizmoOperation; }

	private:
		Application* m_Application;
		Console* m_Console;

		maths::Vector2 m_SceneViewSize;
		maths::Vector2 m_SceneViewPosition;
		uint m_ImGuizmoOperation = 0;
		bool m_FlipImGuiImage = false;
		Entity* m_Selected = nullptr;
	};
}
