#include <chrono>
#include <D3dx9tex.h>
#include "menu.hpp"
#include "../arrays.h"

#include "../valve_sdk/csgostructs.hpp"
#include "../helpers/input.hpp"
#include "../options.hpp"
#include "ui.hpp"
#include "../fonts.h"
#include "../imgui/imgui_internal.h"
#include "../imgui/directx9/imgui_impl_dx9.h"
#include "../features/misc/misc.hpp"
#include "../features/skinchanger/skins.hpp"
#include "../features/visuals/nightmode.hpp"
#include "../helpers/config_manager.hpp"
#include "Header.h"



ImFont* bigFont = nullptr;
ImFont* forTabs = nullptr;
ImFont* forTabs_text = nullptr;
ImFont* forTabs_text_x2 = nullptr;

ImFont* globalFont = nullptr;
WNDPROC original_proc = nullptr;
static int tabselected = 0;
IMGUI_API LRESULT   ImGui_ImplDX9_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

bool isSkeet = false;

#define AIMBOT ("A")
#define RAGE ("K")
#define VISUALS ("D")
#define SKINS ("B")
#define COLORS ("H")
#define MISC ("G")

static int a1 = 0;

void CMenu::ImColors(ImGuiStyle& style)
{
	style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.59f, 0.59f, 0.59f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.045f, 0.045f, 0.045f, 1.00f);
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.11f, 0.11f, 0.11f, 0.00f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.07f, 0.07f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.09f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.04f, 0.04f, 0.04f, 0.88f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.20f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.13f, 0.13f, 0.13f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(1.00f, 1.00f, 1.00f, 0.59f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.24f, 0.40f, 0.95f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.045f, 0.045f, 0.045f, 1.00f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.045f, 0.045f, 0.045f, 1.00f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.045f, 0.045f, 0.045f, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.24f, 0.40f, 0.95f, 1.00f);
	style.Colors[ImGuiCol_Separator] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.24f, 0.40f, 0.95f, 0.59f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.07f, 0.07f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.045f, 0.045f, 0.045f, 1.00f);

}

void DefaultColor()
{
	ImGuiStyle& style = ImGui::GetStyle();

	style.Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.07f, 0.07f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.07f, 0.07f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.07f, 0.07f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.07f, 0.07f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_Column] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_CloseButton] = ImVec4(0.40f, 0.39f, 0.38f, 0.16f);
	style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.40f, 0.39f, 0.38f, 0.39f);
	style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.40f, 0.39f, 0.38f, 1.00f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
}

void CMenu::ImStyles(ImGuiStyle& style)
{//
	style.Alpha = 1.0f;             // Global alpha applies to everything in ImGui
	style.WindowPadding = ImVec2(8, 8);      // Padding within a window
	style.WindowRounding = 0.0f;             // Radius of window corners rounding. Set to 0.0f to have rectangular windows
	style.WindowTitleAlign = ImVec2(0.5f, 0.5f);// Alignment for title bar text
	style.FramePadding = ImVec2(4, 1);      // Padding within a framed rectangle (used by most widgets)
	style.FrameRounding = 0.0f;             // Radius of frame corners rounding. Set to 0.0f to have rectangular frames (used by most widgets).
	style.ItemSpacing = ImVec2(8, 4);      // Horizontal and vertical spacing between widgets/lines
	style.ItemInnerSpacing = ImVec2(4, 4);      // Horizontal and vertical spacing between within elements of a composed widget (e.g. a slider and its label)
	style.TouchExtraPadding = ImVec2(0, 0);      // Expand reactive bounding box for touch-based system where touch position is not accurate enough. Unfortunately we don't sort widgets so priority on overlap will always be given to the first widget. So don't grow this too much!
	style.IndentSpacing = 21.0f;            // Horizontal spacing when e.g. entering a tree node. Generally == (FontSize + FramePadding.x*2).
	style.ColumnsMinSpacing = 6.0f;             // Minimum horizontal spacing between two columns
	style.ScrollbarSize = 10.0f;            // Width of the vertical scrollbar, Height of the horizontal scrollbar
	style.ScrollbarRounding = 3.0f;             // Radius of grab corners rounding for scrollbar
	style.GrabMinSize = 10.0f;            // Minimum width/height of a grab box for slider/scrollbar
	style.GrabRounding = 0.0f;             // Radius of grabs corners rounding. Set to 0.0f to have rectangular slider grabs.
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);// Alignment of button text when button is larger than text.
	style.DisplayWindowPadding = ImVec2(22, 22);    // Window positions are clamped to be visible within the display area by at least this amount. Only covers regular windows.
	style.DisplaySafeAreaPadding = ImVec2(4, 4);      // If you cannot see the edge of your screen (e.g. on a TV) increase the safe area padding. Covers popups/tooltips as well regular windows.
	style.AntiAliasedLines = true;             // Enable anti-aliasing on lines/borders. Disable if you are really short on CPU/GPU.
	style.CurveTessellationTol = 1.25f;            // Tessellation tolerance. Decrease for highly tessellated curves (higher quality, more polygons), increase to reduce quality.
}

void CMenu::Shutdown()
{
	Globals::PlayerListOpened = false;
	Globals::RadioOpened = false;
	Globals::MenuOpened = false;


	SetWindowLongPtrA(FindWindowA(("Valve001"), nullptr), GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(original_proc));

	ImGui_ImplDX9_Shutdown();
}

LRESULT __stdcall proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (Globals::MenuOpened && ImGui_ImplDX9_WndProcHandler(hwnd, msg, wParam, lParam))
		return true;

	return CallWindowProc(original_proc, hwnd, msg, wParam, lParam);
}

void CMenu::RadioFrame()
{
	if (!Globals::MenuOpened)
		return;

	if (!Globals::RadioOpened)
		return;

}

