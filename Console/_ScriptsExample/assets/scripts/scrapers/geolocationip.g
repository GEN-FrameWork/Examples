// Geolocation IP scraper — ip-api.com + ipwho.is fallback (no API key).
// Contract:
//   args   : ip, timeout (optional)
//   results: ok, country, state, city, isp, organization, latitude, longitude
// Note: do not put '{' / '}' inside G string literals — PreScan brace balance ignores strings.

int main()
{
  string ip;
  string url;
  string body;
  string country;
  string region;
  string city;
  string isp;
  string org;
  string lat;
  string lon;
  int    timeout;
  int    ok;

  ok = 0;
  ip = Scraper_GetArg("ip");
  timeout = Scraper_GetArgInt("timeout");
  if(timeout <= 0)
    {
      timeout = 10;
    }

  Scraper_SetResult("ok", "0");

  if(IsEmptyString(ip))
    {
      return 0;
    }

  url = "http://ip-api.com/json/";
  url = AddString(url, ip);
  if(WebClient_Get(url, "", timeout))
    {
      body = WebClient_GetBody();

      country = ExtractBetween(body, "\"country\":\"", "\"");
      region  = ExtractBetween(body, "\"regionName\":\"", "\"");
      city    = ExtractBetween(body, "\"city\":\"", "\"");
      isp     = ExtractBetween(body, "\"isp\":\"", "\"");
      org     = ExtractBetween(body, "\"org\":\"", "\"");
      lat     = ExtractBetween(body, "\"lat\":", ",");
      lon     = ExtractBetween(body, "\"lon\":", ",");

      if(!IsEmptyString(country) && !IsEmptyString(city))
        {
          Scraper_SetResult("country", country);
          Scraper_SetResult("state", region);
          Scraper_SetResult("city", city);
          Scraper_SetResult("isp", isp);
          Scraper_SetResult("organization", org);
          Scraper_SetResult("latitude", lat);
          Scraper_SetResult("longitude", lon);
          Scraper_SetResult("ok", "1");
          ok = 1;
        }
    }

  if(ok == 0)
    {
      url = "https://ipwho.is/";
      url = AddString(url, ip);
      if(WebClient_Get(url, "", timeout))
        {
          body = WebClient_GetBody();

          // Compact or pretty-printed JSON (optional space after ':').
          country = ExtractBetween(body, "\"country\":\"", "\"");
          if(IsEmptyString(country))
            {
              country = ExtractBetween(body, "\"country\": \"", "\"");
            }
          region = ExtractBetween(body, "\"region\":\"", "\"");
          if(IsEmptyString(region))
            {
              region = ExtractBetween(body, "\"region\": \"", "\"");
            }
          city = ExtractBetween(body, "\"city\":\"", "\"");
          if(IsEmptyString(city))
            {
              city = ExtractBetween(body, "\"city\": \"", "\"");
            }
          isp = ExtractBetween(body, "\"isp\":\"", "\"");
          if(IsEmptyString(isp))
            {
              isp = ExtractBetween(body, "\"isp\": \"", "\"");
            }
          org = ExtractBetween(body, "\"org\":\"", "\"");
          if(IsEmptyString(org))
            {
              org = ExtractBetween(body, "\"org\": \"", "\"");
            }
          lat = TrimString(ExtractBetween(body, "\"latitude\":", ","));
          lon = TrimString(ExtractBetween(body, "\"longitude\":", ","));

          if(!IsEmptyString(country) && !IsEmptyString(city))
            {
              Scraper_SetResult("country", country);
              Scraper_SetResult("state", region);
              Scraper_SetResult("city", city);
              Scraper_SetResult("isp", isp);
              Scraper_SetResult("organization", org);
              Scraper_SetResult("latitude", lat);
              Scraper_SetResult("longitude", lon);
              Scraper_SetResult("ok", "1");
              ok = 1;
            }
        }
    }

  return ok;
}
