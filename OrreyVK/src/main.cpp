#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdlib>

#include "OrreyVk.h"

OrreyVk *app;

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);
		app->m_camera.mousePos = glm::vec2(xPos, yPos);
		if (glfwRawMouseMotionSupported())
			glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	app->m_camera.zoom += yoffset;
	app->m_camera.viewUpdated = true;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_W:
		app->m_camera.keys.up = true;
		break;
		case GLFW_KEY_S:
			app->m_camera.keys.down = true;
			break;
		case GLFW_KEY_A:
			app->m_camera.keys.left = true;
			break;
		case GLFW_KEY_D:
			app->m_camera.keys.right = true;
			break;
		case GLFW_KEY_KP_ADD:
			if (mods & GLFW_MOD_SHIFT)
				if (mods & GLFW_MOD_CONTROL)
					app->m_speed += 30.0f;
				else
					app->m_speed += 10.0f;
			else
				app->m_speed += 1.0f;
			break;
		case GLFW_KEY_KP_SUBTRACT:
			if (mods & GLFW_MOD_SHIFT)
				if(mods & GLFW_MOD_CONTROL)
					app->m_speed -= 30.0f;
				else
					app->m_speed -= 10.0f;
			else
				app->m_speed -= 1.0f;
			break;
		case GLFW_KEY_BACKSPACE:
			app->m_speed = 1.0f;
			break;
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, true);
			break;
		}
	}

	if (action == GLFW_RELEASE)
	{
		switch (key)
		{
		case GLFW_KEY_W:
			app->m_camera.keys.up = false;
			break;
		case GLFW_KEY_S:
			app->m_camera.keys.down = false;
			break;
		case GLFW_KEY_A:
			app->m_camera.keys.left = false;
			break;
		case GLFW_KEY_D:
			app->m_camera.keys.right = false;
			break;
		}
	}
}

int main() {
	try {
		app = new OrreyVk();
		app->Run();
		delete(app);
	}
	catch (const std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}