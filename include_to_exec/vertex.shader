#version 330 core
layout (location = 0) in vec2 aPos;


// out mat4 outsidetransform;

out VS_OUT {
    vec4 glPos;
    // mat4 glView;
    // int glInt;
    // bool isCursor;
    // int tileType;
} vs_out;

// uniform mat4 transform;
// uniform vec2 cursorPos;
// uniform float cursorPosX;
// uniform float cursorPosY;
// uniform int type;

void main()
{
    // gl_Position = transform * vec4(aPos.x, aPos.y, 1.0, 1.0);
    vs_out.glPos = vec4(aPos.x, aPos.y, 1.0, 1.0);
    // vs_out.tileType = type;

    // if (cursorPos.x == aPos.x && cursorPos.y == aPos.y) {
    //     vs_out.isCursor = true;
    // }

    // WORKING BELOW
    // if (abs(cursorPosX - aPos.x) < 0.000001 && abs(cursorPosY - aPos.y) < 0.000001) {

    //     vs_out.isCursor = true;
    //     // if (abs(cursorPosY - aPos.y) < 0.000001) {
    //     // }

    // }

    // else vs_out.isCursor = false;
    // END OF WORKING


    // vs_out.glView = transform;
    // outsidetransform = transform;
    // vs_out.glInt = transformint;
}