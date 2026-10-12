// MAC Manufacturer scraper (JavaScript) — api.maclookup.app primary, api.macvendors.com fallback
// args: mac (required), timeout (optional)
// results: ok, manufacturer

function main()
{
  var mac;
  var url;
  var body;
  var manufacturer;
  var timeout;
  var ok;

  ok = 0;
  mac = Scraper_GetArg("mac");
  timeout = Scraper_GetArgInt("timeout");
  if(timeout <= 0)
    {
      timeout = 10;
    }

  Scraper_SetResult("ok", "0");

  if(IsEmptyString(mac))
    {
      return 0;
    }

  url = AddString("https://api.maclookup.app/v2/macs/", mac);
  if(WebClient_Get(url, "", timeout))
    {
      body = WebClient_GetBody();
      manufacturer = ExtractBetween(body, "\"company\":\"", "\"");
    }

  if(IsEmptyString(manufacturer))
    {
      url = AddString("https://api.macvendors.com/", mac);
      if(WebClient_Get(url, "", timeout))
        {
          body = WebClient_GetBody();
          if(IsEmptyString(ExtractBetween(body, "\"detail\":\"", "\"")))
            {
              manufacturer = TrimString(body);
            }
        }
    }

  if(!IsEmptyString(manufacturer))
    {
      Scraper_SetResult("manufacturer", manufacturer);
      Scraper_SetResult("ok", "1");
      ok = 1;
    }

  return ok;
}
