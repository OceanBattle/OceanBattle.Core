#include "../inc/impl/WindowService.hpp"
#include "impl/LocalMap.hpp"
#include "impl/Map.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Thread.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Context.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <cstdio>
#include <cstdlib>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/trigonometric.hpp>
#include <read.hpp>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc//matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>




void WindowService::StartWindow(void * windowProperties) {

    // Cast to valid data
    WSUtils::WindowProperties * data = (WSUtils::WindowProperties*)windowProperties;

    // Create Window
    _windowInstance.create(sf::VideoMode(data->width, data->height), data->name);
    _windowInstance.setActive(true);
    glViewport(0, 0, data->width, data->height);
    _windowInstance.clear(sf::Color::Black);
    _windowInstance.display();

    if(glewInit() != GLEW_OK) std::exit(-1);

    _shaderProgram = glCreateProgram();

    AddShader(GL_VERTEX_SHADER, "vertex.shader");
    AddShader(GL_GEOMETRY_SHADER, "geometry.shader");
    AddShader(GL_FRAGMENT_SHADER, "fragment.shader");

    glLinkProgram(_shaderProgram);


    glGenBuffers(1, &_VBO);
    glGenVertexArrays(1, &_VAO);
    glBindVertexArray(_VAO);

    // Data setting.
    // Here you handle data to render your map.
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);

    // HERE YOU HAVE TO LINK TO THE DATA YOU WANT TO RENDER !! CURENTLY DONE IN SetLocalMap().
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); 
    // End of data setting.

    // glPointSize(25);
    glUseProgram(_shaderProgram);

    _projectionMAT = glm::mat4(1.f);
    _transformMAT = glm::mat4(1.f);

    _transformMAT = glm::translate(_transformMAT, glm::vec3(1.f, -1.0f, -6.f)); 
    _transformMAT = glm::rotate(_transformMAT, glm::radians(-30.0f), glm::vec3(1.0f, 0.0f, 0.0f)); 
    _transformMAT = glm::rotate(_transformMAT, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f)); 


    // _projectionMAT = glm::ortho(-5.f, 5.f, -5.f, 5.f, -1.f, 100.f);
    // _projectionMAT = glm::perspective(glm::radians(90.f), 1.f, -.5f, 100.f);
    _projectionMAT = glm::perspective(glm::radians(90.0f), 1.f, 0.1f, 100.0f);

    // TEST
    // glm::vec4 vec(-0.5f, -0.5f, 1, 1);
    // vec = _projectionMAT * _transformMAT * vec;
    // std::cout << vec.x << ", " << vec.y <<", " << vec.z << ", " << vec.w << std::endl;
    // TEST

    _transformLoc = glGetUniformLocation(_shaderProgram, "transform");
    _projectionLoc = glGetUniformLocation(_shaderProgram, "projection");
    // _cursorPosXLoc = glGetUniformLocation(_shaderProgram, "cursorPosX");
    // _cursorPosYLoc = glGetUniformLocation(_shaderProgram, "cursorPosY");
    _typeLoc = glGetUniformLocation(_shaderProgram, "type");
    glUniform1i(_typeLoc, 0);
    glUniformMatrix4fv(_projectionLoc, 1, GL_FALSE, glm::value_ptr(_projectionMAT));
    glUniformMatrix4fv(_transformLoc, 1, GL_FALSE, glm::value_ptr(_transformMAT));
    // std::cout << _projectionLoc << std::endl;
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);


}

void WindowService::Terminate() {
    _windowInstance.close();
}

