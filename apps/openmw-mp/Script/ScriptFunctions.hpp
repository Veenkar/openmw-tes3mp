//
// Created by koncord on 24.01.16.
//

#ifndef SOURCEPAWN_SCRIPTFUNCTIONS_HPP
#define SOURCEPAWN_SCRIPTFUNCTIONS_HPP

#include <Script/Functions/CharClass.hpp>
#include <Script/Functions/Translocations.hpp>
#include <Script/Functions/GUI.hpp>
#include <Script/Functions/Stats.hpp>
#include <Script/Functions/Items.hpp>
#include <Script/Functions/World.hpp>
#include <RakNetTypes.h>
//#include <amx/amx.h>
#include <tuple>
#include <apps/openmw-mp/Player.hpp>
#include "ScriptFunction.hpp"
#include "Types.hpp"

#define GET_PLAYER(pid, pl, retvalue) \
     pl = Players::GetPlayer(pid); \
     if (player == 0) {\
        fprintf(stderr, "%s: Player with pid \'%d\' not found\n", __PRETTY_FUNCTION__, pid);\
        /*ScriptFunctions::StopServer(1);*/ \
        return retvalue;\
}


class ScriptFunctions
{
public:

    static void GetArguments(std::vector<boost::any> &params, va_list args, const std::string &def);

    static void StopServer(int code) noexcept;

    static void MakePublic(ScriptFunc _public, const char *name, char ret_type, const char *def) noexcept;
    static boost::any CallPublic(const char *name, ...) noexcept;

    static void SendMessage(unsigned short pid, const char *message, bool broadcast) noexcept;
    static void CleanChat(unsigned short pid);
    static void CleanChat();

    /**
     * \brief Create timer
     * \param callback
     * \param msec
     * \return return timer id
     */
    static int CreateTimer(ScriptFunc callback, int msec) noexcept;
    static int CreateTimerEx(ScriptFunc callback, int msec, const char *types, ...) noexcept;

    static void StartTimer(int timerId) noexcept;
    static void StopTimer(int timerId) noexcept;
    static void RestartTimer(int timerId, int msec) noexcept;
    static void FreeTimer(int timerId) noexcept;
    static bool IsTimerElapsed(int timerId) noexcept;

    static void Kick(unsigned short pid) noexcept;

    static constexpr ScriptFunctionData functions[]{
            {"CreateTimer",         ScriptFunctions::CreateTimer},
            {"CreateTimerEx",       reinterpret_cast<Function<void>>(ScriptFunctions::CreateTimerEx)},
            {"MakePublic",          ScriptFunctions::MakePublic},
            {"CallPublic",          reinterpret_cast<Function<void>>(ScriptFunctions::CallPublic)},


            {"StartTimer",          ScriptFunctions::StartTimer},
            {"StopTimer",           ScriptFunctions::StopTimer},
            {"RestartTimer",        ScriptFunctions::RestartTimer},
            {"FreeTimer",           ScriptFunctions::FreeTimer},
            {"IsTimerElapsed",      ScriptFunctions::IsTimerElapsed},

            {"StopServer",          ScriptFunctions::StopServer},

//            {"Cast",              ScriptFunctions::Cast},
            {"SendMessage",         ScriptFunctions::SendMessage},
            {"Kick",                ScriptFunctions::Kick},

            TRANSLOCATIONFUNCTIONS,
            STATSFUNCTIONS,
            ITEMAPI,
            GUIFUNCTIONS,
            CHARCLASSFUNCTIONS,
            WORLDFUNCTIONS,


    };

    static constexpr ScriptCallbackData callbacks[]{
            {"Main",                  Function<int, int, int>()},
            {"OnServerInit",          Function<void>()},
            {"OnServerExit",          Function<void, bool>()},
            {"OnPlayerConnect",       Function<bool, unsigned short>()},
            {"OnPlayerDisconnect",    Function<void, unsigned short>()},
            {"OnPlayerDeath",         Function<void, unsigned short>()},
            {"OnPlayerResurrect",     Function<void, unsigned short>()},
            {"OnPlayerChangeCell",    Function<void, unsigned short>()},
            {"OnPlayerChangeAttributes", Function<void, unsigned short>()},
            {"OnPlayerChangeSkills",  Function<void, unsigned short>()},
            {"OnPlayerUpdateEquiped", Function<void, unsigned short>()},
            {"OnPlayerSendMessage",   Function<bool, unsigned short, const char*>()},
            {"OnPlayerEndCharGen",    Function<void, unsigned short>()},
            {"OnGUIAction",           Function<void, unsigned short, int, const char*>()}
    };
};

#endif //SOURCEPAWN_SCRIPTFUNCTIONS_HPP