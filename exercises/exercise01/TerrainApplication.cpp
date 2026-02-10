#include "TerrainApplication.h"

// (todo) 01.1: Include the libraries you need

#define STB_PERLIN_IMPLEMENTATION
#include <stb_perlin.h>

#include <cmath>
#include <iostream>
#include <vector>


// Helper structures. Declared here only for this exercise
struct Vector2
{
    Vector2() : Vector2(0.f, 0.f) {}
    Vector2(float x, float y) : x(x), y(y) {}
    float x, y;
};

struct Vector3
{
    Vector3() : Vector3(0.f,0.f,0.f) {}
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
    float x, y, z;

    Vector3 Normalize() const
    {
        float length = std::sqrt(1 + x * x + y * y);
        return Vector3(x / length, y / length, z / length);
    }
};

// (todo) 01.8: Declare an struct with the vertex format
struct Vertex
{
    Vector3 position;  // location 0
    Vector2 texCoord;  // location 1
    Vector3 color;     // location 2
    Vector3 normal;    // location 3
};


TerrainApplication::TerrainApplication()
    : Application(1024, 1024, "Terrain demo"), m_gridX(16), m_gridY(16), m_shaderProgram(0)
{
}

void TerrainApplication::Initialize()
{
    Application::Initialize();

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Build shaders and store in m_shaderProgram
    BuildShaders();

    // Exercise 01.1
    #pragma region
    // (todo) 01.1: Create containers for the vertex position
    // std::vector<Vector3> v3_container;
    // std::vector<Vector2> v2_container; 

    // float scaleX = 1.0f / (float)m_gridX;
    // float scaleY = 1.0f / (float)m_gridY;

    // for (unsigned int y = 0; y < m_gridY; y++)
    // {
    //     for (unsigned int x = 0; x < m_gridX; x++)
    //     {
    //         // Vector 2
    //         Vector2 v2_bot_left  = Vector2(0.0f, 0.0f);
    //         Vector2 v2_top_left  = Vector2(0.0f, 1.0f);
    //         Vector2 v2_bot_right = Vector2(1.0f, 0.0f);
    //         Vector2 v2_top_right = Vector2(1.0f, 1.0f);

    //         v2_container.push_back(v2_bot_left);
    //         v2_container.push_back(v2_top_left);
    //         v2_container.push_back(v2_top_right);

    //         v2_container.push_back(v2_bot_left);
    //         v2_container.push_back(v2_top_right);
    //         v2_container.push_back(v2_bot_right);

    //         // Vector 3
    //         float fx  = (float)x * scaleX - 0.5f;
    //         float fy  = (float)y * scaleY - 0.5f;
    //         float fx1 = ((float)x + 1.0f) * scaleX - 0.5f;
    //         float fy1 = ((float)y + 1.0f) * scaleY - 0.5f;

    //         Vector3 bottom_left  = Vector3(fx,  fy,  0.0f);
    //         Vector3 top_left     = Vector3(fx,  fy1, 0.0f);
    //         Vector3 top_right    = Vector3(fx1, fy1, 0.0f);
    //         Vector3 bottom_right = Vector3(fx1, fy,  0.0f);

    //         v3_container.push_back(bottom_left);
    //         v3_container.push_back(top_left);
    //         v3_container.push_back(top_right);

    //         v3_container.push_back(bottom_left);
    //         v3_container.push_back(top_right);
    //         v3_container.push_back(bottom_right);
    //     }
    // }

    // // (todo) 01.1: Initialize VAO, and VBO
    // vao.Bind();
    // vbo.Bind();
    
    // // 0.1.4.4: 
    // //Calculate size of v3_container and v2_container
    // const size_t positionBytes = v3_container.size() * sizeof(Vector3);
    // const size_t textureBytes  = v2_container.size() * sizeof(Vector2);

    // // A single AllocateData, because otherwise second AllocateData call overwrites first AllocateData call 
    // vbo.AllocateData(positionBytes + textureBytes, BufferObject::Usage::StaticDraw);

    // vbo.UpdateData<Vector3>(v3_container, 0);
    // vbo.UpdateData<Vector2>(v2_container, positionBytes);

    // VertexAttribute position(Data::Type::Float, 3);
    // VertexAttribute texture(Data::Type::Float, 2);
    
    // vao.SetAttribute(0, position, 0, 0);
    // vao.SetAttribute(1, texture, positionBytes, 0);

    #pragma endregion

    // Exercise 01.5
    #pragma region
    // std::vector<Vector3> v3_container;
    // std::vector<Vector2> v2_container; 
    // std::vector<unsigned int> indices;

    // float scaleX = 1.0f / (float)m_gridX;
    // float scaleY = 1.0f / (float)m_gridY;

    // unsigned int columnCount = m_gridX + 1;
    // unsigned int rowCount = m_gridY + 1;

    // // Loop to define the grid
    // for (unsigned int y = 0; y < rowCount; y++)
    // {
    //     for (unsigned int x = 0; x < columnCount; x++)
    //     {
    //         float fx = (float)x * scaleX - 0.5f;
    //         float fy = (float)y * scaleY - 0.5f;

    //         Vector3 position_coord = Vector3(fx, fy, 0.0f);
    //         Vector2 texture_coord  = Vector2(x, y);

    //         v3_container.push_back(position_coord);
    //         v2_container.push_back(texture_coord);
    //     }
    // }

    // // Loop to populate indices
    // for (unsigned int y = 0; y < m_gridY; y++)
    // {
    //     for (unsigned int x = 0; x < m_gridX - 1; x++)
    //     {
    //         unsigned int bot_left  = (  x      +  y      * (m_gridX + 1));
    //         unsigned int top_left  = (  x      + (y + 1) * (m_gridX + 1));
    //         unsigned int top_right = ( (x + 1) + (y + 1) * (m_gridX + 1));
    //         unsigned int bot_right = ( (x + 1) +  y      * (m_gridX + 1));

    //         indices.push_back(bot_left);
    //         indices.push_back(top_left);
    //         indices.push_back(top_right);

    //         indices.push_back(top_right);
    //         indices.push_back(bot_left);
    //         indices.push_back(bot_right);
    //     }
    // }


    // // (todo) 01.5: Initialize EBO
    // vao.Bind();
    // vbo.Bind();
    

    // // //Calculate size of v3_container and v2_container
    // const size_t positionBytes = v3_container.size() * sizeof(Vector3);
    // const size_t textureBytes  = v2_container.size() * sizeof(Vector2);

    // // // A single AllocateData, because otherwise second AllocateData call overwrites first AllocateData call 
    // vbo.AllocateData(positionBytes + textureBytes, BufferObject::Usage::StaticDraw);
    // vbo.UpdateData<Vector3>(v3_container, 0);
    // vbo.UpdateData<Vector2>(v2_container, positionBytes);

    // // Create Attributes
    // VertexAttribute position(Data::Type::Float, 3);
    // VertexAttribute texture(Data::Type::Float, 2);

    // // Assign Attributes
    // vao.SetAttribute(0, position, 0, 0);
    // vao.SetAttribute(1, texture, positionBytes, 0);

    // // Bind EBO
    // ebo.Bind();

    // // AllocateData (The space needed to contain the data)
    // std::span<const std::byte> indices_bytes = std::as_bytes(std::span(indices));
    // ebo.AllocateData(indices_bytes, BufferObject::Usage::StaticDraw);

    // // (todo) 01.1: Unbind VAO, and VBO
    // vao.Unbind();
    // vbo.Unbind();
    
    // // (todo) 01.5: Unbind EBO
    // ebo.Unbind();
    #pragma endregion

    // Exercise 01.6
    #pragma region

    // std::vector<Vector3> v3_container;
    // std::vector<Vector2> v2_container; 
    // std::vector<unsigned int> indices;

    // float scaleX = 1.0f / (float)m_gridX;
    // float scaleY = 1.0f / (float)m_gridY;

    // unsigned int columnCount = m_gridX + 1;
    // unsigned int rowCount = m_gridY + 1;

    // // Loop to define the grid
    // for (unsigned int y = 0; y < rowCount; y++)
    // {
    //     for (unsigned int x = 0; x < columnCount; x++)
    //     {
    //         float fx = (float)x * scaleX - 0.5f;
    //         float fy = (float)y * scaleY - 0.5f;


    //         float height = stb_perlin_fbm_noise3(fx, fy, 2.0f, 2.0f, 0.5f, 6);


    //         Vector3 position_coord = Vector3(fx, fy, height);
    //         Vector2 texture_coord  = Vector2(x, y);

    //         v3_container.push_back(position_coord);
    //         v2_container.push_back(texture_coord);
    //     }
    // }

    // // Loop to populate indices
    // for (unsigned int y = 0; y < m_gridY; y++)
    // {
    //     for (unsigned int x = 0; x < m_gridX - 1; x++)
    //     {
    //         unsigned int bot_left  = (  x      +  y      * (m_gridX + 1));
    //         unsigned int top_left  = (  x      + (y + 1) * (m_gridX + 1));
    //         unsigned int top_right = ( (x + 1) + (y + 1) * (m_gridX + 1));
    //         unsigned int bot_right = ( (x + 1) +  y      * (m_gridX + 1));

    //         indices.push_back(bot_left);
    //         indices.push_back(top_left);
    //         indices.push_back(top_right);

    //         indices.push_back(top_right);
    //         indices.push_back(bot_left);
    //         indices.push_back(bot_right);
    //     }
    // }


    // // (todo) 01.5: Initialize EBO
    // vao.Bind();
    // vbo.Bind();
    

    // // //Calculate size of v3_container and v2_container
    // const size_t positionBytes = v3_container.size() * sizeof(Vector3);
    // const size_t textureBytes  = v2_container.size() * sizeof(Vector2);

    // // // A single AllocateData, because otherwise second AllocateData call overwrites first AllocateData call 
    // vbo.AllocateData(positionBytes + textureBytes, BufferObject::Usage::StaticDraw);
    // vbo.UpdateData<Vector3>(v3_container, 0);
    // vbo.UpdateData<Vector2>(v2_container, positionBytes);

    // // Create Attributes
    // VertexAttribute position(Data::Type::Float, 3);
    // VertexAttribute texture(Data::Type::Float, 2);

    // // Assign Attributes
    // vao.SetAttribute(0, position, 0, 0);
    // vao.SetAttribute(1, texture, positionBytes, 0);

    // // Bind EBO
    // ebo.Bind();

    // // AllocateData (The space needed to contain the data)
    // std::span<const std::byte> indices_bytes = std::as_bytes(std::span(indices));
    // ebo.AllocateData(indices_bytes, BufferObject::Usage::StaticDraw);

    // // (todo) 01.1: Unbind VAO, and VBO
    // vao.Unbind();
    // vbo.Unbind();
    
    // // (todo) 01.5: Unbind EBO
    // ebo.Unbind();

    #pragma endregion

    // Exercise 01.7
    #pragma region

    // std::vector<Vector3> v3_container;
    // std::vector<Vector2> v2_container;
    // std::vector<Vector3> v3_colors; 
    // std::vector<unsigned int> indices;

    // float scaleX = 1.0f / (float)m_gridX;
    // float scaleY = 1.0f / (float)m_gridY;

    // unsigned int columnCount = m_gridX + 1;
    // unsigned int rowCount = m_gridY + 1;

    // // Loop to define the grid
    // for (unsigned int y = 0; y < rowCount; y++)
    // {
    //     for (unsigned int x = 0; x < columnCount; x++)
    //     {
    //         float fx = (float)x * scaleX - 0.5f;
    //         float fy = (float)y * scaleY - 0.5f;

    //         float height = stb_perlin_fbm_noise3(fx, fy, 2.0f, 2.0f, 0.5f, 6);

    //         // Pick color based on height
    //         Vector3 color;

    //         if (height < -0.20f)
    //             color = Vector3(0.10f, 0.12f, 0.35f);   // water (deep)
    //         else if (height < -0.05f)
    //             color = Vector3(0.80f, 0.72f, 0.55f);   // sand / beach
    //         else if (height < 0.25f)
    //             color = Vector3(0.10f, 0.45f, 0.15f);   // grass
    //         else if (height < 0.55f)                    
    //             color = Vector3(0.35f, 0.35f, 0.38f);    // rock      
    //         else
    //             color = Vector3(0.95f, 0.95f, 0.95f);   // snow

    //         Vector3 position_coord = Vector3(fx, fy, height);
    //         Vector2 texture_coord  = Vector2(x, y);
    //         Vector3 color_coord    = color;

    //         v3_container.push_back(position_coord);
    //         v2_container.push_back(texture_coord);
    //         v3_colors.push_back(color_coord);
    //     }
    // }

    // // Loop to populate indices
    // for (unsigned int y = 0; y < m_gridY; y++)
    // {
    //     for (unsigned int x = 0; x < m_gridX - 1; x++)
    //     {
    //         unsigned int bot_left  = (  x      +  y      * (m_gridX + 1));
    //         unsigned int top_left  = (  x      + (y + 1) * (m_gridX + 1));
    //         unsigned int top_right = ( (x + 1) + (y + 1) * (m_gridX + 1));
    //         unsigned int bot_right = ( (x + 1) +  y      * (m_gridX + 1));

    //         indices.push_back(bot_left);
    //         indices.push_back(top_left);
    //         indices.push_back(top_right);

    //         indices.push_back(top_right);
    //         indices.push_back(bot_left);
    //         indices.push_back(bot_right);
    //     }
    // }


    // // (todo) 01.5: Initialize EBO
    // vao.Bind();
    // vbo.Bind();
    

    // // //Calculate size of v3_container and v2_container
    // const size_t positionBytes = v3_container.size() * sizeof(Vector3);
    // const size_t textureBytes  = v2_container.size() * sizeof(Vector2);
    // const size_t colorBytes    = v3_colors.size()    * sizeof(Vector3);

    // // // A single AllocateData, because otherwise second AllocateData call overwrites first AllocateData call 
    // vbo.AllocateData(positionBytes + textureBytes + colorBytes, BufferObject::Usage::StaticDraw);
    // vbo.UpdateData<Vector3>(v3_container, 0);
    // vbo.UpdateData<Vector2>(v2_container, positionBytes);
    // vbo.UpdateData<Vector3>(v3_colors, (positionBytes + textureBytes));

    // // Create Attributes
    // VertexAttribute position(Data::Type::Float, 3);
    // VertexAttribute texture(Data::Type::Float, 2);
    // VertexAttribute color(Data::Type::Float, 3);

    // // Assign Attributes
    // vao.SetAttribute(0, position, 0, 0);
    // vao.SetAttribute(1, texture, positionBytes, 0);
    // vao.SetAttribute(2, color, (positionBytes + textureBytes), 0);

    // // Bind EBO
    // ebo.Bind();

    // // AllocateData (The space needed to contain the data)
    // std::span<const std::byte> indices_bytes = std::as_bytes(std::span(indices));
    // ebo.AllocateData(indices_bytes, BufferObject::Usage::StaticDraw);

    // // (todo) 01.1: Unbind VAO, and VBO
    // vao.Unbind();
    // vbo.Unbind();
    
    // // (todo) 01.5: Unbind EBO
    // ebo.Unbind();

    #pragma endregion

    // Exercise 01.8
    #pragma region

    // std::vector<Vertex> vertices;
    // std::vector<unsigned int> indices;

    // float scaleX = 1.0f / (float)m_gridX;
    // float scaleY = 1.0f / (float)m_gridY;

    // unsigned int columnCount = m_gridX + 1;
    // unsigned int rowCount = m_gridY + 1;

    // // Loop to define the grid
    // for (unsigned int y = 0; y < rowCount; y++)
    // {
    //     for (unsigned int x = 0; x < columnCount; x++)
    //     {
    //         float fx = (float)x * scaleX - 0.5f;
    //         float fy = (float)y * scaleY - 0.5f;

    //         float height = stb_perlin_fbm_noise3(fx, fy, 2.0f, 2.0f, 0.5f, 6);

    //         // Pick color based on height
    //         Vector3 color;

    //         if (height < -0.20f)
    //             color = Vector3(0.10f, 0.12f, 0.35f);   // water (deep)
    //         else if (height < -0.05f)
    //             color = Vector3(0.80f, 0.72f, 0.55f);   // sand / beach
    //         else if (height < 0.25f)
    //             color = Vector3(0.10f, 0.45f, 0.15f);   // grass
    //         else if (height < 0.55f)                    
    //             color = Vector3(0.35f, 0.35f, 0.38f);    // rock      
    //         else
    //             color = Vector3(0.95f, 0.95f, 0.95f);   // snow

    //         Vector3 position_coord = Vector3(fx, fy, height);
    //         Vector2 texture_coord  = Vector2(x, y);
    //         Vector3 color_coord    = color;

    //         Vertex v;
    //         v.position = Vector3(fx, fy, height);
    //         v.texCoord = Vector2( (float)x, (float)y );
    //         v.color = color;

    //         vertices.push_back(v);
    //     }
    // }

    // // Loop to populate indices
    // for (unsigned int y = 0; y < m_gridY; y++)
    // {
    //     for (unsigned int x = 0; x < m_gridX - 1; x++)
    //     {
    //         unsigned int bot_left  = (  x      +  y      * (m_gridX + 1));
    //         unsigned int top_left  = (  x      + (y + 1) * (m_gridX + 1));
    //         unsigned int top_right = ( (x + 1) + (y + 1) * (m_gridX + 1));
    //         unsigned int bot_right = ( (x + 1) +  y      * (m_gridX + 1));

    //         indices.push_back(bot_left);
    //         indices.push_back(top_left);
    //         indices.push_back(top_right);

    //         indices.push_back(top_right);
    //         indices.push_back(bot_left);
    //         indices.push_back(bot_right);
    //     }
    // }


    // // (todo) 01.5: Initialize EBO
    // vao.Bind();
    // vbo.Bind();
    
    // // Calculate size of 'vertices' vector
    // std::span<const std::byte> vertices_bytesize = std::as_bytes(std::span(vertices));

    // // single AllocateData
    // vbo.AllocateData(vertices_bytesize, BufferObject::Usage::StaticDraw);

    // // Create Attributes
    // VertexAttribute position(Data::Type::Float, 3);
    // VertexAttribute texture(Data::Type::Float, 2);
    // VertexAttribute color(Data::Type::Float, 3);

    // const size_t vertex_offset = sizeof(Vertex);

    // // Assign Attributes
    // vao.SetAttribute(0, position, offsetof(Vertex, position), vertex_offset);
    // vao.SetAttribute(1, texture,  offsetof(Vertex, texCoord), vertex_offset);
    // vao.SetAttribute(2, color,    offsetof(Vertex, color),    vertex_offset);

    // // Bind EBO
    // ebo.Bind();

    // // AllocateData (The space needed to contain the data)
    // std::span<const std::byte> indices_bytes = std::as_bytes(std::span(indices));
    // ebo.AllocateData(indices_bytes, BufferObject::Usage::StaticDraw);

    // // (todo) 01.1: Unbind VAO, and VBO
    // vao.Unbind();
    // vbo.Unbind();
    
    // // (todo) 01.5: Unbind EBO
    // ebo.Unbind();

    #pragma endregion

    // Exercise 01.9
    #pragma region

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    float scaleX = 1.0f / (float)m_gridX;
    float scaleY = 1.0f / (float)m_gridY;

    unsigned int columnCount = m_gridX + 1;
    unsigned int rowCount = m_gridY + 1;

    // Loop to create vertices
    for (unsigned int y = 0; y < rowCount; y++)
    {
        for (unsigned int x = 0; x < columnCount; x++)
        {
            float fx = (float)x * scaleX - 0.5f;
            float fy = (float)y * scaleY - 0.5f;

            float height = stb_perlin_fbm_noise3(fx, fy, 2.0f, 2.0f, 0.5f, 6);

            // Pick color based on height
            Vector3 color;

            if (height < -0.20f)
                color = Vector3(0.10f, 0.12f, 0.35f);   // water (deep)
            else if (height < -0.05f)
                color = Vector3(0.80f, 0.72f, 0.55f);   // sand / beach
            else if (height < 0.25f)
                color = Vector3(0.10f, 0.45f, 0.15f);   // grass
            else if (height < 0.55f)                    
                color = Vector3(0.35f, 0.35f, 0.38f);    // rock      
            else
                color = Vector3(0.95f, 0.95f, 0.95f);   // snow

            Vector3 position_coord = Vector3(fx, fy, height);
            Vector2 texture_coord  = Vector2(x, y);
            Vector3 color_coord    = color;

            Vertex v;
            v.position = Vector3(fx, fy, height);
            v.texCoord = Vector2( (float)x, (float)y );
            v.color = color;
            v.normal = Vector3(0,0,0);

            vertices.push_back(v);
        }
    }

    // Loop to calculate normals (for lighting)
    for (unsigned int y = 0; y < rowCount; y++)
    {
        for (unsigned int x = 0; x < columnCount; x++)
        {
            // Get index, keeping edge cases in mind
            unsigned int l = (x > 0)               ?   x - 1   :   x;
            unsigned int r = (x + 1 < columnCount) ?   x + 1   :   x;
            unsigned int d = (y > 0)               ?   y - 1   :   y;
            unsigned int u = (y + 1 < rowCount)    ?   y + 1   :   y;

            // Get current vertex and surrounding vertices
            Vertex current = vertices.at( x + y * columnCount );
            Vertex left    = vertices.at( l + y * columnCount );
            Vertex right   = vertices.at( r + y * columnCount );
            Vertex down    = vertices.at( x + d * columnCount );
            Vertex up      = vertices.at( x + u * columnCount );

            // Calculate deltaX and deltaY
            float deltaX = (right.position.z - left.position.z) / (right.position.x - left.position.x);
            float deltaY = (up.position.z - down.position.z) / (up.position.y - down.position.y);

            // Create normal
            Vector3 normal = Vector3(deltaX, deltaY, 1).Normalize();

            current.normal = normal;
            vertices.at(x + y * columnCount) = current; 
        }
    }

    // Loop to populate indices
    for (unsigned int y = 0; y < m_gridY; y++)
    {
        for (unsigned int x = 0; x < m_gridX - 1; x++)
        {
            unsigned int bot_left  = (  x      +  y      * (m_gridX + 1));
            unsigned int top_left  = (  x      + (y + 1) * (m_gridX + 1));
            unsigned int top_right = ( (x + 1) + (y + 1) * (m_gridX + 1));
            unsigned int bot_right = ( (x + 1) +  y      * (m_gridX + 1));

            indices.push_back(bot_left);
            indices.push_back(top_left);
            indices.push_back(top_right);

            indices.push_back(top_right);
            indices.push_back(bot_left);
            indices.push_back(bot_right);
        }
    }


    // (todo) 01.5: Initialize EBO
    vao.Bind();
    vbo.Bind();
    
    // Calculate size of 'vertices' vector
    std::span<const std::byte> vertices_bytesize = std::as_bytes(std::span(vertices));

    // single AllocateData
    vbo.AllocateData(vertices_bytesize, BufferObject::Usage::StaticDraw);

    // Create Attributes
    VertexAttribute position(Data::Type::Float, 3);
    VertexAttribute texture(Data::Type::Float, 2);
    VertexAttribute color(Data::Type::Float, 3);
    VertexAttribute normal(Data::Type::Float, 3);

    const size_t vertex_offset = sizeof(Vertex);

    // Assign Attributes
    vao.SetAttribute(0, position, offsetof(Vertex, position), vertex_offset);
    vao.SetAttribute(1, texture,  offsetof(Vertex, texCoord), vertex_offset);
    vao.SetAttribute(2, color,    offsetof(Vertex, color),    vertex_offset);
    vao.SetAttribute(3, normal,   offsetof(Vertex, normal),   vertex_offset);

    // Bind EBO
    ebo.Bind();

    // AllocateData (The space needed to contain the data)
    std::span<const std::byte> indices_bytes = std::as_bytes(std::span(indices));
    ebo.AllocateData(indices_bytes, BufferObject::Usage::StaticDraw);

    // (todo) 01.1: Unbind VAO, and VBO
    vao.Unbind();
    vbo.Unbind();
    
    // (todo) 01.5: Unbind EBO
    ebo.Unbind();

    #pragma endregion
}

