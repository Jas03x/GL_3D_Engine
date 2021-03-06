//
//  StaticMeshRenderer.hpp
//  BobosPuzzle
//
//  Created by Jas S on 2017-05-09.
//  Copyright © 2017 Jas S. All rights reserved.
//

#ifndef StaticMeshRenderer_hpp
#define StaticMeshRenderer_hpp

#include <stdio.h>

#include "Path.h"
#include "Camera.h"
#include "Shader.h"
#include "StaticMesh.h"
#include "DSFramebuffer.h"

class _StaticMeshRenderer : public Shader
{
private:
    GLuint texture_id;
    GLuint vertex_matrix;
    GLuint normal_matrix;
    GLuint materials;
    
    void bindMeshInstance(const StaticMeshInstance& instance);
    
public:
    _StaticMeshRenderer(){}
    void initalize();
    void bind();
    void render(const StaticMesh& mesh, const std::vector<StaticMeshInstance>* instances = NULL);
    void destroy();
};

extern _StaticMeshRenderer StaticMeshRenderer;

#endif /* StaticMeshRenderer_hpp */
