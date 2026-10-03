// User-Agent ID scraper (JavaScript) — useragentstring.com primary + non-www HTTP fallback
// args: ua (URL-encoded User-Agent, required), timeout (optional)
// results: ok, browser, browser_version, browser_type, os, os_type, os_version, language, language_tag

function main()
{
  var ua;
  var url;
  var body;
  var browser;
  var browserversion;
  var browsertype;
  var osname;
  var ostype;
  var osversion;
  var language;
  var languagetag;
  var timeout;
  var ok;

  ok = 0;
  ua = Scraper_GetArg("ua");
  timeout = Scraper_GetArgInt("timeout");
  if(timeout <= 0)
    {
      timeout = 10;
    }

  Scraper_SetResult("ok", "0");

  if(IsEmptyString(ua))
    {
      return 0;
    }

  url = AddString("https://www.useragentstring.com/?uas=", ua);
  url = AddString(url, "&getJSON=all");
  if(WebClient_Get(url, "", timeout))
    {
      body = WebClient_GetBody();
      browser        = ExtractBetween(body, "\"agent_name\":\"", "\"");
      browserversion = ExtractBetween(body, "\"agent_version\":\"", "\"");
      browsertype    = ExtractBetween(body, "\"agent_type\":\"", "\"");
      osname         = ExtractBetween(body, "\"os_name\":\"", "\"");
      ostype         = ExtractBetween(body, "\"os_type\":\"", "\"");
      osversion      = ExtractBetween(body, "\"os_versionNumber\":\"", "\"");
      if(IsEmptyString(osversion))
        {
          osversion = ExtractBetween(body, "\"os_versionName\":\"", "\"");
        }
      language    = ExtractBetween(body, "\"agent_language\":\"", "\"");
      languagetag = ExtractBetween(body, "\"agent_languageTag\":\"", "\"");
    }

  if(IsEmptyString(browser))
    {
      url = AddString("http://useragentstring.com/?uas=", ua);
      url = AddString(url, "&getJSON=all");
      if(WebClient_Get(url, "", timeout))
        {
          body = WebClient_GetBody();
          browser        = ExtractBetween(body, "\"agent_name\":\"", "\"");
          browserversion = ExtractBetween(body, "\"agent_version\":\"", "\"");
          browsertype    = ExtractBetween(body, "\"agent_type\":\"", "\"");
          osname         = ExtractBetween(body, "\"os_name\":\"", "\"");
          ostype         = ExtractBetween(body, "\"os_type\":\"", "\"");
          osversion      = ExtractBetween(body, "\"os_versionNumber\":\"", "\"");
          if(IsEmptyString(osversion))
            {
              osversion = ExtractBetween(body, "\"os_versionName\":\"", "\"");
            }
          language    = ExtractBetween(body, "\"agent_language\":\"", "\"");
          languagetag = ExtractBetween(body, "\"agent_languageTag\":\"", "\"");
        }
    }

  if(!IsEmptyString(browser))
    {
      Scraper_SetResult("browser", browser);
      Scraper_SetResult("browser_version", browserversion);
      Scraper_SetResult("browser_type", browsertype);
      Scraper_SetResult("os", osname);
      Scraper_SetResult("os_type", ostype);
      Scraper_SetResult("os_version", osversion);
      Scraper_SetResult("language", language);
      Scraper_SetResult("language_tag", languagetag);
      Scraper_SetResult("ok", "1");
      ok = 1;
    }

  return ok;
}
