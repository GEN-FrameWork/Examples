int main()
{
  string location;
  location = Scraper_GetArg("location");
  Scraper_SetResult("ok", "1");
  Scraper_SetResult("condition", "Clear");
  Scraper_SetResult("temperature", "21.5");
  Scraper_SetResult("humidity", "55");
  return 1;
}
