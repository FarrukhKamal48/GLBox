#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace Input {

void Init(GLFWwindow* window);

// enum class KeyCode {
//     Mouse1, Mouse2,
//     Mouse3, Mouse4,
//     Mouse5, Mouse6,
//     Mouse7, Mouse8,
//     
//     Space,  Apostrophe,     
//     Comma,  Minus,          
//     Period, Slash,
//     
//     Num0, Num1,              
//     Num2, Num3,              
//     Num4, Num5,              
//     Num6, Num7,              
//     Num8, Num9,              
//     
//     Semicolon, Equal,          
//     
//     A, B, C, D,
//     E, F, G, H,
//     I, J, K, L,
//     M, N, O, P,
//     Q, R, S, T,
//     U, V, W, X,
//     Y, Z,
//     
//     LeftBracket,    Backslash,      
//     RightBracket,   GraveAccent,   
//     World1, World2,
//     Escape,         Enter,          
//     Tab,            Backspace,      
//     Insert,         Delete,         
//     Right,          Left,           
//     Down,           Up,             
//     PageUp,         PageDown,      
//     Home,           End,            
//     CapsLock,       ScrollLock,    
//     NumLock,        PrintScreen,   
//     Pause,          
//     
//     F1,  F2,  F3, 
//     F4,  F5,  F6, 
//     F7,  F8,  F9, 
//     F10, F11, F12, 
//     F13, F14, F15, 
//     F16, F17, F18, 
//     F19, F20, F21, 
//     F22, F23, F24, 
//     F25,            
//     
//     KP0, KP1, KP2, 
//     KP3, KP4, KP5, 
//     KP6, KP7, KP8, 
//     KP9,           
//     
//     KPDecimal,     KPDivide,      
//     KPMultiply,    KPSubtract,    
//     kpadD,         KPEnter,       
//     KPEqual,       
//     
//     LeftShift,     LeftControl,   
//     LeftAlt,       LeftSuper,     
//     RightShift,    RightControl,  
//     RightAlt,      RightSuper,    
//     Menu,           
// };

bool Button(int button, int action);
bool ButtonHold(int button);

glm::vec2 GetMousePos();

}
