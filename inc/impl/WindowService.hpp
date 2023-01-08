#include "../base/WindowServiceBase.hpp"

// Implementation includes
#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Thread.hpp>
#include <cstddef>
#include <impl/Map.hpp>
#include <SFML/OpenGL.hpp>
#include <glm/glm.hpp>

#ifndef __WINDOWSERVICE__
#define __WINDOWSERVICE__

// Utils needed for functions from WindowService
namespace WSUtils {

    struct WindowProperties {
        int width;
        int height;
        const char * name;
    };

    enum RenderDataType {
        TEXT
    };

    struct RenderData {
        RenderDataType type;  
        char * text;
    };

}




// Implementation of WindowServiceBase.

class WindowService : WindowServiceBase {
    public:

        // - - - - Inherited functions - - - -
        
        void StartWindow(void * windowProperties) override;
        void Terminate() override;
        void ReceiveVisual(void * data) override;
        void Update() override;
        void SetLocalMap(void *map) override;
        void SetServerMap(void *map) override;
        void PollEvents(void * data) override;
        bool IsOpen() override;

        // - - - - Implementation functions - - - -

        // Checks if shader compilation was succesful.
        void CheckShader(GLuint shader);

        // Adds shader to the shader program using filename.
        void AddShader(GLenum type, const char * filename);

        // Draws map on x,y coordinates.
        // (x,y) is bottom left corner.
        void DrawMap();

        // Moves cursor.
        void MoveCursor(Rotation direction);

        // Moves diagonal cursor.
        void MoveDiagonalCursor(Rotation direction);

        void SetRotationPtr(Rotation * ptr);

        void SetLengthShip(int length);

        void SwapRenderMap();

        int * GetCursorPosition();

        void Close();

    private:
        // window instance.
        sf::RenderWindow _windowInstance;
        // cursor position.
        int _cursor[2] = {0,0};

        // local map.
        Map * _localMap;
        // server map.
        Map * _serverMap;

        // render data.
        WSUtils::RenderData * _renderData = nullptr;

        // GL shader program instance.
        GLuint _shaderProgram;

        // GL VAO instance.
        GLuint _VAO;

        // GL VBO instance.
        GLuint _VBO;

        // glm transform matrix.
        glm::mat4 _transformMAT, _projectionMAT;

        // glm cursor pos vector
        glm::vec2 _cursorPosVector;

        // Transform location.
        GLuint _transformLoc, _projectionLoc;
        // Cursor position location.
        // GLuint _cursorPosXLoc, _cursorPosYLoc; // << TRYING NEW SOLUTION
        
        // Type location.
        GLuint _typeLoc;

        // Rotation.
        Rotation * _rotation;

        int _shipLength = 3;

        int _currentRenderMap = 0;


        // Map dimensions.
        // int _mapDimension;

        // Unused 
        // int _size;
        // float * _mapVertices;

};


#endif