void TerrainApplication::Update()
{
    Application::Update();

    UpdateOutputMode();
}

void TerrainApplication::Render()
{
    Application::Render();

    // Clear color and depth
    GetDevice().Clear(true, Color(0.0f, 0.0f, 0.0f, 1.0f), true, 1.0f);

    // Set shader to be used
    glUseProgram(m_shaderProgram);

    // (todo) 01.1: Draw the grid
    vao.Bind();
    //int vertexCount = m_gridX * m_gridY * 6;        // 6 vertices per square (2 triangles)
    //glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    
    int indicesCount = 2 * 3 * m_gridX * m_gridY;
    int vertexCount = (m_gridX + 1) * (m_gridY + 1);
    glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
}

void TerrainApplication::Cleanup()
{
    Application::Cleanup();
}


void TerrainApplication::BuildShaders()
{
    const char* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "layout (location = 1) in vec2 aTexCoord;\n"
        "layout (location = 2) in vec3 aColor;\n"
        "layout (location = 3) in vec3 aNormal;\n"
        "uniform mat4 Matrix = mat4(1);\n"
        "out vec2 texCoord;\n"
        "out vec3 color;\n"
        "out vec3 normal;\n"
        "void main()\n"
        "{\n"
        "   texCoord = aTexCoord;\n"
        "   color = aColor;\n"
        "   normal = aNormal;\n"
        "   gl_Position = Matrix * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
    const char* fragmentShaderSource = "#version 330 core\n"
        "uniform uint Mode = 0u;\n"
        "in vec2 texCoord;\n"
        "in vec3 color;\n"
        "in vec3 normal;\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   switch (Mode)\n"
        "   {\n"
        "   default:\n"
        "   case 0u:\n"
        "       FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
        "       break;\n"
        "   case 1u:\n"
        "       FragColor = vec4(fract(texCoord), 0.0f, 1.0f);\n"
        "       break;\n"
        "   case 2u:\n"
        "       FragColor = vec4(color, 1.0f);\n"
        "       break;\n"
        "   case 3u:\n"
        "       FragColor = vec4(normalize(normal), 1.0f);\n"
        "       break;\n"
        "   case 4u:\n"
        "       FragColor = vec4(color * max(dot(normalize(normal), normalize(vec3(1,0,1))), 0.2f), 1.0f);\n"
        "       break;\n"
        "   }\n"
        "}\n\0";

    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    m_shaderProgram = shaderProgram;
}

void TerrainApplication::UpdateOutputMode()
{
    for (int i = 0; i <= 4; ++i)
    {
        if (GetMainWindow().IsKeyPressed(GLFW_KEY_0 + i))
        {
            int modeLocation = glGetUniformLocation(m_shaderProgram, "Mode");
            glUseProgram(m_shaderProgram);
            glUniform1ui(modeLocation, i);
            break;
        }
    }
    if (GetMainWindow().IsKeyPressed(GLFW_KEY_TAB))
    {
        const float projMatrix[16] = { 0, -1.294f, -0.721f, -0.707f, 1.83f, 0, 0, 0, 0, 1.294f, -0.721f, -0.707f, 0, 0, 1.24f, 1.414f };
        int matrixLocation = glGetUniformLocation(m_shaderProgram, "Matrix");
        glUseProgram(m_shaderProgram);
        glUniformMatrix4fv(matrixLocation, 1, false, projMatrix);
    }
}