void WindowService::DrawMap(int type, int posx, int posy){


    // WORKING BELOW
    // float posXcursor = (float)_cursor[0] * MAP_VERTICES_SPACING;
    // float posYcursor = (float)_cursor[1] * MAP_VERTICES_SPACING;
    // glUniform1f(_cursorPosXLoc, posXcursor);
    // glUniform1f(_cursorPosYLoc, posYcursor);
    // WORKING ABOVE

    // glDrawArrays(GL_POINTS, 0, _localMap->Size() * _localMap->Size());

    // for (int x = 0; x < 10; x++) {
    //     glDrawArrays(GL_POINTS, x, 1);
    // }
    // std::cout << _localMap->Size() * _localMap->Size() << std::endl;

    // for (int renderedTile = 0; renderedTile < _localMap->Size() * _localMap->Size(); renderedTile++){
    //     glDrawArrays(GL_POINTS,renderedTile, 1);
    // }

    // Render local
    glUseProgram(_shaderProgram);
    glBindVertexArray(_VAO);

    glUniform1i(_typeLoc, 0);
    glUniformMatrix4fv(_projectionLoc, 1, GL_FALSE, glm::value_ptr(_projectionMAT));
    glUniformMatrix4fv(_transformLoc, 1, GL_FALSE, glm::value_ptr(_transformMAT));
        
    if(type == 0) {

        // int currentType = 0;

        for (int x = 0; x < _localMap->Size(); x++) {
            for (int y = 0; y < _localMap->Size(); y++) {

                if (_cursor[0] == x && _cursor[1] == y){
                    glUniform1i(_typeLoc, 2);
                    glDrawArrays(GL_POINTS, (y*10) + x, 1);
                    glUniform1i(_typeLoc, 0);
                    continue;   
                }

                switch (*_rotation) {
                    case top:
                        if (_cursor[0] == x && _cursor[1] == y + 1 && y < _localMap->Size()){
                        glUniform1i(_typeLoc, 2);
                        glDrawArrays(GL_POINTS, (y*10) + x, 1);
                        glUniform1i(_typeLoc, 0);
                        continue;  
                        } 
                        break;
                    case down:
                        if (_cursor[0] == x && _cursor[1] == y - 1 && y > 0){
                        glUniform1i(_typeLoc, 2);
                        glDrawArrays(GL_POINTS, (y*10) + x, 1);
                        glUniform1i(_typeLoc, 0);
                        continue;  
                        } 
                        break;
                    case left:
                        if (_cursor[0] == x + 1 && _cursor[1] == y && x < _localMap->Size()){
                        glUniform1i(_typeLoc, 2);
                        glDrawArrays(GL_POINTS, (y*10) + x, 1);
                        glUniform1i(_typeLoc, 0);
                        continue;  
                        } 
                        break;
                    case right:
                        if (_cursor[0] == x - 1 && _cursor[1] == y && x > 0){
                        glUniform1i(_typeLoc, 2);
                        glDrawArrays(GL_POINTS, (y*10) + x, 1);
                        glUniform1i(_typeLoc, 0);
                        continue;  
                        } 
                        break;
                }

                if (_localMap->RawMap()[x][y] != 0) {
                    glUniform1i(_typeLoc, 1);
                    glDrawArrays(GL_POINTS, (y*10) + x, 1);
                    glUniform1i(_typeLoc, 0);
                    continue;
                }

                glDrawArrays(GL_POINTS, (y*10) + x, 1);
                
            }
        }
    }

    // Render server
    if (type == 2) {
        for (int x = 0; x < _localMap->Size(); x++) {
            for (int y = 0; y < _localMap->Size(); y++) {

                if (_cursor[0] == x && _cursor[1] == y){
                    glUniform1i(_typeLoc, 2);
                    glDrawArrays(GL_POINTS, (y*10) + x, 1);
                    glUniform1i(_typeLoc, 0);
                    continue;   
                }


                if (_serverMap->RawMap()[x][y] != 0) {
                    glUniform1i(_typeLoc, 1);
                    glDrawArrays(GL_POINTS, (y*10) + x, 1);
                    glUniform1i(_typeLoc, 0);
                    continue;
                }

                glDrawArrays(GL_POINTS, (y*10) + x, 1);
                
            }
        }
    }

    

    // _windowInstance.pushGLStates();
    
}

void WindowService::SetLocalMap(void *map){
    Map * ptr = (Map*)map;
    _localMap = ptr;

    // Testing 
    glBufferData(GL_ARRAY_BUFFER, ptr->Size() * ptr->Size() * 2 * sizeof(float), ptr->MapIndices(), GL_STATIC_DRAW);
}

void WindowService::SetServerMap(void *map){
    Map * ptr = (Map*)map;
    _serverMap = ptr;
    // _mapDimension = ptr->Size() * ptr->Size();
}

void WindowService::ReceiveVisual(void *data){
    WSUtils::RenderData * ptr = (WSUtils::RenderData*)data;
    _renderData = ptr;

}

