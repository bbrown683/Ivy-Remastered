#include "System/GameWindow.h"
#include "Graphics/Camera.h"
#include "Graphics/Objects/Model/Model.h"
#include "Graphics/Colors.h"
#include "GLFW/glfw3.h"

using namespace Ivy::Graphics;

int main(int argc, char** argv) {    
    Ivy::System::GameWindow window(1080, 720, "Ivy");
    window.MakeCurrent();
    window.Run();
    return 0;
}