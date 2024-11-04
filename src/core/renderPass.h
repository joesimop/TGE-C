#pragma once

#include "global.h"


void create_render_pass(VulkanCore* core);

VkAttachmentDescription create_render_attachment(VulkanCore* core);
VkSubpassDescription create_render_sub_pass();
VkSubpassDependency create_subpass_dependency();
