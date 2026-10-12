int main()
{
  string text;
  string tl;
  text = Scraper_GetArg("text");
  tl = Scraper_GetArg("tl");
  Scraper_SetResult("ok", "1");
  Scraper_SetResult("translation", "Hola Mundo");
  Scraper_SetResult("detected", "en");
  return 1;
}
