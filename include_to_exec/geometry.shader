#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

in VS_OUT {
    vec4 glPos;
    // mat4 glView;
    // int glInt;
    // bool isCursor;
    // int tileType;
} gs_in[];

// out GS_OUT {
//     // float isCursorF;
//     // int tileTypeF;
// } gs_out;

// in mat4 outsidetransform[];

// uniform int transformint;
uniform mat4 transform;
uniform mat4 projection;


// void build_square(vec4 position)
// {    
//     gl_Position = position + vec4(0.5, 0.0, 0.0, 0.0);
//     EmitVertex();   
//     gl_Position = position + vec4(0.5, 0.5, 0.0, 0.0);    
//     EmitVertex();
//     gl_Position = position;
//     EmitVertex();
//     gl_Position = position + vec4( 0.0,  0.5, 0.0, 0.0);  
//     EmitVertex();
//     EndPrimitive();
// }

// void build_square(vec4 position, mat4 transform1)
// {    
//     gl_Position =  transform1 * (position + vec4(0.5, 0.0, 0.0, 0.0));
//     gl_Position.w = 1.f;
//     EmitVertex();   
//     gl_Position = transform1 * (position + vec4(0.5, 0.5, 0.0, 0.0)); 
//     gl_Position.w = 1.f;   
//     EmitVertex();
//     gl_Position = transform1 * position;
//     gl_Position.w = 1.f;
//     EmitVertex();
//     gl_Position = transform1 * (position + vec4( 0.0,  0.5, 0.0, 0.0));  
//     gl_Position.w = 1.f;
//     EmitVertex();
//     EndPrimitive();
// }

// void build_square(vec4 position, int value)
// {    
//     gl_Position = position + vec4(0.5 + value, 0.0, 0.0, 0.0);
//     EmitVertex();   
//     gl_Position = position + vec4(0.5, 0.5, 0.0, 0.0);    
//     EmitVertex();
//     gl_Position = position;
//     EmitVertex();
//     gl_Position = position + vec4( 0.0,  0.5, 0.0, 0.0);  
//     EmitVertex();
//     EndPrimitive();
// }

void build_square(vec4 position, mat4 transform1, mat4 transform2)
{    
    gl_Position =  transform1 * transform2 * (position + vec4(0.5, 0.0, 0.0, 0.0));
    // gl_Position.w = 1.f;
    EmitVertex();   
    gl_Position = transform1 * transform2 * (position + vec4(0.5, 0.5, 0.0, 0.0)); 
    // gl_Position.w = 1.f;   
    EmitVertex();
    gl_Position = transform1 * transform2 * position;
    // gl_Position.w = 1.f;
    EmitVertex();
    gl_Position = transform1 * transform2 * (position + vec4( 0.0,  0.5, 0.0, 0.0));  
    // gl_Position.w = 1.f;
    EmitVertex();
    EndPrimitive();
}

void main() {    

    // if(gs_in[0].isCursor) {
    //     gs_out.isCursorF = 1;
    // } else gs_out.isCursorF = 0;
    // gs_out.tileTypeF = gs_in[0].tileType;

    // build_square(gs_in[0].glPos);
    // build_square(gs_in[0].glPos, transform);
    // build_square(gs_in[0].glPos, transformint);
    build_square(gs_in[0].glPos, projection, transform);
    // build_square(gs_in[0].glPos, transform, projection);


    // vec4 newposition = gs_in[0].glPos + vec4(0.5, 0.0, 0.0, 0.0);
    // // newposition = transform * newposition;
    // gl_Position = newposition;
    // // gl_Position = gs_in[0].glPos + vec4(0.5, 0.0, 0.0, 0.0);    
    // EmitVertex();
    // gl_Position = gs_in[0].glPos + vec4(0.5, 0.5, 0.0, 0.0);    
    // EmitVertex();
    // gl_Position = gs_in[0].glPos;
    // EmitVertex();
    // gl_Position = gs_in[0].glPos + vec4( 0.0,  0.5, 0.0, 0.0);  
    // EmitVertex();
    // EndPrimitive();

}  