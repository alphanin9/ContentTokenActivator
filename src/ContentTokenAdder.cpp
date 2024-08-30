#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

#include <RED4ext/Scripting/Natives/Generated/quest/QuestsContentSystem.hpp>

using namespace Red;

namespace QuestExtensions
{
struct ContentTokenCall
{
    // m_unkArray[1] is set to 0
    // m_unkArray[0] is set to node->forceCreatingToken
    // m_unkInt is set to 3 in our case

    // Other nodes using content token system for spawning/removing token use the same kind of structure too, with different m_unkInt

    std::int64_t m_unkArray[2];
    int m_unkInt;

    ContentTokenCall()
        : m_unkInt(3)
    {
        m_unkArray[0] = true;
        m_unkArray[1] = 0;
    }
};

class ContentHandler
{
public:
    using VFuncSignature = void(__fastcall*)(quest::QuestsContentSystem* aThis, ContentTokenCall* aStruct);

    static constexpr auto m_funcAddrHash = 2770409958u;

    static void ActivateToken()
    {
        auto questContentSystem = GetGameSystem<quest::QuestsContentSystem>();

        if (!questContentSystem)
        {
            return;
        }

        static const auto func = UniversalRelocFunc<VFuncSignature>(m_funcAddrHash);

        // Maybe make it static? Meh, it doesn't use much CPU time anyway...
        ContentTokenCall data{};

        func(questContentSystem, &data);
    }
};
}

RTTI_DEFINE_CLASS(QuestExtensions::ContentHandler, {
    RTTI_METHOD(ActivateToken);
});
