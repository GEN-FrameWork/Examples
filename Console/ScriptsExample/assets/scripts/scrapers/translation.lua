-- Translation scraper (Lua) — Google gtx primary, MyMemory fallback
-- args: text (required), tl (required), sl (optional), timeout (optional)
-- results: ok, translation, detected
-- Percent-encode query robustly. '%' uses a placeholder first because ReplaceAllString
-- re-scans and would loop forever on "%" → "%25".

function main()
  local text
  local sl
  local tl
  local q
  local url
  local body
  local translation
  local detected
  local pair
  local timeout
  local ok

  ok = 0
  text = Scraper_GetArg("text")
  sl   = Scraper_GetArg("sl")
  tl   = Scraper_GetArg("tl")
  timeout = Scraper_GetArgInt("timeout")
  if timeout <= 0 then
    timeout = 10
  end
  if IsEmptyString(sl) then
    sl = "auto"
  end

  Scraper_SetResult("ok", "0")

  if IsEmptyString(text) or IsEmptyString(tl) then
    return 0
  end

  q = text
  q = ReplaceAllString(q, "%", "__PCT__")
  q = ReplaceAllString(q, " ", "%20")
  q = ReplaceAllString(q, "\n", "%0A")
  q = ReplaceAllString(q, "\r", "%0D")
  q = ReplaceAllString(q, "\t", "%09")
  q = ReplaceAllString(q, "&", "%26")
  q = ReplaceAllString(q, "#", "%23")
  q = ReplaceAllString(q, "+", "%2B")
  q = ReplaceAllString(q, "?", "%3F")
  q = ReplaceAllString(q, "=", "%3D")
  q = ReplaceAllString(q, "\"", "%22")
  q = ReplaceAllString(q, "{", "%7B")
  q = ReplaceAllString(q, "}", "%7D")
  q = ReplaceAllString(q, "__PCT__", "%25")

  url = AddString("https://translate.googleapis.com/translate_a/single?client=gtx&sl=", sl)
  url = AddString(url, "&tl=")
  url = AddString(url, tl)
  url = AddString(url, "&dt=t&q=")
  url = AddString(url, q)

  if WebClient_Get(url, "", timeout) then
    body = WebClient_GetBody()
    translation = ExtractBetween(body, "[[[\"", "\",\"")
    detected = ExtractBetween(body, "]],null,\"", "\"")
    if IsEmptyString(detected) then
      detected = sl
    end

    if not IsEmptyString(translation) then
      Scraper_SetResult("translation", translation)
      Scraper_SetResult("detected", detected)
      Scraper_SetResult("ok", "1")
      ok = 1
    end
  end

  if ok == 0 then
    if CompareString(sl, "auto", 1) then
      pair = AddString("Autodetect|", tl)
    else
      pair = AddString(AddString(sl, "|"), tl)
    end

    url = AddString("https://api.mymemory.translated.net/get?q=", q)
    url = AddString(url, "&langpair=")
    url = AddString(url, pair)

    if WebClient_Get(url, "", timeout) then
      body = WebClient_GetBody()
      translation = ExtractBetween(body, "\"translatedText\":\"", "\"")
      detected = ExtractBetween(body, "\"detectedLanguage\":\"", "\"")
      if IsEmptyString(detected) then
        detected = sl
      end

      if (not IsEmptyString(translation)) and IsEmptyString(ExtractBetween(translation, "INVALID", "LANGUAGE")) then
        Scraper_SetResult("translation", translation)
        Scraper_SetResult("detected", detected)
        Scraper_SetResult("ok", "1")
        ok = 1
      end
    end
  end

  return ok
end

return main()
