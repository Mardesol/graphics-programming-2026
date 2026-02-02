#include <ituGL/core/DeviceGL.h>
#include <ituGL/application/Window.h>
#include <iostream>
#include <cmath>

// Exercise 1
#include <ituGL/geometry/VertexBufferObject.h>
#include <ituGL/geometry/VertexArrayObject.h>
#include <ituGL/geometry/VertexAttribute.h>

// Exercise 00.4.4
#include <ituGL/geometry/ElementBufferObject.h>

int buildShaderProgram();
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;    // Exercise 00.5.1

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    DeviceGL deviceGL;

    // glfw window creation
    // --------------------
    Window window(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL");
    if (!window.IsValid())
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        return -1;
    }

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    deviceGL.SetCurrentWindow(window);
    if (!deviceGL.IsReady())
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // build and compile our shader program
    // ------------------------------------
    int shaderProgram = buildShaderProgram();

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        
        // Exercise 00.3
        // -0.5f, -0.5f, 0.0f, // left  
        //  0.5f, -0.5f, 0.0f, // right 
        //  0.5f,  0.5f, 0.0f,  // top   

        // -0.5f, -0.5f, 0.0f, // left  
        //  -0.5f, 0.5f, 0.0f, // right 
        //  0.5f, 0.5f, 0.0f  // top 

        // Exercise 00.4.1
        // -0.5f, -0.5f, 0.0f,  // 0 bottom-left
        //  0.5f, -0.5f, 0.0f,  // 1 bottom-right
        //  0.5f,  0.5f, 0.0f,  // 2 top-right
        // -0.5f,  0.5f, 0.0f   // 3 top-left

        // Exercise 00.6
        0.0f, 0.0f, 0.0f,   // center
        
    };

    // Exercise 00.4.4
    unsigned int triangles[] = {
        0, 1, 2,
        2, 0, 3
    };

    // unsigned int VBO, VAO;

    // glGenVertexArrays(1, &VAO);
    // glGenBuffers(1, &VBO);
    // // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    // glBindVertexArray(VAO);

    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // glEnableVertexAttribArray(0);

    // // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    // glBindBuffer(GL_ARRAY_BUFFER, 0);

    // // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    // glBindVertexArray(0);


    VertexBufferObject vbo;         // Exercise 00.1.2
    VertexArrayObject vao;          // Exercise 00.1.2
    ElementBufferObject ebo;        // Exercise 00.4.5

    vao.Bind();     // Exercise 00.1.4
    vbo.Bind();     // Exercise 00.1.4
    ebo.Bind();     // Exercise 00.4.7

    ebo.AllocateData<unsigned int>(triangles);
    vbo.AllocateData<float>(vertices);          // Exercise 00.1.5

    // Exercise 00.1.6
    VertexAttribute position = VertexAttribute(Data::Type::Float, 3);
    vao.SetAttribute(0, position, 0);

    vbo.Unbind();   // Exercise 00.1.4
    vao.Unbind();   // Exercise 00.1.4
    ebo.Unbind();   // Exercise 00.4.9

    // Exercise 00.5.4
    float time = 0.0f;                                
    const float rotationSpeed = 0.01f;                 // rad per "time unit"
    const float length = std::sqrt(2.0f) / 2.0f;       // sqrt(2)/2
    const float pi = 3.1415926535f;

    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while (!window.ShouldClose())
    {
        // input
        // -----
        processInput(window.GetInternalWindow());

        // render
        // ------
        deviceGL.Clear(Color(0.2f, 0.3f, 0.3f, 1.0f));

        // draw our first triangle
        glUseProgram(shaderProgram);
        vao.Bind(); //(vao); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //glBindVertexArray(0); // no need to unbind it every time 

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        window.SwapBuffers();
        deviceGL.PollEvents();

        time = time + 0.1f;                 
        float angle = time * rotationSpeed;

        float a0 = angle + pi * 0.25f;

        for (int i = 0; i < 4; ++i)
        {
            float base = a0 + i * (pi * 0.5f);
            vertices[i * 3 + 0] = std::sin(base) * length;  // Update vertex column 1
            vertices[i * 3 + 1] = std::cos(base) * length;  // Update vertex column 2
            vertices[i * 3 + 2] = 0.0f;                     // keep z = 0
        }

        vbo.Bind();
        vbo.UpdateData<float>(vertices);
        vbo.Unbind();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    // glDeleteVertexArrays(1, &VAO);
    // glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    // This is now done in the destructor of DeviceGL
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// build the shader program
// ------------------------
int buildShaderProgram() 
{
    const char* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
    const char* fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
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
    return shaderProgram;
}