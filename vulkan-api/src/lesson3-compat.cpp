#include <vulkan/vulkan.h>

#include <GLFW/glfw3.h>
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>

#include <cstdio>

int main()
{
    const int glfwInitStatus = glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow *window = glfwCreateWindow(800, 600, "Vulkan window", nullptr, nullptr);

    uint32_t extension_count = 0;
    VkResult sts =
        vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, nullptr);

    printf("Your system supports %u vulkan extensions\n", extension_count);

    glm::mat4 test_matrix(1.0f);
    glm::vec4 test_vector(1.0f);

    auto result = test_matrix * test_vector;

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
