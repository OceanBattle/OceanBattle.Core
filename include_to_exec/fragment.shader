#version 330 core
out vec4 FragColor;

// in GS_OUT {
//     // float isCursorF;
//     // flat int tileTypeF;
// } fs_in;

uniform int type;

void main()
{

    // FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);

    // if (fs_in.isCursorF == 1) {
    //     FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    // }

    // if (fs_in.isCursorF == 0)
    // {
    //     FragColor = vec4(0.5f, 1.f, 1.0f, 1.0f);
    // }

    if (type == 0) // water
    {
        FragColor = vec4(0.5f, 1.f, 1.0f, 1.0f);
    }
    if (type == 1) // ship
    {
        FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    }
    if (type == 2) // cursor
    {
        FragColor = vec4(0.2f, 0.5f, 0.5f, 1.0f);
    }

} 