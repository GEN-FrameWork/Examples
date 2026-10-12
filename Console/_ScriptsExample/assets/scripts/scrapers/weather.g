// Weather scraper — Open-Meteo primary; Nominatim+forecast then wttr.in fallbacks (no API key).
// Contract:
//   args   : location (required), celsius (1/0), timeout (optional)
//   results: ok, condition, temperature, humidity
// Note: do not put '{' / '}' inside G string literals — PreScan brace balance.

int main()
{
  string location;
  string url;
  string body;
  string current;
  string lat;
  string lon;
  string temp;
  string humidity;
  string code;
  string condition;
  int    timeout;
  int    celsius;
  int    ok;

  ok = 0;
  location = Scraper_GetArg("location");
  celsius  = Scraper_GetArgInt("celsius");
  timeout  = Scraper_GetArgInt("timeout");
  if(timeout <= 0)
    {
      timeout = 10;
    }

  Scraper_SetResult("ok", "0");

  if(IsEmptyString(location))
    {
      return 0;
    }

  url = "https://geocoding-api.open-meteo.com/v1/search?name=";
  url = AddString(url, location);
  url = AddString(url, "&count=1");
  if(WebClient_Get(url, "", timeout))
    {
      body = WebClient_GetBody();
      lat  = ExtractBetween(body, "\"latitude\":", ",");
      lon  = ExtractBetween(body, "\"longitude\":", ",");

      if(!IsEmptyString(lat) && !IsEmptyString(lon))
        {
          url = "https://api.open-meteo.com/v1/forecast?latitude=";
          url = AddString(url, lat);
          url = AddString(url, "&longitude=");
          url = AddString(url, lon);
          url = AddString(url, "&current=temperature_2m,relative_humidity_2m,weather_code,is_day");
          if(celsius == 0)
            {
              url = AddString(url, "&temperature_unit=fahrenheit");
            }

          if(WebClient_Get(url, "", timeout))
            {
              body     = WebClient_GetBody();
              // Skip current_units (same keys, string values) — take the current object slice.
              current  = ExtractBetween(body, "\"current\":", ",\"is_day\"");
              temp     = ExtractBetween(current, "\"temperature_2m\":", ",");
              humidity = ExtractBetween(current, "\"relative_humidity_2m\":", ",");
              code     = ExtractBetween(body, "\"weather_code\":", ",\"is_day\"");
              condition = code;

              if(!CompareString(code, "0", 0)) condition = "Clear";
              if(!CompareString(code, "1", 0)) condition = "Mainly clear";
              if(!CompareString(code, "2", 0)) condition = "Partly cloudy";
              if(!CompareString(code, "3", 0)) condition = "Overcast";
              if(!CompareString(code, "45", 0)) condition = "Fog";
              if(!CompareString(code, "61", 0)) condition = "Rain";
              if(!CompareString(code, "71", 0)) condition = "Snow";
              if(!CompareString(code, "95", 0)) condition = "Thunderstorm";

              if(!IsEmptyString(temp) && !IsEmptyString(humidity))
                {
                  Scraper_SetResult("condition", condition);
                  Scraper_SetResult("temperature", temp);
                  Scraper_SetResult("humidity", humidity);
                  Scraper_SetResult("ok", "1");
                  ok = 1;
                }
            }
        }
    }

  if(ok == 0)
    {
      // Fallback geocoding: Nominatim (needs User-Agent) + Open-Meteo forecast.
      url = "https://nominatim.openstreetmap.org/search?q=";
      url = AddString(url, location);
      url = AddString(url, "&format=json&limit=1");
      if(WebClient_Get(url, "User-Agent: GEN-FrameWork-Scraper/1.0\r\n", timeout))
        {
          body = WebClient_GetBody();
          lat  = ExtractBetween(body, "\"lat\":\"", "\"");
          lon  = ExtractBetween(body, "\"lon\":\"", "\"");

          if(!IsEmptyString(lat) && !IsEmptyString(lon))
            {
              url = "https://api.open-meteo.com/v1/forecast?latitude=";
              url = AddString(url, lat);
              url = AddString(url, "&longitude=");
              url = AddString(url, lon);
              url = AddString(url, "&current=temperature_2m,relative_humidity_2m,weather_code,is_day");
              if(celsius == 0)
                {
                  url = AddString(url, "&temperature_unit=fahrenheit");
                }

              if(WebClient_Get(url, "", timeout))
                {
                  body      = WebClient_GetBody();
                  current   = ExtractBetween(body, "\"current\":", ",\"is_day\"");
                  temp      = ExtractBetween(current, "\"temperature_2m\":", ",");
                  humidity  = ExtractBetween(current, "\"relative_humidity_2m\":", ",");
                  code      = ExtractBetween(body, "\"weather_code\":", ",\"is_day\"");
                  condition = code;

                  if(!CompareString(code, "0", 0)) condition = "Clear";
                  if(!CompareString(code, "1", 0)) condition = "Mainly clear";
                  if(!CompareString(code, "2", 0)) condition = "Partly cloudy";
                  if(!CompareString(code, "3", 0)) condition = "Overcast";
                  if(!CompareString(code, "45", 0)) condition = "Fog";
                  if(!CompareString(code, "61", 0)) condition = "Rain";
                  if(!CompareString(code, "71", 0)) condition = "Snow";
                  if(!CompareString(code, "95", 0)) condition = "Thunderstorm";

                  if(!IsEmptyString(temp) && !IsEmptyString(humidity))
                    {
                      Scraper_SetResult("condition", condition);
                      Scraper_SetResult("temperature", temp);
                      Scraper_SetResult("humidity", humidity);
                      Scraper_SetResult("ok", "1");
                      ok = 1;
                    }
                }
            }
        }
    }

  if(ok == 0)
    {
      url = "https://wttr.in/";
      url = AddString(url, location);
      url = AddString(url, "?format=j1");
      if(WebClient_Get(url, "User-Agent: curl/8.0\r\n", timeout))
        {
          body = WebClient_GetBody();
          condition = TrimString(ExtractBetween(body, "\"value\":\"", "\""));
          humidity  = ExtractBetween(body, "\"humidity\":\"", "\"");
          if(celsius == 0)
            {
              temp = ExtractBetween(body, "\"temp_F\":\"", "\"");
            }
           else
            {
              temp = ExtractBetween(body, "\"temp_C\":\"", "\"");
            }

          if(!IsEmptyString(condition) && !IsEmptyString(temp) && !IsEmptyString(humidity))
            {
              Scraper_SetResult("condition", condition);
              Scraper_SetResult("temperature", temp);
              Scraper_SetResult("humidity", humidity);
              Scraper_SetResult("ok", "1");
              ok = 1;
            }
        }
    }

  return ok;
}
