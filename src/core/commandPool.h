#pragma once

#include "global.h"
#include "graphicsPipeline.h"

void create_command_pool(RenderState* renderState);
void create_command_buffer(RenderState* renderState);
void record_command_buffer(RenderState* renderState);
