-- Public IP scraper (Lua) — api.ipify.org primary, ifconfig.me/ip fallback
-- args: timeout (optional)
-- results: ok ("1"|"0"), ip

function main()
  local body
  local ip
  local timeout
  local ok

  ok = 0
  timeout = Scraper_GetArgInt("timeout")
  if timeout <= 0 then
    timeout = 10
  end

  Scraper_SetResult("ok", "0")

  if WebClient_Get("https://api.ipify.org", "", timeout) then
    body = WebClient_GetBody()
    ip = TrimString(body)
    if not IsEmptyString(ip) then
      Scraper_SetResult("ip", ip)
      Scraper_SetResult("ok", "1")
      ok = 1
    end
  end

  if ok == 0 then
    if WebClient_Get("https://ifconfig.me/ip", "", timeout) then
      body = WebClient_GetBody()
      ip = TrimString(body)
      if not IsEmptyString(ip) then
        Scraper_SetResult("ip", ip)
        Scraper_SetResult("ok", "1")
        ok = 1
      end
    end
  end

  return ok
end

return main()
