#pragma once
#include "VK.h"
#include "Graphics/API/Pipeline.h"
#include "VKDescriptorSet.h"

namespace Lumos
{
	class Shader;

	namespace Graphics
	{
		class VKCommandBuffer;

		class VKPipeline : public Pipeline
		{
		public:
			VKPipeline();
			VKPipeline(const PipelineInfo& pipelineCI);
			~VKPipeline();

			bool Init(const PipelineInfo& pipelineCI);

			void Unload() const;
			void SetActive(Graphics::CommandBuffer* cmdBuffer) override;
			vk::DescriptorSet CreateDescriptorSet();

			vk::DescriptorSetLayout* GetDescriptorLayout(int id) { return &m_DescriptorLayouts[id]; };
			
			vk::DescriptorPool  GetDescriptorPool() const { return m_DescriptorPool; };
			vk::PipelineLayout  GetPipelineLayout() const { return m_PipelineLayout; };
			std::string 		GetPipelineName() 	const { return m_PipelineName; };
			vk::Pipeline 		GetPipeline() 		const { return m_Pipeline; }
			DescriptorSet*		GetDescriptorSet()	const override { return m_DescriptorSet; }
			Shader*				GetShader()			const override { return m_Shader; }

		private:
		
			vk::VertexInputBindingDescription 	m_VertexBindingDescription;
			vk::PipelineLayout 					m_PipelineLayout;
			vk::DescriptorPool 					m_DescriptorPool;
			vk::Pipeline 						m_Pipeline;
			std::vector<vk::DescriptorSetLayout>m_DescriptorLayouts;
			std::string 						m_PipelineName;
			DescriptorSet*						m_DescriptorSet = nullptr;
			Shader*								m_Shader = nullptr;

		};
	}
}


