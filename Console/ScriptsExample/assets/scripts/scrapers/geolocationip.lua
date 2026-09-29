-- Geolocation IP scraper (Lua) — ip-api.com + ipwho.is fallback
-- args: ip (required), timeout (optional)
-- results: ok, country, state, city, isp, organization, latitude, longitude

function main()
  local ip
  local url
  local body
  local country
  local region
  local city
  local isp
  local org
  local lat
  local lon
  local timeout
  local ok

  ok = 0
  ip = Scraper_GetArg("ip")
  timeout = Scraper_GetArgInt("timeout")
  if timeout <= 0 then
    timeout = 10
  end

  Scraper_SetResult("ok", "0")

  if IsEmptyString(ip) then
    return 0
  end

  url = AddString("http://ip-api.com/json/", ip)
  if WebClient_Get(url, "", timeout) then
    body = WebClient_GetBody()

    country = ExtractBetween(body, "\"country\":\"", "\"")
    region  = ExtractBetween(body, "\"regionName\":\"", "\"")
    city    = ExtractBetween(body, "\"city\":\"", "\"")
    isp     = ExtractBetween(body, "\"isp\":\"", "\"")
    org     = ExtractBetween(body, "\"org\":\"", "\"")
    lat     = ExtractBetween(body, "\"lat\":", ",")
    lon     = ExtractBetween(body, "\"lon\":", ",")

    if not IsEmptyString(country) and not IsEmptyString(city) then
      Scraper_SetResult("country", country)
      Scraper_SetResult("state", region)
      Scraper_SetResult("city", city)
      Scraper_SetResult("isp", isp)
      Scraper_SetResult("organization", org)
      Scraper_SetResult("latitude", lat)
      Scraper_SetResult("longitude", lon)
      Scraper_SetResult("ok", "1")
      ok = 1
    end
  end

  if ok == 0 then
    url = AddString("https://ipwho.is/", ip)
    if WebClient_Get(url, "", timeout) then
      body = WebClient_GetBody()

      country = ExtractBetween(body, "\"country\":\"", "\"")
      if IsEmptyString(country) then
        country = ExtractBetween(body, "\"country\": \"", "\"")
      end
      region = ExtractBetween(body, "\"region\":\"", "\"")
      if IsEmptyString(region) then
        region = ExtractBetween(body, "\"region\": \"", "\"")
      end
      city = ExtractBetween(body, "\"city\":\"", "\"")
      if IsEmptyString(city) then
        city = ExtractBetween(body, "\"city\": \"", "\"")
      end
      isp = ExtractBetween(body, "\"isp\":\"", "\"")
      if IsEmptyString(isp) then
        isp = ExtractBetween(body, "\"isp\": \"", "\"")
      end
      org = ExtractBetween(body, "\"org\":\"", "\"")
      if IsEmptyString(org) then
        org = ExtractBetween(body, "\"org\": \"", "\"")
      end
      lat = TrimString(ExtractBetween(body, "\"latitude\":", ","))
      lon = TrimString(ExtractBetween(body, "\"longitude\":", ","))

      if not IsEmptyString(country) and not IsEmptyString(city) then
        Scraper_SetResult("country", country)
        Scraper_SetResult("state", region)
        Scraper_SetResult("city", city)
        Scraper_SetResult("isp", isp)
        Scraper_SetResult("organization", org)
        Scraper_SetResult("latitude", lat)
        Scraper_SetResult("longitude", lon)
        Scraper_SetResult("ok", "1")
        ok = 1
      end
    end
  end

  return ok
end

return main()
