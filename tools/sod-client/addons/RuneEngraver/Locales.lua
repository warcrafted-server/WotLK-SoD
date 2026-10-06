-- English strings are the fallback; add locale overrides below.
RuneEngraverNS = RuneEngraverNS or {}

local english = {
    ["Rune Engraver"] = "Rune Engraver",
    ["Engrave runes you've unlocked."] = "Engrave runes you've unlocked.",
    ["Debug: %s"] = "Debug: %s",
    ["On"] = "On",
    ["Off"] = "Off",
    ["Send: %s"] = "Send: %s",
    ["Search"] = "Search",
    ["Undiscovered"] = "Undiscovered",
    ["Unlocks at %d"] = "Unlocks at %d",
    ["(engraved)"] = "(engraved)",
    ["%d/%d Runes Collected"] = "%d/%d Runes Collected",
    ["You must learn Engraving to engrave runes."] = "You must learn Engraving to engrave runes.",
    ["Engraved: %s"] = "Engraved: %s",
}

local spanish = {
    ["Rune Engraver"] = "Grabador de runas",
    ["Engrave runes you've unlocked."] = "Graba las runas que has desbloqueado.",
    ["Debug: %s"] = "Depuración: %s",
    ["On"] = "activada",
    ["Off"] = "desactivada",
    ["Send: %s"] = "Enviado: %s",
    ["Search"] = "Buscar",
    ["Undiscovered"] = "Sin descubrir",
    ["Unlocks at %d"] = "se desbloquea en el nivel %d",
    ["(engraved)"] = "(grabada)",
    ["%d/%d Runes Collected"] = "%d/%d runas recogidas",
    ["You must learn Engraving to engrave runes."] = "Debes aprender a grabar runas antes de grabarlas.",
    ["Engraved: %s"] = "Grabado: %s",
}

local L = {}
for key, value in pairs(english) do
    L[key] = value
end

local locale = GetLocale()
if locale == "esES" or locale == "esMX" then
    for key, value in pairs(spanish) do
        L[key] = value
    end
end

setmetatable(L, {
    __index = function(_, key)
        return key
    end,
})

RuneEngraverNS.L = L
