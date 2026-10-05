#include "../include/index_buffer.h"
#include "../include/main.h"
#include "../include/opengl_error.h"
#include "../include/renderer.h"
#include "../include/shader.h"
#include "../include/solid.h"
#include "../include/texture.h"
#include "../include/vertex_array.h"
#include "../include/vertex_buffer.h"
#include <GLFW/glfw3.h>
#include <glm/common.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const std::string WINDOW_TITLE = "OpenGL";

void placeholder(GLFWwindow *window) {

        Solid sphere = Solid(glm::vec3(0., 0., 0.f));
        sphere.MakeSphere(.45, 10, 10);

        std::vector<float> vertices = sphere.get_vertices(true);
        std::vector<unsigned int> indices = sphere.get_indices();

        // first triangle setup
        // --------------------

        VertexArray vao1;
        VertexBuffer vbo1(vertices.data(), vertices.size() * sizeof(float));
        VertexBufferLayout layout1;

        layout1.AddAttrib("position", 3, GL_FLOAT, false);
        layout1.AddAttrib("normals", 3, GL_FLOAT, false);
        vao1.AddBuffer(vbo1, layout1);

        IndexBuffer sphereIB(indices.data(), indices.size());

        // second triangle setup
        // ---------------------

        float secondTriangle[] = {
            0.0f,  -0.5f, 0.0f, 0.f,  0.f,  // left
            0.9f,  -0.5f, 0.0f, 1.0f, 0.0f, // right
            0.45f, 0.5f,  0.0f, 1.f,  1.f   // top
        };
        unsigned int secondTriangleIndices[] = {0, 1, 2};

        // Shader secondShader = Shader("../res/shaders/shader_2.vert",
        //                              "../res/shaders/shader_2.frag");
        Shader shader_program =
            Shader("../res/shaders/shader.vert", "../res/shaders/shader.frag");

        VertexArray vao2; // note that we bind to a different VAO now
        VertexBuffer vbo2(secondTriangle, 15 * sizeof(float));

        VertexBufferLayout layout2;

        layout2.AddAttrib("position", 3, GL_FLOAT, false);
        layout2.AddAttrib("texture", 2, GL_FLOAT, false);
        vao2.AddBuffer(vbo2, layout2);

        IndexBuffer secondTriangleIB(secondTriangleIndices, 3);

        // uncomment this call to draw in wireframe polygons.
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        // Rendering
        // ---------

        // for (size_t i = 0; i < vertices.size(); i++) {
        //         std::cout << proj[i % 3][i % 3] * vertices[i] << '\t';
        //         if(i % 3 == 2){
        //                 std::cout << '\n';
        //         }
        // }
        //
        // for (int i = 0; i < 16; i++) {
        //         std::cout << proj[i / 4][i % 4] << '\t';
        //         if (i % 4 == 3) {
        //                 std::cout << '\n';
        //         }
        // }

        Renderer renderer;

        Texture texture("../res/textures/wood.png");
        texture.Bind();
        shader_program.setInt("u_Texture", 0);

        glm::mat4 proj =
            glm::ortho<float>(-float(1.), float(1.), -float(1.), float(1.),
                              -float(10.f), float(10.f));

        shader_program.setMat4("proj", proj);

        float last_frame = -0.03f;

        float moving_framerate_average = 0.f;

        const float framerate_smoothing = .9f;

        while (!glfwWindowShouldClose(window)) {
                ProcessInput(window);

                GLfloat time_val = (GLfloat)glfwGetTime();

                UpdateFramerate(time_val, last_frame, moving_framerate_average,
                                framerate_smoothing, window);

                shader_program.setFloat("time", time_val);

                renderer.Clear(glm::vec4(0.4, 0.7, 0.9, 1.0)); // sky blue

                renderer.Draw(vao1, shader_program, sphereIB);
                renderer.Draw(vao2, shader_program, secondTriangleIB);

                // end of rendering
                glfwSwapBuffers(window);
                glfwPollEvents();
        }
}

