// MAC Manufacturer scraper — api.maclookup.app primary, api.macvendors.com fallback (no API key).
// Contract:
//   args   : mac (required), timeout (optional)
//   results: ok, manufacturer
// Note: do not put '{' / '}' inside G string literals — PreScan brace balance.

int main()
{
  string mac;
  string url;
  string body;
  string manufacturer;
  int    timeout;
  int    ok;

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

  url = "https://api.maclookup.app/v2/macs/";
  url = AddString(url, mac);
  if(WebClient_Get(url, "", timeout))
    {
      body = WebClient_GetBody();
      manufacturer = ExtractBetween(body, "\"company\":\"", "\"");
    }

  if(IsEmptyString(manufacturer))
    {
      url = "https://api.macvendors.com/";
      url = AddString(url, mac);
      if(WebClient_Get(url, "", timeout))
        {
          body = WebClient_GetBody();
          // JSON error payloads include "detail" — keep plain-text vendor names only.
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
