#pragma once

#include <glm/glm.hpp>

namespace UGame
{
	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		void SetProjectionMatrix(const glm::vec3 position)
		{
			this->position = position;
			RecalculateViewMatrix();
		}

		void SetRotation(float rotation)
		{
			this->rotation = rotation;
			RecalculateViewMatrix();
		}

		const glm::mat4& GetProjectionMatrix() const { return projectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return viewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return viewProjectionMatrix; }

	private:
		void RecalculateViewMatrix();
		
		glm::mat4 projectionMatrix;
		glm::mat4 viewMatrix;
		glm::mat4 viewProjectionMatrix;

		glm::vec3 position;
		float rotation;
		
	};
}
