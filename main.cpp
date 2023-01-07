#include "impl/Map.hpp"
#include <cstdio>
#include <impl/WindowService.hpp>
#include <impl/LocalMap.hpp>
#include <iostream>



int main(){

    char ROTRIGHT[] = "Rotation: Right";
    char ROTLEFT[] = "Rotation: Left";
    char ROTDOWN[] = "Rotation: Down";
    char ROTTOP[] = "Rotation: Top";

    WSUtils::WindowProperties properties {
        .width = 800,
        .height = 800,
        .name = "OceanBattle"
    };

    WindowService windowService;
    windowService.StartWindow(&properties);

    LocalMap local(10);
    windowService.SetLocalMap(local.GetMap());
    windowService.SetRotationPtr(local.GetRotation());

    // for (int x = 0; x < local.GetMap()->Size() * local.GetMap()->Size() * 2; x += 2){
    //     std::cout
    //     << "Number :" << x/2 << " X : " <<
    //     local.GetMap()->MapIndices()[x] 
    //     << " Y :" <<
    //     local.GetMap()->MapIndices()[x+1] 
    //     << std::endl;
    // }
    // std::cout << sizeof(local.GetMap()->MapIndices()) << std::endl;

    WSUtils::RenderData data {
        .type = WSUtils::TEXT,
        .text = ROTTOP
    };

    local.SetSize(3);

    windowService.ReceiveVisual(&data);

    while(windowService.IsOpen()){

        switch (*local.GetRotation()) {
            case top:
                data.text = ROTTOP;
                break;
            case down:
                data.text = ROTDOWN;
                break;
            case right:
                data.text = ROTRIGHT;
                break;
            case left:
                data.text = ROTLEFT;
                break;
        }

        windowService.DrawMap(0, 10, 10);
        windowService.Update();
        windowService.PollEvents(&local);
    }

        
}