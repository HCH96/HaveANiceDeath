#include "pch.h"
#include "MenuUI.h"



#include <Engine/CPathMgr.h>
#include <Engine/CTaskMgr.h>

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CLayer.h>
#include <Engine/CGameObject.h>
#include <Engine/components.h>

#include <Scripts/CScriptMgr.h>
#include <Engine/CScript.h>

#include <Engine\CAssetMgr.h>
#include <Engine\CFSM.h>

#include "CImGuiMgr.h"
#include "Inspector.h"
#include "CLevelSaveLoad.h"

#include "UIAnimPannel.h"
#include "MtrlEditorUI.h"



MenuUI::MenuUI()
	: UI("Menu", "##Menu")
{
}

MenuUI::~MenuUI()
{
}

void MenuUI::render()
{
    if (ImGui::BeginMainMenuBar())
    {     
        render_update();

        ImGui::EndMainMenuBar();
    }
}

void MenuUI::render_update()
{
    File();

    Level();

    Tool();

    GameObject();
    
    Asset();
}

void MenuUI::File()
{
    if (ImGui::BeginMenu("File"))
    {
        if (ImGui::MenuItem("Save Level", ""))
        {
            wchar_t szSelect[256] = {};

            OPENFILENAME ofn = {};

            ofn.lStructSize = sizeof(ofn);
            ofn.hwndOwner = nullptr;
            ofn.lpstrFile = szSelect;
            ofn.lpstrFile[0] = '\0';
            ofn.nMaxFile = sizeof(szSelect);
            ofn.lpstrFilter = L"ALL\0*.*\0Level\0*.lv";
            ofn.nFilterIndex = 1;
            ofn.lpstrFileTitle = NULL;
            ofn.nMaxFileTitle = 0;

            // 탐색창 초기 위치 지정
            wstring strInitPath = CPathMgr::GetContentPath();
            strInitPath += L"level\\";
            ofn.lpstrInitialDir = strInitPath.c_str();

            ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

            if (GetSaveFileName(&ofn))
            {                
                CLevelSaveLoad::SaveLevel(CLevelMgr::GetInst()->GetCurrentLevel(), CPathMgr::GetRelativePath(szSelect));
            }
        }

        if (ImGui::MenuItem("Load Level", ""))
        {
            wchar_t szSelect[256] = {};

            OPENFILENAME ofn = {};

            ofn.lStructSize = sizeof(ofn);
            ofn.hwndOwner = nullptr;
            ofn.lpstrFile = szSelect;
            ofn.lpstrFile[0] = '\0';
            ofn.nMaxFile = sizeof(szSelect);
            ofn.lpstrFilter = L"ALL\0*.*\0Level\0*.lv";
            ofn.nFilterIndex = 1;
            ofn.lpstrFileTitle = NULL;
            ofn.nMaxFileTitle = 0;

            // 탐색창 초기 위치 지정
            wstring strInitPath = CPathMgr::GetContentPath();
            strInitPath += L"level\\";
            ofn.lpstrInitialDir = strInitPath.c_str();

            ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

            if (GetOpenFileName(&ofn))
            {                
                CLevel* pLevel = CLevelSaveLoad::LoadLevel(CPathMgr::GetRelativePath(szSelect));
                CLevelMgr::GetInst()->ChangeLevel(pLevel, LEVEL_STATE::STOP);

                // Inspector 의 타겟정보를 nullptr 로 되돌리기
                Inspector* pInspector = (Inspector*)CImGuiMgr::GetInst()->FindUI("##Inspector");
                pInspector->SetTargetObject(nullptr);
            }
        }

        ImGui::EndMenu();
    }
}

void MenuUI::Level()
{
    if (ImGui::BeginMenu("Level"))
    {
        CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();

        LEVEL_STATE State = pCurLevel->GetState();

        bool PlayEnable = false;
        bool PauseEnable = false;
        bool StopEnable = false;

        if (LEVEL_STATE::STOP == State || LEVEL_STATE::PAUSE == State)
            PlayEnable = true;
        else
            PlayEnable = false;

        if (LEVEL_STATE::PLAY == State)
            PauseEnable = true;
        else
            PauseEnable = false;

        if (LEVEL_STATE::PLAY == State || LEVEL_STATE::PAUSE == State)
            StopEnable = true;
        else
            StopEnable = false;

        
        if (ImGui::MenuItem("Play", nullptr, nullptr, PlayEnable))
        {   
            if (LEVEL_STATE::STOP == pCurLevel->GetState())
            {
                CLevelSaveLoad::SaveLevel(pCurLevel, L"Level//temp.lv");
            }
            
            CLevelMgr::GetInst()->ChangeLevelState(LEVEL_STATE::PLAY);
        }

        if (ImGui::MenuItem("Pause", nullptr, nullptr, PauseEnable))
        {
            CLevelMgr::GetInst()->ChangeLevelState(LEVEL_STATE::PAUSE);
        }

        if (ImGui::MenuItem("Stop", nullptr, nullptr, StopEnable))
        {
            CLevel* pLoadedLevel = CLevelSaveLoad::LoadLevel(L"Level//temp.lv");
            CLevelMgr::GetInst()->ChangeLevel(pLoadedLevel, LEVEL_STATE::STOP);

            // Inspector 의 타겟정보를 nullptr 로 되돌리기
            Inspector* pInspector = (Inspector*)CImGuiMgr::GetInst()->FindUI("##Inspector");
            pInspector->SetTargetObject(nullptr);
        }

        ImGui::EndMenu();
    }
}

