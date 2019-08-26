/*
 * =============== Button_SceneBegin_Pointer.cpp ==========================
 *                          -- tpr --
 *                                        CREATE -- 2019.08.25
 *                                        MODIFY -- 
 * ----------------------------------------------------------
 */
#include "Script/uiGos/Button_SceneBegin_Pointer.h"

//-------------------- CPP --------------------//
#include <functional>
#include <string>
#include <vector>

//-------------------- Engine --------------------//
#include "tprAssert.h"
#include "esrc_shader.h" 
#include "esrc_player.h"

//-------------------- Script --------------------//
#include "Script/resource/ssrc.h" 

using namespace std::placeholders;

#include "tprDebug.h" 


namespace uiGos {//------------- namespace uiGos ----------------



/* ===========================================================
 *                   init_in_autoMod
 * -----------------------------------------------------------
 */
void Button_SceneBegin_Pointer::init_in_autoMod(GameObj &goRef_,
                                        const ParamBinary &dyParams_ ){

    //================ animFrameSet／animFrameIdxHandle/ goMesh =================//

        //-- 制作 mesh 实例: "root" --
        GameObjMesh &rootGoMesh = goRef_.creat_new_goMesh(
                                "root", //- gmesh-name
                                "button_beginScene", 
                                "pointer", 
                                RenderLayerType::UIs, //- 固定zOff值  
                                &esrc::get_rect_shader(),  // pic shader
                                glm::vec2{ 0.0f, 0.0f }, //- pposoff
                                5.5,  //- off_z，
                                true, //- isVisible
                                false  // isCollide -- 不参加碰撞检测，也不会写到 mapent上
                                );
        
    //================ bind callback funcs =================//
    //-- 故意将 首参数this 绑定到 保留类实例 dog_a 身上
    goRef_.RenderUpdate = std::bind( &Button_SceneBegin_Pointer::OnRenderUpdate,  _1 );   

    //-------- actionSwitch ---------//
    goRef_.actionSwitch.bind_func( std::bind( &Button_SceneBegin_Pointer::OnActionSwitch,  _1, _2 ) );
    goRef_.actionSwitch.signUp( ActionSwitchType::ButtonState_1 );

    //================ go self vals =================//

    //-- 务必在 mesh:"root" 之后 ---
    goRef_.goPos.init_currentDPos( );
    //...    

    //--- MUST ---
    goRef_.init_check();
}


/* ===========================================================
 *                      OnRenderUpdate
 * -----------------------------------------------------------
 */
void Button_SceneBegin_Pointer::OnRenderUpdate( GameObj &goRef_ ){

    //=====================================//
    //         更新 位移系统
    //-------------------------------------//
    goRef_.move.RenderUpdate();

    //=====================================//
    //  将 确认要渲染的 goMeshs，添加到 renderPool         
    //-------------------------------------//
    goRef_.render_all_goMesh();
}


/* ===========================================================
 *               OnActionSwitch
 * -----------------------------------------------------------
 * -- 
 */
void Button_SceneBegin_Pointer::OnActionSwitch( GameObj &goRef_, ActionSwitchType type_ ){


    //-- 获得所有 goMesh 的访问权 --
    GameObjMesh &goMeshRef = goRef_.get_goMeshRef("root");

    //-- 处理不同的 actionSwitch 分支 --

    switch( type_ ){
        case ActionSwitchType::ButtonState_1:
            goMeshRef.bind_animAction( "button_beginScene", "pointer" );
            break;
        default:
            break;
            //-- 并不报错，什么也不做...
    }
}


}//------------- namespace uiGos: end ----------------

