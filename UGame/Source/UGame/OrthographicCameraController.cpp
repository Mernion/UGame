#include "OrthographicCameraController.h"
#include "Events/KeyCodes.h"
#include "UGame/Input.h"
#include "UGame/Events/MouseEvent.h"
#include "UGame/Events/ApplicationEvent.h"
#include "UGame/Events/Event.h"

namespace UGame
{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool canRotate)
		: aspectRatio(aspectRatio), camera(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel), rotationEnabled(canRotate)
	{
		
	}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		if (Input::IsKeyPressed(UG_KEY_D))
		{
			cameraPosition.x += cameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(UG_KEY_A))
		{
			cameraPosition.x -= cameraTranslationSpeed * ts;
		}

		if (Input::IsKeyPressed(UG_KEY_S))
		{
			cameraPosition.y -= cameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(UG_KEY_W))
		{
			cameraPosition.y += cameraTranslationSpeed * ts;
		}

		if (rotationEnabled)
		{
			if (Input::IsKeyPressed(UG_KEY_Q))
			{
				cameraRotation -= cameraRotationSpeed * ts;
			}

			if (Input::IsKeyPressed(UG_KEY_E))
			{
				cameraRotation += cameraRotationSpeed * ts;
			}

			camera.SetRotation(cameraRotation);
		}

		camera.SetPosition(cameraPosition);
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT(OrthographicCameraController::OnWindowResized));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		zoomLevel -= e.GetY();
		zoomLevel = std::max(zoomLevel, 0.25f);
		camera.SetProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		aspectRatio = (float) e.GetWidth() / (float) e.GetHeight();
		camera.SetProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
		return false;
	}
}
