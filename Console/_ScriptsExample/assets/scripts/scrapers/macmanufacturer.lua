-- MAC Manufacturer scraper (Lua) — api.maclookup.app primary, api.macvendors.com fallback
-- args: mac (required), timeout (optional)
-- results: ok, manufacturer

function main()
  local mac
  local url
  local body
  local manufacturer
  local timeout
  local ok

  ok = 0
  mac = Scraper_GetArg("mac")
  timeout = Scraper_GetArgInt("timeout")
  if timeout <= 0 then
    timeout = 10
  end

  Scraper_SetResult("ok", "0")

  if IsEmptyString(mac) then
    return 0
  end

  url = AddString("https://api.maclookup.app/v2/macs/", mac)
  if WebClient_Get(url, "", timeout) then
    body = WebClient_GetBody()
    manufacturer = ExtractBetween(body, "\"company\":\"", "\"")
  end

  if IsEmptyString(manufacturer) then
    url = AddString("https://api.macvendors.com/", mac)
    if WebClient_Get(url, "", timeout) then
      body = WebClient_GetBody()
      if IsEmptyString(ExtractBetween(body, "\"detail\":\"", "\"")) then
        manufacturer = TrimString(body)
      end
    end
  end

  if not IsEmptyString(manufacturer) then
    Scraper_SetResult("manufacturer", manufacturer)
    Scraper_SetResult("ok", "1")
    ok = 1
  end

  return ok
end

return main()