void CMenu::PlayerListFrame()
{
	static int currentPlayer = -1;

	if (!Utils::IsInGame())
		currentPlayer = -1;

	if (!Globals::MenuOpened)
		return;

	if (!Globals::PlayerListOpened)
		return;

	ImGui::SetNextWindowSize(ImVec2(500, 300));
	if (ImGui::BeginAndroid(("plist1337"), &Globals::PlayerListOpened, false, ImGuiWindowFlags_NoTitleBar))
	{
		ImGui::GetWindowDrawList()->AddRectFilledMultiColor(ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowWidth() / 2, ImGui::GetWindowPos().y - 6), ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowSize().x, ImGui::GetWindowPos().y + 2), Vars.barColor1.x, Vars.barColor1.y, Vars.barColor1.h, Vars.barColor1.w);
		ImGui::GetWindowDrawList()->AddRectFilledMultiColor(ImVec2(ImGui::GetWindowPos().x - 5, ImGui::GetWindowPos().y - 6), ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowSize().x / 2, ImGui::GetWindowPos().y + 2), Vars.barColor2.x, Vars.barColor2.y, Vars.barColor2.h, Vars.barColor2.w);
		ImGui::Spacing();


		/*if (Utils::IsInGame())
		{
			for (int i = 0; i <= Interfaces::GlobalVars->maxClients; i++)
			{
				if (i == Interfaces::Engine->GetLocalPlayer())
					continue;

				C_BasePlayer* Target = (C_BasePlayer*)Interfaces::EntityList->GetClientEntity(i);
				if (!Target)
					continue;
				if (Target->GetClientClass()->m_ClassID != CCSPlayer)
					continue;

				if (Target->IsTeammate())
					continue;

				if (Target->GetPlayerInfo().szName == "GOTV" && !Target->m_hActiveWeapon())
					continue;

				player_info_t entityInformation;
				Interfaces::Engine->GetPlayerInfo(i, &entityInformation);

				player_info_t localinfo; Interfaces::Engine->GetPlayerInfo(Interfaces::Engine->GetLocalPlayer(), &localinfo);

				char buf[255]; sprintf_s(buf, u8"%s", entityInformation.szName);
				ImGui::Text(buf);
			}
		}*/
	}
	ImGui::End();
}

void CMenu::RenderLegitbotTab()
{
	static int selected = 0;

	if (ImGui::ButtonSelectable(("Globals"), ImVec2(220, 40), selected == 0, forTabs_text, forTabs_text_x2))
		selected = 0;
	ImGui::SameLine();
	if (ImGui::ButtonSelectable(ActiveWeaponName.c_str(), ImVec2(220, 40), selected == 1, forTabs_text, forTabs_text_x2))
		selected = 1;

	switch (selected)
	{
	case 0:
		ImGui::BeginGroup();
		ImGui::Spacing();
		ImGui::Checkbox(("Enable Legitbot"), &Vars.legit_enable);
		ImGui::Checkbox(("Ignore Team##AIM"), &Vars.legit_ignoreteam);
		ImGui::Checkbox(("Smoke Check"), &Vars.legit_smokecheck);
		ImGui::Checkbox(("Flash Check"), &Vars.legit_flashcheck);
		ImGui::Checkbox(("Draw FOV"), &Vars.legit_drawfovaimbot);
		ImGui::Checkbox(("Backtracking"), &Vars.legit_backtracking);

		ImGui::PushItemWidth(142);
		ImGui::Combo(("Triggerbot key"), &Vars.legit_trigger_key, AllKeys, IM_ARRAYSIZE(AllKeys));
		ImGui::PopItemWidth();

		//ImGui::SliderFloat("test1", &Vars.test, 200, 500);
		//ImGui::SliderFloat("test2", &Vars.test2, 200, 500);
		//ImGui::SliderFloat("test3", &Vars.test3, 0.f, 30.f);

		ImGui::EndGroup();
		break;
	case 1:
		if (!Globals::WeaponTabValid)
			ImGui::Text(("Take a gun"));
		else
		{
			ImGui::PushItemWidth(142);
			ImGui::BeginGroup();
			ImGui::Spacing();
			ImGui::Checkbox(("Enable aimbot"), &WeaponSettings->aim_enabled);
			if (Globals::LocalPlayer->m_hActiveWeapon()->IsPistol()) {
				ImGui::Checkbox(("Autopistol"), &WeaponSettings->aim_autopistol);
			}
			if (Globals::LocalPlayer->m_hActiveWeapon()->IsSniper()) {
				ImGui::Checkbox(("Only on scope"), &WeaponSettings->aim_only_in_zoom);
			}
			ImGui::Checkbox(("Nearest"), &WeaponSettings->aim_nearest);
			ImGui::Text(("Hitbox:"));
			ImGui::Combo(("##aimbot.hitbox"), &WeaponSettings->aim_hitbox, hitbox_list, IM_ARRAYSIZE(hitbox_list));
			ImGui::Text(("Hitchance"));
			ImGui::SliderFloat(("##hitchnc"), &WeaponSettings->aim_hitchance, 0.f, 100.f, "%.2f %%");
			ImGui::Checkbox(("Ignore walls"), &WeaponSettings->aim_ignore_walls);
			ImGui::Checkbox(("pSilent"), &WeaponSettings->aim_perfect_silent);
			ImGui::Checkbox(("Recoil based fov"), &WeaponSettings->aim_recoil_based_fov);

			//ImGui::Checkbox("Dynamic fov", &WeaponSettings->fov_type);

			ImGui::EndGroup();

			ImGui::SameLine();

			ImGui::BeginGroup();
			ImGui::Text((WeaponSettings->aim_perfect_silent ? "FOV - pSilent" : "FOV"));
			if (WeaponSettings->aim_perfect_silent)
				ImGui::SliderFloat(("##silent_fov"), &WeaponSettings->aim_psilent_fov, 0, 3, "%.2f");
			else
				ImGui::SliderFloat(("##FOV"), &WeaponSettings->aim_fov, 0, 50, "%.2f");

			ImGui::Text(WeaponSettings->aim_perfect_silent ? ("Smooth (Inactive)") : ("Smooth"));
			ImGui::SliderFloat(("##Smooth"), &WeaponSettings->aim_smooth, 0, 20, "%.2f");

			if (Globals::LocalPlayer->m_hActiveWeapon()->IsAutomaticGun()) {
				ImGui::Text(("FOV after 1 bullet"));
				ImGui::SliderFloat(("##FOV - 2 b"), &WeaponSettings->aim_fov_2, 0, 50, "%.2f");
				ImGui::Text(("Smooth after 1 bullet"));
				ImGui::SliderFloat(("##Smooth 2 b"), &WeaponSettings->aim_smooth_2, 0, 20, "%.2f");
			}
			ImGui::EndGroup();

			ImGui::SameLine();

			ImGui::BeginGroup();
			ImGui::Spacing();
			ImGui::Checkbox(("RCS"), &WeaponSettings->aim_rcs);
			ImGui::SliderInt(("##aimbot.rcs_x"), &WeaponSettings->aim_rcs_x, 0, 100, "X: %.0f");
			ImGui::SliderInt(("##aimbot.rcs_y"), &WeaponSettings->aim_rcs_y, 0, 100, "Y: %.0f");

			ImGui::Spacing();
			ImGui::Spacing();

			ImGui::Text(("ShotDelay"));
			ImGui::SliderInt(("##aimbot.shot_delay"), &WeaponSettings->aim_shot_delay, 0, 100);

			ImGui::Text(("KillDelay"));
			ImGui::SliderInt(("##aimbot.kill_delay"), &WeaponSettings->aim_kill_delay, 0, 1000);

			ImGui::EndGroup();

			ImGui::Spacing();
			const ImRect bb(ImVec2(ImGui::GetCurrentWindow()->Pos.x, ImGui::GetCurrentWindow()->DC.CursorPos.y), ImVec2(ImGui::GetCurrentWindow()->Pos.x + ImGui::GetCurrentWindow()->Size.x, ImGui::GetCurrentWindow()->DC.CursorPos.y + 1.0f));
			ImGui::GetCurrentWindow()->DrawList->AddLine(bb.Min + ImVec2(132, 0), ImVec2(bb.Max.x, bb.Min.y), ImGui::GetColorU32(ImGuiCol_Separator));
			ImGui::Spacing();


			ImGui::BeginGroup();

			ImGui::BeginGroup();
			ImGui::Spacing();
			ImGui::Checkbox(("Enable triggerbot"), &WeaponSettings->trigger_enable);
			ImGui::Checkbox(("Head"), &WeaponSettings->trigger_Head);
			ImGui::Checkbox(("Body"), &WeaponSettings->trigger_Body);
			ImGui::Checkbox(("Misc"), &WeaponSettings->trigger_Misc);
			ImGui::EndGroup();

			ImGui::SameLine(150);

			ImGui::BeginGroup();
			ImGui::Text(("Delay"));
			ImGui::SliderInt(("##Delay"), &WeaponSettings->trigger_delay, 0, 100);
			ImGui::Text(("HitChance"));
			ImGui::SliderFloat(("##hitchnctr"), &WeaponSettings->trigger_hitchance, 0.f, 100.f, "%.2f %%");
			ImGui::EndGroup();
			ImGui::EndGroup();

			ImGui::PopItemWidth();
		}
		break;
	}
}