void step1(GLFWwindow *window) {

        float triangle[] = {
            0.0f,  0.5f,  0.0f, // left
            0.9f,  0.5f,  0.0f, // right
            0.45f, -0.5f, 0.0f, // top
        };
        unsigned int indices[] = {0, 1, 2};

        Shader shader_program =
            Shader("../res/shaders/step1.vert", "../res/shaders/step1.frag");

        VertexArray vao;
        VertexBuffer vbo(triangle, 15 * sizeof(float));

        VertexBufferLayout layout;

        layout.AddAttrib("position", 3, GL_FLOAT, false);
        vao.AddBuffer(vbo, layout);

        // IndexBuffer triangleIB(indices, 3);

        Renderer renderer;

        float last_frame = -0.03f;

        float moving_framerate_average = 0.f;

        const float framerate_smoothing = .9f;

        while (!glfwWindowShouldClose(window)) {
                ProcessInput(window);

                GLfloat time_val = (GLfloat)glfwGetTime();

                UpdateFramerate(time_val, last_frame, moving_framerate_average,
                                framerate_smoothing, window);

                shader_program.setFloat("time", time_val);

                renderer.Clear(glm::vec4(0.4, 0.7, 0.9, 1.0)); // sky blue

                // renderer.Draw(vao, shader_program, triangleIB);
                vao.Bind();
                // ib.Bind();
                shader_program.apply();
                GLCheckError(glDrawArrays(GL_TRIANGLES, 0, 3));

                // end of rendering
                glfwSwapBuffers(window);
                glfwPollEvents();
        }
}

void step1a(GLFWwindow *window) {
        Solid cube = Solid(glm::vec3(0., 0., 0.));
        cube.MakeCuboid(.5, .5, .5);

        Shader shader_program =
            Shader("../res/shaders/step1.vert", "../res/shaders/step1.frag");

        std::vector<float> vertices = cube.get_vertices(false);
        std::vector<unsigned int> indices = cube.get_indices();

        VertexArray vao;
        VertexBuffer vbo(vertices.data(), vertices.size() * sizeof(float));
        // there might be some issue with pointers here

        VertexBufferLayout layout;

        layout.AddAttrib("position", 3, GL_FLOAT, false);
        vao.AddBuffer(vbo, layout);

        IndexBuffer triangleIB(indices.data(), indices.size());

        Renderer renderer;

        float last_frame = -0.03f;

        float moving_framerate_average = 0.f;

        const float framerate_smoothing = .9f;

        while (!glfwWindowShouldClose(window)) {
                ProcessInput(window);

                GLfloat time_val = (GLfloat)glfwGetTime();

                UpdateFramerate(time_val, last_frame, moving_framerate_average,
                                framerate_smoothing, window);

                shader_program.setFloat("time", time_val);

                renderer.Clear(glm::vec4(0.4, 0.7, 0.9, 1.0)); // sky blue

                renderer.Draw(vao, shader_program, triangleIB);

                // end of rendering
                glfwSwapBuffers(window);
                glfwPollEvents();
        }
}

void step2(GLFWwindow *window) {
        Solid cube = Solid(glm::vec3(0., 0., 0.));
        cube.MakeCuboid(.5, .5, .5);

        Shader shader_program =
            Shader("../res/shaders/step2.vert", "../res/shaders/step2.frag");

        Texture t("../res/textures/wood.png");
        t.Bind();

        std::vector<float> vertices = cube.get_vertices(false);
        std::vector<unsigned int> indices = cube.get_indices();
        std::vector<float> vertex_buffer{};

        std::array<int, 16> texcoords = {0, 0, 0, 1, 1, 0, 1, 1,
                                         1, 1, 1, 0, 0, 1, 0, 0};

        for (size_t i = 0; i < vertices.size(); i++) {
                vertex_buffer.push_back(vertices[i]);
                if (i % 3 != 2) {
                        continue;
                }

                int index = i / 3;

                vertex_buffer.push_back(float(texcoords[2 * index]));
                vertex_buffer.push_back(float(texcoords[2 * index + 1]));
        }
        // something in this loop causes an invalid free

        VertexArray vao;
        VertexBuffer vbo(vertex_buffer.data(),
                         vertex_buffer.size() * sizeof(float));
        // there might be some issue with pointers here

        VertexBufferLayout layout;

        layout.AddAttrib("position", 3, GL_FLOAT, false);
        layout.AddAttrib("textures", 2, GL_FLOAT, false);
        vao.AddBuffer(vbo, layout);

        IndexBuffer triangleIB(indices.data(), indices.size());

        Renderer renderer;

        float last_frame = -0.03f;

        float moving_framerate_average = 0.f;

        const float framerate_smoothing = .9f;

        while (!glfwWindowShouldClose(window)) {
                ProcessInput(window);

                GLfloat time_val = (GLfloat)glfwGetTime();

                UpdateFramerate(time_val, last_frame, moving_framerate_average,
                                framerate_smoothing, window);

                shader_program.setFloat("time", time_val);

                renderer.Clear(glm::vec4(0.4, 0.7, 0.9, 1.0)); // sky blue

                renderer.Draw(vao, shader_program, triangleIB);

                // end of rendering
                glfwSwapBuffers(window);
                glfwPollEvents();
        }
}