void WindowService::Update() {
    
    // if (_renderData != nullptr) {
    //     if (_renderData->type == WSUtils::TEXT) {
    //         sf::Font font;
    //         font.loadFromFile("Hack-Bold.ttf");
    //         sf::Text text;
    //         text.setPosition(30, 30);
    //         text.setFont(font);
    //         text.setString(_renderData->text);
    //         text.setCharacterSize(24);
    //         text.setFillColor(sf::Color::Red);
    //         _windowInstance.draw(text);
    //     }
    // }
    // _windowInstance.popGLStates();

  

    _windowInstance.display();
    
    glClear(GL_COLOR_BUFFER_BIT);
    // _windowInstance.clear(sf::Color::Black);

    // Working on fonts
    // sf::Font font;
    // if(!font.loadFromFile("Hack-Bold.ttf")){
    //     std::cout << "cant load font" << std::endl;
    // }
    
    // sf::Text text;
    // // text.setPosition(30, 30);
    // text.setFont(font);
    // text.setString("HelloWorld");
    // text.setCharacterSize(40);
    // text.setFillColor(sf::Color::Red);
    // _windowInstance.draw(text);
    // Fonts ^^^^^

    // _windowInstance.pushGLStates();
    // _windowInstance.resetGLStates();
    // sf::RectangleShape rec;
    // rec.setSize(sf::Vector2f(200.f, 200.f));
    // rec.setFillColor(sf::Color::Red);
    // _windowInstance.draw(rec);
    // _windowInstance.popGLStates();
}

void WindowService::MoveCursor(Rotation direction) {
    switch (direction) {
        case top:
            if (_cursor[1] == 0) return;
            _cursor[1] -= 1; 
            break;
        case down:
            if (_cursor[1] == _localMap->Size() - 1) return;
            _cursor[1] += 1;
            break;
        case left:
            if (_cursor[0] == 0) return;
            _cursor[0] -= 1;
            break;
        case right:
            if (_cursor[0] == _localMap->Size() - 1) return;
            _cursor[0] += 1;
            break;
    }
}

void WindowService::MoveDiagonalCursor(Rotation direction){
    switch (direction) {
        case top:
            MoveCursor(down);
            MoveCursor(right);
            break;
        case down:
            MoveCursor(top);
            MoveCursor(left);
            break;
        case left:
            MoveCursor(left);
            MoveCursor(down);
            break;
        case right:
            MoveCursor(right);
            MoveCursor(top);
            break;
    }
}




void WindowService::PollEvents(void * data) {
    LocalMap * local = (LocalMap*)data;
    sf::Event event;
    while(_windowInstance.pollEvent(event)) {

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::A) MoveCursor(left);
            if (event.key.code == sf::Keyboard::D) MoveCursor(right);
            if (event.key.code == sf::Keyboard::W) MoveCursor(down);
            if (event.key.code == sf::Keyboard::S) MoveCursor(top);
            // if (event.key.code == sf::Keyboard::A) MoveDiagonalCursor(left);
            // if (event.key.code == sf::Keyboard::D) MoveDiagonalCursor(right);
            // if (event.key.code == sf::Keyboard::W) MoveDiagonalCursor(top);
            // if (event.key.code == sf::Keyboard::S) MoveDiagonalCursor(down);
            if (event.key.code == sf::Keyboard::R) local->RotateShip();
            if (event.key.code == sf::Keyboard::Enter) local->PlaceShip(_cursor[0], _cursor[1], 2);
            if (event.key.code == sf::Keyboard::Escape) _windowInstance.close();

            // std::cout << "Cursor now X: " << (float)_cursor[0] * MAP_VERTICES_SPACING
            //  << " Y: " << (float)_cursor[1] * MAP_VERTICES_SPACING << std::endl; 
        }

        if (event.type == sf::Event::Resized) {
            glViewport(0, 0, event.size.width, event.size.height);
        }

    }

}

bool WindowService::IsOpen() {
    return _windowInstance.isOpen();
}

void WindowService::CheckShader(GLuint shader){
    GLint success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        GLint logSize = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
        char * log = new char[logSize];
        glGetShaderInfoLog(shader, logSize, nullptr, log);
        std::cout << log << std::endl;
        delete[] log;
    }
}

void WindowService::AddShader(GLenum type, const char * filename){

    FileManager manager;

    manager.ReadFile(filename);

    const char * source = manager.GetFile(0);

    GLuint shader;

    shader = glCreateShader(type);

    glShaderSource(shader, 1, &source, nullptr);

    glCompileShader(shader);

    CheckShader(shader);

    glAttachShader(_shaderProgram, shader);
}

void WindowService::SetRotationPtr(Rotation *ptr){
    _rotation = ptr;
}