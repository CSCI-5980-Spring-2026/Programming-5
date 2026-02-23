#include <GopherEngine/Renderer/ResourceUploader.hpp>

#include <GL/glew.h>          // Must come first
#include <SFML/OpenGL.hpp>    // After glew

#include <iostream>
using namespace std;

namespace GopherEngine
{
    bool ResourceUploader::upload_mesh(const Mesh& mesh) {

        // Release any existing GPU resources before re-uploading
        if(mesh.vao_ != 0)
            mesh.gpu_release_();

        glGenVertexArrays(1, &mesh.vao_);
        glGenBuffers(1, &mesh.vbo_);
        glGenBuffers(1, &mesh.ebo_);
        
        glBindVertexArray(mesh.vao_);

        // If there is no interleaved vertex data, interleave it into a single buffer: position, normal, uv
        if(mesh.buffer_.empty())
        {
            mesh.buffer_.reserve(mesh.vertices_.size() * 12);  // 3 + 3 + 4 + 2 floats per vertex

            for(size_t i = 0; i < mesh.vertices_.size(); i++)
            {
                mesh.buffer_.push_back(mesh.vertices_[i].x);
                mesh.buffer_.push_back(mesh.vertices_[i].y);
                mesh.buffer_.push_back(mesh.vertices_[i].z);

                if(i < mesh.normals_.size())
                {
                    mesh.buffer_.push_back(mesh.normals_[i].x);
                    mesh.buffer_.push_back(mesh.normals_[i].y);
                    mesh.buffer_.push_back(mesh.normals_[i].z);
                }
                else
                {
                    mesh.buffer_.push_back(0.f);
                    mesh.buffer_.push_back(0.f);
                    mesh.buffer_.push_back(0.f);
                }

                if(i < mesh.colors_.size())
                {
                    mesh.buffer_.push_back(mesh.colors_[i].r);
                    mesh.buffer_.push_back(mesh.colors_[i].g);
                    mesh.buffer_.push_back(mesh.colors_[i].b);
                    mesh.buffer_.push_back(mesh.colors_[i].a);
                }
                else
                {
                    mesh.buffer_.push_back(1.f);
                    mesh.buffer_.push_back(1.f);
                    mesh.buffer_.push_back(1.f);
                    mesh.buffer_.push_back(1.f);
                }

                if(i < mesh.uvs_.size())
                {
                    mesh.buffer_.push_back(mesh.uvs_[i].x);
                    mesh.buffer_.push_back(mesh.uvs_[i].y);
                }
                else
                {
                    mesh.buffer_.push_back(0.f);
                    mesh.buffer_.push_back(0.f);
                }
            }
        }

        glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo_);
        glBufferData(GL_ARRAY_BUFFER, mesh.buffer_.size() * sizeof(float), mesh.buffer_.data(), GL_STATIC_DRAW);

        // Indices
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ebo_);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
                     mesh.indices_.size() * sizeof(unsigned int), 
                     mesh.indices_.data(), 
                     GL_STATIC_DRAW);

        constexpr unsigned int stride = 12 * sizeof(float);  // 3 + 3 + 4 + 2 floats per vertex

        // location 0: position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
        glEnableVertexAttribArray(0);

        // location 1: normal
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // localtion 2: color
        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        // location 3: uv
        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, stride, (void*)(10 * sizeof(float)));
        glEnableVertexAttribArray(3);

        glBindVertexArray(0);

        // Set up GPU release function to clean up buffers when mesh is destroyed
        mesh.gpu_release_ = [&mesh]() {
            if(mesh.vao_ != 0) glDeleteVertexArrays(1, &mesh.vao_);
            if(mesh.vbo_ != 0) glDeleteBuffers(1, &mesh.vbo_);
            if(mesh.ebo_ != 0) glDeleteBuffers(1, &mesh.ebo_);
        };

        if(mesh.vao_ == 0)
        {
            cerr << "Failed to upload geometry to GPU" << endl;
            return false;
        }

        // Clear CPU-side buffer to save memory, since data is now on GPU
        mesh.buffer_.clear();  
        
        return true;
    }

    void ResourceUploader::release_mesh(const Mesh& mesh) {

        if(mesh.vao_ != 0) glDeleteVertexArrays(1, &mesh.vao_);
        if(mesh.vbo_ != 0) glDeleteBuffers(1, &mesh.vbo_);
        if(mesh.ebo_ != 0) glDeleteBuffers(1, &mesh.ebo_);
        mesh.vao_ = mesh.vbo_ = mesh.ebo_ = 0;

    }
}