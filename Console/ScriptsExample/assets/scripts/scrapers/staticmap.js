// Static map scraper (JavaScript) — gui.farm primary, mapmap.ai fallback (no API key).
// args: latitude, longitude, outpath (required); address, width, height, zoom, timeout (optional)
// results: ok ("1"|"0"), path, provider

function main()
{
  var lat;
  var lon;
  var address;
  var outpath;
  var url;
  var place;
  var wstr;
  var hstr;
  var zstr;
  var width;
  var height;
  var zoom;
  var timeout;
  var ok;

  ok = 0;
  lat     = Scraper_GetArg("latitude");
  lon     = Scraper_GetArg("longitude");
  address = Scraper_GetArg("address");
  outpath = Scraper_GetArg("outpath");
  width   = Scraper_GetArgInt("width");
  height  = Scraper_GetArgInt("height");
  zoom    = Scraper_GetArgInt("zoom");
  timeout = Scraper_GetArgInt("timeout");

  if(timeout <= 0)
    {
      timeout = 10;
    }
  if(width <= 0)
    {
      width = 240;
    }
  if(height <= 0)
    {
      height = 140;
    }
  if(zoom <= 0)
    {
      zoom = 11;
    }

  Scraper_SetResult("ok", "0");

  if(IsEmptyString(outpath))
    {
      return 0;
    }

  if(IsEmptyString(lat) || IsEmptyString(lon))
    {
      if(IsEmptyString(address))
        {
          return 0;
        }
      place = ReplaceAllString(address, " ", "+");
    }
   else
    {
      place = AddString(lat, ",");
      place = AddString(place, lon);
    }

  wstr = SPrintf("", "%d", width);
  hstr = SPrintf("", "%d", height);
  zstr = SPrintf("", "%d", zoom);

  url = "https://gui.farm/tools/map-generator.png?place=";
  url = AddString(url, place);
  url = AddString(url, "&mode=light&color=red&ratio=16:9&width=");
  url = AddString(url, wstr);
  url = AddString(url, "&zoom=");
  url = AddString(url, zstr);

  if(WebClient_GetToFile(url, outpath, "", timeout))
    {
      if(IsItExists(outpath))
        {
          Scraper_SetResult("path", outpath);
          Scraper_SetResult("provider", "gui.farm");
          Scraper_SetResult("ok", "1");
          ok = 1;
        }
    }

  if(ok == 0)
    {
      if(!IsEmptyString(lat) && !IsEmptyString(lon))
        {
          url = "https://mapmap.ai/api/static-map?center=";
          url = AddString(url, lon);
          url = AddString(url, ",");
          url = AddString(url, lat);
          url = AddString(url, "&zoom=");
          url = AddString(url, zstr);
          url = AddString(url, "&size=");
          url = AddString(url, wstr);
          url = AddString(url, "x");
          url = AddString(url, hstr);

          if(WebClient_GetToFile(url, outpath, "", timeout))
            {
              if(IsItExists(outpath))
                {
                  Scraper_SetResult("path", outpath);
                  Scraper_SetResult("provider", "mapmap.ai");
                  Scraper_SetResult("ok", "1");
                  ok = 1;
                }
            }
        }
    }

  return ok;
}
