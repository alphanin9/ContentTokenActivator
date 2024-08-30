---@diagnostic disable: undefined-global
local g_context = {
    m_isInitialized = false,
    m_isInOverlay = false
}

local Spew = function(...)
    print("[Content token activator]", ...)
end

local IsInGame = function()
    local systemRequestsHandler = Game.GetSystemRequestsHandler()

    return not systemRequestsHandler:IsPreGame()
end

registerForEvent("onOverlayOpen", function()
    g_context.m_isInOverlay = true
end)

registerForEvent("onOverlayClose", function()
    g_context.m_isInOverlay = false
end)

registerForEvent("onDraw", function()
    if not g_context.m_isInitialized then
        return
    end

    if not g_context.m_isInOverlay then
        return
    end

    if not IsInGame() then
        return
    end

    if ImGui.Begin("Content token activator") then
        if ImGui.Button("Force a token activation") then
            ContentHandler.ActivateToken()
            Spew("Activated a content token!")
        end
    end
end)

registerForEvent("onInit", function()
    local pluginInstalled = pcall(function()
        return not not ContentHandler.ActivateToken
    end)

    if not pluginInstalled then
        Spew("Plugin is not installed correctly!")
        return
    end

    g_context.m_isInitialized = true

    Spew("Content token activator is ready...")
end)