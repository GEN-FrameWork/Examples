// Geolocation IP scraper (JavaScript) — ip-api.com + ipwho.is fallback
// args: ip (required), timeout (optional)
// results: ok, country, state, city, isp, organization, latitude, longitude

function main()
{
  var ip;
  var url;
  var body;
  var country;
  var region;
  var city;
  var isp;
  var org;
  var lat;
  var lon;
  var timeout;
  var ok;

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

  url = AddString("http://ip-api.com/json/", ip);
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
      url = AddString("https://ipwho.is/", ip);
      if(WebClient_Get(url, "", timeout))
        {
          body = WebClient_GetBody();

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