void MenuUI::GameObject()
{
    if (ImGui::BeginMenu("GameObject"))
    {
        if (ImGui::MenuItem("Create Empty Object", ""))
        {
            CGameObject* pNewObj = new CGameObject;
            pNewObj->SetName(L"New GameObject");
            pNewObj->AddComponent(new CTransform);
            GamePlayStatic::SpawnGameObject(pNewObj, 0);
        }
        ImGui::Separator();

        if (ImGui::BeginMenu("Add Component", ""))
        {
            if (ImGui::MenuItem("Add Collider"))
            {
                Inspector* inspector = (Inspector*)CImGuiMgr::GetInst()->FindUI("##Inspector");
                CGameObject* TargetObject = inspector->GetTargetObject();

                if (nullptr != TargetObject)
                {
                    TargetObject->AddComponent(new CCollider2D());
                    inspector->SetTargetObject(TargetObject);
                }
            }


            if (ImGui::MenuItem("Add Animator"))
            {
                Inspector* inspector = (Inspector*)CImGuiMgr::GetInst()->FindUI("##Inspector");
                CGameObject* TargetObject = inspector->GetTargetObject();

                if (nullptr != TargetObject)
                {
                    TargetObject->AddComponent(new CAnimator2D());
                inspector->SetTargetObject(TargetObject);
                }
            }

            if (ImGui::MenuItem("Add Light"))
            {
                Inspector* inspector = (Inspector*)CImGuiMgr::GetInst()->FindUI("##Inspector");
                CGameObject* TargetObject = inspector->GetTargetObject();

                if (nullptr != TargetObject)
                {
                    TargetObject->AddComponent(new CLight2D());
                inspector->SetTargetObject(TargetObject);
                }
            }

            if (ImGui::MenuItem("Add StateMachine"))
            {
                Inspector* inspector = (Inspector*)CImGuiMgr::GetInst()->FindUI("##Inspector");
                CGameObject* TargetObject = inspector->GetTargetObject();

                if (nullptr != TargetObject)
                {
                    TargetObject->AddComponent(new CStateMachine());
                inspector->SetTargetObject(TargetObject);
                }
            }

            if (ImGui::MenuItem("Add MeshRender"))
            {
                Inspector* inspector = (Inspector*)CImGuiMgr::GetInst()->FindUI("##Inspector");
                CGameObject* TargetObject = inspector->GetTargetObject();

                if (nullptr != TargetObject)
                {
                    TargetObject->AddComponent(new CMeshRender());
                inspector->SetTargetObject(TargetObject);
                }
            }

            if (ImGui::MenuItem("Add TileMap"))
            {
                Inspector* inspector = (Inspector*)CImGuiMgr::GetInst()->FindUI("##Inspector");
                CGameObject* TargetObject = inspector->GetTargetObject();

                if (nullptr != TargetObject)
                {
                    TargetObject->AddComponent(new CTileMap());
                inspector->SetTargetObject(TargetObject);
                }
            }

            if (ImGui::MenuItem("Add ParticleSystem"))
            {
                Inspector* inspector = (Inspector*)CImGuiMgr::GetInst()->FindUI("##Inspector");
                CGameObject* TargetObject = inspector->GetTargetObject();

                if (nullptr != TargetObject)
                {
                    TargetObject->AddComponent(new CParticleSystem());
                inspector->SetTargetObject(TargetObject);
                }
            }

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Delete Component", ""))
        {
            if (ImGui::MenuItem("Delete Collider"))
            {
                Inspector* inspector = (Inspector*)CImGuiMgr::GetInst()->FindUI("##Inspector");
                CGameObject* TargetObject = inspector->GetTargetObject();

                if (nullptr != TargetObject)
                {
                    TargetObject->DeleteComponent(COMPONENT_TYPE::COLLIDER2D);
                inspector->SetTargetObject(TargetObject);
                }
            }

            if (ImGui::MenuItem("Delete Animator"))
            {
                Inspector* inspector = (Inspector*)CImGuiMgr::GetInst()->FindUI("##Inspector");
                CGameObject* TargetObject = inspector->GetTargetObject();

                if (nullptr != TargetObject)
                {
                    TargetObject->DeleteComponent(COMPONENT_TYPE::ANIMATOR2D);
                inspector->SetTargetObject(TargetObject);
                }
            }

            if (ImGui::MenuItem("Delete Light"))
            {
                Inspector* inspector = (Inspector*)CImGuiMgr::GetInst()->FindUI("##Inspector");
                CGameObject* TargetObject = inspector->GetTargetObject();

                if (nullptr != TargetObject)
                {
                    TargetObject->DeleteComponent(COMPONENT_TYPE::LIGHT2D);
                inspector->SetTargetObject(TargetObject);
                }
            }

            if (ImGui::MenuItem("Delete StateMachine"))
            {
                Inspector* inspector = (Inspector*)CImGuiMgr::GetInst()->FindUI("##Inspector");
                CGameObject* TargetObject = inspector->GetTargetObject();

                if (nullptr != TargetObject)
                {
                    TargetObject->DeleteComponent(COMPONENT_TYPE::STATEMACHINE);
                inspector->SetTargetObject(TargetObject);
                }
            }

            if (ImGui::MenuItem("Delete MeshRender"))
            {
                Inspector* inspector = (Inspector*)CImGuiMgr::GetInst()->FindUI("##Inspector");
                CGameObject* TargetObject = inspector->GetTargetObject();

                if (nullptr != TargetObject)
                {
                    TargetObject->DeleteComponent(COMPONENT_TYPE::MESHRENDER);
                inspector->SetTargetObject(TargetObject);
                }
            }


            if (ImGui::MenuItem("Delete TileMap"))
            {
                Inspector* inspector = (Inspector*)CImGuiMgr::GetInst()->FindUI("##Inspector");
                CGameObject* TargetObject = inspector->GetTargetObject();

                if (nullptr != TargetObject)
                {
                    TargetObject->DeleteComponent(COMPONENT_TYPE::TILEMAP);
                inspector->SetTargetObject(TargetObject);
                }
            }

            if (ImGui::MenuItem("Delete ParticleSystem"))
            {
                Inspector* inspector = (Inspector*)CImGuiMgr::GetInst()->FindUI("##Inspector");
                CGameObject* TargetObject = inspector->GetTargetObject();

                if (nullptr != TargetObject)
                {
                    TargetObject->DeleteComponent(COMPONENT_TYPE::PARTICLESYSTEM);
                inspector->SetTargetObject(TargetObject);
                }
            }

            ImGui::EndMenu();
        }



        if (ImGui::BeginMenu("Script", ""))
        {
            vector<wstring> vecScriptName;
            CScriptMgr::GetScriptInfo(vecScriptName);

            for (size_t i = 0; i < vecScriptName.size(); ++i)
            {
                if (ImGui::MenuItem(ToString(vecScriptName[i]).c_str()))
                {
                    Inspector* inspector = (Inspector*)CImGuiMgr::GetInst()->FindUI("##Inspector");
                    if (nullptr != inspector->GetTargetObject())
                    {                     
                        inspector->GetTargetObject()->AddComponent(CScriptMgr::GetScript(vecScriptName[i]));
                        inspector->SetTargetObject(inspector->GetTargetObject());


                    }
                }
            }

            ImGui::EndMenu();
        }

        ImGui::EndMenu();
    }
}

void MenuUI::Asset()
{
    if (ImGui::BeginMenu("Asset"))
    {
        if (ImGui::BeginMenu("Create New FSM"))
        {
            static char textBuffer[256] = "";
            ImGui::InputText("##CreateFSMName", textBuffer, IM_ARRAYSIZE(textBuffer));

            if (ImGui::Button("create"))
            {
                Ptr<CFSM> pFSM = new CFSM(nullptr, false);
                
                // 경로 설정
                wchar_t szPath[255] = {};
                string strFSMPath = textBuffer;
                wstring wstrFSMPath = ToWString(strFSMPath);

                wstring FilePath = CPathMgr::GetContentPath();
                swprintf_s(szPath, L"FSM\\%s.fsm", wstrFSMPath.c_str());

                if (exists(FilePath + szPath))
                {
                    int value = MessageBoxA(nullptr, "FSM 이미 존재합니다. \n덮어쓰시겠습니까?", "Material Already Exist!", MB_YESNO);
                    if (value == IDYES)
                    {
                        pFSM->Save(szPath);
                    }
                }
                else
                {
                     pFSM->Save(szPath);
                }


                

            }
            ImGui::EndMenu(); // Set Go Name
        }


        ImGui::EndMenu();
    }
}

void MenuUI::Tool()
{
    if (ImGui::BeginMenu("Tool"))
    {
        if (ImGui::MenuItem("Create Animation"))
        {
            UIAnimPannel* pAnimToolMain = (UIAnimPannel*)CImGuiMgr::GetInst()->FindUI("##Animation Tool_Main");
            pAnimToolMain->Activate();
        }

        if (ImGui::MenuItem("Material Editor"))
        {
            MtrlEditorUI* pMtrlEditorUI = (MtrlEditorUI*)CImGuiMgr::GetInst()->FindUI("##MtrlInspector");
            pMtrlEditorUI->Activate();
        }

        ImGui::EndMenu();
    }
}
