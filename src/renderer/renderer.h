/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 17:14:45 by maldavid          #+#    #+#             */
/*   Updated: 2022/12/18 22:15:50 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __RENDERER__
#define __RENDERER__

#include <array>
#include <vector>
#include <memory>

#include <renderer/core/vk_surface.h>
#include <renderer/core/render_core.h>
#include <renderer/core/vk_semaphore.h>
#include <renderer/pipeline/pipeline.h>
#include <renderer/command/vk_cmd_pool.h>
#include <renderer/command/vk_cmd_buffer.h>
#include <renderer/swapchain/vk_swapchain.h>
#include <renderer/swapchain/vk_render_pass.h>

#include <core/errors.h>

#include <glm/glm.hpp>

namespace mlx
{
	struct Vertex
	{
		glm::vec2 pos;
		glm::vec3 color;

		static VkVertexInputBindingDescription getBindingDescription()
		{
			VkVertexInputBindingDescription bindingDescription{};
			bindingDescription.binding = 0;
			bindingDescription.stride = sizeof(Vertex);
			bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

			return bindingDescription;
		}

		static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions()
		{
			std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions;

			attributeDescriptions[0].binding = 0;
			attributeDescriptions[0].location = 0;
			attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
			attributeDescriptions[0].offset = offsetof(Vertex, pos);

			attributeDescriptions[1].binding = 0;
			attributeDescriptions[1].location = 1;
			attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
			attributeDescriptions[1].offset = offsetof(Vertex, color);

			return attributeDescriptions;
		}
	};

	class Renderer
	{
		public:
			Renderer() = default;

            void init();

            bool beginFrame();
            void endFrame();

			void destroy();
            
			inline class MLX_Window* getWindow() { return _window; }
            inline void setWindow(class MLX_Window* window) { _window = window; }

            inline Surface& getSurface() noexcept { return _surface; }
            inline CmdPool& getCmdPool() noexcept { return _cmd_pool; }
            inline SwapChain& getSwapChain() noexcept { return _swapchain; }
            inline Semaphore& getSemaphore() noexcept { return _semaphore; }
            inline RenderPass& getRenderPass() noexcept { return _pass; }
            inline CmdBuffer& getCmdBuffer(int i) noexcept { return _cmd_buffers[i]; }
            inline CmdBuffer& getActiveCmdBuffer() noexcept { return _cmd_buffers[_active_image_index]; }
            inline uint32_t getActiveImageIndex() noexcept { return _active_image_index; }
            inline uint32_t getImageIndex() noexcept { return _image_index; }

            constexpr inline void requireFrameBufferResize(int index) noexcept { _framebufferResized = true; }

			~Renderer() = default;

		private:
			GraphicPipeline _pipeline;
            RenderPass _pass;
            Surface _surface;
            CmdPool _cmd_pool;
            SwapChain _swapchain;
            Semaphore _semaphore;
            std::array<CmdBuffer, MAX_FRAMES_IN_FLIGHT> _cmd_buffers;

			class MLX_Window* _window;

            uint32_t _active_image_index = 0;
            uint32_t _image_index = 0;
            bool _framebufferResized = false;
	};
}

#endif
