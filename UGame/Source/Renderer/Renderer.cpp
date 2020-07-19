#include "Renderer.h"
#include "RenderCommand.h"
#include "OrthographicCamera.h"


namespace UGame
{
	Renderer::SceneData* Renderer::sceneData = new SceneData;

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		sceneData->viewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader> shader, const glm::mat4& transform)
	{
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", sceneData->viewProjectionMatrix);
		shader->UploadUniformMat4("u_Transform", transform);
		
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}
