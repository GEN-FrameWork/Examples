int main()
{
  string ua;
  ua = Scraper_GetArg("ua");
  Scraper_SetResult("ok", "1");
  Scraper_SetResult("browser", "Chrome");
  Scraper_SetResult("browser_version", "120.0.0.0");
  Scraper_SetResult("browser_type", "Browser");
  Scraper_SetResult("os", "Windows 10");
  Scraper_SetResult("os_type", "Windows");
  Scraper_SetResult("os_version", "10");
  Scraper_SetResult("language", "");
  Scraper_SetResult("language_tag", "");
  return 1;
}
