-- Weather scraper (Lua) — Open-Meteo primary, wttr.in fallback
-- args: location (required), celsius (1/0), timeout (optional)
-- results: ok, condition, temperature, humidity

function main()
  local location
  local url
  local body
  local current
  local lat
  local lon
  local temp
  local humidity
  local code
  local condition
  local timeout
  local celsius
  local ok

  ok = 0
  location = Scraper_GetArg("location")
  celsius  = Scraper_GetArgInt("celsius")
  timeout  = Scraper_GetArgInt("timeout")
  if timeout <= 0 then
    timeout = 10
  end

  Scraper_SetResult("ok", "0")

  if IsEmptyString(location) then
    return 0
  end

  url = AddString("https://geocoding-api.open-meteo.com/v1/search?name=", location)
  url = AddString(url, "&count=1")
  if WebClient_Get(url, "", timeout) then
    body = WebClient_GetBody()
    lat  = ExtractBetween(body, "\"latitude\":", ",")
    lon  = ExtractBetween(body, "\"longitude\":", ",")

    if (not IsEmptyString(lat)) and (not IsEmptyString(lon)) then
      url = AddString("https://api.open-meteo.com/v1/forecast?latitude=", lat)
      url = AddString(url, "&longitude=")
      url = AddString(url, lon)
      url = AddString(url, "&current=temperature_2m,relative_humidity_2m,weather_code,is_day")
      if celsius == 0 then
        url = AddString(url, "&temperature_unit=fahrenheit")
      end

      if WebClient_Get(url, "", timeout) then
        body      = WebClient_GetBody()
        current   = ExtractBetween(body, "\"current\":", ",\"is_day\"")
        temp      = ExtractBetween(current, "\"temperature_2m\":", ",")
        humidity  = ExtractBetween(current, "\"relative_humidity_2m\":", ",")
        code      = ExtractBetween(body, "\"weather_code\":", ",\"is_day\"")
        condition = code

        if not CompareString(code, "0", 0) then condition = "Clear" end
        if not CompareString(code, "1", 0) then condition = "Mainly clear" end
        if not CompareString(code, "2", 0) then condition = "Partly cloudy" end
        if not CompareString(code, "3", 0) then condition = "Overcast" end
        if not CompareString(code, "45", 0) then condition = "Fog" end
        if not CompareString(code, "61", 0) then condition = "Rain" end
        if not CompareString(code, "71", 0) then condition = "Snow" end
        if not CompareString(code, "95", 0) then condition = "Thunderstorm" end

        if (not IsEmptyString(temp)) and (not IsEmptyString(humidity)) then
          Scraper_SetResult("condition", condition)
          Scraper_SetResult("temperature", temp)
          Scraper_SetResult("humidity", humidity)
          Scraper_SetResult("ok", "1")
          ok = 1
        end
      end
    end
  end

  if ok == 0 then
    url = AddString("https://nominatim.openstreetmap.org/search?q=", location)
    url = AddString(url, "&format=json&limit=1")
    if WebClient_Get(url, "User-Agent: GEN-FrameWork-Scraper/1.0\r\n", timeout) then
      body = WebClient_GetBody()
      lat  = ExtractBetween(body, "\"lat\":\"", "\"")
      lon  = ExtractBetween(body, "\"lon\":\"", "\"")

      if (not IsEmptyString(lat)) and (not IsEmptyString(lon)) then
        url = AddString("https://api.open-meteo.com/v1/forecast?latitude=", lat)
        url = AddString(url, "&longitude=")
        url = AddString(url, lon)
        url = AddString(url, "&current=temperature_2m,relative_humidity_2m,weather_code,is_day")
        if celsius == 0 then
          url = AddString(url, "&temperature_unit=fahrenheit")
        end

        if WebClient_Get(url, "", timeout) then
          body      = WebClient_GetBody()
          current   = ExtractBetween(body, "\"current\":", ",\"is_day\"")
          temp      = ExtractBetween(current, "\"temperature_2m\":", ",")
          humidity  = ExtractBetween(current, "\"relative_humidity_2m\":", ",")
          code      = ExtractBetween(body, "\"weather_code\":", ",\"is_day\"")
          condition = code

          if not CompareString(code, "0", 0) then condition = "Clear" end
          if not CompareString(code, "1", 0) then condition = "Mainly clear" end
          if not CompareString(code, "2", 0) then condition = "Partly cloudy" end
          if not CompareString(code, "3", 0) then condition = "Overcast" end
          if not CompareString(code, "45", 0) then condition = "Fog" end
          if not CompareString(code, "61", 0) then condition = "Rain" end
          if not CompareString(code, "71", 0) then condition = "Snow" end
          if not CompareString(code, "95", 0) then condition = "Thunderstorm" end

          if (not IsEmptyString(temp)) and (not IsEmptyString(humidity)) then
            Scraper_SetResult("condition", condition)
            Scraper_SetResult("temperature", temp)
            Scraper_SetResult("humidity", humidity)
            Scraper_SetResult("ok", "1")
            ok = 1
          end
        end
      end
    end
  end

  if ok == 0 then
    url = AddString("https://wttr.in/", location)
    url = AddString(url, "?format=j1")
    if WebClient_Get(url, "User-Agent: curl/8.0\r\n", timeout) then
      body = WebClient_GetBody()
      condition = TrimString(ExtractBetween(body, "\"value\":\"", "\""))
      humidity  = ExtractBetween(body, "\"humidity\":\"", "\"")
      if celsius == 0 then
        temp = ExtractBetween(body, "\"temp_F\":\"", "\"")
      else
        temp = ExtractBetween(body, "\"temp_C\":\"", "\"")
      end

      if (not IsEmptyString(condition)) and (not IsEmptyString(temp)) and (not IsEmptyString(humidity)) then
        Scraper_SetResult("condition", condition)
        Scraper_SetResult("temperature", temp)
        Scraper_SetResult("humidity", humidity)
        Scraper_SetResult("ok", "1")
        ok = 1
      end
    end
  end

  return ok
end

return main()
