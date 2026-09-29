// Translation scraper (JavaScript) — Google gtx primary, MyMemory fallback
// args: text (required), tl (required), sl (optional), timeout (optional)
// results: ok, translation, detected

function main()
{
  var text;
  var sl;
  var tl;
  var q;
  var url;
  var body;
  var translation;
  var detected;
  var pair;
  var timeout;
  var ok;

  ok = 0;
  text = Scraper_GetArg("text");
  sl   = Scraper_GetArg("sl");
  tl   = Scraper_GetArg("tl");
  timeout = Scraper_GetArgInt("timeout");
  if(timeout <= 0)
    {
      timeout = 10;
    }
  if(IsEmptyString(sl))
    {
      sl = "auto";
    }

  Scraper_SetResult("ok", "0");

  if(IsEmptyString(text) || IsEmptyString(tl))
    {
      return 0;
    }

  q = ReplaceAllString(text, " ", "%20");
  url = AddString("https://translate.googleapis.com/translate_a/single?client=gtx&sl=", sl);
  url = AddString(url, "&tl=");
  url = AddString(url, tl);
  url = AddString(url, "&dt=t&q=");
  url = AddString(url, q);

  if(WebClient_Get(url, "", timeout))
    {
      body = WebClient_GetBody();
      translation = ExtractBetween(body, "[[[\"", "\",\"");
      detected = ExtractBetween(body, "]],null,\"", "\"");
      if(IsEmptyString(detected))
        {
          detected = sl;
        }

      if(!IsEmptyString(translation))
        {
          Scraper_SetResult("translation", translation);
          Scraper_SetResult("detected", detected);
          Scraper_SetResult("ok", "1");
          ok = 1;
        }
    }

  if(ok == 0)
    {
      if(CompareString(sl, "auto", 1))
        {
          pair = AddString("Autodetect|", tl);
        }
       else
        {
          pair = AddString(AddString(sl, "|"), tl);
        }

      url = AddString("https://api.mymemory.translated.net/get?q=", q);
      url = AddString(url, "&langpair=");
      url = AddString(url, pair);

      if(WebClient_Get(url, "", timeout))
        {
          body = WebClient_GetBody();
          translation = ExtractBetween(body, "\"translatedText\":\"", "\"");
          detected = ExtractBetween(body, "\"detectedLanguage\":\"", "\"");
          if(IsEmptyString(detected))
            {
              detected = sl;
            }

          if(!IsEmptyString(translation) && IsEmptyString(ExtractBetween(translation, "INVALID", "LANGUAGE")))
            {
              Scraper_SetResult("translation", translation);
              Scraper_SetResult("detected", detected);
              Scraper_SetResult("ok", "1");
              ok = 1;
            }
        }
    }

  return ok;
}