void CMenu::RenderSkinsTab()
{
	static int selected = 0;

	if (ImGui::ButtonSelectable(("Knife CT"), ImVec2(100, 40), selected == 0, forTabs_text, forTabs_text_x2))
		selected = 0;
	ImGui::SameLine();
	if (ImGui::ButtonSelectable(("Knife TT"), ImVec2(100, 40), selected == 1, forTabs_text, forTabs_text_x2))
		selected = 1;
	ImGui::SameLine();
	if (ImGui::ButtonSelectable(("Gloves"), ImVec2(100, 40), selected == 2, forTabs_text, forTabs_text_x2))
		selected = 2;
	ImGui::SameLine();
	if (ImGui::ButtonSelectable(ActiveWeaponName.c_str(), ImVec2(100, 40), selected == 3, forTabs_text, forTabs_text_x2))
		selected = 3;

	switch (selected)
	{
	case 0:
		ImGui::Checkbox(("Enabled"), &Vars.weapon[WEAPON_KNIFE].enabled);
		ImGui::InputInt(("Seed"), &Vars.weapon[WEAPON_KNIFE].seed);
		ImGui::InputInt(("StatTrak"), &Vars.weapon[WEAPON_KNIFE].stat_trak);
		ImGui::SliderFloat(("Wear"), &Vars.weapon[WEAPON_KNIFE].wear, 0.f, 1.f, "%.3f");
		ImGui::InputText(("Name Tag"), Vars.weapon[WEAPON_KNIFE].custom_name, 32);

		ImGui::Combo(("Paint Kit"), &Vars.weapon[WEAPON_KNIFE].paint_kit_vector_index, [](void* data, int idx, const char** out_text)
		{
			*out_text = k_skins[idx].name.c_str();
			return true;
		}, nullptr, k_skins.size(), 10);

		ImGui::Combo(("Knife##Model"), &Vars.weapon[WEAPON_KNIFE].definition_override_vector_index, [](void* data, int idx, const char** out_text)
		{
			*out_text = k_knife_names.at(idx).name;
			return true;
		}, nullptr, k_knife_names.size(), 5);
		break;
	case 1:
		ImGui::Checkbox("Enabled", &Vars.weapon[WEAPON_KNIFE_T].enabled);
		ImGui::InputInt("Seed", &Vars.weapon[WEAPON_KNIFE_T].seed);
		ImGui::InputInt("StatTrak", &Vars.weapon[WEAPON_KNIFE_T].stat_trak);
		ImGui::SliderFloat("Wear", &Vars.weapon[WEAPON_KNIFE_T].wear, 0.f, 1.f, "%.3f");
		ImGui::InputText("Name Tag", Vars.weapon[WEAPON_KNIFE_T].custom_name, 32);

		ImGui::Combo("Paint Kit", &Vars.weapon[WEAPON_KNIFE_T].paint_kit_vector_index, [](void* data, int idx, const char** out_text)
		{
			*out_text = k_skins[idx].name.c_str();
			return true;
		}, nullptr, k_skins.size(), 10);

		ImGui::Combo("Knife##Model", &Vars.weapon[WEAPON_KNIFE_T].definition_override_vector_index, [](void* data, int idx, const char** out_text)
		{
			*out_text = k_knife_names.at(idx).name;
			return true;
		}, nullptr, k_knife_names.size(), 5);
		break;
	case 2:
		ImGui::Checkbox(("Enabled"), &Vars.weapon[5028].enabled);
		ImGui::Combo(("Glove##model"), &Vars.weapon[5028].definition_override_vector_index, [](void* data, int idx, const char** out_text)
		{
			*out_text = k_glove_names.at(idx).name;
			return true;
		}, nullptr, k_glove_names.size(), 5);

		ImGui::Combo(("Paint Kit"), &Vars.weapon[5028].paint_kit_vector_index, [](void* data, int idx, const char** out_text)
		{
			*out_text = k_gloves[idx].name.c_str();
			return true;
		}, nullptr, k_gloves.size(), 10);
		ImGui::SliderFloat(("Wear"), &Vars.weapon[5028].wear, 0.f, 1.f, "%.3f");

		break;
	case 3:
		if (!Globals::WeaponTabValid)
			ImGui::Text(("Take a gun"));
		else {
			ImGui::Checkbox(("Enabled"), &WeaponSettings->enabled);
			ImGui::InputInt(("Seed"), &WeaponSettings->seed);
			ImGui::InputInt(("StatTrak"), &WeaponSettings->stat_trak);
			ImGui::SliderFloat(("Wear"), &WeaponSettings->wear, 0.f, 1.f, "%.3f");
			ImGui::InputText(("Name Tag"), WeaponSettings->custom_name, 32);

			ImGui::Combo(("Paint Kit"), &WeaponSettings->paint_kit_vector_index, [](void* data, int idx, const char** out_text)
			{
				*out_text = k_skins[idx].name.c_str();
				return true;
			}, nullptr, k_skins.size(), 10);
		}
		break;
	}

	if (ImGui::Button(("Update")))
	{
		CSkinChanger::Get().Update();
	}
}

