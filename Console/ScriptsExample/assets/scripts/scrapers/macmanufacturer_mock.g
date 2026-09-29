int main()
{
  string mac;
  mac = Scraper_GetArg("mac");
  Scraper_SetResult("ok", "1");
  Scraper_SetResult("manufacturer", "Apple, Inc.");
  return 1;
}
