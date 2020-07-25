#pragma once
#include "Renderer/OrthographicCamera.h"
#include "Core/Timestep.h"
#include "UGame/Core.h"

namespace UGame
{
	class Event;
	class WindowResizeEvent;
	class MouseScrolledEvent;
	
	class UGAME_API OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool canRotate = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return camera; }
		const OrthographicCamera& GetCamera() const { return camera; }

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
		
		float aspectRatio;
		float zoomLevel = 1.f;
		
		OrthographicCamera camera;

		bool rotationEnabled = false;

		float cameraTranslationSpeed = 1.f;
		float cameraRotationSpeed = 100.f;
		
		glm::vec3 cameraPosition{0.f};
		float cameraRotation = 0.f;
	};
}