void CMenu::RenderRagebotTab()
{
	static int selected = 0;

	if (ImGui::ButtonSelectable(("Globals"), ImVec2(220, 40), selected == 0, forTabs_text, forTabs_text_x2))
		selected = 0;
	ImGui::SameLine();
	if (ImGui::ButtonSelectable(("Weapon"), ImVec2(220, 40), selected == 1, forTabs_text, forTabs_text_x2))
		selected = 1;

	if (selected == 0) 
	{
		ImGui::BeginGroup();
		{
			ImGui::PushItemWidth(152);
			ImGui::Checkbox(("Enable Ragebot"), &Vars.ragebot_enabled);
			ImGui::Checkbox(("Auto zeus"), &Vars.ragebot_autozeus);
			ImGui::Text(("FOV"));
			ImGui::SliderInt(("##FOV"), &Vars.ragebot_fov, 0, 180);
			ImGui::PopItemWidth();
		}
		ImGui::EndGroup();

		ImGui::SameLine(162);

		ImGui::BeginGroup();
		{
			ImGui::PushItemWidth(152);
			ImGui::SliderInt("Fakelag", &Vars.ragebot_fakelag_amt, 0, 16);
			ImGui::SliderInt("Slowwalk", &Vars.ragebot_slowwalk_amt, 0, 100);
			ImGui::Combo(("Slowwalk key"), &Vars.ragebot_slowwalk_key, AllKeys, IM_ARRAYSIZE(AllKeys));
			ImGui::Spacing();
			ImGui::Combo("Pitch", &Vars.ragebot_antiaim_pitch, aa_pitch_list, IM_ARRAYSIZE(aa_pitch_list));
			ImGui::Combo("Yaw", &Vars.ragebot_antiaim_yaw, aa_yaw_list, IM_ARRAYSIZE(aa_yaw_list));
			ImGui::Checkbox("Desync", &Vars.ragebot_antiaim_desync);
			ImGui::PopItemWidth();
		}
		ImGui::EndGroup();

	}
	else if (selected == 1) {
		static int curGroup = 0;
		if (ImGui::ButtonSelectable("Pistols", ImVec2(55, 25), curGroup == WEAPON_GROUPS::PISTOLS)) curGroup = WEAPON_GROUPS::PISTOLS;
		ImGui::SameLine();
		if (ImGui::ButtonSelectable("Rifles", ImVec2(55, 25), curGroup == WEAPON_GROUPS::RIFLES)) curGroup = WEAPON_GROUPS::RIFLES;
		ImGui::SameLine();
		if (ImGui::ButtonSelectable("SMG", ImVec2(55, 25), curGroup == WEAPON_GROUPS::SMG)) curGroup = WEAPON_GROUPS::SMG;
		ImGui::SameLine();
		if (ImGui::ButtonSelectable("Shotguns", ImVec2(55, 25), curGroup == WEAPON_GROUPS::SHOTGUNS)) curGroup = WEAPON_GROUPS::SHOTGUNS;
		ImGui::SameLine();
		if (ImGui::ButtonSelectable("Scout", ImVec2(55, 25), curGroup == WEAPON_GROUPS::SCOUT)) curGroup = WEAPON_GROUPS::SCOUT;
		ImGui::SameLine();
		if (ImGui::ButtonSelectable("Auto", ImVec2(55, 25), curGroup == WEAPON_GROUPS::AUTO)) curGroup = WEAPON_GROUPS::AUTO;
		ImGui::SameLine();
		if (ImGui::ButtonSelectable("AWP", ImVec2(55, 25), curGroup == WEAPON_GROUPS::AWP)) curGroup = WEAPON_GROUPS::AWP;
		ImGui::BeginGroup();
		{
			ImGui::PushItemWidth(142);

			ImGui::Checkbox(("Auto Scope"), &Vars.ragebot_autoscope[curGroup]);
			ImGui::Checkbox(("Auto Stop"), &Vars.ragebot_autostop[curGroup]);
			ImGui::Checkbox(("Auto Crouch"), &Vars.ragebot_autocrouch[curGroup]);

			ImGui::SliderFloat(("Hitchance"), &Vars.ragebot_hitchance[curGroup], 0.f, 100.f);
			ImGui::SliderFloat(("Min Damage"), &Vars.ragebot_mindamage[curGroup], 0.f, 100.f);
			ImGui::SliderInt(("Baim after x shots"), &Vars.ragebot_baim_after_shots[curGroup], 0, 10);

			ImGui::Combo("Target Selection", &Vars.ragebot_selection[curGroup], selectiontypes, IM_ARRAYSIZE(selectiontypes));

			static std::string prevValue = "Select";
			if (ImGui::BeginCombo("Hitscan", "Select", 0))
			{
				//prevValue = "Hitscan";
				std::vector<std::string> vec;
				for (size_t i = 0; i < IM_ARRAYSIZE(hitboxes); i++)
				{
					ImGui::Selectable(hitboxes[i], &Vars.ragebot_hitbox[i][curGroup], ImGuiSelectableFlags_::ImGuiSelectableFlags_DontClosePopups);
					if (Vars.ragebot_hitbox[i][curGroup])
						vec.push_back(hitboxes[i]);
				}

				for (size_t i = 0; i < vec.size(); i++)
				{
					if (vec.size() == 1)
						prevValue += vec.at(i);
					else if (i != vec.size())
						prevValue += vec.at(i) + ", ";
					else
						prevValue += vec.at(i);
				}
				ImGui::EndCombo();
			} 
			ImGui::PopItemWidth();
		}
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		{
			ImGui::PushItemWidth(142);
			ImGui::Text("Multipoint Scale");
			for (int i = 0; i < 8; i++) {
				if (Vars.ragebot_hitbox[i])
					ImGui::SliderFloat(hitboxes[i], &Vars.ragebot_hitbox_multipoint_scale[i][curGroup], 0.f, 1.f);
			}
			ImGui::PopItemWidth();
		}
		ImGui::EndGroup();
	}
}