void step3(GLFWwindow *window) {
        Solid cube = Solid(glm::vec3(0., 0., 0.));
        cube.MakeCuboid(.5, .5, .5);

        Shader shader_program =
            Shader("../res/shaders/step3.vert", "../res/shaders/step3.frag");

        Texture t("../res/textures/wood.png");
        t.Bind();

        std::vector<float> vertices = cube.get_vertices(false);
        std::vector<unsigned int> indices = cube.get_indices();
        std::vector<float> vertex_buffer{};

        std::array<int, 16> texcoords = {0, 0, 0, 1, 1, 0, 1, 1,
                                         1, 1, 1, 0, 0, 1, 0, 0};

        for (size_t i = 0; i < vertices.size(); i++) {
                vertex_buffer.push_back(vertices[i]);
                if (i % 3 != 2) {
                        continue;
                }

                int index = i / 3;

                vertex_buffer.push_back(float(texcoords[2 * index]));
                vertex_buffer.push_back(float(texcoords[2 * index + 1]));
        }
        // something in this loop causes an invalid free

        VertexArray vao;
        VertexBuffer vbo(vertex_buffer.data(),
                         vertex_buffer.size() * sizeof(float));
        // there might be some issue with pointers here

        VertexBufferLayout layout;

        layout.AddAttrib("position", 3, GL_FLOAT, false);
        layout.AddAttrib("textures", 2, GL_FLOAT, false);
        vao.AddBuffer(vbo, layout);

        IndexBuffer triangleIB(indices.data(), indices.size());

        Renderer renderer;

        // glm::mat4 proj = glm::perspective<float>(
        //     30.f, float(SCR_WIDTH) / float(SCR_HEIGHT), .1, 100.f);

        glm::mat4 proj = glm::perspective(
            30.f, float(SCR_WIDTH) / float(SCR_HEIGHT), 0.1f, 100.f);
        // glm::mat4 proj = glm::identity<glm::mat4>();
        shader_program.setMat4("proj", proj);

        // // glm::mat4 view = glm::lookAt(glm::vec3(-10., -10., -10.),
        // glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
        glm::mat4 view = glm::lookAt(
            glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f,
                      0.0f)); // glm::mat4 view = glm::identity<glm::mat4>();
        shader_program.setMat4("view", view);

        for (int i = 0; i < 4; i++) {
                std::cout << proj[i][0] << "\t" << proj[i][1] << "\t"
                          << proj[i][2] << "\t" << proj[i][3] << "\n";
        }

        float last_frame = -0.03f;

        float moving_framerate_average = 0.f;

        const float framerate_smoothing = .9f;

        while (!glfwWindowShouldClose(window)) {
                ProcessInput(window);

                GLfloat time_val = (GLfloat)glfwGetTime();

                glm::mat4 model = glm::rotate(glm::identity<glm::mat4>(),
                                              time_val, glm::vec3(.2, 1., 0.));
                // glm::mat4 model = glm::identity<glm::mat4>();
                shader_program.setMat4("model", model);

                UpdateFramerate(time_val, last_frame, moving_framerate_average,
                                framerate_smoothing, window);

                shader_program.setFloat("time", time_val);

                renderer.Clear(glm::vec4(0.4, 0.7, 0.9, 1.0)); // sky blue

                renderer.Draw(vao, shader_program, triangleIB);

                // end of rendering
                glfwSwapBuffers(window);
                glfwPollEvents();
        }
}

int main() {
        GLInit();
        GLFWwindow *window = MakeWindow(SCR_WIDTH, SCR_HEIGHT, WINDOW_TITLE);

        GLenum err = glewInit();
        if (GLEW_OK != err) {
                /* Problem: glewInit failed, something is seriously wrong. */
                fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        }

        GLCheckError(glEnable(GL_DEPTH_TEST));
        GLCheckError(glEnable(GL_BLEND));
        GLCheckError(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GLCheckError(glBlendEquation(GL_FUNC_ADD));

        step3(window);

        glfwTerminate();
        return 0;
}
