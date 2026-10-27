// Translation scraper — Google gtx primary, MyMemory fallback (no API key).
// Contract:
//   args   : text (required), tl (required), sl (optional, default auto), timeout (optional)
//   results: ok, translation, detected
// Note: do not put '{' / '}' inside G string literals — PreScan brace balance.
// Percent-encode query robustly. '%' uses a placeholder first because XSTRING::Replace
// re-scans and would loop forever on "%" → "%25".

int main()
{
  string text;
  string sl;
  string tl;
  string q;
  string url;
  string body;
  string translation;
  string detected;
  string pair;
  int    timeout;
  int    ok;

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

  // Percent-encode query. Shield '%' before emitting "%25" (Replace re-scans).
  // Braces via SPrintf — G PreScan forbids '{' / '}' inside string literals.
  string lb;
  string rb;
  lb = SPrintf("", "%c", 123);
  rb = SPrintf("", "%c", 125);

  q = text;
  q = ReplaceAllString(q, "%", "__PCT__");
  q = ReplaceAllString(q, " ", "%20");
  q = ReplaceAllString(q, "\n", "%0A");
  q = ReplaceAllString(q, "\r", "%0D");
  q = ReplaceAllString(q, "\t", "%09");
  q = ReplaceAllString(q, "&", "%26");
  q = ReplaceAllString(q, "#", "%23");
  q = ReplaceAllString(q, "+", "%2B");
  q = ReplaceAllString(q, "?", "%3F");
  q = ReplaceAllString(q, "=", "%3D");
  q = ReplaceAllString(q, "\"", "%22");
  q = ReplaceAllString(q, lb, "%7B");
  q = ReplaceAllString(q, rb, "%7D");
  q = ReplaceAllString(q, "__PCT__", "%25");

  url = "https://translate.googleapis.com/translate_a/single?client=gtx&sl=";
  url = AddString(url, sl);
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
          pair = "Autodetect|";
          pair = AddString(pair, tl);
        }
       else
        {
          pair = AddString(sl, "|");
          pair = AddString(pair, tl);
        }

      url = "https://api.mymemory.translated.net/get?q=";
      url = AddString(url, q);
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