void CMenu::RenderVisualsTab()
{
	static int selected = 0;

	if (ImGui::ButtonSelectable(("Players"), ImVec2(135, 40), selected == 0, forTabs_text, forTabs_text_x2))
		selected = 0;
	ImGui::SameLine();
	if (ImGui::ButtonSelectable(("Misc##Visuals_tab"), ImVec2(135, 40), selected == 1, forTabs_text, forTabs_text_x2))
		selected = 1;
	ImGui::SameLine();
	if (ImGui::ButtonSelectable(("Colors##Visuals_tab"), ImVec2(135, 40), selected == 2, forTabs_text, forTabs_text_x2))
		selected = 2;

	switch (selected)
	{
	case 0:
		ImGui::BeginGroup();
		ImGui::Checkbox(("Enable esp"), &Vars.esp_enabled);
		ImGui::Checkbox(("Ignore team"), &Vars.esp_ignore_team);
		ImGui::Checkbox(("Visible only"), &Vars.esp_visible_only);

		ImGui::Spacing();
		ImGui::Checkbox(("Box"), &Vars.esp_player_boxes);
		ImGui::Checkbox(("Health"), &Vars.esp_player_health);
		ImGui::Checkbox(("Name"), &Vars.esp_player_names);
		ImGui::Checkbox(("Weapon"), &Vars.esp_player_weapons);

		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		ImGui::Checkbox(("Enable chams##CHAMS"), &Vars.chams_player_enabled);
		ImGui::Checkbox(("Ignore team##CHAMS"), &Vars.chams_player_ignore_team);
		ImGui::Checkbox(("Visible only##CHAMS"), &Vars.chams_player_visible_only);
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		ImGui::Checkbox(("Enable glow##GLOW"), &Vars.glow_enabled);
		ImGui::Checkbox(("Ignore team##GLOW"), &Vars.glow_ignore_team);
		ImGui::Checkbox(("Visible only##GLOW"), &Vars.glow_visible_only);
		ImGui::EndGroup();
		break;
	case 1:
		ImGui::BeginGroup();

		ImGui::Text(("Item ESP"));
		ImGui::Checkbox(("Enable"), &Vars.esp_drop_enable);
		ImGui::PushItemWidth(150);
		ImGui::Text(("Distance"));
		ImGui::SliderInt(("##Distance"), &Vars.esp_drop_distance, 0, 3500);
		ImGui::PopItemWidth();
		ImGui::BeginChild(("##itemesp"), ImVec2(150, 200));
		ImGui::Checkbox(("Dropped Weapons"), &Vars.esp_dropped_weapons);
		ImGui::Checkbox(("Planted C4"), &Vars.esp_planted_c4);
		ImGui::Checkbox(("Pistol Case"), &Vars.esp_case_pistol);
		ImGui::Checkbox(("Light Case"), &Vars.esp_case_light_weapon);
		ImGui::Checkbox(("Heavy Case"), &Vars.esp_case_heavy_weapon);
		ImGui::Checkbox(("Explosive Case"), &Vars.esp_case_explosive);
		ImGui::Checkbox(("Tools case"), &Vars.esp_case_tools);
		ImGui::Checkbox(("Airdrop"), &Vars.esp_random);
		ImGui::Checkbox(("Full Armor"), &Vars.esp_dz_armor_helmet);
		ImGui::Checkbox(("Helmet"), &Vars.esp_dz_helmet);
		ImGui::Checkbox(("Armor"), &Vars.esp_dz_armor);
		ImGui::Checkbox(("Tablet Upgrade"), &Vars.esp_upgrade_tablet);
		ImGui::Checkbox(("Briefcase"), &Vars.esp_briefcase);
		ImGui::Checkbox(("Parachute"), &Vars.esp_parachutepack);
		ImGui::Checkbox(("Cash Dufflebag"), &Vars.esp_dufflebag);
		ImGui::Checkbox(("Ammobox"), &Vars.esp_ammobox);
		ImGui::EndChild();
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		ImGui::Text(("Misc visuals"));
		ImGui::BeginChild(("##othervisuals"), ImVec2(150, 200));
		ImGui::Checkbox(("Spread Xair"), &Vars.visuals_spreadxair);
		ImGui::Checkbox(("Crosshair"), &Vars.visuals_crosshair);
		ImGui::Checkbox(("No visual recoil"), &Vars.visuals_norecoil);
		ImGui::Checkbox(("No flash"), &Vars.visuals_noflash);

		if (ImGui::Checkbox(("Nightmode"), &Vars.visuals_nightmode))
			CNightmode::Get().PerformNightmode();

		ImGui::Checkbox(("Remove scope borders"), &Vars.visuals_noscopeborder);
		ImGui::Checkbox(("Thirdperson"), &Vars.visuals_thirdperson); ImGui::SameLine();
		ImGui::PushItemWidth(60);
		ImGui::Combo(("##key"), &Vars.visuals_thirdperson_key, AllKeys, IM_ARRAYSIZE(AllKeys));
		ImGui::PopItemWidth();
		ImGui::Checkbox(("Watermark"), &Vars.visuals_watermark);

		ImGui::EndChild();

		ImGui::EndGroup();
		break;
	case 2:
		ImGui::BeginGroup();
		ImGui::Text(("Esp"));
		ImGui::ColorEdit4(("Enemy visible##esp"), Vars.color_esp_enemy_visible, ImGuiColorEditFlags_NoInputs);
		ImGui::ColorEdit4(("Enemy hidden##esp"), Vars.color_esp_enemy_hidden, ImGuiColorEditFlags_NoInputs);
		ImGui::ColorEdit4(("Team visible##esp"), Vars.color_esp_team_visible, ImGuiColorEditFlags_NoInputs);
		ImGui::ColorEdit4(("Team hidden##esp"), Vars.color_esp_team_hidden, ImGuiColorEditFlags_NoInputs);
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		ImGui::Text(("Chams"));
		ImGui::ColorEdit4(("Enemy visible##chams"), Vars.color_chams_enemy_visible, ImGuiColorEditFlags_NoInputs);
		ImGui::ColorEdit4(("Enemy hidden##chams"), Vars.color_chams_enemy_hidden, ImGuiColorEditFlags_NoInputs);
		ImGui::ColorEdit4(("Team visible##chams"), Vars.color_chams_team_visible, ImGuiColorEditFlags_NoInputs);
		ImGui::ColorEdit4(("Team hidden##chams"), Vars.color_chams_team_hidden, ImGuiColorEditFlags_NoInputs);
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		ImGui::Text(("Glow"));
		ImGui::ColorEdit4(("Enemy visible##glow"), Vars.color_glow_enemy_visible, ImGuiColorEditFlags_NoInputs);
		ImGui::ColorEdit4(("Enemy hidden##glow"), Vars.color_glow_enemy_hidden, ImGuiColorEditFlags_NoInputs);
		ImGui::ColorEdit4(("Team visible##glow"), Vars.color_glow_team_visible, ImGuiColorEditFlags_NoInputs);
		ImGui::ColorEdit4(("Team hidden##glow"), Vars.color_glow_team_hidden, ImGuiColorEditFlags_NoInputs);
		ImGui::EndGroup();
		break;
	}
}

