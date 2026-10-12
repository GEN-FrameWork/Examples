// Public IP scraper (JavaScript) — api.ipify.org primary, ifconfig.me/ip fallback
// args: timeout (optional)
// results: ok ("1"|"0"), ip

function main()
{
  var body;
  var ip;
  var timeout;
  var ok;

  ok = 0;
  timeout = Scraper_GetArgInt("timeout");
  if(timeout <= 0)
    {
      timeout = 10;
    }

  Scraper_SetResult("ok", "0");

  if(WebClient_Get("https://api.ipify.org", "", timeout))
    {
      body = WebClient_GetBody();
      ip = TrimString(body);
      if(!IsEmptyString(ip))
        {
          Scraper_SetResult("ip", ip);
          Scraper_SetResult("ok", "1");
          ok = 1;
        }
    }

  if(ok == 0)
    {
      if(WebClient_Get("https://ifconfig.me/ip", "", timeout))
        {
          body = WebClient_GetBody();
          ip = TrimString(body);
          if(!IsEmptyString(ip))
            {
              Scraper_SetResult("ip", ip);
              Scraper_SetResult("ok", "1");
              ok = 1;
            }
        }
    }

  return ok;
}
