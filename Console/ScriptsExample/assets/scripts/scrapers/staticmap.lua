-- Static map scraper (Lua) — gui.farm primary, mapmap.ai fallback (no API key).
-- args: latitude, longitude, outpath (required); address, width, height, zoom, timeout (optional)
-- results: ok ("1"|"0"), path, provider

function main()
  local lat
  local lon
  local address
  local outpath
  local url
  local place
  local wstr
  local hstr
  local zstr
  local width
  local height
  local zoom
  local timeout
  local ok

  ok = 0
  lat     = Scraper_GetArg("latitude")
  lon     = Scraper_GetArg("longitude")
  address = Scraper_GetArg("address")
  outpath = Scraper_GetArg("outpath")
  width   = Scraper_GetArgInt("width")
  height  = Scraper_GetArgInt("height")
  zoom    = Scraper_GetArgInt("zoom")
  timeout = Scraper_GetArgInt("timeout")

  if timeout <= 0 then
    timeout = 10
  end
  if width <= 0 then
    width = 240
  end
  if height <= 0 then
    height = 140
  end
  if zoom <= 0 then
    zoom = 11
  end

  Scraper_SetResult("ok", "0")

  if IsEmptyString(outpath) then
    return 0
  end

  if IsEmptyString(lat) or IsEmptyString(lon) then
    if IsEmptyString(address) then
      return 0
    end
    place = ReplaceAllString(address, " ", "+")
  else
    place = AddString(lat, ",")
    place = AddString(place, lon)
  end

  wstr = SPrintf("", "%d", width)
  hstr = SPrintf("", "%d", height)
  zstr = SPrintf("", "%d", zoom)

  url = "https://gui.farm/tools/map-generator.png?place="
  url = AddString(url, place)
  url = AddString(url, "&mode=light&color=red&ratio=16:9&width=")
  url = AddString(url, wstr)
  url = AddString(url, "&zoom=")
  url = AddString(url, zstr)

  if WebClient_GetToFile(url, outpath, "", timeout) then
    if IsItExists(outpath) then
      Scraper_SetResult("path", outpath)
      Scraper_SetResult("provider", "gui.farm")
      Scraper_SetResult("ok", "1")
      ok = 1
    end
  end

  if ok == 0 then
    if (not IsEmptyString(lat)) and (not IsEmptyString(lon)) then
      url = "https://mapmap.ai/api/static-map?center="
      url = AddString(url, lon)
      url = AddString(url, ",")
      url = AddString(url, lat)
      url = AddString(url, "&zoom=")
      url = AddString(url, zstr)
      url = AddString(url, "&size=")
      url = AddString(url, wstr)
      url = AddString(url, "x")
      url = AddString(url, hstr)

      if WebClient_GetToFile(url, outpath, "", timeout) then
        if IsItExists(outpath) then
          Scraper_SetResult("path", outpath)
          Scraper_SetResult("provider", "mapmap.ai")
          Scraper_SetResult("ok", "1")
          ok = 1
        end
      end
    end
  end

  return ok
end

return main()