void CMenu::RenderMiscTab()
{
	ImGui::PushItemWidth(150);

	ImGui::Checkbox(("BunnyHop"), &Vars.misc_bhop);
	ImGui::Checkbox(("FastDuck"), &Vars.misc_fastduck);
	ImGui::Checkbox(("AutoStrafe"), &Vars.misc_autostrafe);
	ImGui::Checkbox(("Clantag"), &Vars.misc_clantag);
	ImGui::Checkbox(("AutoAccept"), &Vars.misc_autoaccept);
	//ImGui::Checkbox(("AntiKick"), &Vars.misc_antikick);
	ImGui::Checkbox(("Spectator List"), &Vars.misc_spectlist);
	ImGui::SliderInt(("Override fov"), &Vars.misc_overridefov, 0, 180);
	ImGui::Checkbox("Force in scope", &Vars.misc_overridefov_inscope);
	ImGui::SliderInt(("Viewmodel fov"), &Vars.misc_viewmodelfov, 0, 180);

	//ImGui::Checkbox(("Fake Latency"), &Vars.misc_latency_enable);
	//ImGui::PushItemWidth(150);
	//ImGui::SliderInt(("##latency_amt"), &Vars.misc_latency_amt, 0, 500);

}

void CMenu::MainFrame()
{
	if (!Globals::MenuOpened)
		return;

	ImGui::SetNextWindowSize(ImVec2(600, 381));
	if (ImGui::BeginAndroid(("nixwaree1337"), &Globals::MenuOpened, true, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar))
	{
		ImGui::GetWindowDrawList()->AddRectFilledMultiColor(ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowSize().x / 2, ImGui::GetWindowPos().y - 6), ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowSize().x, ImGui::GetWindowPos().y + 2), Vars.barColor1.x, Vars.barColor1.y, Vars.barColor1.h, Vars.barColor1.w);
		ImGui::GetWindowDrawList()->AddRectFilledMultiColor(ImVec2(ImGui::GetWindowPos().x - 5, ImGui::GetWindowPos().y - 6), ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowSize().x / 2, ImGui::GetWindowPos().y + 2), Vars.barColor2.x, Vars.barColor2.y, Vars.barColor2.h, Vars.barColor2.w);
		ImGui::Spacing();
		ImGui::BeginChild("##tabs", ImVec2(125, 338));
		{
			ImGui::SameLine(18);
			ImGui::Dummy(ImVec2(0, 30 ));

			ImGui::Dummy(ImVec2(0, 0));

			ImGui::PushFont(forTabs_text);

			if (ImGui::MyButton(("Legitbot"), AIMBOT, forTabs, tabselected == 0, ImVec2(130, 40)))
				tabselected = 0;
			if (ImGui::MyButton(("Ragebot"), RAGE, forTabs, tabselected == 1, ImVec2(130, 40)))
				tabselected = 1;
			if (ImGui::MyButton(("Visuals"), VISUALS, forTabs, tabselected == 2, ImVec2(130, 40)))
				tabselected = 2;
			if (ImGui::MyButton(("Skins"), SKINS, forTabs, tabselected == 3, ImVec2(130, 40)))
				tabselected = 3;
			if (ImGui::MyButton(("Misc"), MISC, forTabs, tabselected == 4, ImVec2(130, 40)))
				tabselected = 4;
			ImGui::PopFont();
		}
		ImGui::EndChild();

		ImGui::SameLine();
		ImGui::BeginGroup();
		{
			switch (tabselected)
			{
			case 0:
				RenderLegitbotTab();
				break;
			case 1: 
				RenderRagebotTab();
				break;
			case 2:
				RenderVisualsTab();
				break;
			case 3:
				RenderSkinsTab();
				break;
			case 4:
				RenderMiscTab();
				break;
			}
		}
		ImGui::EndGroup();

		ImGui::BeginGroup();
		/*if (ImGui::ButtonGradientEx(("Unload"), ImVec2(110, 24)))
			ImGui::OpenPopup(("Unload window"));

		bool open = true;
		if (ImGui::BeginPopupModal(("Unload window"), &open))
		{
			ImGui::Text(("Are you sure?"));
			ImGui::Spacing();
			if (ImGui::Button(("Unload")))
				g_Unload = true;
			ImGui::SameLine();
			if (ImGui::Button(("Cancel")))
				ImGui::CloseCurrentPopup();
			ImGui::EndPopup();
		}
		ImGui::SameLine();*/
		
		ImGui::PushItemWidth(140);
		ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.045f, 0.045f, 0.045f, 1.00f));

		ImGui::Combo(("##configselect"), &a1, items, ARRAYSIZE(items));
		ImGui::PopStyleColor();

		ImGui::PopItemWidth();

		ImGui::SameLine();

		if (ImGui::ButtonGradientEx(("Load"), ImVec2(140, 24)))
		{
			CConfig::Get().Load(items[a1]);
			CSkinChanger::Get().Update();
		}
		ImGui::SameLine();
		if (ImGui::ButtonGradientEx(("Save"), ImVec2(140, 24)))
		{
			CConfig::Get().Save(items[a1]);
		}
		ImGui::SameLine();
		/*if (ImGui::Button(("Rehook"), ImVec2(69, 23)))
		{
			Hooks::net_channel_hook_manager.~vfunc_hook();
			Hooks::net_channel_hook_manager.setup(reinterpret_cast<DWORD**>(Interfaces::ClientState->m_NetChannel));
			Hooks::oSendDatagram = Hooks::net_channel_hook_manager.get_original<Hooks::SendDatagram_t>(index::SendDatagram);
			Hooks::net_channel_hook_manager.hook_index(index::SendDatagram, Hooks::hkSendDatagram);
		}
		ImGui::SameLine();*/
		if (ImGui::ButtonGradientEx(("Radio"), ImVec2(140, 24)))
		{
			Globals::RadioOpened = !Globals::RadioOpened;
		}
		//ImGui::Checkbox(("PlayerList"), &CMenu::Get().PlayerListOpened);

		ImGui::EndGroup();
		ImGui::End();
	}
}

