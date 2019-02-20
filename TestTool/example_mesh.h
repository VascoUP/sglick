#pragma once

#include <assimp/Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include "gl_scene.h"

class example_mesh
{
public:
	static glick::scene::Mesh* get();
};