bool CMenu::Initialize(IDirect3DDevice9* device)
{
	static bool once = false;
	if (!once)
	{
		HWND hWindow = FindWindowA(("Valve001"), 0);

		ImGui_ImplDX9_Init(hWindow, device);
		ImGuiStyle& style = ImGui::GetStyle();

		ImStyles(ImGui::GetStyle());
		ImColors(ImGui::GetStyle());

		ImGui::GetIO().FontDefault = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(Ubuntu_compressed_data, Ubuntu_compressed_size, 13, NULL, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
		forTabs = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(IconsForTabs_compressed_data, IconsForTabs_compressed_size, 25, NULL, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
		forTabs_text = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(Ubuntu_compressed_data, Ubuntu_compressed_size, 15, NULL, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
		forTabs_text_x2 = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(Ubuntu_compressed_data, Ubuntu_compressed_size, 18, NULL, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());

		ImGui_ImplDX9_CreateDeviceObjects();
		original_proc = (WNDPROC)SetWindowLongA(hWindow, GWL_WNDPROC, (LONG)(LONG_PTR)proc);

		ImFontConfig config;
		config.FontDataOwnedByAtlas = false;

		ImGui::GetIO().IniFilename = nullptr;
		once = true;
	}
	return once;
}

void CMenu::SpectatorListFrame()
{
	if (!Vars.misc_spectlist)
		return;

	int specs = 0;
	int modes = 0;
	std::string spect = "";
	std::string mode = "";
	int DrawIndex = 1;

	for (int playerId : Utils::GetObservervators(Interfaces::Engine->GetLocalPlayer()))
	{
		if (playerId == Interfaces::Engine->GetLocalPlayer())
			continue;

		C_BasePlayer* pPlayer = (C_BasePlayer*)Interfaces::EntityList->GetClientEntity(playerId);

		if (!pPlayer)
			continue;

		player_info_t Pinfo;
		Interfaces::Engine->GetPlayerInfo(playerId, &Pinfo);

		if (Pinfo.fakeplayer)
			continue;

		spect += Pinfo.szName;
		spect += "\n";
		specs++;

		if (spect != "")
		{
			Color PlayerObsColor;
			switch (pPlayer->m_iObserverMode())
			{
			case 4:
				mode += ("Perspective");
				break;
			case 5:
				mode += ("3rd Person");
				break;
			case 6:
				mode += ("Free look");
				break;
			case 1:
				mode += ("Deathcam");
				break;
			case 2:
				mode += ("Freezecam");
				break;
			case 3:
				mode += ("Fixed");
				break;
			default:
				break;
			}

			mode += "\n";
			modes++;
		}
	}
	bool misc_Spectators = true;

	if (ImGui::BeginAndroid(("Spectator List - Nixware"), &misc_Spectators, false, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollWithMouse))
	{
		ImGui::GetWindowDrawList()->AddRectFilledMultiColor(ImVec2(ImGui::GetWindowPos().x + 100, ImGui::GetWindowPos().y - 6), ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowSize().x, ImGui::GetWindowPos().y + 2), Vars.barColor1.x, Vars.barColor1.y, Vars.barColor1.h, Vars.barColor1.w);
		ImGui::GetWindowDrawList()->AddRectFilledMultiColor(ImVec2(ImGui::GetWindowPos().x - 5, ImGui::GetWindowPos().y - 6), ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowSize().x / 2, ImGui::GetWindowPos().y + 2), Vars.barColor2.x, Vars.barColor2.y, Vars.barColor2.h, Vars.barColor2.w);
		if (specs > 0) spect += "\n";     /*ËÀÑÒ*/
		if (modes > 0) mode += "\n";
		ImVec2 size = ImGui::CalcTextSize(spect.c_str());

		ImGui::SetWindowSize(ImVec2(200, 25 + size.y));
		ImGui::Columns(2);

		ImGui::Text(("Name"));
		ImGui::NextColumn();

		ImGui::Text(("Mode"));
		ImGui::NextColumn();
		ImGui::Separator();

		ImGui::Text(spect.c_str());
		ImGui::NextColumn();

		ImGui::Text(mode.c_str());
		ImGui::Columns(1);
		DrawIndex++;
	}
	ImGui::End();
}

void CMenu::EndScene(IDirect3DDevice9* device)
{	
	Globals::WeaponTabValid = Utils::IsInGame() && Globals::LocalPlayer->IsAlive() && Globals::LocalPlayer->m_hActiveWeapon()->IsGun();

	if (CMenu::Initialize(device))
	{
		if (Utils::IsKeyPressed(VK_INSERT))
			Globals::MenuOpened = !Globals::MenuOpened;

		if (isSkeet) {
			Vars.barColor1 = CVariables::Colour4(ImColor(201, 84, 192), ImColor(204, 227, 54), ImColor(204, 227, 54), ImColor(201, 84, 192));
			Vars.barColor2 = CVariables::Colour4(ImColor(55, 177, 218), ImColor(201, 84, 192), ImColor(201, 84, 192), ImColor(55, 177, 218));
		}
		else {
			Vars.barColor1 = CVariables::Colour4(ImColor(255, 0, 0), ImColor(255, 0, 0), ImColor(255, 0, 0), ImColor(255, 0, 0));
			Vars.barColor2 = CVariables::Colour4(ImColor(255, 0, 0), ImColor(255, 0, 0), ImColor(255, 0, 0), ImColor(255, 0, 0));
		}

		DWORD dwOld_D3DRS_COLORWRITEENABLE; IDirect3DVertexDeclaration9* vertDec; IDirect3DVertexShader9* vertShader;
		device->GetRenderState(D3DRS_COLORWRITEENABLE, &dwOld_D3DRS_COLORWRITEENABLE);
		device->GetVertexDeclaration(&vertDec);
		device->GetVertexShader(&vertShader);
		device->SetRenderState(D3DRS_COLORWRITEENABLE, 0xffffffff);
		device->SetRenderState(D3DRS_SRGBWRITEENABLE, false);
		device->SetSamplerState(NULL, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
		device->SetSamplerState(NULL, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
		device->SetSamplerState(NULL, D3DSAMP_ADDRESSW, D3DTADDRESS_WRAP);
		device->SetSamplerState(NULL, D3DSAMP_SRGBTEXTURE, NULL);
		ImGui_ImplDX9_NewFrame();

		CMenu::MainFrame();
		CMenu::RadioFrame();
		CMenu::PlayerListFrame();
		CMenu::SpectatorListFrame();

		ImGui::Render();
		device->SetRenderState(D3DRS_COLORWRITEENABLE, dwOld_D3DRS_COLORWRITEENABLE);
		device->SetRenderState(D3DRS_SRGBWRITEENABLE, true);
		device->SetVertexDeclaration(vertDec);
		device->SetVertexShader(vertShader);
	}
} 

void CMenu::InvalidateDeviceObjects() { ImGui_ImplDX9_InvalidateDeviceObjects(); }
void CMenu::CreateDeviceObjects() { ImGui_ImplDX9_CreateDeviceObjects(); }